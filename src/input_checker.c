//"at-eee" Jakub M.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char** argv) {

    FILE *fptr1;
    
    fptr1 = fopen(argv[1], "r");
    
    char word[4];
    
    int i, x;
    
    while(fscanf(fptr1, "%s", word) != EOF){
        
        i = 0;
        
        while(word[i] != '\0'){
            
            if(word[i] != 'A' && !isdigit(word[i])){
                printf("Blad!!! w %s podano nieprawidlowy znak!\n", argv[1]);
                return 3;
            }
            
            i++;
        }
    
    
    }
    
    fclose(fptr1);

    return 0;
}

