/*
 * Proje1.c
 * ders sayisini her öğrenci için 3 olarak alıp
 * buna göre fonksiyonların oluşturulduğu dosya.
 * Proje-1
 * 8.12.2023
 * Fatma zehra ÇILGIN
 */

#include "proje1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define dersSayisi 3

Ders createDers(char *dersAdi, unsigned short int kredi, unsigned short int puan)
{ // Ders struct döndüren fonksiyon.
    Ders ders;
    ders.dersAdi = (char *)malloc(256 * sizeof(char));
    strcpy(ders.dersAdi, dersAdi);
    ders.kredi = kredi;
    ders.puan = puan;
    return ders;
    bellekIadeDers(&ders); // malloc ifadesi yüzünden bellek iadesi yaptık.
}

float calculateOgrenciOrtalama(Ogrenci *ogrenci)
{ // öğrencinin aldığı derslerin ortalamasını alıp döndüren fonksiyon.
    float sum = 0;

    for (int i = 0; i < dersSayisi; i++)
    {
        sum += ogrenci->aldigiDersler[i].puan;
    }
    return sum / dersSayisi;
}

Ogrenci createOgrenci(char *ogrAdi, char *ogrSoyAdi, char *bolumu, Ders *aldigiDersler)
{ // Ogrenci struct döndüren fonksiyon.
    Ogrenci ogrenci;
    ogrenci.ogrAdi = (char *)malloc(256 * sizeof(char));
    strcpy(ogrenci.ogrAdi, ogrAdi);
    ogrenci.ogrSoyAdi = (char *)malloc(256 * sizeof(char));
    strcpy(ogrenci.ogrSoyAdi, ogrSoyAdi);
    ogrenci.bolumu = (char *)malloc(256 * sizeof(char));
    strcpy(ogrenci.bolumu, bolumu);
    ogrenci.aldigiDersler = (Ders *)malloc(dersSayisi * sizeof(Ders));
    for (int i = 0; i < dersSayisi; i++)
    {
        ogrenci.aldigiDersler[i] = createDers(
            aldigiDersler[i].dersAdi,
            aldigiDersler[i].kredi,
            aldigiDersler[i].puan);
    }
    ogrenci.ortalama = calculateOgrenciOrtalama(&ogrenci); // Calculate the average
    return ogrenci;
    bellekIadeOgrenci(&ogrenci);
    // malloc ifadeleri yüzünden bellek iadesi  yaptık.
}

void printOgrenci(Ogrenci *ogrenci)
{ // parametre olarak verilen öğrencinin bilgilerini
  // ve aldığı dersleri yazdıran fonksiyon.
    printf("Ad: %s\nSoyad: %s\nBolum: %s\nOrtalama: %.2f\n", ogrenci->ogrAdi, ogrenci->ogrSoyAdi, ogrenci->bolumu, ogrenci->ortalama);
    for (int i = 0; i < dersSayisi; i++)
    {
        printf("Ders %d: %s - Kredi: %hu, Puan: %hu\n", i + 1, ogrenci->aldigiDersler[i].dersAdi, ogrenci->aldigiDersler[i].kredi, ogrenci->aldigiDersler[i].puan);
    }
    printf("------------------------------------------");
}

void printOgrenciList(Ogrenci *ogrenciList, int ogrenciSayisi)
{ // Oluşturulan öğrencileri tuttuğumuz arrayi yazdıran fonksiyon.
    for (int i = 0; i < ogrenciSayisi; i++)
    {
        printf("Ogrenci %d'in bilgileri:\n", i + 1);
        printOgrenci(&ogrenciList[i]);
        printf("\n");
    }
}

float calculateDersOrtalama(char *dersAdi, Ogrenci *ogrenciList, int ogrenciSayisi)
{ // parametre olarak aldığı dersAdi değerine göre bir dersin
  // aritmetik ortalamasını hesaplayıp döndüren fonksiyon.
    float toplamPuan = 0;
    int ogrenciSayisiDersAlan = 0;

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (strcmp(ogrenciList[i].aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                toplamPuan += ogrenciList[i].aldigiDersler[j].puan;
                ogrenciSayisiDersAlan++;
                break;
            }
        }
    }
    if (ogrenciSayisiDersAlan == 0)
    {
        printf("Hata: Bu dersi alan ogrenci bulunamadi.\n");
        return -1;
    }
    return toplamPuan / ogrenciSayisiDersAlan;
}

float calculateDersStandartSapma(char *dersAdi, Ogrenci *ogrenciList, int ogrenciSayisi)
{ // Parametre olarak aldığı dersAdi değerine göre bir
  // dersin standart sapmasını hesaplayıp döndüren fonksiyon.
    float ortalama = calculateDersOrtalama(dersAdi, ogrenciList, ogrenciSayisi);
    if (ortalama == -1)
    {
        return -1;
    }
    float toplamKareFark = 0;
    int ogrenciSayisiDersAlan = 0;

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        for (int j = 0; j < dersSayisi; j++)
        {
            if (strcmp(ogrenciList[i].aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                toplamKareFark += (ogrenciList[i].aldigiDersler[j].puan - ortalama) * (ogrenciList[i].aldigiDersler[j].puan - ortalama);
                ogrenciSayisiDersAlan++;
                break;
            }
        }
    }
    if (ogrenciSayisiDersAlan == 0)
    {
        printf("Hata: Bu dersi alan ogrenci bulunamadi.\n");
        return -1;
    }
    return sqrt(toplamKareFark / ogrenciSayisiDersAlan);
}

float calculateKovaryans(Ders ders1, Ders ders2, Ogrenci *ogrenciList, int ogrenciSayisi)
{ // Parametre olarak aldığı Ders türünden
    // iki dersin kovaryansını hesaplayıp döndüren fonksiyon.
    float ortalamaDers1 = calculateDersOrtalama(ders1.dersAdi, ogrenciList, ogrenciSayisi);
    float ortalamaDers2 = calculateDersOrtalama(ders2.dersAdi, ogrenciList, ogrenciSayisi);

    float toplamKovaryans = 0;
    int ogrenciSayisiDers1Alan = 0;
    int ogrenciSayisiDers2Alan = 0;

    for (int i = 0; i < ogrenciSayisi; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (strcmp(ogrenciList[i].aldigiDersler[j].dersAdi, ders1.dersAdi) == 0)
            {
                float fark1 = ogrenciList[i].aldigiDersler[j].puan - ortalamaDers1;
                for (int k = 0; k < 10; k++)
                {
                    if (strcmp(ogrenciList[i].aldigiDersler[k].dersAdi, ders2.dersAdi) == 0)
                    {
                        float fark2 = ogrenciList[i].aldigiDersler[k].puan - ortalamaDers2;
                        toplamKovaryans += fark1 * fark2;
                        ogrenciSayisiDers1Alan++;
                        ogrenciSayisiDers2Alan++;
                        break;
                    }
                }
                break;
            }
        }
    }

    if (ogrenciSayisiDers1Alan == 0 || ogrenciSayisiDers2Alan == 0)
    {
        printf("Hata: Belirtilen derslerden en az birini alan ogrenci bulunamadi.\n");
        return -1;
    }

    return toplamKovaryans / (ogrenciSayisiDers1Alan - 1);
}

void printYuksekNotAlanOgrenciler(char *dersAdi, Ogrenci *ogrenciList, int ogrenciSayisi)
{ // Parametre olarak aldığı dersAdi değerine göre bir dersin ortalama
    // puanından daha yüksek not almış öğrencileri listeleyen fonksiyon.
    float dersOrtalama = calculateDersOrtalama(dersAdi, ogrenciList, ogrenciSayisi);
    if (dersOrtalama == -1)
    {
        return;
    }
    printf("%s dersinin ortalamasindan daha yuksek not alanlar:\n", dersAdi);
    for (int i = 0; i < ogrenciSayisi; i++)
    {
        for (int j = 0; j < dersSayisi; j++)
        {
            if (strcmp(ogrenciList[i].aldigiDersler[j].dersAdi, dersAdi) == 0)
            {
                if (ogrenciList[i].aldigiDersler[j].puan > dersOrtalama)
                {
                    printf("%s %s\n", ogrenciList[i].ogrAdi, ogrenciList[i].ogrSoyAdi);
                }
                break;
            }
        }
    }
}

void writeOgrenciDosyaya(Ogrenci *ogrenciList, int ogrenciSayisi, char *dosyaAdi)
{ // oluşturulan öğrenci bilgilerini bir dosyaya yazan fonksiyon.
    FILE *filep = fopen(dosyaAdi, "w");
    if (filep == NULL)
    {
        printf("Dosya olusmadi");
    }
    else
    {
        for (int i = 0; i < ogrenciSayisi; i++)
        {
            fprintf(filep, "Ad: %s\nSoyad: %s\nBolum: %s\nNot: %.2f\n\n",
                    ogrenciList[i].ogrAdi, ogrenciList[i].ogrSoyAdi, ogrenciList[i].bolumu, ogrenciList[i].ortalama);
            fprintf(filep, "ALDIGI DERSLER:\n");
            for (int j = 0; j < dersSayisi; j++)
            {
                fprintf(filep, "%s -->> kredi:%hu puani:%hu \n", ogrenciList[i].aldigiDersler[j].dersAdi, ogrenciList[i].aldigiDersler[j].kredi,
                        ogrenciList[i].aldigiDersler[j].puan);
            }
            fprintf(filep, "\n");
        }
        fclose(filep);
        printf("Ogrenci bilgileri dosyaya yazildi...\n\n");
    }
}

void readDosyadanOgrenci(Ogrenci *ogrenciList, int ogrenciSayisi, char *dosyaAdi)
{
    FILE *filep = fopen(dosyaAdi, "r");
    if (filep == NULL)
    {
        printf("Dosya olusmadi");
    }
    else
    {
        printOgrenciList(ogrenciList, ogrenciSayisi);
        for (int i = 0; i < ogrenciSayisi; i++)
        {

            fscanf(filep, "Ad: %s\nSoyad: %s\nBolum: %s\nNot: %f\n\n",
                   ogrenciList[i].ogrAdi, ogrenciList[i].ogrSoyAdi, ogrenciList[i].bolumu, &ogrenciList[i].ortalama);
            fscanf(filep, "ALDIGI DERSLER:\n");
            for (int j = 0; j < dersSayisi; j++)
            {
                fscanf(filep, "%s -->> kredi:%hu puani:%hu \n", ogrenciList[i].aldigiDersler[j].dersAdi, &ogrenciList[i].aldigiDersler[j].kredi,
                       &ogrenciList[i].aldigiDersler[j].puan);
            }

            fscanf(filep, "\n");
        }
        fclose(filep);
        printf("Ogrenci bilgileri dosyadan okundu ve yazdirildi.\n\n");
    }
}

void bellekIadeOgrenci(Ogrenci *ogrenci)
{ // bellek iadesi yapar.
    free(ogrenci->aldigiDersler);
    free(ogrenci->ogrAdi);
    free(ogrenci->ogrSoyAdi);
    free(ogrenci->bolumu);
}

void bellekIadeOgrenciList(Ogrenci *ogrenciList, int ogrenciSayisi)
{ // bellek iadesi yapar.
    for (int i = 0; i < ogrenciSayisi; i++)
    {
        bellekIadeOgrenci(&ogrenciList[i]);
    }
    free(ogrenciList); // Öğrenci dizisinin kendisi için bellek iadesi
}

void bellekIadeDers(Ders *ders)
{ // bellek iadesi yapar.
    free(ders->dersAdi);
}
