
/// LISTA ZADAŃ:
/// okienko czatu
/// info w lg rogu
/// server, stolik, nick wpisywany w allegro
/// wyłączenie gry po przegranej (okno dialogowe)
/// jesteś pewien, że chcesz opuścić grę? (okno dialogowe)
/// kolorowe tło | hierarchia kart
/// zrobić README.md

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
    short kolor;
};

class KUPKA_KASY;
short faza = -1;

struct miejsce
{
    short status;
    string nick;
    string zagranie;
    int kasa;
    int zaklad;
    short pule;
    karta karty[2];
    int dod_czas;
    KUPKA_KASY * kupka;
    int poprzedni_zaklad;
    int ile_zgarniam;
private:
    int poprzednia_faza;
public:
    miejsce()
    {
        status = -2;
        nick = "X";
        zagranie = "X";
        kasa = 1000;
        zaklad = 0;
        pule = 0;
        dod_czas = 25;
        poprzednia_faza = -1;
        poprzedni_zaklad = 0;
        ile_zgarniam = 0;
    }
    int zapamietaj()
    {
        if (poprzednia_faza != faza) {
            poprzedni_zaklad = zaklad;
        }
        poprzednia_faza = faza;
    }
};

string nazwa_stolika;
const short max_liczba_miejsc = 12;

short liczba_miejsc = 8;

string komunikat = "Czekam na sygnał stolika...";

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
const short poczatkowy_czas_dodatkowy = 25;

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
string z_ (string txt) {
    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] == ' ') txt[i] = '_';
    }
    return txt;
}
string tysiace (int kasa) {
    string txt = intostring(kasa);
    if (kasa >= 1000) return wycinek(txt,0,txt.length()-3) + "." + wycinek(txt,txt.length()-3,txt.length());
    else return txt;
}
float odleglosc(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
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

class BITMAPA
{
    ALLEGRO_BITMAP * wsk;
public:
    ALLEGRO_BITMAP * operator()(){return wsk;}
    int w, h, r;
    bool init (string s)
    {
        ALLEGRO_BITMAP * obrazek = al_load_bitmap(string("bitmapy/" + s).c_str());
        if (!obrazek) {
            cout << "Nie mogę załadować obrazka bitmapy/" + s << endl;
            return false;
        }
        w = al_get_bitmap_width(obrazek);
        h = al_get_bitmap_height(obrazek);
        wsk = al_create_bitmap(na_moim_kompie(w),na_moim_kompie(h));
        al_set_target_bitmap(wsk);
        al_clear_to_color(al_map_rgba(0,0,0,0));
        al_draw_scaled_bitmap(obrazek,0,0,w,h,0,0,na_moim_kompie(w),na_moim_kompie(h),0);
        al_set_target_bitmap(al_get_backbuffer(display));
        w = na_moim_kompie(w);
        h = na_moim_kompie(h);
        r = w/2;
        return true;
    }
};

BITMAPA przod_karta[13][4];
BITMAPA tyl_karty;
BITMAPA moneta;
BITMAPA znacznik_dealera;
BITMAPA good;

ALLEGRO_COLOR white;
ALLEGRO_COLOR black;
ALLEGRO_COLOR green;
ALLEGRO_COLOR red;

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

void rysuj_slup (float x, float y, float w, float h, bool r, bool g, bool b)
{
    for (float i = x; i <= x+w/2; i++) {
        al_draw_line(i,y,i,y+h,al_map_rgb(r*(255-(127.0*((w/2-(i-x))/(w/2)))), g*(255-(127.0*((w/2-(i-x))/(w/2)))), b*(255-(127.0*((w/2-(i-x))/(w/2))))),1);
    }
    for (float i = x+w; i >= x+w/2; i--) {
        al_draw_line(i,y,i,y+h,al_map_rgb(r*(255-(127.0*((w/2-(x+w-i))/(w/2)))), g*(255-(127.0*((w/2-(x+w-i))/(w/2)))), b*(255-(127.0*((w/2-(x+w-i))/(w/2))))),1);
    }
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

class KUPKA_KASY
{
    const float speed = na_moim_kompie(5.0);
    struct LATACZ
    {
        int ile_dolecialo;
        KUPKA_KASY * wsk;
        LATACZ(KUPKA_KASY * a1)
        {
            wsk = a1;
            ile_dolecialo = 0;
        }
        ~LATACZ()
        {
            wsk = NULL;
        }
    };
public:
    vector <LATACZ> latacze;
    KUPKA_KASY * cel;
    float x, y;
    bool czy_prawo;
    int kasa;
    KUPKA_KASY()
    {
        cel = NULL;
    }
    KUPKA_KASY(KUPKA_KASY * arg)
    {
        cel = arg;
    }
    ~KUPKA_KASY()
    {
        delete cel;
        latacze.erase(latacze.begin(),latacze.end());
    }
    void lec_do(KUPKA_KASY * cel)
    {
        latacze.push_back(LATACZ(new KUPKA_KASY(cel)));
        latacze.back().ile_dolecialo = 0;
        latacze.back().wsk->kasa = kasa;
        latacze.back().wsk->x = x;
        latacze.back().wsk->y = y;
        latacze.back().wsk->czy_prawo = czy_prawo;
    }
    int dolecialo(int i = 0)
    {
        int pom = 0;
        if (i < latacze.size()) {
            pom = latacze[i].ile_dolecialo;
            latacze[i].ile_dolecialo = 0;
        }
        return pom;
    }
    void kasuj()
    {
        for (int i = 0; i < latacze.size(); i++) {
            if (latacze[i].wsk != NULL || latacze[i].ile_dolecialo != 0) return;
        }
        latacze.erase(latacze.begin(),latacze.end());
    }
    bool aktualizuj()
    {
        for (int i = 0; i < latacze.size(); i++) {
            if (latacze[i].wsk != NULL) {
                if (!latacze[i].wsk->aktualizuj()) {
                    latacze[i].ile_dolecialo = latacze[i].wsk->kasa;
                    latacze[i].wsk = NULL;
                }
            }
        }
        kasuj();
        if (cel != NULL) {
            if (odleglosc(x,y,cel->x,cel->y) <= speed+1) return false;
            float odleglosc_x = cel->x - x;
            float odleglosc_y = cel->y - y;
            x += odleglosc_x/abs(odleglosc_x) * speed * (pow(odleglosc_x,2) / (pow(odleglosc_x,2) + pow(odleglosc_y,2)));
            y += odleglosc_y/abs(odleglosc_y) * speed * (pow(odleglosc_y,2) / (pow(odleglosc_x,2) + pow(odleglosc_y,2)));
        }
        return true;
    }
    void rysuj()
    {
        if (kasa > 0) {
            al_draw_bitmap (moneta(), x, y, 0);
            int font_size = na_moim_kompie(15);
            if (!czy_prawo) {
                al_draw_text(font(font_size), black, x - moneta.r*0.5, y, ALLEGRO_ALIGN_RIGHT, tysiace(kasa).c_str());
            } else {
                al_draw_text(font(font_size), black, x + moneta.r*2.5, y, ALLEGRO_ALIGN_LEFT, tysiace(kasa).c_str());
            }
        }
        for (int i = 0; i < latacze.size(); i++) {
            if (latacze[i].wsk != NULL) latacze[i].wsk->rysuj();
        }
    }
};

class eliptyczny_stol {

    int pomiedzy_kartami;
    int font_size;

    class STOLIKOWA_KARTA
    {
        float cel_x, cel_y;
        float speed = na_moim_kompie(5.0);
        float droga;
        float x;
        short lp;
    public:
        bool pokazuj;
        STOLIKOWA_KARTA(short i, float a1, float a2)
        {
            lp = i;
            cel_x = a1;
            cel_y = a2;
            droga = na_moim_kompie(200);
            pokazuj = false;
        }
        void pokaz()
        {
            pokazuj = true;
            if (lp == 3 || lp == 4) x = cel_x + droga;
            else x = cel_x - droga;
        }
        void ukryj()
        {
            pokazuj = false;
        }
        void aktualizuj()
        {
            if (abs(cel_x - x) <= speed) {
                x = cel_x;
            } else if (x < cel_x) x += speed;
            else if (cel_x < x) x -= speed;
        }
        void rysuj()
        {
            if (!pokazuj) return;
            float a = 255.0 * ((droga-abs(cel_x-x))/droga);
            al_draw_tinted_bitmap(przod_karta[karty[lp].liczba-2][karty[lp].kolor](),al_map_rgba(a,a,a,a),x,cel_y,0);
        }
    };

    STOLIKOWA_KARTA * stolikowa_karta[5];

    bool wyslane;
    short poprzednia_faza;

    ALLEGRO_BITMAP * bmp;

    void utworz_bmp()
    {
        bmp = al_create_bitmap(screen_w,screen_h);
        al_clear_to_color(al_map_rgba(0,0,0,0));
        al_set_target_bitmap(bmp);

        int g1 = 255, g2 = 70;
        float szer = float(w/2+1) / (g1-g2);
        float wys = float(h/2+1) / (g1-g2);
        for (int i = 0; i < float(w/2+1)/szer; i++) {
            al_draw_ellipse(cx, cy, szer*i, wys*i, al_map_rgb(0,255-(float(szer*i)/float(w/2+1))*(g1-g2),0), szer+0.5);
        }
        for (float i = 1; i < 5; i+=0.1) {
            al_draw_ellipse(cx, cy, w/2 + i, h/2 + i, al_map_rgb(40+i*25,40+i*25,40+i*25), 1);
        }
        for (float i = 0; i < 3; i+=0.1) {
            al_draw_ellipse(cx, cy, w/2 + i+5, h/2 + i+5, al_map_rgb(165-i*25,165-i*25,165-i*25), 1);
        }

        al_set_target_bitmap(bmp);
    }

public:

    int w, h;
    int cx, cy;

    KUPKA_KASY * kupka;

    class STOLIKOWA_PULA
    {
        int w, h;
        int x, y;
        int font_size;
        eliptyczny_stol * wlasciciel;
    public:
        STOLIKOWA_PULA()
        {
            w = na_moim_kompie(120);
            h = na_moim_kompie(25);
            x = screen_w/2 - w/2;
            y = centrum_y - tyl_karty.h/2 - h - na_moim_kompie(20);
            font_size = na_moim_kompie(15);
        }
        void rysuj() {

            if (pula[0] < 1 && faza != 4) return;

            al_draw_filled_rectangle(x+w/4, y, x+w-w/4, y+h, black);

            for (int i = 0; i < w/4; i++) {
                int a = (float)255*((float)1-(float)i/(float)((float)w/4));
                al_draw_line(x+w-w/4+i, y, x+w-w/4+i, y+h, al_map_rgba(0,0,0,a), 1);
                al_draw_line(x+w/4-i, y, x+w/4-i, y+h, al_map_rgba(0,0,0,a), 1);
            }
            al_draw_text(font(font_size), white, x+w/2, y+h/2-font_size/2, ALLEGRO_ALIGN_CENTRE, string("PULA: "+intostring(PULA())).c_str());
        }

    };

    STOLIKOWA_PULA * stolikowa_pula;

    void init() {
        pomiedzy_kartami = na_moim_kompie(10);
        font_size = na_moim_kompie(17);
        w = na_moim_kompie(375)*2, h = na_moim_kompie(175)*2;
        cx = screen_w/2, cy = centrum_y;
        kupka = new KUPKA_KASY;
        kupka->kasa = 0;
        kupka->x = cx - na_moim_kompie(20);
        kupka->y = cy + tyl_karty.h/2 + moneta.r*2;
        kupka->czy_prawo = true;
        stolikowa_pula = new STOLIKOWA_PULA();
        wyslane = false;
        for (short i = 0; i < 5; i++){
            float x = cx - tyl_karty.w * 2.5 - pomiedzy_kartami * 2 + (tyl_karty.w + pomiedzy_kartami) * i;
            float y = cy - tyl_karty.h/2;
            stolikowa_karta[i] = new STOLIKOWA_KARTA(i,x,y);
        }
        poprzednia_faza = -1;
        utworz_bmp();
    }

    void aktualizuj()
    {
        for(int i = 0; i < 5; i++) stolikowa_karta[i]->aktualizuj();

        if (faza != poprzednia_faza) {
            if (faza == 1) {
                stolikowa_karta[0]->pokaz();
                stolikowa_karta[1]->pokaz();
                stolikowa_karta[2]->pokaz();
            } else if (faza == 2) {
                stolikowa_karta[3]->pokaz();
            } else if (faza == 3) {
                stolikowa_karta[4]->pokaz();
            } else if (faza == 4) {
                for (int i = 0; i < 5; i++) {
                    if (!stolikowa_karta[i]->pokazuj) {
                        stolikowa_karta[i]->pokaz();
                    }
                }
            } else if (faza == 0 || faza == -1) {
                for (int i = 0; i < 5; i++) stolikowa_karta[i]->ukryj();
            }
        }
        poprzednia_faza = faza;

        if (faza == 0) {
            for (int i = 0; i < liczba_miejsc; i++) kupka->kasa += pula[i];
            kupka->latacze.erase(kupka->latacze.begin(),kupka->latacze.end());
            wyslane == false;
        }
        if (faza == 4) {
            for (int i = 0; i < kupka->latacze.size(); i++) {
                if (kupka->latacze[i].wsk != NULL) kupka->latacze[i].wsk->cel = gracz[i].kupka;
                gracz[i].zaklad += kupka->dolecialo(i);
            }
        }
        if (faza == 4 && kupka->kasa == PULA() && !wyslane) {
            for (int i = 0; i < liczba_miejsc; i++) {
                kupka->kasa = gracz[i].zaklad;
                gracz[i].zaklad = 0;
                kupka->lec_do(gracz[i].kupka);
            }
            wyslane = true;
            kupka->kasa = 0;
        }
        kupka->aktualizuj();
    }

    void rysuj() {

        al_draw_bitmap(bmp,0,0,0);

        if (komunikat == "X") {
            for (int i = 0; i < 5; i++) {
                stolikowa_karta[i]->rysuj();
            }
        } else al_draw_text(font(font_size), black, cx, cy-font_size/2, ALLEGRO_ALIGN_CENTRE, bez_(komunikat).c_str());

        for (int i = 0; i < 5; i++) {
            stolikowa_karta[i]->rysuj();
        }

        kupka->rysuj();

        stolikowa_pula->rysuj();
    }
};

eliptyczny_stol stolik;

class tablica_gracza {

public:

    int w, h;
    int font_size;
    int pomiedzy_napisami;
    int pomiedzy_kartami;

    bool tryb_dod;
    int pozostale_sekundy;

    KUPKA_KASY * kupka;

private:

    system_klikania m;

    int numer_siedzenia;
    int numer_gracza;

    bool wolne_miejsce;
    bool tryb_siadania;

    void rysuj_karty() {

        float x1 = cx - pomiedzy_kartami/2 - tyl_karty.w/2;
        float y1 = cy - h/2 - tyl_karty.h/2;
        float x2 = x1 + pomiedzy_kartami;
        float y2 = y1 - pomiedzy_kartami/2;

        if (numer_gracza == moje_miejsce || faza > 3) {
            al_draw_bitmap (przod_karta[gracz[numer_gracza].karty[0].liczba-2][gracz[numer_gracza].karty[0].kolor](), x1, y1, 0);
            al_draw_bitmap (przod_karta[gracz[numer_gracza].karty[1].liczba-2][gracz[numer_gracza].karty[1].kolor](), x2, y2, 0);
        } else {
            al_draw_bitmap (tyl_karty(), x1, y1, 0);
            al_draw_bitmap (tyl_karty(), x2, y2, 0);
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

    short poprzednia_faza;

    void rysuj_zaklad() {

        int poprzednie_x = kupka->x;
        if (dealer == numer_gracza && faza>=0 && faza<=3) {
            al_draw_bitmap (znacznik_dealera(),kupka->x,kupka->y,0);
            if (kupka->czy_prawo) kupka->x += moneta.r*2.5;
            else kupka->x -= moneta.r*2.5;
        }
        kupka->kasa = gracz[numer_gracza].zaklad;
        kupka->rysuj();
        kupka->x = poprzednie_x;
    }

    string kasa() {
        if (wolne_miejsce) return "Miejsce";
        if (gracz[numer_gracza].kasa == 0) return "All in";
        return tysiace (gracz[numer_gracza].kasa);
    }

    double start_odlicznia;
    int czas_dodatkowy;
    ALLEGRO_COLOR kolor_czcionki;
    double koniec_zagrania;

    void kupka_xy (int x, int y, bool b) {

        switch (x) {
            case 0: kupka->x = cx-w/2-moneta.r*4; break;
            case 1: kupka->x = cx-w/2 - moneta.r + roznica(tyl_karty.w/2 + pomiedzy_kartami/2, w/2) / 2; break;
            case 2: kupka->x = cx+w/2 - moneta.r - roznica(tyl_karty.w/2 + pomiedzy_kartami/2, w/2) / 2; break;
            case 3: kupka->x = cx+w/2+moneta.r*2; break;
        }

        switch (y) {
            case 0: kupka->y = cy-h/2-moneta.r*4; break;
            case 2: kupka->y = cy-moneta.r; break;
            case 5: kupka->y = cy+h/2+moneta.r*2; break;
        }

        if (b) kupka->czy_prawo = 1;
        else kupka->czy_prawo = 0;
    }

    class DYMEK {
        int dh, dy, dz;
        tablica_gracza * ojciec;
    public:
        DYMEK(tablica_gracza * wsk)
        {
            ojciec = wsk;
            dh = moneta.r*3;
            dy = ojciec->cy + ojciec->h/2 + 5 + na_moim_kompie(4);
            dz = dh/3;
        }
        void rysuj()
        {
            string tekst;
            if (ojciec->numer_gracza == grajacy) {
                stringstream ss;
                tekst = intostring(ojciec->pozostale_sekundy) + " sek.";
            } else if ((al_current_time() < ojciec->koniec_zagrania && gracz[ojciec->numer_gracza].zagranie != "X") || gracz[ojciec->numer_gracza].zagranie == "Zwycięzca") {
                ojciec->kolor_czcionki = black;
                tekst = gracz[ojciec->numer_gracza].zagranie;
                if (tekst == "Zwycięzca") {
                    tekst = "Zgarniam " + intostring(gracz[ojciec->numer_gracza].ile_zgarniam);
                } else if (tekst == "Sprawdzam") {
                    tekst += " " + intostring(gracz[ojciec->numer_gracza].zaklad);
                } else if (tekst == "Przebijam") {
                    tekst += " do " + intostring(gracz[ojciec->numer_gracza].zaklad);
                }
            } else {
                return;
            }
            float w = dh + al_get_text_width(font(ojciec->font_size), tekst.c_str());
            al_draw_filled_rounded_rectangle(ojciec->cx-ojciec->w/2, dy, ojciec->cx-ojciec->w/2+w, dy+dh, dz, dz, white);
            al_draw_rounded_rectangle(ojciec->cx-ojciec->w/2, dy, ojciec->cx-ojciec->w/2+w, dy+dh, dz, dz, black, 1);
            //al_draw_filled_rectangle(ojciec->cx-ojciec->w/2, dy, ojciec->cx-ojciec->w/2+w, dy+dh, white);
            //al_draw_rectangle(ojciec->cx-ojciec->w/2, dy, ojciec->cx-ojciec->w/2+w, dy+dh, black, 1);
            al_draw_filled_triangle(ojciec->cx-ojciec->w/2+4*(ojciec->w/20), ojciec->cy+ojciec->h/2-(ojciec->w/20), ojciec->cx-ojciec->w/2+3*(ojciec->w/20), dy, ojciec->cx-ojciec->w/2+5*(ojciec->w/20), dy, white);
            al_draw_line(ojciec->cx-ojciec->w/2+4*(ojciec->w/20), ojciec->cy+ojciec->h/2-(ojciec->w/20), ojciec->cx-ojciec->w/2+3*(ojciec->w/20), dy, black, 1);
            al_draw_line(ojciec->cx-ojciec->w/2+4*(ojciec->w/20), ojciec->cy+ojciec->h/2-(ojciec->w/20), ojciec->cx-ojciec->w/2+5*(ojciec->w/20), dy, black, 1);
            al_draw_text(font(ojciec->font_size), ojciec->kolor_czcionki, ojciec->cx-ojciec->w/2+dh/2, dy+dh/2 - ojciec->font_size/2, ALLEGRO_ALIGN_LEFT, tekst.c_str());
        }
    };

    DYMEK * dymek;

public:

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
            case 3: cx = cx0/2 + cx2/2 - na_moim_kompie(50); cy = cy0/2 + cy2/2 - na_moim_kompie(50); kupka_xy(1,5,true); break;
            case 5: cx = cx0/2 + cx1/2 + na_moim_kompie(50); cy = cy0/2 + cy3/2 - na_moim_kompie(50); kupka_xy(2,5,false); break;
            case 1: cx = cx3/2 + cx2/2 - na_moim_kompie(50); cy = cy1/2 + cy2/2 + na_moim_kompie(50); kupka_xy(2,0,true); break;
            case 7: cx = cx3/2 + cx1/2 + na_moim_kompie(50); cy = cy1/2 + cy3/2 + na_moim_kompie(50); kupka_xy(1,0,false); break;
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

    void init(int arg) {
        w = 0;
        h = na_moim_kompie(55);
        font_size = na_moim_kompie(14);
        pomiedzy_napisami = (h - font_size * 2) / 3.5;
        pomiedzy_kartami = na_moim_kompie(14);
        kolor_czcionki = black;
        start_odlicznia = -1;
        tryb_siadania = false;
        kupka = new KUPKA_KASY;
        ustaw_x_i_y(arg);
        poprzednia_faza = -1;
        dymek = new DYMEK(this);
    }

    int cx, cy;

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
            if (wolne_miejsce) al_draw_text (font(font_size), white, cx, cy - pomiedzy_napisami/2 -font_size, ALLEGRO_ALIGN_CENTRE, string("Wolne").c_str());
            else al_draw_text (font(font_size), white, cx, cy - pomiedzy_napisami/2 -font_size, ALLEGRO_ALIGN_CENTRE, bez_(gracz[numer_gracza].nick).c_str());
            al_draw_text(font(font_size), white, cx, cy + pomiedzy_napisami/2, ALLEGRO_ALIGN_CENTRE, kasa().c_str());
        }

        if (wolne_miejsce) obramowka(35,35,35,10);
        else if (numer_gracza == grajacy) obramowka(200,200,0,40);
        else if (numer_gracza == moje_miejsce) obramowka(215,0,0,60);
        else if (gracz[numer_gracza].status < 0) obramowka(123,123,123,30);
        else obramowka(205,205,205,45);

        rysuj_zaklad();

        dymek->rysuj();
    }

    void aktualizuj() {

        if (poprzednia_faza != faza) {
            kupka->kasa = gracz[numer_gracza].poprzedni_zaklad;
            if (kupka->kasa > 0 && faza != 0 && faza != -1) kupka->lec_do(stolik.kupka);
        }
        poprzednia_faza = faza;
        stolik.kupka->kasa += kupka->dolecialo();
        kupka->aktualizuj();

        m.aktualizuj(cx, cy, w, h);

        if (numer_gracza == moje_miejsce) tryb_siadania = false;
        else if (tryb_siadania) {
            if (m.click()) moje_siedzenie = numer_siedzenia;
            if (!m.najechane && !mouse_pressed) tryb_siadania = false;
        }
        else if (m.click()) tryb_siadania = true;

        numer_gracza = mod (numer_siedzenia - moje_siedzenie + moje_miejsce, (int) liczba_miejsc);
        gracz[numer_gracza].kupka = kupka;

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
                czas_dodatkowy = gracz[numer_gracza].dod_czas;
            }
            pozostale_sekundy = czas_na_zagranie-(int)(al_current_time() - start_odlicznia);
            if (pozostale_sekundy < 0) {
                pozostale_sekundy += czas_dodatkowy;
                kolor_czcionki = red;
                tryb_dod = true;
            } else {
                kolor_czcionki = al_map_rgb(0,127,0);
                tryb_dod = false;
            }
        }
    }
};

tablica_gracza tablica [max_liczba_miejsc];

class przycisk_zagrania {

public:

    int cx, cy;
    int w, h;

    static int stan_suwaka();
    static int pasek_czasu_w();

private:

    int n;
    int font_size;
    int pomiedzy_napisami;
    int pomiedzy_przyciskami;

    system_klikania m;

    string napis() {
        switch (n) {
            case 1: return "Pasuję";
            case 2: if (gracz[moje_miejsce].zaklad - najwyzszy_zaklad() < 0) return "Sprawdzam"; return "Czekam";
            case 3: return "Przebijam";
        }
    }

    void rysuj_napis(string txt)
    {
        if (txt == "Czekam" || txt == "Pasuję") {
            al_draw_text(font(font_size), white, cx, cy - font_size/2 - font_size/6, ALLEGRO_ALIGN_CENTRE, txt.c_str());
        } else {
            al_draw_text(font(font_size), white, cx, cy - font_size - font_size/6, ALLEGRO_ALIGN_CENTRE, txt.c_str());
            if (txt == "Sprawdzam") {
                al_draw_text(font(font_size), white, cx, cy + font_size/6, ALLEGRO_ALIGN_CENTRE, intostring(najwyzszy_zaklad()).c_str());
            } else if (txt == "Przebijam") {
                al_draw_text(font(font_size), white, cx, cy + font_size/6, ALLEGRO_ALIGN_CENTRE, string("do "+intostring(stan_suwaka()+gracz[moje_miejsce].zaklad)).c_str());
            }
        }
    }

public:

    void init(int i) {
        n = i;
        w = na_moim_kompie(100), h = na_moim_kompie(55);
        cx = pasek_czasu_w() + w/2;
        pomiedzy_przyciskami = na_moim_kompie(5);
        cy = screen_h - na_moim_kompie(20) - h/2 - 3*(h+pomiedzy_przyciskami) + n*(h+pomiedzy_przyciskami);
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

        rysuj_napis(napis());
    }
};

przycisk_zagrania przycisk1;
przycisk_zagrania przycisk2;
przycisk_zagrania przycisk3;

class PASEK_CZASU
{
public:
    static const int p_w = 20;
    static const int p_x = 20;
private:
    int x, y;
    int w, h;
    double ulamek;
    bool czas_dodatkowy;
    int moj_czas_dod;
    double start;
    int sekundy;
    float wciecie;
public:
    PASEK_CZASU()
    {
        x = na_moim_kompie(p_x);
        y = przycisk1.cy - przycisk1.h/2;
        w = na_moim_kompie(p_w);
        h = (przycisk3.cy+przycisk3.h/2)-(przycisk1.cy-przycisk1.h/2);
        czas_dodatkowy = false;
        ulamek = 1;
        moj_czas_dod = 25;
        sekundy = 10;
    }
    void aktualizuj()
    {
        if (sekundy != tablica[moje_siedzenie].pozostale_sekundy) {
            sekundy = tablica[moje_siedzenie].pozostale_sekundy;
            start = al_current_time();
        }

        if (!tablica[moje_siedzenie].tryb_dod) {
            czas_dodatkowy = false;
            ulamek = double(double(sekundy) - (al_current_time() - start)) / double(czas_na_zagranie);
        } else {
            czas_dodatkowy = true;
            ulamek = double(double(sekundy) - (al_current_time() - start)) / double(poczatkowy_czas_dodatkowy);
        }
        ulamek = zakres(ulamek, 0.0, 1.0);
    }
    void rysuj()
    {
        if (tablica[moje_siedzenie].tryb_dod) {
            rysuj_slup(x+1, y+h-double(h)*ulamek+1, w-2, double(h)*ulamek-1, 1,0,0);
        } else {
            rysuj_slup(x+1, y+h-double(h)*ulamek+1, w-2, double(h)*ulamek-1, 0,1,0);
        }
        al_draw_rounded_rectangle(x, y, x+w, y+h, na_moim_kompie(2), na_moim_kompie(2), black, na_moim_kompie(2));
    }
};

PASEK_CZASU * pasek_czasu = NULL;

int przycisk_zagrania::pasek_czasu_w()
{
    return na_moim_kompie(PASEK_CZASU::p_w) + na_moim_kompie(PASEK_CZASU::p_x)*2;
}

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
            if (przyszle_zagranie == z) al_draw_bitmap (good(), x - abs(bok-good.w)/2, y - abs(bok-good.h)/2, 0);
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
    float pieniadz_w;
    int min_by_przebic;

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

        stan = zakres(int(min_by_przebic + (przesuwak_cx-(x[3]+miara/4))/pieniadz_w), 1, gracz[moje_miejsce].kasa);
    }
};

suwak_przebijania suwak;

int przycisk_zagrania::stan_suwaka() {return suwak.stan;}

class okno_czatu { // klasa do dopracowania

    vector <string> komunikaty;
    int ile_komunikatow;

public:

    void init() {
        ile_komunikatow = 20;
        komunikaty.push_back("");
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

void rysuj_slup (int x, int y, int w, int h, bool r, bool g, bool b)
{
    for (int i = x; i <= x+w/2; i++) {
        al_draw_line(i,y,i,y+h,al_map_rgb(r*255*(127/(i/(w/2))), g*255*(127/(i/(w/2))), b*255*(127/(i/(w/2)))),1);
    }
    for (int i = x+w; i >= x+w/2; i--) {
        al_draw_line(i,y,i,y+h,al_map_rgb(r*255*(127/(i/(w/2))), g*255*(127/(i/(w/2))), b*255*(127/(i/(w/2)))),1);
    }
}

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
        gracz.push_back(miejsce());
        pula.push_back(0);
    }
}

// ../init

int bitmap_init() {

    al_init_image_addon();

    if (!moneta.init("moneta.png")) return -1;
    if (!znacznik_dealera.init("dealer.png")) return -1;
    if (!good.init("good.png")) return -1;
    if (!tyl_karty.init("tył.jpeg")) return -1;

    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {

            string plik;

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

            if (!przod_karta[i][j].init(plik)) return -1;
        }
    }

    return 0;
}

int color_init() {

    white = al_map_rgb(255,255,255);
    black = al_map_rgb(0,0,0);
    green = al_map_rgb(0,255,0);
    red = al_map_rgb(255,0,0);

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
        gracz[i].zapamietaj();
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
        if (faza == 4) gracz[i].ile_zgarniam = gracz[i].zaklad;
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

        } else if (przyszle_zagranie == 1) {
            if (najwyzszy_zaklad() > gracz[moje_miejsce].zaklad) {
                przyszle_zagranie = -1;
                return true;
            }
            ss << "CZEKAM";

        } else if (przyszle_zagranie == 2) ss << "SPRAWDZAM";

        else ss << "PRZEBIJAM " << suwak.stan;

        send_packet(nazwa_stolika + " Stolik " + ss.str());
        service_websockets();

        przyszle_zagranie = -1;
        grajacy = -1; // może spowodować core dumped
    }

    return true;
}

// ../rysowanie

class TLO
{
    ALLEGRO_BITMAP * bmp;
public:
    TLO()
    {
        bmp = al_create_bitmap(screen_w,screen_h);
        al_set_target_bitmap(bmp);
        al_clear_to_color(al_map_rgba(0,0,0,0));

        float przekatna = sqrt(pow(screen_h-centrum_y,2)+pow(screen_w/2,2));
        float szary = 255;
        float grubosc = (przekatna-stolik.h/2) / szary;

        float r = stolik.h/2;
        for (int i = szary; r < przekatna; i--) {
            al_draw_circle(screen_w/2,centrum_y,r,al_map_rgb(i,i,i),grubosc+1);
            r += grubosc;
        }

        al_set_target_bitmap(al_get_backbuffer(display));
    }
    void rysuj()
    {
        al_draw_bitmap(bmp,0,0,0);
    }
};

TLO * tlo = NULL;

/********************************
 Funkcje 1
*********************************/

int stoliki(int argc, char** argv) {

    cout << endl;
    string serwer, nick;

    if (argc == 4) {

        serwer = z_(string(argv[1]));
        nazwa_stolika = z_(string(argv[2]));
        nick = z_(string(argv[3]));

    } else {

        cout << "Serwer: ";
        getline(cin,serwer);
        serwer = z_(serwer);

        cout << "Stolik: ";
        getline(cin,nazwa_stolika);
        nazwa_stolika = z_(nazwa_stolika);

        cout << "Nick: ";
        getline(cin,nick);
        nick = z_(nick);

        cout << endl;
    }

    if (!connect_to_server(serwer)) {
        cout << endl << "Połączenie nie powiodło się." << endl << endl; return -1;
    }
    cout << endl;

    stringstream ss;

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

    time_t moment_zakonczenia = time(NULL) + 15;

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
                        cout << "Dołączono do stolika " << nazwa_stolika << endl << endl;

                        dostosowanie_do_liczby_miejsc();
                        gracz[moje_miejsce] = miejsce();

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
    screen_w = disp_data.width;
    screen_h = disp_data.height;
    centrum_y = screen_h/2 - na_moim_kompie(20);

    /*
    al_set_new_display_flags(ALLEGRO_WINDOWED);
    cout << "w: ";
    cin >> screen_w;
    cout << "h: ";
    cin >> screen_h;
    centrum_y = screen_h/2 - na_moim_kompie(20);
    */

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
    for (int i = 0; i < liczba_miejsc; i++) tablica[i].init(i);
    przycisk1.init(1);
    przycisk2.init(2);
    przycisk3.init(3);
    pasek_czasu = new PASEK_CZASU;
    opcje.init(przycisk2.cy, przycisk2.cx-przycisk2.w/2-przycisk_zagrania::pasek_czasu_w()/2);
    suwak.init();
    czat.init();
    tlo = new TLO;

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

    stolik.aktualizuj();

    for (int i = 0; i < liczba_miejsc; i++) {
        tablica[i].aktualizuj();
    }

    if (moje_miejsce == grajacy) {
        if (przyszle_zagranie >= 0) zagraj();
        else {
            pasek_czasu->aktualizuj();
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
    nazwa_okna << "PokerOnline - " << bez_(nazwa_stolika) << " - " << bez_(gracz[moje_miejsce].nick) << " - " << gracz[moje_miejsce].kasa;
    al_set_window_title(display, nazwa_okna.str().c_str());

    tlo->rysuj();

    stolik.rysuj();

    for (int i = 0; i < liczba_miejsc; i++) {
        tablica[i].rysuj();
    }

    if (moje_miejsce == grajacy && przyszle_zagranie < 0) {
        pasek_czasu->rysuj();
        przycisk1.rysuj();
        przycisk2.rysuj();
        przycisk3.rysuj();
        suwak.rysuj();
    } else if (moje_miejsce != grajacy && gracz[moje_miejsce].status > 1 && (faza==0 || faza==1 || faza==2 || faza==3)) {
        opcje.rysuj();
    }

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

int main(int argc, char** argv) {

    if (stoliki(argc, argv) != 0) {
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
