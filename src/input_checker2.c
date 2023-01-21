//"at-eee" Jakub M.
//sluzy do sprawdzania inputu dla programu testing.sh

#define MAKS_ILOSC_ZNAKOW 5+1
#define NAZWA_PLIKU argv[1]
//5+1, bo 5 znakow + 1 znak '\0' (tzw. "termination special character").

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv) {

    FILE *fptr1;
    
    fptr1 = fopen(NAZWA_PLIKU, "r");
    
    char word[MAKS_ILOSC_ZNAKOW]; //"slowo"
    
    int i = 0;

    //sprawdzenie nr 1: czy wejscie podane przez uzytkownika posiada nieprawidlowy znak.

    fscanf(fptr1, "%s", word);

    while(word[i] != '\0' && i < MAKS_ILOSC_ZNAKOW+1){//przerwij jak tylko petla dojdzie do "znaku terminacji" badz gdy przekroczy dlugosc tablicy word.
            
            if(!isdigit(word[i])){
                printf("Blad!!! w pierwszej linii pliku %s podano nieprawidlowy znak!\nPrzerywam dzialanie programu.\n", NAZWA_PLIKU);
                return 1;
            }
            
            i++;
    }

    i = 0;

    char previous_word[MAKS_ILOSC_ZNAKOW]; //poprzednie "slowo"

    strcpy(previous_word, word);
    
    while(fscanf(fptr1, "%s", word) != EOF){
        
        i = 0;
        
        while(word[i] != '\0' && i < MAKS_ILOSC_ZNAKOW+1){//przerwij jak tylko petla dojdzie do "znaku terminacji" badz gdy przekroczy dlugosc tablicy word.
	    //macierz prawda/falsz wyjasniona slownie (by rozjasnic troche co dzieje sie w warunku instrukcji if):
	    ////
			//jezeli znak o indeksie "i" nie jest cyfra, ani nie jest jedna z liter: A, B, C
			//lub: jest litera A, B lub C, ALE indeks "i" jest wyzszy od 0 (to znaczy wyraz sklada sie z wiecej niz jednego znaku),
			//lub: 2 slowa wystepujace tuz po sobie sa literami (a nie litera i liczba, badz dwiema liczbami),
			//to: *zwroc blad*.
            if(  (!isdigit(word[i]) && word[i] != 'A' && word[i] != 'B' && word[i] != 'C')
			   ||((word[i] == 'A' || word[i] == 'B' || word[i] == 'C') && i > 0)
			   ||(isalpha(previous_word[0]) && isalpha(word[0]))  ){
                printf("Blad!!! w pliku %s w parametrach podano nieprawidlowy znak badz litery w dwoch parametrach wystepujacych tuz po sobie!!!\nPrzerywam dzialanie programu.\n", NAZWA_PLIKU);
                return 1;
            }
            
            i++;
        }

		strcpy(previous_word, word);
    
    }
    
    fclose(fptr1);

	//sprawdzenie nr 2: czy w wejsciu zazadano permutacji przekraczajacej mozliwosci programu.
	
	fptr1 = fopen(argv[1], "r");
	
	fscanf(fptr1, "%s", word); //pomin/zignoruj pierwsza linie pliku wejsciowego.
	
	char type_of_test = '0'; //z jakim typem testu mamy "do czynienia".
	int dlugosc_permutacji;
	char already_checked_length = 0; //(ma imitowac bool'a) zabezpieczenie dla testu typu B.
	
	while(fscanf(fptr1, "%s", word) != EOF){
		
		if(type_of_test == 'A'){
			
			dlugosc_permutacji = atoi(word);
			
			if(dlugosc_permutacji > 9){
				
				printf("Blad!!! Uzytkownik zazadal do testowania permutacji o dlugosci przekraczajacej mozliwosci programu \"perm.sh\" (t.j: o liczbie elementow wiekszej niz 9)!!!\n");
				return 2;
			}

		}else if(type_of_test == 'B' && already_checked_length == 0){

			dlugosc_permutacji = atoi(word);
			
			if(dlugosc_permutacji > 9){
				
				printf("Blad!!! Uzytkownik zazadal do testowania permutacji o dlugosci przekraczajacej mozliwosci programu \"perm.sh\" (t.j: o liczbie elementow wiekszej niz 9)!!!\n");
				return 2;
			}

			already_checked_length++;
		}
		
		if(word[0] == 'A' || word[0] == 'B' || word[0] == 'C'){
			
			type_of_test = word[0];
			already_checked_length = 0;
			
		}
       
	}

    return 0;
}
