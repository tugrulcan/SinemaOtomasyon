#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char kullaniciAdi[5];
    char sifre[5];
}girisBilgisi;

typedef enum{
    Bos,
    Dolu
}eKoltuk;
typedef struct {
    eKoltuk koltuklar[50];
}Seans;

typedef struct {
    char salonAdi[5];
    Seans seanslar[5];
}SalonBilgisi;

typedef enum {
    Ogrenci,
    Tam
}eBiletTipi;
typedef struct{
    int salonID;
    int seansID;
    int koltukID;
    eBiletTipi biletTipi;
}BiletBilgisi;

void gorevliGirisBilgiGuncelle();
void sifrele(char *metin);
void sifreyiCoz(char *sifreliMetin);

void menu();
int girisYap();
void biletSatisiYap();
int doluKoltukSayisiBul(Seans seans);
void biletiKaydet(int salonID, int seansID, int koltukID, eBiletTipi Tip);
void salonBiletKaydet(SalonBilgisi sb, int salonID);
FILE* dosyayiAc(char dosyaAdi[15], char acmaModu[2]);

void salonDolulukBilgileriniYazdir();
void hasilatBilgileriniYazdir();
void dosyalariBaslangicDurumlarinaGetir();
void islemSonrasiMenu();
void menu();
int main()
{
    printf("********** SINEMA OTOMASYONU **********");
    menu();


        return 0;
}
//Her dosya açma isleminde kontrol yapmak yerine burada kontrol ediyoruz.
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

void gorevliGirisBilgiGuncelle()
{
    girisBilgisi gb;
    printf("--------GOREVLI SISTEM GIRIS BILGI GUNCELLEME--------\n");
    printf("Sistem girisi icin;\nKullanici adini giriniz: ");
    gets(gb.kullaniciAdi);
    printf("Sifreyi giriniz: ");
    gets(gb.sifre);


    sifrele(gb.kullaniciAdi);
    sifrele(gb.sifre);

    FILE *pDosya = dosyayiAc("sifre.txt", "w");
    if ( (fwrite(&gb, sizeof(girisBilgisi), 1, pDosya))!= 1  ){
            printf("Gorevli giris bilgilerini guncellerken dosya yazma hatasi!");
    exit(1);
    }else{
        printf("Gorevli giris bilgileri basariyla guncellendi!\n");
    }

    fclose(pDosya);
}
//shifting ile karakterleri sifreleniyor.
void sifrele(char *metin){
    int i = 0;
    while(metin[i] != '\0'){
        metin[i] = metin[i] + 5;
        i++;
    }
}
void sifreyiCoz(char *sifreliMetin){
    int i = 0;
    while(sifreliMetin[i] != '\0'){
        sifreliMetin[i] = sifreliMetin[i] - 5;
        i++;
    }
}
int girisYap()
{
    int girisSonucu = 0;
    girisBilgisi gBilgisi;
    FILE* pDosya = dosyayiAc("sifre.txt", "r");
    fread(&gBilgisi, sizeof(girisBilgisi), 1, pDosya);

    sifreyiCoz(gBilgisi.kullaniciAdi);
    sifreyiCoz(gBilgisi.sifre);
    girisBilgisi kGirdi;

    printf("*********SINEMA OTOMASYON GOREVLI GIRISI*********\n");
    do{
        printf("Kullanici Adi: ");
        gets(kGirdi.kullaniciAdi);
        printf("Parola: ");
        gets(kGirdi.sifre);
    }while( strcmp(gBilgisi.kullaniciAdi, kGirdi.kullaniciAdi) != 0 && strcmp(gBilgisi.sifre, kGirdi.sifre) != 0  );

    girisSonucu = 1;
    fclose(pDosya);
    return girisSonucu;
}

void biletSatisiYap()
{
    printf("********** BILET SATISI **********\n");
    SalonBilgisi sbRed, sbGreen, sbBlue;

    FILE* pDosyaRed = dosyayiAc("SalonRed.txt", "r+");
    FILE* pDosyaGreen = dosyayiAc("SalonGreen.txt", "r+");
    FILE* pDosyaBlue = dosyayiAc("SalonBlue.txt", "r+");

    if(fread(&sbRed, sizeof(SalonBilgisi), 1, pDosyaRed) != 1)
        {
            printf("Red salonun verilerini okurken hata olustu!");
            exit(1);
        }
    if(fread(&sbGreen, sizeof(SalonBilgisi), 1, pDosyaGreen) != 1)
        {
            printf("Green salonun verilerini okurken hata olustu!.");
            exit(1);
        }
    if(fread(&sbBlue, sizeof(SalonBilgisi), 1, pDosyaBlue) != 1)
        {
            printf("Blue salonun verilerini okurken hata olustu!");
            exit(1);
        }
    fclose(pDosyaRed);
    fclose(pDosyaGreen);
    fclose(pDosyaBlue);


    printf("Salonlar:\n1.Red\n2.Green\n3.Blue\n\n");
    printf("Salon kodunu giriniz: ");
    int s1, s2;
    scanf("%d", &s1);
    switch (s1)
    {
        case 1:
            printf("Seans seciminizi giriniz(1-5):");
            scanf("%d", &s2);
            int doluluk = doluKoltukSayisiBul( sbRed.seanslar[s2-1] );
            printf("\n\n%s salonunda,  %d seansi icin dolu koltuk sayisi: %d\n", sbRed.salonAdi, s2, doluluk);
            if( doluluk >= 50 )
            {
                printf("%s salonunda, %d seansinda bos yer kalmamistir!", sbRed.salonAdi, s2);
                islemSonrasiMenu();
            }
            else
                {
                printf("Bilet tipi;\n1.Ogrenci\n2.Tam\nBilet tipini seciniz: ");
                scanf("%d", &s1);
                eBiletTipi tip;
                tip =  (s1==1) ? Ogrenci: Tam ;
                sbRed.seanslar[s2-1].koltuklar[doluluk] = Dolu;
                biletiKaydet(1, s2, doluluk, tip);
                salonBiletKaydet(sbRed,1);
                }
            break;

        case 2:
            printf("Seans seciminizi giriniz(1-5):");
            scanf("%d", &s2);
            doluluk = doluKoltukSayisiBul( sbGreen.seanslar[s2-1] );
            printf("\n\n%s salonunda,  %d seansi icin dolu koltuk sayisi: %d\n", sbGreen.salonAdi, s2, doluluk);
            if( doluluk >= 50 )
            {
                printf("%s salonunda, %d seansinda bos yer kalmamistir!", sbGreen.salonAdi, s2);
                islemSonrasiMenu();
            }
            else
                {
                printf("Bilet tipi;\n1.Ogrenci\n2.Tam\nBilet tipini seciniz: ");
                scanf("%d", &s1);
                eBiletTipi tip;
                tip =  (s1==1) ? Ogrenci: Tam ;
                sbGreen.seanslar[s2-1].koltuklar[doluluk] = Dolu;
                biletiKaydet(2, s2, doluluk, tip);
                salonBiletKaydet(sbGreen,2);
                }
            break;

        case 3:
            printf("Seans seciminizi giriniz(1-5):");
            scanf("%d", &s2);
            doluluk = doluKoltukSayisiBul( sbBlue.seanslar[s2-1] );
            printf("\n\n%s salonunda,  %d seansi icin dolu koltuk sayisi: %d\n", sbBlue.salonAdi, s2, doluluk);
            if( doluluk >= 50 )
            {
                printf("%s salonunda, %d seansinda bos yer kalmamistir!", sbBlue.salonAdi, s2);
                islemSonrasiMenu();
            }
            else
                {
                printf("Bilet tipi;\n1.Ogrenci\n2.Tam\nBilet tipini seciniz: ");
                scanf("%d", &s1);
                eBiletTipi tip;
                tip =  (s1==1) ? Ogrenci: Tam ;
                sbBlue.seanslar[s2-1].koltuklar[doluluk] = Dolu;
                biletiKaydet(3, s2, doluluk, tip);
                salonBiletKaydet(sbBlue,3);
                }
            break;
    }


    fclose(pDosyaRed);
    fclose(pDosyaGreen);
    fclose(pDosyaBlue);
}
int doluKoltukSayisiBul(Seans seans)
{
    int s = 0;
    int i;
    for (i = 0; i<50; i++){
        if(seans.koltuklar[i] == Dolu)
            s++;
        else break;
    }
    return s;
}
void biletiKaydet(int salonID, int seansID, int koltukID, eBiletTipi Tip)
{
    FILE* pDosyaBilet = dosyayiAc("satilanBiletler.txt", "a+");
    BiletBilgisi satilanBilet;
    satilanBilet.salonID = salonID;
    satilanBilet.seansID = seansID;
    satilanBilet.koltukID = koltukID;
    satilanBilet.biletTipi = Tip;

    if(fwrite(&satilanBilet, sizeof(BiletBilgisi), 1, pDosyaBilet) != 1){
        printf("Satilan bilet yazma hatasi!");
        exit(1);
    }else {
        printf("\nBilet kaydedildi.\n");
    }
}

void salonBiletKaydet(SalonBilgisi sb, int salonID)
{
    FILE* pSalonDosya;
    switch(salonID)
    {
        case 1:
            pSalonDosya = dosyayiAc("SalonRed.txt","w+");
            if( fwrite(&sb, sizeof(SalonBilgisi), 1, pSalonDosya) != 1 )
                {
                    printf("Bilet bilgisi, %s salona yazarken hata oldu!", sb.salonAdi);
                    exit(1);
                }
                else {
                    printf("Bilet, %s salonunun dosyasina kaydedildi.\n", sb.salonAdi);
                        fclose(pSalonDosya);

                }
            break;
            case 2:
            pSalonDosya = dosyayiAc("SalonGreen.txt","w+");
            if( fwrite(&sb, sizeof(SalonBilgisi), 1, pSalonDosya) != 1 )
                {
                    printf("Bilet bilgisi, %s salona yazarken hata oldu!", sb.salonAdi);
                    exit(1);
                }
                else {

                    printf("Bilet, %s salonunun dosyasina kaydedildi.\n", sb.salonAdi);
                        fclose(pSalonDosya);
              }
            break;
            case 3:
            pSalonDosya = dosyayiAc("SalonBlue.txt","w+");
            if( fwrite(&sb, sizeof(SalonBilgisi), 1, pSalonDosya) != 1 )
                {
                    printf("Bilet bilgisi, %s salona yazarken hata oldu!", sb.salonAdi);
                    exit(1);
                }
                else {

                    printf("Bilet, %s salonunun dosyasina kaydedildi.\n", sb.salonAdi);
                        fclose(pSalonDosya);
              }
            break;

    }
}
void salonDolulukBilgileriniYazdir()
{
    printf("\n********** SALON DOLULUK BILGILERI **********\n");
    SalonBilgisi sbRed, sbGreen, sbBlue;

    FILE* pDosyaRed = dosyayiAc("SalonRed.txt", "r+");
    FILE* pDosyaGreen = dosyayiAc("SalonGreen.txt", "r+");
    FILE* pDosyaBlue = dosyayiAc("SalonBlue.txt", "r+");

    if(fread(&sbRed, sizeof(SalonBilgisi), 1, pDosyaRed) != 1)
        {
            printf("Red salonun verilerini okurken hata olustu!");
            exit(1);
        }
    if(fread(&sbGreen, sizeof(SalonBilgisi), 1, pDosyaGreen) != 1)
        {
            printf("Green salonun verilerini okurken hata olustu!.");
            exit(1);
        }
    if(fread(&sbBlue, sizeof(SalonBilgisi), 1, pDosyaBlue) != 1)
        {
            printf("Blue salonun verilerini okurken hata olustu!");
            exit(1);
        }
    fclose(pDosyaRed);
    fclose(pDosyaGreen);
    fclose(pDosyaBlue);
    printf("Red Salonu;\n");
    int i;
    for (i= 0 ; i< 5; i++)
    {
        printf("%d seansi, izleyici sayisi: %d\n", i+1, doluKoltukSayisiBul(sbRed.seanslar[i]));
    }
    printf("\nGreen Salonu;\n");
    for (i= 0 ; i< 5; i++)
    {
        printf("%d seansi, izleyici sayisi: %d\n", i+1, doluKoltukSayisiBul(sbGreen.seanslar[i]));
    }
        printf("\bBlue Salonu;\n");
    for (i= 0 ; i< 5; i++)
    {
        printf("%d seansi, izleyici sayisi: %d\n", i+1, doluKoltukSayisiBul(sbBlue.seanslar[i]));
    }
}

void hasilatBilgileriniYazdir()
{
    printf("\n********** HASILAT BILGILERI **********\n");
    FILE* pSatilanBiletler = dosyayiAc("satilanBiletler.txt", "r");
    BiletBilgisi bb;
    int tamBiletSayisi = 0, ogrenciBiletSayisi=0;
    while ( fread(&bb, sizeof(BiletBilgisi), 1, pSatilanBiletler) == 1 )
    {
        if(bb.biletTipi == Ogrenci) ogrenciBiletSayisi++;
        else if (bb.biletTipi == Tam) tamBiletSayisi++;
    }
    fclose( pSatilanBiletler);

    printf("\n\nSatilan;\nOgrenci bileti sayisi: %d\nTam bilet sayisi:%d\n\nToplam hasilat: %d tl",
            ogrenciBiletSayisi, tamBiletSayisi, ((ogrenciBiletSayisi*20) + (tamBiletSayisi*30)) );
    FILE* pDosyaHasilat = dosyayiAc("toplamHasilat.txt", "a+");
    fprintf(pDosyaHasilat,"Satilan;\nOgrenci bileti sayisi: %d\nTam bilet sayisi:%d\n\nToplam hasilat: %d tl",
            ogrenciBiletSayisi, tamBiletSayisi, ((ogrenciBiletSayisi*20) + (tamBiletSayisi*30)) );
            fclose(pDosyaHasilat);
}
void dosyalariBaslangicDurumlarinaGetir()
{
        SalonBilgisi sbRed, sbGreen, sbBlue;

    int t = 0 ;
    for (t = 0; t < 5 ; t++){
        sbRed.salonAdi[t] = '\0';
        sbGreen.salonAdi[t] = '\0';
        sbBlue.salonAdi[t] = '\0';
    }

    strcpy(sbRed.salonAdi, "Red");
    strcpy(sbGreen.salonAdi,"Green");
    strcpy(sbBlue.salonAdi, "Blue");

    int i, j;
     for(i = 0; i< 5 ; i++ ){
        for(j= 0; j < 50; j++){
            sbRed.seanslar[i].koltuklar[j] = Bos;
            sbGreen.seanslar[i].koltuklar[j] = Bos;
            sbBlue.seanslar[i].koltuklar[j] = Bos;
        }
     }

    FILE* pDosyaRed = dosyayiAc("SalonRed.txt", "w+");
    FILE* pDosyaGreen = dosyayiAc("SalonGreen.txt", "w+");
    FILE* pDosyaBlue = dosyayiAc("SalonBlue.txt", "w+");


    if(fwrite(&sbRed, sizeof(SalonBilgisi), 1, pDosyaRed) != 1)
        {
            printf("red sifirlama hata.");
            exit(1);
        }
    if(fwrite(&sbGreen, sizeof(SalonBilgisi), 1, pDosyaGreen) != 1)
        {
            printf("green sifirlama hata.");
            exit(1);
        }
    if(fwrite(&sbBlue, sizeof(SalonBilgisi), 1, pDosyaBlue) != 1)
        {
            printf("blue  sifirlama hata.");
            exit(1);
        }

    FILE* pDosyaHasilat = dosyayiAc("toplamHasilat.txt", "w+");
    FILE*  pDosyaSatilan = dosyayiAc("satilanBiletler.txt", "w+");
    fclose(pDosyaRed);
    fclose(pDosyaGreen);
    fclose(pDosyaBlue);
    fclose(pDosyaHasilat);
    fclose(pDosyaSatilan);

    printf("Dosyalarin icerikleri silindi.");
}

void islemSonrasiMenu()
{
    int secim = 0;
    do {
        printf("\n\n\n\n**************************************\n1. Ana menu\n");
        printf("2. Programdan Cikis\nSeciminiz: ");
        scanf("%d", &secim);
    }while(secim < 0 && secim >3);
    if(secim == 1)
        menu();
    else
    {
        printf("Programdan cikiliyor.");
        exit(1);
    }

}
void menu(){

    printf("\n\n\n***************  MENU  ****************\n\n");
        int secim = 0;
    do {
        printf("\n1.Bilet Satisi\n");
    printf("2.Hasilat Bilgisini Goruntule\n");
    printf("3.Salonlarin Doluluk Bilgisi Goruntule\n");
    printf("4.Otomasyon Giris Bilgierini Guncelle\n");
    printf("5.Kayit Dosyalarini Sil ve Yeniden Olustur\n");
    printf("6. Cikis\n");
    printf("Seciminiz: ");
    scanf("%d", &secim);
    } while(secim < 1 && secim >6);

    switch(secim)
    {
    case 1:
        biletSatisiYap();
        islemSonrasiMenu();

        break;
    case 2:
        hasilatBilgileriniYazdir();
        islemSonrasiMenu();
        break;
    case 3:
        salonDolulukBilgileriniYazdir();
        islemSonrasiMenu();
        break;
    case 4:
        gorevliGirisBilgiGuncelle();
        islemSonrasiMenu();
        break;
    case 5:
        dosyalariBaslangicDurumlarinaGetir();
        islemSonrasiMenu();
        break;
    case 6:
        printf("program sonlandiriliyor...");
        exit(1);
    default:
        printf("Hatali secim.");
        exit(1);
        break;
    }
}
