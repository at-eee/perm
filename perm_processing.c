//"at-eee" Jakub Malinowski
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "functions_declarations.h"

#define newline fprintf(fptr2, "\n")
#define tabulator fprintf(fptr2, "\t")
#define hline fprintf(fptr2, "\t\\hline\n")//Stands for: horizontal line.

//[ENG] Warning! comments are mixed with both polish and english language as of yet.
//[PL] Uwaga! Póki co język używany w komentarzach jest przeplatany między polskim i angielskim.

int previous_permutation[100];
int next_permutation[100];

int main(int argc, char** argv) {
    
    
    int permutation[100];
    int permutation_length;
    char permutation_type[4] = {' '};
    
    FILE *fptr1;
    
    fptr1 = fopen("data.txt", "r");
    
    fscanf(fptr1, "%d", &permutation_length);
    fscanf(fptr1, "%s", permutation_type);
    int permutation_amount;
    
    FILE *fptr2;
    
    fptr2 = fopen("result.tex", "a");
    
    switch(permutation_type[0]){
    
        case 'A':
            
            permutation_amount = NULL;
            
            permutation_case(fptr1, fptr2, permutation, permutation_length, permutation_amount, 0, argv);
            
            break;
        
        default:
        
            permutation_amount = atoi(permutation_type);           
            
            permutation_case(fptr1, fptr2, permutation, permutation_length, permutation_amount, 1, argv);
            
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

void base_permutation(FILE *fptr2, int permutation_length){//writes base permutation i. e: prints first "row" of the two-line notation's permutation.
    
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", i+1); if(i!=permutation_length-1) fprintf(fptr2, "& ");}

}

//wypisuje output do pliku, w zaleznosci od tego co podał użytkownik na wejściu (case'a, który został wybrany).
void permutation_case(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length, int permutation_amount, char perm_case, char** argv){

    
        long long int zakres_petli;
        
        fprintf(fptr2, "\\section{Wygenerowany rodzaj permutacji nr %s:}\n", argv[1]);
        
        if(perm_case == 0){
            fprintf(fptr2, "\\subsection*{Użytkownik zażądał wypisania wszystkich możliwych\\\\ permutacji %d-elementowych.}\n\n", permutation_length);
            zakres_petli = silnia(permutation_length);
        }else/*(dla perm_case równego 1)*/{
            fprintf(fptr2, "\\subsection*{Użytkownik zażądał wypisania %d losowych permutacji %d-elementowych.}\n\n", permutation_amount, permutation_length);
            zakres_petli = permutation_amount;
        }
        
        //                                                      same as: permutation[i]
        for(int i = 0; i < permutation_length; i++) fscanf(fptr1, "%d", next_permutation+i);
        
        for(long long int j = 0; j < zakres_petli; j++){ //1. permutation = next_permutation, 2. scan next_permutation, 3. previous_permutation = permutation, 4. back to step 1
            
            for(int i = 0; i < permutation_length; i++) permutation[i] = next_permutation[i];
            
            fprintf(fptr2, "\\subsection{}\n");
            
            fprintf(fptr2, "\\begin{center}\n");
            
            write_current_permutation(fptr1, fptr2, permutation, permutation_length);
            
            fprintf(fptr2, "\\begin{tabular}{|m{0.6\\linewidth}|m{0.4\\linewidth}|}\n");
            hline;
            
            fprintf(fptr2, "\tNazwa Parametru & Parametr \\\\\n");
            hline;
            
            write_two_line_notation(fptr1, fptr2, permutation, permutation_length);

            write_one_line_notation(fptr1, fptr2, permutation, permutation_length);

            write_cycle_notation(fptr1, fptr2, permutation, permutation_length);
            
            //tzw. "flag" - tutaj nazwany jako "perm_case", jednak wczesniej nazwany w functions_declarations.h jako "flag".
            if(perm_case == 0){
                
                write_previous_permutation(fptr1, fptr2, permutation, permutation_length, j);
            
            }
            
            for(int i = 0; i < permutation_length; i++) fscanf(fptr1, "%d", next_permutation+i);
            
            if(perm_case == 0){
                
                write_next_permutation(fptr1, fptr2, permutation, permutation_length, j, zakres_petli);
            
            }

            write_square_of_permutation(fptr1, fptr2, permutation, permutation_length);
            
            fprintf(fptr2, "\\end{tabular}\n");
            
            fprintf(fptr2, "\\end{center}\n");

            newline; newline;
            
            if(perm_case == 0) for(int i = 0; i < permutation_length; i++) previous_permutation[i] = permutation[i];

        }
        
}

void write_current_permutation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){

    fprintf(fptr2, "\\[\n");
    
    fprintf(fptr2, "\\begin{pmatrix}\n");
    tabulator;
    base_permutation(fptr2, permutation_length);
    fprintf(fptr2, "\\\\ \n");
    tabulator;
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    newline;
    fprintf(fptr2, "\\end{pmatrix}\n");
    
    fprintf(fptr2, "\\]\n");
    newline;
    
}

void write_two_line_notation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){
    
    fprintf(fptr2, "\tzapis permutacji w dwóch liniach (two-line notation) & $\\begin{pmatrix} ");
    base_permutation(fptr2, permutation_length);
    fprintf(fptr2, "\\\\ \n");
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    fprintf(fptr2, "\\end{pmatrix}$ \\\\ \n");

    hline;
    
}

void write_one_line_notation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){
    
    fprintf(fptr2, "\tzapis permutacji w jednej linii (one-line notation) & $\\begin{pmatrix} ");
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    fprintf(fptr2, "\\end{pmatrix}$ \\\\ \n");

    hline;
    
}

void write_previous_permutation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length, long long int loop_iteration){
    
    if(loop_iteration == 0) fprintf(fptr2, "\tPoprzednia permutacja (previous permutation) & Brak poprzedniej permutacji! (pierwsza permutacja)\\\\ \n");
    else{
        fprintf(fptr2, "\tpoprzednia permutacja (previous permutation) & $\\begin{pmatrix} ");
        base_permutation(fptr2, permutation_length);
        fprintf(fptr2, "\\\\ \n");
        for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", previous_permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
        fprintf(fptr2, "\\end{pmatrix}$ \\\\ \n");
    }
    hline;

}

void write_next_permutation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length, long long int loop_iteration, long long int max_iteration){

    if(loop_iteration == max_iteration-1) fprintf(fptr2, "\tNastępna permutacja (next permutation) & Brak następnej permutacji! (ostatnia permutacja)\\\\ \n");
    else{
        fprintf(fptr2, "\tnastępna permutacja (next permutation) & $\\begin{pmatrix} ");
        base_permutation(fptr2, permutation_length);
        fprintf(fptr2, "\\\\ \n");
        for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", next_permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
        fprintf(fptr2, "\\end{pmatrix}$ \\\\ \n");
    }
    hline;

}

void write_square_of_permutation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){

    fprintf(fptr2, "\tzlozenie permutacji samej ze soba (kwadrat permutacji (permutation's square)) & $\\begin{pmatrix} ");
    base_permutation(fptr2, permutation_length);
    fprintf(fptr2, "\\\\ \n");
    int composed_permutation[permutation_length];//--
    compute_composition(permutation, composed_permutation, permutation_length);//--
    for(int i = 0; i < permutation_length; i++) {fprintf(fptr2, "%d ", composed_permutation[i]); if(i!=permutation_length-1) fprintf(fptr2, "& ");}
    fprintf(fptr2, "\\end{pmatrix}$ \\\\ \n");

    hline;

}

void compute_composition(int permutation[], int* composed_permutation, int permutation_length){//calculates the square of particular permutation.
    
    for(int i = 0; i < permutation_length; i++){
      //to samo co: composed_permutation+i (?)
        composed_permutation[i] = permutation[permutation[i]-1];

    }

}

void write_cycle_notation(FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length){
    
    bool finished;
    bool used_indexes[9] = {0};//scisle zwiazane z permutation_length.
    int next_index;//nastepny indeks, ktory ma byc sprawdzany
    
    fprintf(fptr2, "\tzapis permutacji w postaci cyklicznej (cycle notation) & $");

    for(int i = 0; i < permutation_length; i++){//najpierw sprawdzany czy istnieje cykl liczby samej ze soba.

        if(permutation[i] == i+1){

            used_indexes[i] = 1;
            fprintf(fptr2, "\\begin{pmatrix} ");
            fprintf(fptr2, "%d ", permutation[i]);
            fprintf(fptr2, "\\end{pmatrix} ");
            
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
                    fprintf(fptr2, "\\end{pmatrix} ");
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
    
    fprintf(fptr2, "$ \\\\ \n");
    
    hline;

}