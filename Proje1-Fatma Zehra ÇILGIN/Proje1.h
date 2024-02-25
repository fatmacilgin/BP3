/*
 * Proje1.h
 * oluşturulan fonksiyonların prototiplerini tanımlar.
 * Proje-1
 * 8.12.2023
 * Fatma zehra ÇILGIN
 */

#ifndef PROJE1_H
#define PROJE1_H

typedef struct
{
    char *dersAdi;
    unsigned short int kredi;
    unsigned short int puan;
} Ders;

typedef struct
{
    char *ogrAdi;
    char *ogrSoyAdi;
    char *bolumu;
    float ortalama;
    Ders *aldigiDersler;
} Ogrenci;

Ders createDers(char *dersAdi, unsigned short int kredi, unsigned short int puan);
float calculateOgrenciOrtalama(Ogrenci *ogrenci);
Ogrenci createOgrenci(char *ogrAdi, char *ogrSoyAdi, char *bolumu, Ders *aldigiDersler);
void printOgrenci(Ogrenci *ogrenci);
void printOgrenciList(Ogrenci *ogrenciList, int ogrenciSayisi);
float calculateDersOrtalama(char *dersAdi, Ogrenci *ogrenciList, int ogrenciSayisi);
float calculateDersStandartSapma(char *dersAdi, Ogrenci *ogrenciList, int ogrenciSayisi);
float calculateKovaryans(Ders ders1, Ders ders2, Ogrenci *ogrenciList, int ogrenciSayisi);
void printYuksekNotAlanOgrenciler(char *dersAdi, Ogrenci *ogrenciList, int ogrenciSayisi);
void writeOgrenciDosyaya(Ogrenci *ogrenciList, int ogrenciSayisi, char *dosyaAdi);
void readDosyadanOgrenci(Ogrenci *ogrenciList, int ogrenciSayisi, char *dosyaAdi);
void bellekIadeOgrenci(Ogrenci *ogrenci);
void bellekIadeOgrenciList(Ogrenci *ogrenciList, int ogrenciSayisi);
void bellekIadeDers(Ders *ders);

#endif
