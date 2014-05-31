
/// LISTA ZADAŃ:
/// animacja wejścia karty
/// okienko czatu
/// info w lg rogu
/// hierarchia kart w pg rogu
/// server, stolik, nick wpisywany w allegro
/// wyłączenie gry po przegranej (okno dialogowe)
/// jesteś pewien, że chcesz opuścić grę? (okno dialogowe)
/// zagranie jako dymek (tam gdzie kupka, kupka przesunięta)
/// pasek czasu (gdzie?)

/// Poker Texas Holdem Online (C) Benedykt Kula

#include "../../network/websockets/client.h"

#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

//
// Wspólne ze Stolik.cpp
//

struct karta {
    short liczba;
    /**/ short kolor;
};

struct miejsce {
    short status;
    string nick;
    string zagranie;
    int kasa;
    int zaklad;
    short pule;
    karta karty[2];
    int dod_czas;
};

string nazwa_stolika;
const short max_liczba_miejsc = 12;

short liczba_miejsc = 8;

string komunikat = "Gra rozpocznie się gdy do stolika dołączy 3+ graczy.";

short faza = -1;

vector < miejsce > gracz;

short dealer = -1, grajacy = -1;

vector < long long int > pula;
karta karty[5];

int najwyzszy_zaklad() {

    int naj = 0;

    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status > -1)
            if (gracz[i].zaklad > naj)
                naj = gracz[i].zaklad;
    }

    return naj;
}

int PULA() {
    int zwrot = 0;
    for (int i = 0; i < liczba_miejsc; i++) {
        zwrot += pula[i];
        zwrot += gracz[i].zaklad;
    }
    return zwrot;
}

const short czas_na_zagranie = 10;

//
// Inne
//

float przyszle_zagranie = -1;

template < class typ > typ max_3 (typ a, typ b, typ c) {
    if (a > b && a > c) return a;
    else if (b > a && b > c) return b;
    return c;
}
template < class typ > typ zakres (typ liczba, int from, int to) {
    if (liczba < from) return from;
    else if (liczba > to) return to;
    return liczba;
}
template < class typ > typ roznica (typ a, typ b) {
    return abs(a-b);
}
template < class typ > typ mod (typ a, typ b) {
    typ pom;
    pom = a%b;
    if (pom >= 0) return pom;
    return pom+b;
}
string intostring (int n) {
    stringstream ss;
    ss << n;
    return ss.str();
}
string wycinek (string t1, int from, int to) {
    string t2;
    for (int i = from; i < to; i++) {
        t2 += t1[i];
    }
    return t2;
}
string bez_ (string txt) {
    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] == '_') txt[i] = ' ';
    }
    return txt;
}
string tysiace (int kasa) {
    string txt = intostring(kasa);
    if (kasa >= 1000) return wycinek(txt,0,txt.length()-3) + "." + wycinek(txt,txt.length()-3,txt.length());
    else return txt;
}

int screen_w;
int screen_h;
int centrum_y;

class FONT;

class SKALOWANIE
{
public:
    int w;
    int h;
    SKALOWANIE()
    {
        w = 1024;
        h = 600;
    }
    int operator() (int n)
    {
        return int(double(n) * max(double(screen_w)/double(w), double(screen_h)/double(h)));
    }
};

SKALOWANIE na_moim_kompie;

class FONT
{
private:

    vector <ALLEGRO_FONT*> f;

public:

    int init()
    {
        /*
        if (!al_init_font_addon()) {
            cerr << "Nie mogę załadować dodatku font." << endl;
            return -1;
        }
        if (!al_init_ttf_addon()) {
            cerr << "Nie mogę załadować dodatku ttf." << endl;
            return -1;
        }
        */

        al_init_font_addon();
        al_init_ttf_addon();

        f.reserve(1);
        f[0] = al_load_ttf_font("bitmapy/arial.ttf",8,0);
        if (!f[0]) {
            cerr << "Nie mogę załadować czcionki arial.ttf" << endl;
            return -1;
        }

        return 0;
    }

    ALLEGRO_FONT* operator() (int n)
    {
        while (f.size() <= n-8) {
            f.push_back(al_load_ttf_font("bitmapy/arial.ttf",f.size()+8,0));
        }

        n -= 8;
        n = zakres(n, 0, f.size()-1);
        return f[n];
    }
};

FONT font;

short moje_miejsce;
short moje_siedzenie = 0;

bool wyjdz = false;

bool key[ALLEGRO_KEY_MAX];
int mouse_x;
int mouse_y;
bool mouse_pressed = false;
const float FPS = 60;

ALLEGRO_DISPLAY_MODE disp_data;

ALLEGRO_DISPLAY * display = NULL;
ALLEGRO_EVENT_QUEUE * event_queue = NULL;
ALLEGRO_TIMER * timer = NULL;

struct bitmapa {
    ALLEGRO_BITMAP * wsk;
    int w, h;
    bool init (string s) {
        wsk = al_load_bitmap(string("bitmapy/" + s).c_str());
        if (!wsk) {
            cout << "Nie mogę załadować obrazka bitmapy/" + s << endl;
            return false;
        }
        w = al_get_bitmap_width(wsk);
        h = al_get_bitmap_height(wsk);
        return true;
    }
};

ALLEGRO_BITMAP * wsk_karta[13][4];
ALLEGRO_BITMAP * tyl_karty = NULL;

ALLEGRO_BITMAP * moneta = NULL;
ALLEGRO_BITMAP * znacznik_dealera = NULL;

bitmapa good;

ALLEGRO_COLOR white;
ALLEGRO_COLOR black;

int karta_w;
int karta_h;

void rysuj_prostokat (int cx,int cy,int w,int h,int r1,int g1,int b1,int r2,int g2,int b2,int a=255) {

    float grubosc_lini = (float) ((float) h / (float) max_3 (roznica(r1,r2),roznica(g1,g2),roznica(b1,b2)));
    bool r=false, g=false, b=false;
    if(roznica(r1,r2)==max_3(roznica(r1,r2),roznica(g1,g2),roznica(b1,b2)))r=true;
    if(roznica(g1,g2)==max_3(roznica(r1,r2),roznica(g1,g2),roznica(b1,b2)))g=true;
    if(roznica(b1,b2)==max_3(roznica(r1,r2),roznica(g1,g2),roznica(b1,b2)))b=true;
    r1=max(r1,r2), g1=max(g1,g2), b1=max(b1,b2);
    float y = cy-h/2;

    for (int i = 0; y < cy+h/2; i++) {
            al_draw_line(cx-w/2,y,cx+w/2,y,al_map_rgba(r1,g1,b1,a),grubosc_lini);
            if(r)r1--; if(g)g1--; if(b)b1--;
            y += (float) grubosc_lini;
    }

    al_draw_rectangle (cx-w/2,cy-h/2,cx+w/2,cy+h/2,black,1);
}

int k (int a, int b) { return min(a,b) + roznica(a,b)*0.2; }

void rysuj_prostokat2 (int cx,int cy,int w,int h,int r1,int g1,int b1,int r2,int g2,int b2,int a=255) {
    rysuj_prostokat (cx,cy-h/4,w,h/2,k(r1,r2),k(g1,g2),k(b1,b2),max(r1,r2),max(g1,g2),max(b1,b2),a);
    al_draw_filled_rectangle(cx-w/2, cy, cx+w/2, cy+h/2, al_map_rgb(min(r1,r2),min(g1,g2),min(b1,b2)));
}

class system_klikania {

    bool klikniete;

public:

    bool najechane, klikane;

    system_klikania () {
        najechane = 0;
        klikane = 0;
        klikniete = 0;
    }

    void aktualizuj (int cx, int cy, int w, int h) {

        if (mouse_pressed && najechane) klikane = true;

        if ((!mouse_pressed) && mouse_x >= cx-w/2 && mouse_x <= cx+w/2 && mouse_y >= cy-h/2 && mouse_y <= cy+h/2) najechane = true;
        else najechane = false;

        if (!mouse_pressed) {
            if (klikane && najechane) klikniete = true;
            klikane = false;
        }
    }

    bool click() {
        if (!klikniete) return false;
        klikniete = false;
        return true;
    }
};

int moneta_r;
void rysuj_kupke (int kasa, bool czy_prawo, int x, int y) {
    al_draw_bitmap (moneta, x, y, 0);
    int font_size = na_moim_kompie(15);
    if (!czy_prawo) {
        al_draw_text(font(font_size), black, x - moneta_r*0.5, y, ALLEGRO_ALIGN_RIGHT, tysiace(kasa).c_str());
    } else {
        al_draw_text(font(font_size), black, x + moneta_r*2.5, y, ALLEGRO_ALIGN_LEFT, tysiace(kasa).c_str());
    }
}

class eliptyczny_stol {

    int pomiedzy_kartami;
    int font_size;

    void rysuj_karty() {

        short ile_kart; //3*faza-2*(faza-1)

        if (faza == 1) ile_kart = 3;
        else if (faza == 2) ile_kart = 4;
        else if (faza > 2) ile_kart = 5;
        else ile_kart = 0;

        for (short i = 0; i < ile_kart; i++){
            float x = cx - karta_w * 2.5 - pomiedzy_kartami * 2 + (karta_w + pomiedzy_kartami) * i;
            float y = cy - karta_h/2;
            al_draw_bitmap(wsk_karta[karty[i].liczba-2][karty[i].kolor],x,y,0);
        }
    }

public:

    int w, h;
    int cx, cy;

    void init() {
        pomiedzy_kartami = 10;
        font_size = na_moim_kompie(17);
    }

    void rysuj() {

        w = na_moim_kompie(375)*2, h = na_moim_kompie(175)*2;
        cx = screen_w/2, cy = centrum_y;

        for (int i = 0; i < h/2; i++) {
            al_draw_ellipse(cx, cy, w/2 - i, h/2 - i, al_map_rgb(0,70+i,0), 2);
        }
        for (float i = 1; i < 5; i+=0.1) {
            al_draw_ellipse(cx, cy, w/2 + i, h/2 + i, al_map_rgb(40+i*25,40+i*25,40+i*25), 1);
        }
        for (float i = 0; i < 3; i+=0.1) {
            al_draw_ellipse(cx, cy, w/2 + i+5, h/2 + i+5, al_map_rgb(165-i*25,165-i*25,165-i*25), 1);
        }

        if (komunikat == "X") rysuj_karty();
        else al_draw_text(font(font_size), black, cx, cy-font_size/2, ALLEGRO_ALIGN_CENTRE, bez_(komunikat).c_str());
    }
};

eliptyczny_stol stolik;

class tablica_gracza {

public:

    int w, h;
    int font_size;
    int pomiedzy_napisami;
    int pomiedzy_kartami;

private:

    system_klikania m;

    int numer_siedzenia;
    int numer_gracza;

    bool wolne_miejsce;
    bool tryb_siadania;

    int k_x, k_y; bool k_czy_prawo;

    void rysuj_karty() {

        float x1 = cx - pomiedzy_kartami/2 - karta_w/2;
        float y1 = cy - h/2 - karta_h/2;
        float x2 = x1 + pomiedzy_kartami;
        float y2 = y1 - pomiedzy_kartami/2;

        if (numer_gracza == moje_miejsce || faza > 3) {
            al_draw_bitmap (wsk_karta[gracz[numer_gracza].karty[0].liczba-2][gracz[numer_gracza].karty[0].kolor], x1, y1, 0);
            al_draw_bitmap (wsk_karta[gracz[numer_gracza].karty[1].liczba-2][gracz[numer_gracza].karty[1].kolor], x2, y2, 0);
        } else {
            al_draw_bitmap (tyl_karty, x1, y1, 0);
            al_draw_bitmap (tyl_karty, x2, y2, 0);
        }
    }

    void obramowka( int r, int g, int b, int roznica = 35) {
        int pom_w = w-10;
        int pom_h = h-10;
        for (int i = 0; i < 3; i++) {
            al_draw_rectangle(cx - pom_w/2 - 5-i,cy - pom_h/2 - 5-i,cx + pom_w/2 + 5+i,cy + pom_h/2 + 5+i, al_map_rgb(zakres(r-(2*roznica)+roznica*i,0,255),zakres(g-(2*roznica)+roznica*i,0,255),zakres(b-(2*roznica)+roznica*i,0,255)), 1);
        }
        for (int i = 3; i < 5; i++) {
            al_draw_rectangle(cx - pom_w/2 - 5-i,cy - pom_h/2 - 5-i,cx + pom_w/2 + 5+i,cy + pom_h/2 + 5+i, al_map_rgb(zakres(r+(2*roznica)-roznica*i,0,255),zakres(g+(2*roznica)-roznica*i,0,255),zakres(b+(2*roznica)-roznica*i,0,255)), 1);
        }
    }

    void rysuj_zaklad() {
        int x = k_x;
        if (dealer == numer_gracza && faza>=0 && faza<=3) {
            al_draw_bitmap (znacznik_dealera,k_x,k_y,0);
            if (k_czy_prawo) x += moneta_r*2.5;
            else x -= moneta_r*2.5;
        }
        if (gracz[numer_gracza].zaklad > 0) rysuj_kupke (gracz[numer_gracza].zaklad, k_czy_prawo, x, k_y);
    }

    string kasa() {
        if (wolne_miejsce) return "Miejsce";
        if (gracz[numer_gracza].kasa == 0) return "All in";
        return tysiace (gracz[numer_gracza].kasa);
    }

    double start_odlicznia;
    int pozostale_sekundy;
    int czas_absatkowy;
    ALLEGRO_COLOR kolor_czcionki;
    double koniec_zagrania;

    string napis() {
        if (wolne_miejsce) {
            kolor_czcionki = white;
            return "Wolne";
        } else if (numer_gracza == grajacy) {
            stringstream ss;
            ss << pozostale_sekundy << " sek.";
            return ss.str();
        } else if ((al_current_time() < koniec_zagrania && gracz[numer_gracza].zagranie != "X") || gracz[numer_gracza].zagranie == "Zwycięzca") {
            kolor_czcionki = al_map_rgb_f(1,1,0);
            return gracz[numer_gracza].zagranie;
        }
        kolor_czcionki = white;
        return gracz[numer_gracza].nick;
    }

    void kupka_xy (int x, int y, bool b) {

        switch (x) {
            case 0: k_x = cx-w/2-moneta_r*4; break;
            case 1: k_x = cx-w/2 - moneta_r + roznica(karta_w/2 + pomiedzy_kartami/2, w/2) / 2; break;
            case 2: k_x = cx+w/2 - moneta_r - roznica(karta_w/2 + pomiedzy_kartami/2, w/2) / 2; break;
            case 3: k_x = cx+w/2+moneta_r*2; break;
        }

        switch (y) {
            case 0: k_y = cy-h/2-moneta_r*4; break;
            case 2: k_y = cy-moneta_r; break;
            case 5: k_y = cy+h/2+moneta_r*2; break;
        }

        if (b) k_czy_prawo = 1;
        else k_czy_prawo = 0;
    }

public:

    void init() {
        w = 0;
        h = na_moim_kompie(55);
        font_size = na_moim_kompie(14);
        pomiedzy_napisami = (h - font_size * 2) / 3.5;
        pomiedzy_kartami = na_moim_kompie(14);
        kolor_czcionki = white;
        start_odlicznia = -1;
        tryb_siadania = false;
    }

    int cx, cy;

    int ustaw_x_i_y (int i) {

        numer_siedzenia = i;

        int cx0,cy0,cx1,cy1,cx2,cy2,cx3,cy3;

        switch (liczba_miejsc) {

        case 8:
            cx0 = screen_w / 2, cy0 = stolik.cy - stolik.h/2;
            cx3 = screen_w / 2, cy1 = stolik.cy + stolik.h/2;
            cx2 = stolik.cx - stolik.w/2, cy2 = stolik.cy;
            cx1 = stolik.cx + stolik.w/2, cy3 = stolik.cy;
            switch (i) {
            case 4: cx = screen_w / 2; cy = stolik.cy - stolik.h/2; kupka_xy(1,5,true); break;
            case 0: cx = screen_w / 2; cy = stolik.cy + stolik.h/2; kupka_xy(2,0,true); break;
            case 2: cx = stolik.cx - stolik.w/2; cy = stolik.cy; kupka_xy(3,2,true); break;
            case 6: cx = stolik.cx + stolik.w/2; cy = stolik.cy; kupka_xy(0,2,false); break;
            case 3: cx = cx0/2 + cx2/2 - 50; cy = cy0/2 + cy2/2 - 50; kupka_xy(1,5,true); break;
            case 5: cx = cx0/2 + cx1/2 + 50; cy = cy0/2 + cy3/2 - 50; kupka_xy(2,5,false); break;
            case 1: cx = cx3/2 + cx2/2 - 50; cy = cy1/2 + cy2/2 + 50; kupka_xy(2,0,true); break;
            case 7: cx = cx3/2 + cx1/2 + 50; cy = cy1/2 + cy3/2 + 50; kupka_xy(1,0,false); break;
            }
            break;

        case 4:
            switch (i) {
            case 2: cx = screen_w / 2; cy = stolik.cy - stolik.h/2; break;
            case 0: cx = screen_w / 2; cy = stolik.cy + stolik.h/2; break;
            case 1: cx = stolik.cx - stolik.w/2; cy = stolik.cy; break;
            case 3: cx = stolik.cx + stolik.w/2; cy = stolik.cy; break;
            }
            break;

        case 2:
            switch (i) {
            case 1: cx = stolik.cx - stolik.w/2; cy = stolik.cy; break;
            case 0: cx = stolik.cx + stolik.w/2; cy = stolik.cy; break;
            }
            break;

        default:
            cout << "Ta wersja programu nie obsługuje gry przy stoliku dla " << liczba_miejsc << " graczy.\n";
            cout << "Dołącz do stolika dla 8 graczy.\n";
            wyjdz = true;
            return -1;
        }
        return 0;
    }

    void rysuj() {

        if (gracz[numer_gracza].status > -2) {
            wolne_miejsce = false;
            w = na_moim_kompie(130);
        } else {
            wolne_miejsce = true;
            w = na_moim_kompie(92);
        }

        ustaw_x_i_y (numer_siedzenia);

        if (gracz[numer_gracza].status > -1 && faza >= 0) rysuj_karty();

        if (tryb_siadania) {
            al_draw_filled_rectangle (cx-w/2,cy-h/2,cx+w/2,cy+h/2,white);
            al_draw_text (font(font_size), black, cx, cy - pomiedzy_napisami/5 -font_size, ALLEGRO_ALIGN_CENTRE, string("Kliknij").c_str());
            al_draw_text(font(font_size), black, cx, cy + pomiedzy_napisami/5, ALLEGRO_ALIGN_CENTRE, string("by usiąść").c_str());
        } else {
            int a;
            if (wolne_miejsce) a = 200;
            else a = 235;
            rysuj_prostokat(cx,cy,w,h,60,60,60,0,0,0,a);
            al_draw_text (font(font_size), kolor_czcionki, cx, cy - pomiedzy_napisami/2 -font_size, ALLEGRO_ALIGN_CENTRE, napis().c_str());
            al_draw_text(font(font_size), white, cx, cy + pomiedzy_napisami/2, ALLEGRO_ALIGN_CENTRE, kasa().c_str());
        }

        if (wolne_miejsce) obramowka(35,35,35,10);
        else if (numer_gracza == grajacy) obramowka(200,200,0,40);
        else if (numer_gracza == moje_miejsce) obramowka(215,0,0,60);
        else if (gracz[numer_gracza].status < 0) obramowka(123,123,123,30);
        else obramowka(205,205,205,45);

        rysuj_zaklad();
    }

    void aktualizuj() {

        m.aktualizuj(cx, cy, w, h);

        if (numer_gracza == moje_miejsce) tryb_siadania = false;
        else if (tryb_siadania) {
            if (m.click()) moje_siedzenie = numer_siedzenia;
            if (!m.najechane && !mouse_pressed) tryb_siadania = false;
        }
        else if (m.click()) tryb_siadania = true;

        numer_gracza = mod (numer_siedzenia - moje_siedzenie + moje_miejsce, (int) liczba_miejsc);

        if (numer_gracza != grajacy) {
            if (start_odlicznia > 0) {
                start_odlicznia = -1;
                koniec_zagrania = al_current_time() + 4;
            } else {
                if (gracz[numer_gracza].zagranie == "WpłacamMC") {gracz[numer_gracza].zagranie = "Wpłacam MC";koniec_zagrania = al_current_time() + 3;}
                if (gracz[numer_gracza].zagranie == "WpłacamDC") {gracz[numer_gracza].zagranie = "Wpłacam DC";koniec_zagrania = al_current_time() + 5;}
            }
        } else  {
            if (start_odlicznia < 0) {
                start_odlicznia = al_current_time();
                czas_absatkowy = gracz[numer_gracza].dod_czas;
            }
            pozostale_sekundy = czas_na_zagranie-(int)(al_current_time() - start_odlicznia);
            if (pozostale_sekundy < 0) {
                pozostale_sekundy += czas_absatkowy;
                kolor_czcionki = al_map_rgb_f(1,0,0);
            } else kolor_czcionki = al_map_rgb_f(1,1,0);
        }
    }
};

tablica_gracza tablica [max_liczba_miejsc];

class przycisk_zagrania {

    int n;
    int font_size;
    int pomiedzy_napisami;

    system_klikania m;

    string napis() {
        switch (n) {
            case 1: return "Pasuję";
            case 2: if (gracz[moje_miejsce].zaklad - najwyzszy_zaklad() < 0) return "Sprawdzam"; return "Czekam";
            case 3: return "Przebijam";
        }
    }

public:

    int cx, cy;
    int w, h;

    void init(int i) {
        n = i;
        w = na_moim_kompie(100), h = na_moim_kompie(55);
        cx = na_moim_kompie(20) + w/2;
        cy = screen_h - na_moim_kompie(20) - h/2 - 3*(h+5) + n*(h+5);
        font_size = na_moim_kompie(14);
    }

    void klik() {

        m.aktualizuj(cx, cy, w, h);

        if (m.click()) {
            if (n == 1) przyszle_zagranie = 0;
            else if (n == 3) przyszle_zagranie = 3;
            else {
                if (gracz[moje_miejsce].zaklad - najwyzszy_zaklad() < 0) przyszle_zagranie = 2;
                else przyszle_zagranie = 1;
            }
        }
    }

    void rysuj() {

        int k = 32;

        if (m.klikane) rysuj_prostokat (cx, cy, w , h, 255-k*2, 10, 10, 90-k*2, 10, 10);
        else if (m.najechane) rysuj_prostokat (cx, cy, w, h, 255-k, 20, 20, 90-k, 20, 20);
        else rysuj_prostokat (cx, cy, w, h, 255, 30, 30, 90, 30, 30);

        al_draw_text(font(font_size), white, cx, cy - font_size/2 - font_size/6, ALLEGRO_ALIGN_CENTRE, napis().c_str());
    }
};

przycisk_zagrania przycisk1;
przycisk_zagrania przycisk2;
przycisk_zagrania przycisk3;

class opcje_zagran {

    int cy;
    int x;
    int bok;
    int pomiedzy;

    class opcja {

        system_klikania sk;
        float z;
        string txt;
        int bok;
        int x, y;
        int ile_sprawdzam;
        int font_size;

    public:

        void init (float f, string s, int i1, int i2, int i3) {
            z = f;
            txt = s;
            bok = i1;
            x = i2;
            y = i3;
            font_size = na_moim_kompie(15);
        }

        void aktualizuj() {
            sk.aktualizuj(x+bok/2, y+bok/2, bok, bok);
            if (z == 2) {
                if (przyszle_zagranie == 2 && ile_sprawdzam < najwyzszy_zaklad()) {
                    przyszle_zagranie = -1;
                }
                txt = "Sprawdzam " + intostring(najwyzszy_zaklad());
            }
            if (sk.click()) {
                if (przyszle_zagranie != z) {
                    przyszle_zagranie = z;
                    if (z == 2) ile_sprawdzam = najwyzszy_zaklad();
                }
                else przyszle_zagranie = -1;
            }
        }

        void rysuj() {
            al_draw_rectangle (x, y, x+bok, y+bok, black, 2);
            al_draw_text (font(font_size), black, x+bok*1.5, y+bok/2-font_size/2, ALLEGRO_ALIGN_LEFT, txt.c_str());
            if (przyszle_zagranie == z) al_draw_bitmap (good.wsk, x - abs(bok-good.w)/2, y - abs(bok-good.h)/2, 0);
        }
    };

    opcja o[5];

public:

    void init (int a, int b) {

        cy = a;
        x = b;
        bok = na_moim_kompie(24); x+=bok/2;
        pomiedzy = na_moim_kompie(15);

        o[0].init(0,"Pasuję",bok,x,cy-1.5*bok-pomiedzy);
        o[1].init(0.5,"Czekam/Pasuję",bok,x,cy-bok/2);
        o[2].init(1,"Czekam",bok,x,cy+bok/2+pomiedzy);
        o[3].init(0,"Pasuję",bok,x,cy-pomiedzy/2-bok/2);
        o[4].init(2,"Sprawdzam ",bok,x,cy+pomiedzy/2+bok/2);
    }

    void aktualizuj() {
        if (najwyzszy_zaklad() <= gracz[moje_miejsce].zaklad) {
            o[0].aktualizuj();
            o[1].aktualizuj();
            o[2].aktualizuj();
        } else {
            o[3].aktualizuj();
            o[4].aktualizuj();
        }
    }

    void rysuj() {
        if (najwyzszy_zaklad() <= gracz[moje_miejsce].zaklad) {
            o[0].rysuj();
            o[1].rysuj();
            o[2].rysuj();
        } else {
            o[3].rysuj();
            o[4].rysuj();
        }
    }
};

opcje_zagran opcje;

class suwak_przebijania {

    int miara;
    int w;
    int cy;
    int x[6];

    int przesuwak_cx;
    int poprawka_na_uchwyt;
    bool tryb_przesuwania;
    int min_by_przebic;
    float pieniadz_w;

    system_klikania plus;
    system_klikania przesuwak;
    system_klikania minus;

    void rysuj_stan () {
        int font_size = na_moim_kompie(15);
        al_draw_filled_rectangle (x[0], cy-miara/2, x[1], cy+miara/2, white);
        al_draw_rectangle (x[0], cy-miara/2, x[1], cy+miara/2, black, 1);
        al_draw_text(font(font_size), black, x[0]+(x[1]-x[0])/2, cy - font_size/2, ALLEGRO_ALIGN_CENTRE, intostring(stan).c_str());
    }

    void rysuj_minus () {

        int k = 32;
        if (minus.klikane) rysuj_prostokat (x[2], cy, miara, miara, 255-k*2, 10, 10, 90-k*2, 10, 10);
        else if (minus.najechane) rysuj_prostokat (x[2], cy, miara, miara, 255-k, 20, 20, 90-k, 20, 20);
        else rysuj_prostokat (x[2], cy, miara, miara, 255, 30, 30, 90, 30, 30);

        int a = miara/2, b = miara/7;
        al_draw_filled_rectangle (x[2]-a/2, cy-b/2, x[2]+a/2, cy+b/2, black);
    }

    void rysuj_suwak () {
        int h = miara/1.8;
        rysuj_prostokat (x[3]+(przesuwak_cx-x[3])/2, cy, przesuwak_cx-x[3], h, 255, 30, 30, 90, 30, 30);
        al_draw_filled_rectangle (x[3], cy-h/2, x[4], cy+h/2, al_map_rgba(15,15,15,1));
        al_draw_rectangle (x[3], cy-h/2, x[4], cy+h/2, black, 1);
    }

    void rysuj_przesuwak () {
        int k1 = 127+50, k2 = 127-50;
        rysuj_prostokat (przesuwak_cx, cy, miara/2, miara, k1, k1, k1, k2, k2, k2);
    }

    void rysuj_plus () {

        int k = 32;
        if (plus.klikane) rysuj_prostokat (x[5], cy, miara, miara, 255-k*2, 10, 10, 90-k*2, 10, 10);
        else if (plus.najechane) rysuj_prostokat (x[5], cy, miara, miara, 255-k, 20, 20, 90-k, 20, 20);
        else rysuj_prostokat (x[5], cy, miara, miara, 255, 30, 30, 90, 30, 30);

        int a = miara/2, b = miara/7;
        al_draw_filled_rectangle (x[5]-a/2, cy-b/2, x[5]+a/2, cy+b/2, black);
        al_draw_filled_rectangle (x[5]-b/2, cy-a/2, x[5]+b/2, cy+a/2, black);
    }

public:

    int stan;

    void init() {
        miara = na_moim_kompie(32);
        w = na_moim_kompie(220);
        cy = przycisk3.cy;
        stan = 0;
        //x: 0   1  2  3     4  5
        //   |275| |-| |#####| |+|
        x[0] = przycisk3.cx + przycisk3.w/2 + miara*0.75;
        x[1] = x[0] + miara*1.4;
        x[2] = x[1] + miara*1;
        x[3] = x[2] + miara*1;
        x[4] = x[3] + w;
        x[5] = x[4] + miara*1;
        tryb_przesuwania = false;
    }

    void rysuj() {
        rysuj_stan();
        rysuj_minus();
        rysuj_suwak();
        rysuj_przesuwak();
        rysuj_plus();
    }

    void aktualizuj() {

        if (moje_miejsce != grajacy) {
            stan = -1;
            return;
        } else if (stan == -1) {
            min_by_przebic = najwyzszy_zaklad()*2-gracz[moje_miejsce].zaklad;
            przesuwak_cx = x[3] + miara/4;
            pieniadz_w = float(w-miara/2) / (gracz[moje_miejsce].kasa-min_by_przebic);
        }

        przesuwak.aktualizuj (przesuwak_cx, cy, miara/2, miara);
        if (przesuwak.klikane && (!tryb_przesuwania)) {
            tryb_przesuwania = true;
            poprawka_na_uchwyt = przesuwak_cx-mouse_x;
        } else if (!mouse_pressed) tryb_przesuwania = false;
        if (tryb_przesuwania) {
            przesuwak_cx = zakres (mouse_x+poprawka_na_uchwyt, x[3]+miara/4, x[4]-miara/4);
        }

        minus.aktualizuj (x[2], cy, miara, miara);
        if (minus.click()) przesuwak_cx = zakres (przesuwak_cx-(10*pieniadz_w), x[3]+miara/4, x[4]-miara/4);

        plus.aktualizuj (x[5], cy, miara, miara);
        if (plus.click()) przesuwak_cx = zakres (przesuwak_cx+(10*pieniadz_w), x[3]+miara/4, x[4]-miara/4);

        stan = zakres (int (min_by_przebic + (przesuwak_cx-(x[3]+miara/4))/pieniadz_w), 1, gracz[moje_miejsce].kasa);
    }
};

suwak_przebijania suwak;

class okno_czatu { // klasa do dopracowania

    vector <string> komunikaty;
    int ile_komunikatow;

public:

    void init() {
        ile_komunikatow = 20;
    }

    void odbierz(string txt) {
        txt = wycinek(txt, string(nazwa_stolika + " CZAT Stolik ").size(), txt.size());
        komunikaty.push_back(txt);
        //if (komunikaty.size() == komunikaty[0] = txt;
        //else komunikaty.push_back(txt);
    }

    void rysuj() {
        al_draw_text(font(14), white, screen_w-20, screen_h-20, ALLEGRO_ALIGN_RIGHT, komunikaty.back().c_str());
    }
};

okno_czatu czat;

/*  KOSZ

void wypisz_dane() {
    cout << endl << "*****DANE*****\n";
    cout << "Dealer: " << dealer << " Grający: " << grajacy << endl;
    cout << "PULA: " << PULA() << endl;
    cout << "pule:";
    for (int i = 0; i < liczba_miejsc; i++)
        cout << " " << pula[i];
    cout << endl;
    cout << "Faza: " << faza << endl;
    cout << "KARTY: ";
    for (int i = 0; i < 5; i++) {
        cout << karty[i].liczba << " " << karty[i].kolor << " | ";
    }
    cout << endl << "MIEJSCA:\n";
    for (int i = 0; i < liczba_miejsc; i++) {
        cout << i << ": "
        << gracz[i].status << " "
        << gracz[i].nick << " "
        << gracz[i].zagranie << " "
        << gracz[i].kasa << " "
        << gracz[i].zaklad << " "
        << gracz[i].pule << " "
        << gracz[i].karty[0].liczba << " "
        << gracz[i].karty[0].kolor << " "
        << gracz[i].karty[1].liczba << " "
        << gracz[i].karty[1].kolor << endl;
    }
    cout << endl;
}

bool qwertyuiop=true;
short poprzednia_faza = 0;
void zagrania() {

    if (grajacy == moje_miejsce && przyszle_zagranie >= 0) zagraj();

    else{
    if(grajacy != moje_miejsce || faza == poprzednia_faza+1) qwertyuiop=true;
    if (grajacy == moje_miejsce && qwertyuiop){
        poprzednia_faza = faza;
        qwertyuiop=false;
    wypisz_dane();
    cout << endl << "0 - Pasuję\n0.5 - Czek/Pas\n1 - Czekam\n2 - Sprawdzam\n3 - Przebijam\n\n" << "Zagranie: ";
    cin >> przyszle_zagranie;
    if (przyszle_zagranie == 3) {
        cout << "ile? ";
        cin >> suwak.stan;
    }cout << endl;}}
*/

/********************************
 Funkcje 2
*********************************/

// ../stoliki

void dostosowanie_do_liczby_miejsc() {

    for (int i = 0; i < liczba_miejsc; i++) {
        gracz.push_back((miejsce) {-2,"X","X",1000,0,0,(karta){0,0},(karta){0,0},25});
        pula.push_back(0);

        if (tablica[i].ustaw_x_i_y(i) != 0) break;
    }
}

// ../init

int bitmap_init() {

    al_init_image_addon();

    moneta = al_load_bitmap("bitmapy/moneta.png");
    if (!moneta) {
        cout << "Nie mogę załadować obrazka bitmapy/moneta.png" << endl;
        return -1;
    }
    moneta_r = al_get_bitmap_width(moneta)/2;

    znacznik_dealera = al_load_bitmap("bitmapy/dealer.png");
    if (!znacznik_dealera) {
        cout << "Nie mogę załadować obrazka bitmapy/dealer.png" << endl;
        return -1;
    }

    if (!good.init("good.png")) return -1;

    tyl_karty = al_load_bitmap("bitmapy/tył.jpeg");
    if (!tyl_karty) {
        cout << "Nie mogę załadować obrazka bitmapy/tył.jpeg" << endl;
        return -1;
    }

    karta_w = al_get_bitmap_width(tyl_karty);
    karta_h = al_get_bitmap_height(tyl_karty);

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {

            string plik = "bitmapy/";

            switch (i) {
            case 12: plik += "a"; break;
            case 11: plik += "k"; break;
            case 10: plik += "q"; break;
            case 9: plik += "j"; break;
            case 8: plik += "10"; break;
            default: plik += (char)(i+2+48);
            }

            switch (j) {
            case 0: plik += "pik"; break;
            case 1: plik += "kier"; break;
            case 2: plik += "karo"; break;
            default: plik += "trefl";
            }

            plik += ".jpeg";

            wsk_karta[i][j] = al_load_bitmap (plik.c_str());

            if (!wsk_karta[i][j]) {
                cout << "Nie mogę załadować obrazka " << plik << endl;
                //return -1;
            }
        }
    }

    return 0;
}

int color_init() {

    white = al_map_rgb(255,255,255);
    black = al_map_rgb(0,0,0);

    return 0;
}

// ../paczki

void wczytaj_dane(string t) {

    stringstream ss;

    ss << t;

    ss >> komunikat;

    ss >> faza;

    int n = 0;
    if (faza == 1) n = 3;
    else if (faza == 2) n = 4;
    else if (faza == 3 || faza == 4) n = 5;
    for (int i = 0; i < n; i++) {
        ss >> karty[i].liczba;
        ss >> karty[i].kolor;
    }

    for (int i = 0; i < liczba_miejsc; i++) {
        ss >> pula[i];
    }

    ss >> dealer;
    ss >> grajacy;

    for (int i = 0; i < liczba_miejsc; i++) {
        ss >> gracz[i].status;
        if (gracz[i].status > -2) {
            ss >> gracz[i].nick;
            ss >> gracz[i].zagranie;
            ss >> gracz[i].kasa;
            ss >> gracz[i].zaklad;
            ss >> gracz[i].pule;
            ss >> gracz[i].karty[0].liczba;
            ss >> gracz[i].karty[0].kolor;
            ss >> gracz[i].karty[1].liczba;
            ss >> gracz[i].karty[1].kolor;
            ss >> gracz[i].dod_czas;
        }
    }

    /**/ if (grajacy == moje_miejsce) opcje.aktualizuj();
}

bool zagraj() {

    if (przyszle_zagranie < 0) return false;

    else {
        stringstream ss;

        if (przyszle_zagranie == 0) ss << "PASUJE";

        else if (przyszle_zagranie == 0.5) {
            if (najwyzszy_zaklad() > gracz[moje_miejsce].zaklad) ss << "PASUJE";
            else ss << "CZEKAM";

        } else if (przyszle_zagranie == 1) ss << "CZEKAM";

        else if (przyszle_zagranie == 2) ss << "SPRAWDZAM";

        else ss << "PRZEBIJAM " << suwak.stan;

        send_packet(nazwa_stolika + " Stolik " + ss.str());
        service_websockets();

        przyszle_zagranie = -1;
        grajacy = -1; // może spowodować core dumped
    }

    return true;
}

// ../rysowanie

void rysuj_tlo() {

    float przekatna = sqrt(pow(screen_h-centrum_y,2)+pow(screen_w/2,2));
    float szary = 255;
    float grubosc = (przekatna-stolik.h/2) / szary;

    float r = stolik.h/2;
    for (int i = szary; r < przekatna; i--) {
        al_draw_circle(screen_w/2,centrum_y,r,al_map_rgb(i,i,i),grubosc+1);
        r += grubosc;
    }
}

void rysuj_pule() {

    if (pula[0] < 1) return;

    int x = 50, y = 60, w = 90, h = 25, font_size = na_moim_kompie(16);
    for (int i = 0; i < w/2; i++) {
        int a = (float)255*((float)1-(float)i/(float)((float)w/2));
        al_draw_line(x+w/2+i, y, x+w/2+i, y+h, al_map_rgba(0,0,0,a), 1);
        al_draw_line(x+w/2-i, y, x+w/2-i, y+h, al_map_rgba(0,0,0,a), 1);
    }

    al_draw_text(font(font_size), white, x+w/2, y+h/2-font_size/2, ALLEGRO_ALIGN_CENTRE, string("PULA").c_str());

    for (int i = 0; i < liczba_miejsc; i++) {
        if (pula[i] < 1) break;
        rysuj_kupke (pula[i],true,x+w/3-moneta_r,y+h+10+moneta_r*3*i);
    }
}

/********************************
 Funkcje 1
*********************************/

int stoliki() {

    cout << endl;

    stringstream ss;

    cout << "Serwer: ";
    string serwer;
    cin >> serwer;

    cout << "Stolik: ";
    cin >> nazwa_stolika;

    cout << "Nick: ";
    string nick;
    cin >> nick;

    cout << endl;
    if (!connect_to_server(serwer)) {
        cout << endl << "Połączenie nie powiodło się." << endl << endl; return -1;
    }
    cout << endl;

    send_packet("spam");
    usleep(10);
    int n = service_websockets();
    send_packet("spam");
    usleep(10);
    n = service_websockets();

    send_packet(nazwa_stolika + " Stolik WBIJAM " + nick);
    n = service_websockets();

    string paczka;

    cout << "Oczekiwanie na sygnał stolika..." << endl << endl;

    time_t moment_zakonczenia = time(NULL) + 5;

    for (int i = 0; ; i++) {
        n = service_websockets();

        if (receive_packet(paczka)) {
            ss.clear(); ss.str("");
            ss << paczka;
            ss >> paczka;

            if (paczka == nazwa_stolika) {
                ss >> paczka;

                if (paczka == nick) {
                    ss >> paczka;

                    if (paczka == "ZAPRASZAM") {
                        ss >> liczba_miejsc;
                        ss >> moje_miejsce;
                        cout << "Dołączono do stolika '" << nazwa_stolika << "'" << endl << endl;

                        dostosowanie_do_liczby_miejsc();
                        gracz[moje_miejsce] = (miejsce) {-1,nick,"X",1000,0,0,(karta){2,2},(karta){2,2}};

                        break;

                    } else if (paczka == "PRZELUDNIENIE") {

                        cout << "Niestety przy stoliku " << nazwa_stolika << " nie ma wolnego miejsca.\n" << endl;
                        return -1;
                    }
                }
            }
        }

        if (time(NULL) >= moment_zakonczenia) {
            cout << "Stolik '" << nazwa_stolika << "' nie odpowiada." << endl << endl;
            return -1;
        }
    }

    return 0;
}

int init() {

    if (!al_init()) {
        cerr << "Błąd podczas inicjalizacji allegro." << endl;
        return -1;
    }

    if (!al_init_primitives_addon()) {
        cerr << "Błąd podczas inicjalizacji dodatku 'primitives'." << endl;
        return -1;
    }

    if (!al_install_keyboard()) {
        cerr << "Błąd podczas inicjalizacji klawiatury." << endl;
        return -1;
    }

    if (!al_install_mouse()) {
        cerr << "Błąd podczas inicjalizacji myszy." << endl;
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        cerr << "Błąd podczas inicjalizacji zegara." << endl;
        return -1;
    }

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_get_display_mode(0, &disp_data);
    screen_w = disp_data.width; //- 31;
    screen_h = disp_data.height; //- 54;
    centrum_y = screen_h/2 - 20;

al_set_new_display_flags(ALLEGRO_WINDOWED);
cout << "w: ";
cin >> screen_w;
cout << "h: ";
cin >> screen_h;

    display = al_create_display(screen_w, screen_h);
    if(!display) {
        cerr << "Błąd podczas inicjalizacji ekranu." << endl;
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if(!event_queue) {
        cerr << "Błąd podczas inicjalizacji kolejki zdarzeń." << endl;
        al_destroy_display(display);
        al_destroy_timer(timer);
        return -1;
    }

    if (font.init() != 0) return -1;
    if (bitmap_init() != 0) return -1;
    if (color_init() != 0) return -1;
    stolik.init();
    for (int i = 0; i < liczba_miejsc; i++) tablica[i].init();
    przycisk1.init(1);
    przycisk2.init(2);
    przycisk3.init(3);
    opcje.init(przycisk2.cy, przycisk2.cx-przycisk2.w/2);
    suwak.init();
    czat.init();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_clear_to_color(black);
    al_flip_display();

    al_start_timer(timer);

    return 0;
}

string dane;

void paczki() {

    service_websockets();
    string s;

    while (receive_packet(s)) {

        stringstream ss;
        ss << s;
        ss >> s;

        if (s == nazwa_stolika) {
            ss >> s;

            if (s == "Wszyscy" || s == "Gracze" || s == gracz[moje_miejsce].nick) {
                ss >> s;

                if (s == "END") {
                    dane += wycinek(ss.str(),nazwa_stolika.length()+string(" Gracze END ").length(),ss.str().length());
                    wczytaj_dane(dane);
                    dane = "";
                }

                if (s == "DANE") dane += wycinek(ss.str(),nazwa_stolika.length()+string(" Gracze DANE ").length(),ss.str().length());

            } else if (s == "CZAT") {
                czat.odbierz(ss.str());
            }
        }
    }

    return;
}

void zawsze() {

    paczki();

    for (int i = 0; i < liczba_miejsc; i++) {
        tablica[i].aktualizuj();
    }

    if (moje_miejsce == grajacy) {
        if (przyszle_zagranie >= 0) zagraj();
        else {
            przycisk1.klik();
            przycisk2.klik();
            przycisk3.klik();
        }
    } else if (gracz[moje_miejsce].status > 1 && (faza==0 || faza==1 || faza==2 || faza==3)) {
        opcje.aktualizuj();
    }

    suwak.aktualizuj();
}

void rysowanie() {

    al_clear_to_color(black);

    stringstream nazwa_okna;
    nazwa_okna << "PokerOnline - " << nazwa_stolika << " - " << gracz[moje_miejsce].nick << " - " << gracz[moje_miejsce].kasa;
    al_set_window_title(display, nazwa_okna.str().c_str());

    rysuj_tlo();

    stolik.rysuj();

    for (int i = 0; i < liczba_miejsc; i++) {
        tablica[i].rysuj();
    }

    if (moje_miejsce == grajacy && przyszle_zagranie < 0) {
        przycisk1.rysuj();
        przycisk2.rysuj();
        przycisk3.rysuj();
        suwak.rysuj();
    } else if (moje_miejsce != grajacy && gracz[moje_miejsce].status > 1 && (faza==0 || faza==1 || faza==2 || faza==3)) {
        opcje.rysuj();
    }

    rysuj_pule();

    czat.rysuj();
}

void sprzatanie() {

    stringstream ss;

    ss << nazwa_stolika << " Stolik SPADAM " << moje_miejsce;
    send_packet(ss.str());
    int n = service_websockets();

    return;
}

/********************************
 int main()
*********************************/

int main() {

    if (stoliki() != 0) {
        return -1;
    }

    if (init() != 0) {
        cerr << "Inicjalizacja nie powiodła się." << endl;
        wyjdz = true;
    }

    // Event Loop

    bool przerysuj = true;

    while (wyjdz != true) {

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        if(ev.type == ALLEGRO_EVENT_TIMER) {

            przerysuj = true;

            zawsze();


        } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            key[ev.keyboard.keycode] = true;
        } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
            key[ev.keyboard.keycode] = false;

            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                wyjdz = true;
            }
        } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            wyjdz = true;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES || ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
            mouse_x = ev.mouse.x;
            mouse_y = ev.mouse.y;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
            mouse_pressed = false;
        } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            mouse_pressed = true;
        }

        if (przerysuj && al_is_event_queue_empty(event_queue)) {
            przerysuj = false;

            rysowanie();
            al_flip_display();
        }
    }

    sprzatanie();

    return 0;
}
