#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void gorevliGirisBilgiEkle();
void girisYap();
FILE* dosyayiAc(char dosyaAdi[15], char acmaModu[2]);
typedef struct{
    char kullaniciAdi[15];
    char sifre[15];
}girisBilgisi;

int main()
{
    gorevliGirisBilgiEkle();

        return 0;
}
//Her dosya açma iþleminde kontrol yapmak yerine burada kontrol ediyoruz.
FILE* dosyayiAc(char dosyaAdi[15], char acmaModu[2])
{
    FILE *pDosya;
    pDosya = fopen(dosyaAdi, acmaModu);
    if(pDosya == NULL)
    {
        printf("Dosya: %s , %s modunda acilirken hata olustu.", dosyaAdi, acmaModu);
        exit(1);
    }

    return pDosya;
}


void gorevliGirisBilgiEkle()
{
    girisBilgisi gb;
    printf("--------GOREVLI SISTEM GIRIS BILGI EKLEME--------\n");
    printf("Sistem girisi icin;\nKullanici adini giriniz: ");
    gets(gb.kullaniciAdi);
    printf("Sifreyi giriniz: ");
    gets(gb.sifre);


}
void girisYap()
{
    int girisSonucu = 0;
    girisBilgisi gBilgisi;
    FILE* pDosya = dosyayiAc("sifre.txt", "r");
    if( (fread(&gBilgisi, sizeof(girisBilgisi), 1, pDosya)) != 1 )
    {
        printf("Kullanici adi ve sifreyi dosyadan okurken hata olustu!");
        exit(1);
    }





    fclose(pDosya);
}
