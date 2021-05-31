#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct{
    int parkurUzunlugu;
    int engelSayisi;
    int *engeller;
}Xurvivor;
void parkurDuzeni(Xurvivor *parkur);
void bubbleSort(int *pointerr, int size);
void swap(int *Ptr1, int *Ptr2);
void dosyayaYazma(Xurvivor *parKur);
int AralarindaAsalMi(int *EngelNoktasi, int HP);
int main()
{
    Xurvivor Parkur;
    parkurDuzeni(&Parkur);
    bubbleSort(&Parkur.engeller[0],Parkur.engelSayisi);
    dosyayaYazma(&Parkur);
    free(Parkur.engeller);  //Engel Sayisi * 4byte kadar ayrilan bellek geri veriliyor.
    return 0;
}
void parkurDuzeni(Xurvivor *parkur){
    int i;
    srand(time(NULL));
    parkur->parkurUzunlugu = 50 + rand()%51;  // [50-100] arasindaki parkur uzunlugu belirleniyor.
    parkur->engelSayisi = 2 + rand()%4;  // [2-5] aralýgýndaki engel sayisi belirleniyor.
    parkur->engeller = (int*)malloc(sizeof(int)*(parkur->engelSayisi));  //Engellerin tutulacagý dinamik bir dizi oluþturuluyor.
    for(i=0; i<parkur->engelSayisi; i++)
        parkur->engeller[i] = 5 + rand()%(parkur->parkurUzunlugu - 4);  //[5-parkuruzunlugu] araligindaki engel noktalari olusturuluyor.
}
void bubbleSort(int *pointerr, int size){   //Kabarcik Siralamasi yapiliyor
    int i,j;
    for(i=0;i<size-1;i++)
        for(j=0;j<size-1;j++)
            if(pointerr[j]>pointerr[j+1])
                swap(&pointerr[j],&pointerr[j+1]);
}
void swap(int *Ptr1, int *Ptr2){  //Takas yapiliyor
    int temp=*Ptr1;
    *Ptr1=*Ptr2;
    *Ptr2=temp;
}
void dosyayaYazma(Xurvivor *parKur){
    int i,HP=100;
    FILE *DosyaPtr;
    if( (DosyaPtr = fopen("log.txt","w")) == NULL ) //Dosya acilma kontrolu yapiliyor.
    {
        printf("log.txt dosyasi acilamadi!");
        exit(1);
    }
    fprintf(DosyaPtr,"Yarisma Basladi !!!\nYarismaci HP = %d\n",HP);
    for(i=0; i<parKur->engelSayisi; i++)
        if( AralarindaAsalMi(&parKur->engeller[i],HP) ) //Her engel noktasi icin HP degeri ile aralarinda asallik kontrolu yapiliyor.
        {
            fprintf(DosyaPtr,"Yarismaci %d. metreye kadar bir engelle karsilasmadi\n",parKur->engeller[i]);
            fprintf(DosyaPtr,"%d. metrede bir engel var.\t %d ve %d aralarinda asaldir\n",parKur->engeller[i],HP,parKur->engeller[i]);
            HP -= parKur->engeller[i];
            fprintf(DosyaPtr,"Yarismaci HP = %d\n",HP);
            if(HP<=0)
            {
                    fputs("Uzgunum!!! yarismayi tamamlayamadin.\n",DosyaPtr);
                    fclose(DosyaPtr); //Dosya kapatiliyor.
                    free(parKur->engeller); //Ramden Engelsayisi*4byte kadar ayrilan bellek geri birakiliyor.
                    exit(1);
            }
        }
        else
        {
            fprintf(DosyaPtr,"Yarismaci %d. metreye kadar bir engelle karsilasmadi\n",parKur->engeller[i]);
            fprintf(DosyaPtr,"%d. metrede bir engel var.\t %d ve %d aralarinda asal degildir\n",parKur->engeller[i],HP,parKur->engeller[i]);
            fprintf(DosyaPtr,"Yarismaci HP = %d\n",HP);
        }
    fprintf(DosyaPtr,"Yarismaci %d. metreye kadar bir engelle karsilasmadi\nTebrikler!!! Yarismayi %d HP ile bitirdiniz.",parKur->parkurUzunlugu,HP);
    fclose(DosyaPtr);   //Dosya kapatiliyor.
}
int AralarindaAsalMi(int *EngelNoktasi, int HP){
    int i,tut;
    if( HP > (*EngelNoktasi) ) //For kucuk olana kadar donecek bunun icin kontrol yapiliyor
        tut = (*EngelNoktasi);
    else tut = HP;

    for(i=2; i <= tut; i++)  //HP ve EngelNoktasi arasinda ortak bolen kontolu icin olusturuluyor.
        if( (*EngelNoktasi%i == 0) && (HP%i == 0) )
            return 0;  //HP ve EngelNoktasi aralarinda asal degil ise fonksiyonun cagirildigi if blogu calismayacak else calisacak.
        return 1;  //HP ve EngelNoktasi aralarinda asal ise fonksiyon 1 return edecek ve fonksiyonun cagirildigi if blogu calisacak.
}
