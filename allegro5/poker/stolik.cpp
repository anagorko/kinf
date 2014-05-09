// (C) Benedykt Kula

#include "../../network/websockets/client.h"

#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

string wycinek (string t1, int from, int to) {
    string t2;
    for (int i = from; i < to; i++) {
        t2 += t1[i];
    }
    return t2;
}

enum RELACJE {mniejsze, rowne, wieksze};

enum kolory {
    pik = 0,
    kier = 1,
    karo = 2,
    trefl = 3
};

struct karta {
    short liczba;
    short kolor;
    static bool wg_liczba (karta a, karta b) {return a.liczba > b.liczba;}
    static bool wg_kolor (karta a, karta b) {return a.kolor > b.kolor;}
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
    vector <short> uklad;
    void wykryj_uklad();
};

string nazwa_stolika;

const short max_liczba_miejsc = 12;
short liczba_miejsc = 8;

int wysokoscMC = 5;
int wysokoscDC = 10;

string komunikat = "X";

short faza = -1;

vector < miejsce > gracz;

short dealer = -1, grajacy = -1;
short zwyciezca, zwycieski_uklad;

vector < int > pula;
karta karty[5];
karta * karty_na_stole = karty;

bool w_talii[13][4];

short aktualna_pula = 0;

short liczba_graczy() {
    short zwrot = 0;
    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status > -2) zwrot++;
    }
    return zwrot;
}

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

void zeruj_pule() {
    for (int i = 0; i < liczba_miejsc; i++) {
        pula[i] = 0;
    }
}

short ile_statusow(int n) {
    short zwrot = 0;
    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status == n) zwrot++;
    }
    return zwrot;
}

string zmiana_nicku(string t) {

    string t1 = t;

    if (t[0]=='a'||t[0]=='A')
        if (t[1]=='n'||t[1]=='N')
            if (t[2]=='a'||t[2]=='A')
                if (t[3]=='g'||t[3]=='G')
                    if (t[5]=='r'||t[5]=='R')
                        if (t[6]=='k'||t[6]=='K')
                            if (t[7]=='o'||t[7]=='O')
                                return "NajwyższyAdmin";
    while(1) {

        bool pom = true;
        string a = t;

        for (int i = 0; i < liczba_miejsc; i++) {
            if (gracz[i].status > -2 && gracz[i].nick == t) {
                if (pom) pom = false;
                else {
                    t += "++";
                    break;
                }
            }
        }

        if (a == t) break;

    }

    if (t1 != t) {
        send_packet(nazwa_stolika + " CZAT Stolik Nick \"" + t1 + "\" został zmieniony na: \"" + t + "\".");
        service_websockets();
    }

    return t;
}

const short czas_na_zagranie = 8;

/********************************
 Funkcje
*********************************/

// ../paczki/licytacja

bool WBIJAM(string nick_nowego) {

    stringstream ss;

    if (liczba_graczy() < liczba_miejsc) {

        int miejsce_nowego = random () % (liczba_miejsc - liczba_graczy());

        for (int i = 0; i < liczba_miejsc; i++) {
            if (gracz[i].status == -2) {
                if (miejsce_nowego > 0) {
                    miejsce_nowego--;
                } else {
                    miejsce_nowego = i;
                    break;
                }
            }
        }

        gracz[miejsce_nowego].status = -1;
        gracz[miejsce_nowego].nick = nick_nowego;
        gracz[miejsce_nowego].zagranie = "X";
        gracz[miejsce_nowego].kasa = 1000;
        gracz[miejsce_nowego].zaklad = 0;
        gracz[miejsce_nowego].dod_czas = 25;

        ss.str(""); ss.clear();
        ss << nazwa_stolika << " " << gracz[miejsce_nowego].nick << " ZAPRASZAM " << liczba_miejsc << " " << miejsce_nowego;
        send_packet(ss.str());
        service_websockets();

        gracz[miejsce_nowego].nick = zmiana_nicku(nick_nowego);

    } else {

        ss.str(""); ss.clear();
        ss << nazwa_stolika << " " << nick_nowego << " PRZELUDNIENIE";
        send_packet(ss.str());
        service_websockets();
    }

    return true;
}

bool SPADAM(short odchodzacy) {

        gracz[odchodzacy].pule = -1;
        gracz[odchodzacy].status = -2;

        return true;
}

bool PASUJE() {

    gracz[grajacy].zagranie = "Pasuję";

    gracz[grajacy].pule = -1;

    gracz[grajacy].status = -1;

    return true;
}

bool CZEKAM() {

    if (gracz[grajacy].zaklad < najwyzszy_zaklad()) {
        PASUJE();
        send_packet(nazwa_stolika + " CZAT Stolik " + gracz[grajacy].nick + " spasowany za nieprawidłowe zagranie.");
        service_websockets();
        return true;
    }

    gracz[grajacy].zagranie = "Czekam";

    gracz[grajacy].status = 1;

    return true;
}

bool SPRAWDZAM() {

    gracz[grajacy].zagranie = "Sprawdzam";

    if (gracz[grajacy].kasa > najwyzszy_zaklad() - gracz[grajacy].zaklad) {

        gracz[grajacy].kasa -= najwyzszy_zaklad() - gracz[grajacy].zaklad;
        gracz[grajacy].zaklad += najwyzszy_zaklad() - gracz[grajacy].zaklad;

        gracz[grajacy].status = 1;

    } else {

        gracz[grajacy].zaklad += gracz[grajacy].kasa;
        gracz[grajacy].kasa = 0;

        gracz[grajacy].status = 0;
    }

    return true;
}

bool PRZEBIJAM(int suma) {

    if (gracz[grajacy].kasa < suma || suma < 2 * najwyzszy_zaklad() - gracz[grajacy].zaklad) {
        PASUJE();
        send_packet(nazwa_stolika + " CZAT Stolik " + gracz[grajacy].nick + " spasowany za nieprawidłowe zagranie.");
        service_websockets();
        return true;
    }

    gracz[grajacy].zagranie = "Przebijam";

    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status == 1) gracz[i].status = 3;
    }

    if (gracz[grajacy].kasa == suma) {

        gracz[grajacy].zaklad += gracz[grajacy].kasa;
        gracz[grajacy].kasa = 0;

        gracz[grajacy].status = 0;

    } else {

        gracz[grajacy].kasa -= suma;
        gracz[grajacy].zaklad += suma;

        gracz[grajacy].status = 1;
    }

    return true;
}

void ZMIENIAM_NICK (int kto, string nowy_nick) {
    send_packet(nazwa_stolika+" CZAT Stolik "+gracz[kto].nick+" zmienia nick na: "+zmiana_nicku(nowy_nick)+".");
    service_websockets();
    gracz[kto].nick = zmiana_nicku(nowy_nick);
}

/********************************
 Funkcje 2
*********************************/

// ../licytacja

void rozeslij_dane() {

    stringstream ss;

    ss << komunikat << " ";

    ss << faza << " ";

    int n = 0;
    if (faza == 1) n = 3;
    else if (faza == 2) n = 4;
    else if (faza == 3 || faza == 4) n = 5;
    for (int i = 0; i < n; i++) {
        ss << karty[i].liczba << " " << karty[i].kolor << " ";
    }

    for (int i = 0; i < liczba_miejsc; i++) {
        ss << pula[i] << " ";
    }

    ss << dealer << " " << grajacy << " ";

    for (int i = 0; i < liczba_miejsc; i++) {
        ss << gracz[i].status << " ";
        if (gracz[i].status > -2) {
            ss
            << gracz[i].nick << " "
            << gracz[i].zagranie << " "
            << gracz[i].kasa << " "
            << gracz[i].zaklad << " "
            << gracz[i].pule << " "
            << gracz[i].karty[0].liczba << " "
            << gracz[i].karty[0].kolor << " "
            << gracz[i].karty[1].liczba << " "
            << gracz[i].karty[1].kolor << " "
            << gracz[i].dod_czas << " "
            ;
        }
        /**/ if (gracz[i].zagranie != "X") gracz[i].zagranie = "X";
    }

    ///

    int podzial;
    int limit = 128 - nazwa_stolika.length() - string(" Gracze DANE ").length();

    podzial = ss.str().length() / limit;
    if ((ss.str().length() % limit) != 0) podzial++;

    for (int i = 0; i < podzial; i++) {
        if (i == podzial-1) send_packet(nazwa_stolika + " Gracze END " + wycinek(ss.str(),i*limit,ss.str().length()));
        else send_packet(nazwa_stolika + " Gracze DANE " + wycinek(ss.str(),i*limit,(i+1)*limit));
        service_websockets();
    }
}

bool paczki() {

    int n = service_websockets();

    string paczka;

    while (receive_packet(paczka)) {

        stringstream ss;
        ss.str(""); ss.clear();
        ss << paczka;

        string czy;
        ss >> czy;

        if (czy == nazwa_stolika) {
            ss >> czy;
            if (czy == "Stolik" || czy == "stolik"|| czy == "Wszyscy") {

                ss >> czy;

                if (czy == "WBIJAM") {
                    string a;
                    ss >> a;
                    WBIJAM(a);
                    return false;
                } else if (czy == "SPADAM") {
                    int a;
                    ss >> a;
                    SPADAM(a);
                    if (a == grajacy) return true;
                    else return false;
                } else if (czy == "PASUJE") {
                    return PASUJE();
                } else if (czy == "CZEKAM") {
                    return CZEKAM();
                } else if (czy == "SPRAWDZAM") {
                    return SPRAWDZAM();
                } else if (czy == "PRZEBIJAM") {
                    int a;
                    ss >> a;
                    return PRZEBIJAM(a);
                } else if (czy == "ZMIENIAM_NICK") {
                    int n;
                    string t;
                    ss >> n >> t;
                    ZMIENIAM_NICK(n,t);
                    return false;
                }
            }
        }
    }

    return false;
}

// ../rozdanie

void zbierz_zaklady() { // funkcja do dopracowania

    while (1) {
        int min;
        short numer;
        bool first = true;
        for (int i = 0; i < liczba_miejsc; i++) {
            if (gracz[i].zaklad > 0) {
                if (first) {
                    min = gracz[i].zaklad;
                    numer = i;
                    first = false;
                } else if (gracz[i].zaklad < min) {
                    min = gracz[i].zaklad;
                    numer = i;
                }
            }
        }
        if (first) break;
        for (int i = 0; i < liczba_miejsc; i++) {
            if (gracz[i].zaklad != 0) {
                pula[aktualna_pula] += min;
                gracz[i].zaklad -= min;
                gracz[i].pule = aktualna_pula;
            }
        }
        // poniższa linijka była pisana na szybko, może zawierać błąd ;)
        if (gracz[numer].status == 0) aktualna_pula++;
    }
}

void wyloz_karte(int n) {

    while (1) {
        karty[n].liczba = (random() % 13) + 2;
        karty[n].kolor = (kolory) (random() % 4);
        if (w_talii[karty[n].liczba-2][karty[n].kolor]) {
            w_talii[karty[n].liczba-2][karty[n].kolor] = false;
            break;
        }
    }
}

/////////

void licytacja() {

    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status > 0) gracz[i].status = 3;
    }

    grajacy = dealer + 1;

    short ciemne = 2;

    for (;; grajacy++) {

        if (faza != 0) ciemne = 0;
        grajacy = int(abs(grajacy)) % int(liczba_miejsc);

        if (ile_statusow(3)+ile_statusow(1) < 2 || ile_statusow(3) == 0) break;

        if (gracz[grajacy].status > 1 && gracz[grajacy].kasa > 0) {

            if (ciemne == 2) {

                PRZEBIJAM(wysokoscMC);
                gracz[grajacy].zagranie = "WpłacamMC";
                ciemne--;

            } else if (ciemne == 1) {

                PRZEBIJAM(wysokoscDC);
                gracz[grajacy].zagranie = "WpłacamDC";
                if (gracz[grajacy].status > 0) gracz[grajacy].status = 3;
                ciemne--;

            } else {

                rozeslij_dane();

                time_t czas = time(NULL);
                while (1) {
                    if (paczki()) break;
                    if (difftime(time(NULL),czas) >= czas_na_zagranie) {
                        if (gracz[grajacy].dod_czas <= 0) {
                            PASUJE();
                        } else {
                            send_packet(nazwa_stolika + " CZAT Stolik " + gracz[grajacy].nick + ", upływa twój czas dodatkowy.");
                            service_websockets();
                            czas = time(NULL);

                            for (int i = 1;;) {
                                if (paczki() || gracz[grajacy].status < 0) break;
                                if (difftime(time(NULL),czas) >= i) {
                                    gracz[grajacy].dod_czas--;
                                    i++;
                                }
                                if (gracz[grajacy].dod_czas <= 0) {
                                    PASUJE();
                                    break;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }

    zbierz_zaklady();
}

/********************************
 Funkcje 1
*********************************/

int ustawienia() {

    cout << endl << "Serwer: ";
    string serwer;
    cin >> serwer;

    cout << "Nazwa: ";
    cin >> nazwa_stolika;

    while (nazwa_stolika.length() > 50) {
        cout << "Nazwa stolika musi się mieścić w 50 znakach: ";
        cin >> nazwa_stolika;
    }

    //cout << "Limit miejsc: ";
    //cin >> liczba_miejsc;
    /**/ liczba_miejsc = 8;

    dealer = random() % 8;

    while (cin.fail() || liczba_miejsc < 2 || liczba_miejsc > max_liczba_miejsc) {
        cin.clear();
        cout << "Limit miejsc musi być liczbą z przedziału od 2 do 12: ";
        cin >> liczba_miejsc;
    }

    for (int i = 0; i < liczba_miejsc; i++) {
        gracz.push_back((miejsce) {-2,"X","X",1000,0,0,(karta){0,0},(karta){0,0},25});
        pula.push_back(0);
    }

    cout << endl;
    if (!connect_to_server(serwer)) {
        cout << endl << "Połączenie nie powiodło się." << endl << endl;
        return -1;
    }
    cout << endl;

    zeruj_pule();

    return 0;
}

void pre_flop() {

    faza = 0;

    komunikat = "X";

    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status > -2) gracz[i].status = 3;
        gracz[i].zagranie = "X";
        gracz[i].dod_czas += 5; // do przetestowania
        if (gracz[i].dod_czas > 25) gracz[i].dod_czas = 25;
    }

    aktualna_pula = 0;

    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 4; j++)
            w_talii[i][j] = true;

    if (dealer == liczba_miejsc) dealer = 0;
    else dealer++;

    if (gracz[dealer].status == -2) {

        for (int i = dealer + 1; ; i++) {

            if (i == liczba_miejsc) i = 0;

            if (gracz[i].status != -2) {
                dealer = i;
                break;
            }
        }
    }

    for (short i = 0; i < 5; i++) {
        karty[i].liczba = -1;
        karty[i].kolor = -1;
    }

    for (int i = 0; i < liczba_miejsc; i++) {
        if (gracz[i].status > -2) {
            for (int j = 0; j < 2; j++) {
                while (1) {
                    gracz[i].karty[j].liczba = (random() % 13) + 2;
                    gracz[i].karty[j].kolor = (kolory) (random() % 4);
                    if (w_talii[gracz[i].karty[j].liczba-2][gracz[i].karty[j].kolor]) {
                        w_talii[gracz[i].karty[j].liczba-2][gracz[i].karty[j].kolor] = false;
                        break;
                    }
                }
            }
        }
    }

    rozeslij_dane();

    licytacja();
}

void flop() {
    faza = 1;
    wyloz_karte(0);
    wyloz_karte(1);
    wyloz_karte(2);
    if (ile_statusow(1) > 1) licytacja();
}

void turn() {
    faza = 2;
    wyloz_karte(3);
    if (ile_statusow(1) > 1) licytacja();
}

void the_river() {
    faza = 3;
    wyloz_karte(4);
    if (ile_statusow(1) > 1) licytacja();
}

void miejsce::wykryj_uklad() {
    uklad.clear();
    karta k[7];
    for (int i = 0; i < 5; i++) k[i] = karty_na_stole[i];
    k[5] = karty[0];
    k[6] = karty[1];

    sort (k, k+7, karta::wg_liczba);

    // Kolor
    bool czy_kolor=0;
    short naj_kolor=0;
    int kolor_ile[4];
    for (int i = 0; i < 4; i++, naj_kolor++) {
        kolor_ile[i]=0;
        for (int j = 1; j < 7; j++) {
            if (kolor_ile[i] >= 4) {
                czy_kolor = true;
                break;
            } else if (k[j].kolor == i) kolor_ile[i]++;
        }
        if (czy_kolor) break;
    }

    // Strit
    int strit_ile=0, strit_start=0;
    for (int i=1; i < 7; i++) {
        if (strit_ile >= 4) break;
        else if (k[i-1].liczba-1 == k[i].liczba) {
            strit_ile++;
            if (strit_ile==3 && k[i].liczba==0 && k[0].liczba==12) strit_ile++;
        } else {
            strit_ile = 0;
            strit_start = i;
        }
    }

    // Poker
    bool czy_poker = 0;
    if (strit_ile >= 4) {
        czy_poker = 1;
        naj_kolor = k[strit_start].kolor;
        for (int i = strit_start+1; i < 7 && i < strit_start+5; i++) {
            if (k[i].kolor != naj_kolor) {
                czy_poker = false;
                break;
            }
        }
    }

    // Wielokrotnosci kart
    vector <karta> kombo;
    for (int i = 1, kombos = 0; i < 8; i++) {
        if (k[i-1].liczba == k[i].liczba && i!=7) kombos++;
        else {
            kombo.push_back({k[i-1].liczba,short(kombos)});
            kombos = 0;
        }
    }
    sort (kombo.begin(), kombo.end(), karta::wg_kolor);

    // Wykrycie układu
    if (czy_poker) {
        uklad.push_back(8);
        uklad.push_back(k[strit_start].liczba);
    } else if (kombo[0].kolor == 3) {
        uklad.push_back(7);
        uklad.push_back(kombo[0].liczba);
        if (k[0].liczba != kombo[0].liczba) uklad.push_back(k[0].liczba);
        else uklad.push_back(k[4].liczba);
    } else if (kombo[0].kolor == 2 && kombo[1].kolor == 1) {
        uklad.push_back(6);
        uklad.push_back(kombo[0].liczba);
        uklad.push_back(kombo[1].liczba);
    } else if (czy_kolor) {
        uklad.push_back(5);
        for (int i=0, j=0; j<5; i++) {
            if (k[i].kolor == naj_kolor) {
                j++;
                uklad.push_back(k[i].liczba);
            }
        }
    } else if (strit_ile >= 4) {
        uklad.push_back(4);
        uklad.push_back(k[strit_start].liczba);
    } else if (kombo[0].kolor == 2) {
        uklad.push_back(3);
        uklad.push_back(kombo[0].liczba);
        uklad.push_back(kombo[1].liczba);
        uklad.push_back(kombo[2].liczba);
    } else if (kombo[0].kolor == 1 && kombo[1].kolor == 1) {
        uklad.push_back(2);
        uklad.push_back(kombo[0].liczba);
        uklad.push_back(kombo[1].liczba);
        for (int i = 0; i < 7; i++) {
            if (k[i].liczba != kombo[0].liczba && k[i].liczba != kombo[1].liczba) {
                uklad.push_back(k[i].liczba);
                break;
            }
        }
    } else if (kombo[0].kolor == 1) {
        uklad.push_back(1);
        for (int i = 0; i < 4; i++) {
            uklad.push_back(kombo[i].liczba);
        }
    } else {
        uklad.push_back(0);
        for (int i = 0; i < 5; i++) {
            uklad.push_back(k[i].liczba);
        }
    }
}

RELACJE relacja (vector<short>a,vector<short>b) {
    for (int i = 0; i < min(a.size(),b.size()); i++) {
        if (a[i] < b[i]) return mniejsze;
        if (a[i] > b[i]) return wieksze;
    }
    return rowne;
}

void wykrycie_kart() {

    faza = 4;

    for (int i = 0; i < liczba_miejsc; i++) gracz[i].wykryj_uklad();

    for (int i = 0; i < liczba_miejsc && pula[i]!=0; i++) {
        vector <short> zwyciezcy;
        vector <short> naj; naj.push_back(-1);
        for (int j = 0; j < liczba_miejsc; j++) {
            if (gracz[j].pule >= i && gracz[j].status >= 0) {
                if (relacja(gracz[j].uklad, naj) == rowne) {
                    zwyciezcy.push_back(j);
                } else if (relacja(gracz[j].uklad, naj) == wieksze) {
                    zwyciezcy.clear();
                    zwyciezcy.push_back(j);
                    naj = gracz[j].uklad;
                }
            }
        }
        if (i == 0 && zwyciezcy.size() > 0) zwyciezca = zwyciezcy[0];
        for (int j = 0; j < zwyciezcy.size(); j++) {
            gracz[zwyciezcy[j]].zaklad += pula[i]/zwyciezcy.size();
            gracz[zwyciezcy[j]].zagranie = "Zwycięzca";
        }
    }

    zeruj_pule();
    grajacy = -1;

    send_packet(nazwa_stolika + " CZAT Stolik Główną pulę zgarnia " + gracz[zwyciezca].nick + ".");
    service_websockets();
    rozeslij_dane();

    usleep(14000000);

    for (short i = 0; i < liczba_miejsc; i++) {
        gracz[i].kasa += gracz[i].zaklad;
        gracz[i].zaklad = 0;
        if (gracz[i].kasa <= 0) {
            gracz[i].status = -2;
            gracz[i].pule = -1;
            send_packet(nazwa_stolika + " CZAT Stolik " + gracz[zwyciezca].nick + " zbankrutował.");
            service_websockets();
        }
    }

    gracz[zwyciezca].zagranie = "X";
    rozeslij_dane();
}

int main() {

    srandom(time(NULL)+getpid());

    if (ustawienia() != 0) return -1;

    while (1) {

        faza = -1;

        komunikat = "Gra_rozpocznie_się_gdy_do_stolika_dołączy_3+_graczy.";

        while (1) {
            paczki();
            if (liczba_graczy() < 2) {
                while (1) {
                    paczki();
                    if (liczba_graczy() > 2) {
                        time_t czas = time(NULL);
                        for (int i = 0; i < 10;) {
                            stringstream ss;
                            ss << "Gra_rozpocznie_się_za_" << 10-i << "_sek.";
                            komunikat = ss.str();
                            rozeslij_dane();
                            while (1) if (difftime(time(NULL),czas) >= 1) {
                                i++;
                                czas = time(NULL);
                                break;
                            }
                        }
                        break;
                    }
                    if (liczba_graczy() > 2) break;
                }
            } else break;
        }

        pre_flop();
        flop();
        turn();
        the_river();
        wykrycie_kart();
    }

    return 0;
}
