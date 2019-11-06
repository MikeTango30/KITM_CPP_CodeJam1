#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

ifstream in("tel.txt");
ofstream out("loterija.txt");

int const MESKENAI = 1;
int const ZUIKENAI = 2;

void nuskaitytiDuomenis(int kiek, int telefonai[]);
void rastiMeskenuTelKieki(int telefonai[], int kiek, int &meskenuTelKiekis);
void atskirtiTelefonus(int meskenai[], int zuikenai[], int telefonai[], int meskenuTelKiekis, int zuikenuTelKiekis, int kiek);
void isrikiuotiMasyvus(int meskenai[], int zuikenai[], int meskenuTelKiekis, int zuikenuTelKiekis);
int skaitmenuSuma(int skaicius);
void rastiLaimingaTel(int kiek, int telefonai[], int laimingiTelefonai[], int laimingiSkaiciai[],
                      int &laiminguSkaiciuKiekis, int &laiminguTelefonuKiekis, int &laimingasSkaicius);
void isvestiRezultata(int meskenai[], int zuikenai[], int laimingiTelefonai[] , int laimingiSkaiciai[],
                      int laiminguSkaiciuKiekis, int meskenuTelKiekis, int zuikenuTelKiekis, int laiminguTelefonuKiekis,
                      int laimingasSkaicius);

int main()
{
    if(!in) {
        return 1;
    }

    int kiek = 0,
        meskenuTelKiekis = 0,
        zuikenuTelKiekis = 0,
        laimingasSkaicius = 0,
        laiminguTelefonuKiekis = 0,
        laiminguSkaiciuKiekis = 0;

    while(!in.eof()){
        in.ignore(80, '\n');
        kiek++;
    }

    int telefonai[kiek],
        laimingiTelefonai[kiek],
        laimingiSkaiciai[kiek];

    nuskaitytiDuomenis(kiek, telefonai);
    rastiMeskenuTelKieki(telefonai, kiek, meskenuTelKiekis);
    zuikenuTelKiekis = kiek - meskenuTelKiekis;

    int meskenai[meskenuTelKiekis],
        zuikenai[zuikenuTelKiekis];

    atskirtiTelefonus(meskenai, zuikenai, telefonai, meskenuTelKiekis, zuikenuTelKiekis, kiek);
    isrikiuotiMasyvus(meskenai, zuikenai, meskenuTelKiekis, zuikenuTelKiekis);
    rastiLaimingaTel(kiek, telefonai, laimingiTelefonai, laimingiSkaiciai, laiminguSkaiciuKiekis,
                     laiminguTelefonuKiekis, laimingasSkaicius);
    isvestiRezultata(meskenai, zuikenai, laimingiTelefonai, laimingiSkaiciai,
                     laiminguSkaiciuKiekis, meskenuTelKiekis, zuikenuTelKiekis, laiminguTelefonuKiekis,
                     laimingasSkaicius);

    in.close();
    out.close();

    return 0;
}

void nuskaitytiDuomenis(int kiek, int telefonai[])
{
    in.seekg(0);
    for(int i = 0; i < kiek; i++){
        in >> telefonai[i];
    }

}

void rastiMeskenuTelKieki(int telefonai[], int kiek, int &meskenuTelKiekis)
{
    for(int i = 0; i < kiek; i++){
       if (telefonai[i]/10000 == MESKENAI) {
            meskenuTelKiekis++;
       }
    }
}

void atskirtiTelefonus(int meskenai[], int zuikenai[], int telefonai[], int meskenuTelKiekis, int zuikenuTelKiekis, int kiek)
{
    meskenuTelKiekis = 0,
    zuikenuTelKiekis = 0;

    for(int i = 0; i < kiek; i++){
       if (telefonai[i]/10000 == MESKENAI) {
            meskenai[meskenuTelKiekis] = telefonai[i];
            meskenuTelKiekis++;
       } else if (telefonai[i]/10000 == ZUIKENAI) {
            zuikenai[zuikenuTelKiekis] = telefonai[i];
            zuikenuTelKiekis++;
       }
    }
}

void isrikiuotiMasyvus(int meskenai[], int zuikenai[], int meskenuTelKiekis, int zuikenuTelKiekis)
{
    sort(meskenai, meskenai + meskenuTelKiekis);
    sort(zuikenai, zuikenai + zuikenuTelKiekis);
    reverse(meskenai, meskenai + meskenuTelKiekis);
    reverse(zuikenai, zuikenai + zuikenuTelKiekis);
}

int skaitmenuSuma(int skaicius)
{
    int suma = 0;

    if (skaicius/10000 == MESKENAI || ZUIKENAI) {
        suma = skaicius/10000 + skaicius%10000/1000 + skaicius%1000/100 + skaicius%100/10 + skaicius%10;
    }

    return suma;
}

void rastiLaimingaTel(int kiek, int telefonai[], int laimingiTelefonai[], int laimingiSkaiciai[],
                      int &laiminguSkaiciuKiekis, int &laiminguTelefonuKiekis, int &laimingasSkaicius)
{
    laimingiTelefonai[laiminguTelefonuKiekis] = 0;
    while(laimingiTelefonai[laiminguTelefonuKiekis] == 0){
        srand(time(0)+laiminguSkaiciuKiekis);
        laimingasSkaicius = rand() % 45;
        int suma;

        for(int i = 0; i < kiek; i++){
            if(skaitmenuSuma(telefonai[i]) == laimingasSkaicius) {
                laimingiTelefonai[laiminguTelefonuKiekis] = telefonai[i];
                laiminguTelefonuKiekis++;
            }
        }
        laimingiSkaiciai[laiminguSkaiciuKiekis] = laimingasSkaicius;
        laiminguSkaiciuKiekis++;
    }
}

void isvestiRezultata(int meskenai[], int zuikenai[], int laimingiTelefonai[] , int laimingiSkaiciai[],
                      int laiminguSkaiciuKiekis, int meskenuTelKiekis, int zuikenuTelKiekis, int laiminguTelefonuKiekis,
                      int laimingasSkaicius)
{
    out << "***MESKENAI***" << '\n';
    for(int i = 0; i < meskenuTelKiekis; i++){
        out << meskenai[i] << '\n';
    }

    out << "***ZUIKENAI***" << '\n';
    for(int i = 0; i < zuikenuTelKiekis; i++){
        out << zuikenai[i] << '\n';
    }

    //isvedam laimingus kaicius be laimetojo - paskutinis masyve yra su laimetojais
    for(int i = 0; i < laiminguSkaiciuKiekis - 1; i++){
        out << "Sugeneruotas skaicius " << laimingiSkaiciai[i] << ". Niekas Nelaimejo." << '\n';
    }

    //laimingas skaicius su laimetojais
    out << "Sugeneruotas skaicius " << laimingiSkaiciai[laiminguSkaiciuKiekis - 1] << ". Yra " << laiminguTelefonuKiekis << " laimetojai (as)." << '\n';

    out << "***Laimetojai***" << '\n';
    for(int i = 0; i < laiminguTelefonuKiekis; i++){
        out << laimingiTelefonai[i] << '\n';
    }
}
