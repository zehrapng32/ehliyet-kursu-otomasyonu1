#include <iostream>
#include <fstream>
#include <conio.h>
#include <cstring>

using namespace std;

struct Kursiyer {
    char isim[30];
    char soyad[30];
    int yas;
    int no;
};


Kursiyer k[50];
int sayi = 0;
int sonNo = 1000;

void kaydet() {
    ofstream f("data.dat", ios::binary | ios::trunc);

    if (!f) {
        cerr << "Hata: Veriler dosyaya kaydedilemedi!\n";
        return;
    }
    f.write((char*)&sayi, sizeof(int));
    f.write((char*)&sonNo, sizeof(int));
    if (sayi > 0) {
        f.write((char*)k, sizeof(Kursiyer) * sayi);
    }
    f.close();
    cout << "\nVeriler basariyla kaydedildi.";
}

void oku() {
    ifstream f("data.dat", ios::binary);
    if (!f) {

        return;
    }
    f.read((char*)&sayi, sizeof(int));
    f.read((char*)&sonNo, sizeof(int));


    if (sayi < 0 || sayi > 50) {
        sayi = 0;
        sonNo = 1000;
    }
    else if (sayi > 0) {
        f.read((char*)k, sizeof(Kursiyer) * sayi);
    }
    f.close();
}

void ekle() {
    if (sayi >= 50) {
        cout << "\nKapasite dolu (Max 50).\n";
        return;
    }
    cout << "\n--- Yeni Kayit ---\n";
    cout << "Ad: "; cin >> k[sayi].isim;
    cout << "Soyad: "; cin >> k[sayi].soyad;
    cout << "Yas: "; cin >> k[sayi].yas;

    k[sayi].no = ++sonNo;
    sayi++;
    cout << "Kayit basarili! No: " << sonNo << endl;
}

void listele() {
    cout << "\n--- KURSİYER LİSTESİ ---\n";
    if (sayi == 0) {
        cout << "Liste su an bos.\n";
        return;
    }
    for (int i = 0; i < sayi; i++) {
        cout << "ID: " << k[i].no
            << " | " << k[i].isim << " " << k[i].soyad
            << " | Yas: " << k[i].yas << endl;
    }
}

void ara() {
    char ad[30];
    cout << "\nAranacak Kişinin Adı: ";
    cin >> ad;

    bool bulundu = false;
    for (int i = 0; i < sayi; i++) {
        if (strcmp(k[i].isim, ad) == 0) {
            cout << "\nKayit Bulundu:";
            cout << "\nNo: " << k[i].no << "\nIsim: " << k[i].isim << " " << k[i].soyad << "\nYas: " << k[i].yas << endl;
            bulundu = true;
        }
    }
    if (!bulundu) cout << "Kayit bulunamadi.\n";
}

void sil() {
    int no;
    cout << "\nSilinecek No: ";
    cin >> no;

    for (int i = 0; i < sayi; i++) {
        if (k[i].no == no) {
            for (int j = i; j < sayi - 1; j++) {
                k[j] = k[j + 1];
            }
            sayi--;
            cout << "Kayit silindi.\n";
            return;
        }
    }
    cout << "No bulunamadi.\n";
}

void bilgi() {
    cout << "\n--- EHLIYET SINIFLARI ---\n";
    cout << "B - Otomobil (18 yas)\n";
    cout << "A - Motor (18 yas)\n";
    cout << "C - Kamyon (21 yas)\n";
    cout << "D - Otobus (24 yas)\n";
}

int main() {

    setlocale(LC_ALL, "Turkish");

    oku();

    char secim;
    do {
        cout << "\n\n--- SÜRÜCÜ KURSU OTOMASYONU ---\n";
        cout << "1- Ekle\n2- Listele\n3- Ara\n4- Sil\n5- Bilgi\n0- Kaydet ve Cikis\n";
        cout << "Seciminiz: ";
        secim = _getch();

        switch (secim) {
        case '1': ekle(); break;
        case '2': listele(); break;
        case '3': ara(); break;
        case '4': sil(); break;
        case '5': bilgi(); break;
        case '0': kaydet(); return 0;
        default: cout << "\nGeçersiz seçim!"; break;
        }
        cout << "\nDevam etmek icin bir tusa basin...";
        _getch();
        system("cls");
    } while (true);

    return 0;
}