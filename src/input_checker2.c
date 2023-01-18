//"at-eee" Jakub M.
//sluzy do sprawdzania inputu dla programu testing.sh

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char** argv) {

    FILE *fptr1;
    
    fptr1 = fopen(argv[1], "r");
    
    char word[5];
    
    int i = 0, x;

    fscanf(fptr1, "%s", word);

    while(word[i] != '\0' && i < 6){
            
            if(!isdigit(word[i])){
                printf("Blad!!! w pierwszej linii pliku %s podano nieprawidlowy znak!\n", argv[1]);
                return 53;
            }
            
            i++;
    }

    i = 0;
    
    while(fscanf(fptr1, "%s", word) != EOF){
        
        i = 0;
        
        while(word[i] != '\0' && i < 6){
	    //macierz prawda/falsz wyjasniona slownie (by rozjasnic troche co dzieje sie w warunku instrukcji if):
	    ////
            //jezeli znak o indeksie "i" nie jest cyfra, ani nie jest jedna z liter: A, B, C
	    //lub jest litera A, B lub C, ALE indeks "i" jest wyzszy od 0 (to znaczy wyraz sklada sie z wiecej
            //niz jednego znaku), to: *zwroc blad*.
            if((!isdigit(word[i]) && word[i] != 'A' && word[i] != 'B' && word[i] != 'C')
               ||((word[i] == 'A' || word[i] == 'B' || word[i] == 'C') && i > 0 )){
                printf("Blad!!! w pliku %s w parametrach podano nieprawidlowy znak!\n", argv[1]);
                return 53;
            }
            
            i++;
        }
    
    
    }
    
    fclose(fptr1);

    return 0;
}
