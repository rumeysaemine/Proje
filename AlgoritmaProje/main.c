#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


const char matrix_bigram_strings[10][3] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};

const char matrix_trigram_strings[10][4]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};


//Ingilizce dilinin frekans degerleri
const float frequency_eng[20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.01, 0.01, 0.01, 0.01, 1.81, 0.73, 0.72, 0.42, 0.42, 0.01, 0.01, 0.01, 0.01, 0.01 };
//Almanca dilinin frekans degerleri
const float frequency_germ[20]={ 0.01, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.01, 0.01, 0.01, 0.01, 0.01, 1.04, 0.76, 0.75, 0.72, 0.62 };

float calculated_frequencies[20];
float distances [2]={0,0};

int counter[20];
int a,b,c,k,sayac=0;


// 1.ASAMA:Kullanicidan alinan metni temizleyen fonksiyonu tanimladik
void filter_str(char str[])
{
    for(int i=0; i<strlen(str); i++)                  //Metindeki tüm karakterleri kontrol eden dongu.
    {
        if(!((str[i]>=65 & str[i]<=90)||(str[i]>=97 & str[i]<=122)))
            str[i] = ' ';
    }
}

// 2.ASAMA:Bigramlarin frekanlarini hesaplayan fonksiyonu tanimladik
void calculate_frequencies_bi(char str[])
{
    int m=strlen(str);
    for(b=0;b<10;b++)                                 //matrix_bigram_strings dizisindeki her bir bigram(10 tane) icin olusturdugumuz dongu
    {
        sayac = 0;

        for(a=0;a<strlen(str);a++)                    //metindeki karakterler icin olusturdugumuz dongu
        {
            for(c=0;c<2;c++)                          //Her bir bigramda bulunan 2 karakter icin olusturdugumuz dongu
            {
                if(str[a] != matrix_bigram_strings[b][c])
                    break;
                if((str[a]==matrix_bigram_strings[b][c])&&(str[a+1]==matrix_bigram_strings[b][c+1]))
                    {
                        sayac +=1;                    //Dongu yardimiyla her bir bigramin metinde kac kez gectigini hesapladik
                    }
            }
        }
        counter[b]=sayac;                             //Her bir bigramin metinde gecme miktarini tutan dizi
        calculated_frequencies[b]=sayac*2*100/m;      //Bigramlarin frekanlarini hesaplayarak diziye yerlestirdik
    }

    // Bigramlarin frekanslarini ekrana yazdirdik
	printf("Bigramlarin Frekanslari:\n");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<2;j++)
        {
            printf("%c",matrix_bigram_strings[i][j]);
        }
        printf(" = %d\n",counter[i]);
    }

    // Bigramlarin frekans yuzdesini ekrana yazdirdik
	printf("\nBigramlarin Frekans Yuzdesi:\n");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<2;j++)
        {
            printf ("%c",matrix_bigram_strings[i][j]);
        }
        printf(" = %.2f \n",calculated_frequencies[i]/100);
	}
}

//3.ASAMA:Trigramlarin frekanslarini hesaplayan foksiyonu tanimladik
void calculate_frequencies_tri(char str[])
{
    int m=strlen(str);
	for(b=0;b<10;b++)                                 //matrix_trigram_strings dizisindeki her bir trigram(10 tane) icin olusturdugumuz dongu
    {
        sayac = 0;

        for(a=0;a<strlen(str);a++)                    //metindeki karakterler icin olusturdugumuz dongu
        {
            for(c=0;c<3;c++)                          //Her bir trigramda bulunan 3 karakter icin olusturdugumuz dongu
            {
                if(str[a] != matrix_trigram_strings[b][c])
                    break;
                if((str[a]==matrix_trigram_strings[b][c])&&(str[a+1]==matrix_trigram_strings[b][c+1])& str[a+2]==matrix_trigram_strings[b][c+2])
                    {
                        sayac +=1;                    //Dongu yardimiyla her bir trigramin metinde kac kez gectigini hesapladik
                    }
            }
        }
        counter[b+10]=sayac;                          //counter[b+10]--->Dizinin 10.indisinden baslayarak elemanlari yerlestirdik
        calculated_frequencies[b+10]=sayac*3*100/m;
    }

    //Trigramlarin frekanslarini ekrana yazdirdik
    printf("Trigramlarin Frekanslari:\n");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf ("%c",matrix_trigram_strings[i][j]);
        }
        printf(" = %d\n",counter[i+10]);
    }

    //Trigramlarin frekans yuzdesini ekrana yazdirdik
    printf("\nTrigramlarin Frekans Yuzdesi:\n");
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<3;j++)
        {
            printf ("%c",matrix_trigram_strings[i][j]);
        }
        printf(" = %.2f \n",calculated_frequencies[i+10]/100);
    }
}

//4.ASAMA:Frekans matrisleri arasinda uzaklik hesabi yapan fonksiyonu tanimladik
void calculate_distances(float mesafe[],int z)
{
    float toplam=0.0;
    float toplam2=0.0;

    for(int i=0;i<20;i++)
    {
        toplam+=pow(frequency_eng[i]-calculated_frequencies[i],2.0);                     // Ingilizce icin oklid bagintisiyla uzaklik hesapladik
    }
    mesafe[0]=sqrt(toplam);

    for(int i=0;i<20;i++)
    {
        toplam2+=pow(frequency_germ[i]-calculated_frequencies[i],2.0);                   // Almanca icin oklid bagintisiyla uzaklik hesapladik
    }
    mesafe[1]=sqrt(toplam2);
}

//5.ASAMA:Metnin yazildigi dili tahmin eden fonksiyonu tanimladik
void detect_lang(float fark1,float fark2)
{
    if (fark1<fark2)                                  //Uzaklik degerlerini karsilastirdik
        printf("INGILIZCE");

    else
        printf("ALMANCA");
}


int main()
{
    char metin[10000];
    printf("\n***GIRDIGINIZ METNIN HANGI DILDE YAZILDIGI TAHMIN EDILECEKTIR(INGILIZCE/ALMANCA)***");
    printf("\n\nMetni giriniz: \n");
    gets(metin);

    //1.Fonksiyon
    filter_str(metin);

    for(int i=0;i<strlen(metin);i++)                  //Metinde bulunan tum harfleri kucuk harfe cevirmesi icin olusturdugumuz dongu
        metin[i]=tolower(metin[i]);

    printf("\nMetin Ciktisi: \n");
    puts(metin);

    printf("\n\n\n***********************************************************************\n");
    printf("***********************************************************************\n\n\n");

    //2.Fonksiyon
    calculate_frequencies_bi(metin);

    printf("\n\n\n***********************************************************************\n");
    printf("***********************************************************************\n\n\n");

    //3.Fonksiyon
    calculate_frequencies_tri(metin);

    printf("\n\n\n***********************************************************************\n");
    printf("***********************************************************************\n\n\n");

    //4.Fonksiyon
    calculate_distances(distances,2);

    //calculated_frequencies dizisinin elemanlarini ekrana yazdirdik
    printf("calculated_frequencies dizisinin elemanlari:\n\n");
    for(int i=0;i<20;i++)
        printf("%.2f  ",calculated_frequencies[i]/100);
    printf("\n\n****************\n\n");

    //distances dizisinin elemanlarini ekrana yazdirdik
    printf("distances dizisinin elemanlari:\n\n");
    for(int i=0;i<2;i++)
        printf("%.2f  ",distances[i]);

    printf("\n\n\n***********************************************************************\n");
    printf("***********************************************************************\n\n\n");

	//5.Fonksiyon
    printf("Tahmin Edilen Dil:");
    detect_lang(distances[0],distances[1]);           //Fonksiyona parametre olarak distances dizisinin elemanlarini verdik

    printf("\n\n\n***********************************************************************\n");
    printf("***********************************************************************\n\n\n");

    return 0;
}
