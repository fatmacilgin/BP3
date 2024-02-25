/*
 * main.c
 * veriler oluşturulup fonksiyonların testini yapar.
 * Proje-1
 * 8.12.2023
 * Fatma zehra ÇILGIN
 */
#include "Proje1.h"
#include <stdio.h>

int main(int argc, char *argv[])
{

   Ders Ogr1Ders1 = createDers("Matematik", 3, 60);
   Ders Ogr1Ders2 = createDers("Fizik", 4, 40);
   Ders Ogr1Ders3 = createDers("Kimya", 5, 80);
   Ders ogr1[3] = {Ogr1Ders1, Ogr1Ders2, Ogr1Ders3};

   Ogrenci ogrenci1 = createOgrenci("Ibrahim", "Tatlises", "Bilgisayar Muhendisligi", ogr1);

   Ders Ogr2Ders1 = createDers("Matematik", 3, 30);
   Ders Ogr2Ders2 = createDers("Fizik", 4, 60);
   Ders Ogr2Ders3 = createDers("Kimya", 5, 30);
   Ders ogr2[3] = {Ogr2Ders1, Ogr2Ders2, Ogr2Ders3};

   Ogrenci ogrenci2 = createOgrenci("Hakan", "Altun", "Elektrik Muhendisligi", ogr2);

   Ders Ogr3Ders1 = createDers("Matematik", 3, 90);
   Ders Ogr3Ders2 = createDers("Fizik", 4, 20);
   Ders Ogr3Ders3 = createDers("Kimya", 5, 50);
   Ders ogr3[3] = {Ogr3Ders1, Ogr3Ders2, Ogr3Ders3};

   Ogrenci ogrenci3 = createOgrenci("Ferdi", "Ozbegen", "Endustri Muhendisligi", ogr3);

   // Ogrenci* ogrenciList = (Ogrenci*)malloc(ogrenciSayisi * sizeof(Ogrenci));

   Ogrenci ogrenciList[3] = {ogrenci1, ogrenci2, ogrenci3};
   int ogrenciSayisi = sizeof(ogrenciList) / sizeof(ogrenciList[0]);

   printOgrenci(&ogrenci1);
   printf("\n");

   printOgrenci(&ogrenci2);
   printf("\n");

   printOgrenci(&ogrenci3);
   printf("\n");

   printOgrenciList(ogrenciList, ogrenciSayisi);
   printf("\n");

   float matematikOrtalama = calculateDersOrtalama("Matematik", ogrenciList, ogrenciSayisi);
   printf("Matematik Dersinin Ortalamasi: %.2f\n", matematikOrtalama);
   printf("-----------------------------------\n");


   float fizikStandartSapma = calculateDersStandartSapma("Fizik", ogrenciList, ogrenciSayisi);
   printf("Fizik Dersinin Standart Sapmasi: %.2f\n", fizikStandartSapma);
    printf("-----------------------------------\n");

   float kovaryans = calculateKovaryans(Ogr2Ders1, Ogr2Ders2, ogrenciList, ogrenciSayisi);
   printf("Matematik ve Fizik dersinin Kovaryansi: %.2f\n", kovaryans);
    printf("-----------------------------------\n");

   printYuksekNotAlanOgrenciler("Fizik", ogrenciList, ogrenciSayisi);
    printf("-----------------------------------\n");

   writeOgrenciDosyaya(ogrenciList, ogrenciSayisi, argv[1]);

   if (argc != 2)
   {
      fprintf(stderr, "Kullanim: %s <dosya_adi>\n", argv[0]);
   }
   readDosyadanOgrenci(ogrenciList, ogrenciSayisi, argv[1]);

   bellekIadeOgrenciList(ogrenciList, ogrenciSayisi);

   return 0;
}