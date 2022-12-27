//file name: functions_declarations.h

//[ENG] Warning! comments are mixed with both polish and english language as of yet.
//[PL] Uwaga! Póki co język używany w komentarzach jest przeplatany między polskim i angielskim.

#define domyslne_parametry FILE *fptr1, FILE *fptr2, int permutation[], int permutation_length

//funkcja okreslajaca dzialanie programu w zaleznosci od rodzaju generowanej permutacji (swego rodazju "core" danego programu).
void permutation_case(domyslne_parametry, int permutation_amount, char flag, char** argv);

//funkcje wypisujace do pliku:
void write_current_permutation(domyslne_parametry);
void write_two_line_notation(domyslne_parametry);
void write_one_line_notation(domyslne_parametry);
void write_previous_permutation(domyslne_parametry, long long int loop_iteration);
void write_next_permutation(domyslne_parametry, long long int loop_iteration, long long int max_iteration);
void write_cycle_notation(domyslne_parametry);
void write_square_of_permutation(domyslne_parametry);
//-"podfunkcja" funkcji write_square_of_permutation:
void compute_composition(int permutation[], int composed_permutation[], int permutation_length);

//funkcje pomocnicze:
long long int silnia(int permutaion_length);
void base_permutation(FILE *fptr2, int permutation_length);

//functions described in more detail under the end of the "main" scope in the perm_processing.c file.
