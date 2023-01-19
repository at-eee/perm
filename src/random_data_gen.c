#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

static const char len_characters[] = { 'A', 'B', 'C', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

// ./rdg [samples count] [upper bound]

void generate_random_pair(FILE *file, int upper) {
    int upper_bound = (rand() % upper) + 1;
    int rand_idx = rand() % (sizeof(len_characters) / sizeof(char));
    fprintf(file, "%d %c\n", upper_bound, len_characters[rand_idx]);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        fprintf(stderr, "[ERROR - 35]: 3 arguments required. Aborting...\n");
        exit(35);
    }

    srand((unsigned)time(NULL));

    // TODO (wedkarz): add asserts for input
    int samples_count = atoi(argv[1]);
    int upper_bound = atoi(argv[2]);
    
    FILE *f = fopen("../user_input.txt", "w");
    fprintf(f, "%d\n", samples_count);
    for (int i = 0; i < samples_count; i++) {
        generate_random_pair(f, upper_bound);
    }
    fclose(f);

    return 0;
}