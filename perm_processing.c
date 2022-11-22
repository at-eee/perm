//"at-eee" Jakub Malinowski
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define newline fprintf(fptr2, "\n")
#define tabulator fprintf(fptr2, "\t")
#define domyslne_parametry FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length

//[ENG] Warning! comments are mixed with both polish and english language as of yet.
//[PL] Uwaga! Póki co język używany w komentarzach jest przeplatany między polskim i angielskim.

//functions described in more detail under the end of the "main" scope.
long long int silnia(int permutaion_length);
void/*"char*"?*/ base_permutation2(FILE *fptr2, int permutation_length);
void permutation_case(domyslne_parametry, int permutation_amount, char flag);
//funkcje wypisujace do plikow:
void write_two_line_notation(domyslne_parametry);
void write_one_line_notation(domyslne_parametry);
void write_cycle_notation(domyslne_parametry);
void write_square_of_permutation(domyslne_parametry);
//"podfunkcja" funkcji write_square_of_permutation:
void compute_composition(int permutation[], int composed_permutation[], int permutation_length);

char base_permutation[100];

int main() {

    
    int permutation[100];
    int permutation_length;
    char permutation_type[4] = {' '};
    
    FILE *fptr1;
    
    fptr1 = fopen("data.txt", "r");
    
    fscanf(fptr1, "%d", &permutation_length);
    fscanf(fptr1, "%s", permutation_type);
    int permutation_amount;
    
    FILE *fptr2;
    
    fptr2 = fopen("result.out"/*"wygenerowane_permutacje.tex"*/, "a");
    
    switch(permutation_type[0]){
    
        case 'A':
            
            permutation_amount = NULL;
            
            permutation_case(fptr1, fptr2, permutation, permutation_length, permutation_amount, 0);
            
            break;
        
        default:
        
            permutation_amount = atoi(permutation_type);           
            
            permutation_case(fptr1, fptr2, permutation, permutation_length, permutation_amount, 1);
            
            break;
        
    }
    
    fclose(fptr1);
    fclose(fptr2);
    
    return 0;
}

long long int silnia(int permutaion_length){

    long long int n = 1;
    
    for(int i = 1; i <= permutaion_length; i++) n *= i;
    
    return n;

}

void base_permutation2(FILE *fptr2, int permutation_length){//writes base permutation i. e: prints first "row" of the two-line notation's permutation to char base_permutation[].
    
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", i+1); if(i!=permutation_length-1) fprintf(fptr2, "& ");}

}

//wypisuje output do pliku, w zaleznosci od tego co podał użytkownik na wejściu (case'a, który został wybrany).
void permutation_case(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length, int permutation_amount, char perm_case){

    
        long long int zakres_petli;
        
        fprintf(fptr2, "\\subsection*{Wygenerowana permutacja nr 1:}\n");
        
        if(perm_case == 0){
            fprintf(fptr2, "\\subsection*{Uzytkownik zazadal wypisania wszystkich mozliwych\\\\ permutacji %d-elementowych.}\n", permutation_length);
            zakres_petli = silnia(permutation_length);
        }else/*(dla perm_case równego 1)*/{
            fprintf(fptr2, "\\subsection*{Uzytkownik zazadal wypisania %d losowych permutacji %d-elementowych.}\n", permutation_amount, permutation_length);
            zakres_petli = permutation_amount;
        }
        
        for(long long int j = 0; j < zakres_petli; j++){

            for(int i = 0; i < permutation_length; i++) fscanf(fptr1, "%d", permutation+i);

            //two-line notation.
            //zapis permutacji w dwoch liniach (two-line notation):;
            
            write_two_line_notation(fptr1, fptr2, permutation, permutation_length);

            //one-line notation
            //zapis permutacji w jednej linii (one-line notation):
            write_one_line_notation(fptr1, fptr2, permutation, permutation_length);

            //cycle notation permutation
            //printf("zapis permutacji w postaci cyklicznej (cycle notation): \n");

            write_cycle_notation(fptr1, fptr2, permutation, permutation_length);

            //złożenie permutacji samej ze sobą (permutation's square?)
            //printf("zlozenie permutacji samej ze soba: \n");

            write_square_of_permutation(fptr1, fptr2, permutation, permutation_length);

            newline;

        }
        
}

void write_two_line_notation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){
    
    fprintf(fptr2, "\\subsection*{two line notation:}\n");
    fprintf(fptr2, "\\[\n");

    fprintf(fptr2, "\\begin{pmatrix}\n");
    tabulator;
    base_permutation2(fptr2, permutation_length);
    fprintf(fptr2, "\\\\ \n");
    tabulator;
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    newline;
    fprintf(fptr2, "\\end{pmatrix}\n");

    fprintf(fptr2, "\\]\n");
    newline;
    
}

void write_one_line_notation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){
    
    fprintf(fptr2, "\\subsection*{one line notation:}\n");
    fprintf(fptr2, "\\[\n");

    fprintf(fptr2, "\\begin{pmatrix}\n");
    tabulator;
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    newline;
    fprintf(fptr2, "\\end{pmatrix}\n");

    fprintf(fptr2, "\\]\n");
    newline;
    
}

void write_square_of_permutation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){

    fprintf(fptr2, "\\subsection*{square of permutation:}\n");
    fprintf(fptr2, "\\[\n");

    fprintf(fptr2, "\\begin{pmatrix}\n");
    tabulator;
    base_permutation2(fptr2, permutation_length);
    fprintf(fptr2, "\\\\ \n");
    tabulator;
    int composed_permutation[permutation_length];
    compute_composition(permutation, composed_permutation, permutation_length);
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", composed_permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    newline;
    fprintf(fptr2, "\\end{pmatrix}\n");

    fprintf(fptr2, "\\]\n");
    newline;

}

void compute_composition(int permutation[], int* composed_permutation, int permutation_length){//calculates the square of particular permutation.

    //int* ptr = composed_permutation;
    
    for(int i = 0; i < permutation_length; i++){
      //to samo co: composed_permutation+i (?)
        composed_permutation[i] = permutation[permutation[i]-1];

    }
    
    //return ptr;

}

void write_cycle_notation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){
    
    bool finished;
    bool used_indexes[9] = {0};//scisle zwiazane z permutation_length.
    int next_index;//nastepny indeks, ktory ma byc sprawdzany
    
    fprintf(fptr2, "\\subsection*{cycle notation permutation:}\n");
    fprintf(fptr2, "\\[\n");

    for(int i = 0; i < permutation_length; i++){//najpierw sprawdzany czy istnieje cykl liczby samej ze soba.

        if(permutation[i] == i+1){

            used_indexes[i] = 1;
            fprintf(fptr2, "\\begin{pmatrix} ");
            fprintf(fptr2, "%d ", permutation[i]);
            fprintf(fptr2, "\\end{pmatrix}\n");
            
        }

    }

    for(int i = 0; i < permutation_length; i++){//teraz sprawdzamy czy wystepuje zwykly ciag cykliczny.

        if(permutation[i] != i+1 && used_indexes[i] == 0){//jezeli liczba nie jest rowna samej sobie i nie wystapila jeszcze ani razu wczesniej.
            
            fprintf(fptr2, "\\begin{pmatrix} ");
            fprintf(fptr2, "%d & ", i+1);//poczatkowy wyraz ciagu
            next_index = permutation[i]-1;
            used_indexes[i] = 1;

            finished = 0;

            while(!finished){//wykonuj tak długo, jak nie zostanie wyodrębniony pełen ciąg cykliczny.

                if(permutation[next_index] == i+1){

                    fprintf(fptr2, "%d ", next_index+1);
                    fprintf(fptr2, "\\end{pmatrix}\n");
                    used_indexes[next_index] = 1;
                    finished = 1;

                }else{//jezeli cykl sie nie zapetlił, kontynuuj (przypisz kolejny index):

                    fprintf(fptr2, "%d & ", next_index+1);
                    used_indexes[next_index] = 1;
                    next_index = permutation[next_index]-1;

                }


            }

        }

    }

    
    fprintf(fptr2, "\\]\n");
    newline;

}