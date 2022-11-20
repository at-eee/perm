#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

bool is_number(const char *num)
{
        int idx = strlen(num);

        while (idx--)
        {
                if (num[idx] > 47 && num[idx] < 58)
                {
                        continue;
                }
                return false;
        }
        return true;
}

void print_permutations(int arr_num, char *arr_len)
{
        if (!strcmp(arr_len, "A"))
        {
                while (arr_num > 9)
                {
                        printf("W trosce o twoj dysk prosimy o podanie liczby z zakresu 1-9:\n");
                        scanf("%d", &arr_num);
                }

                if (arr_num == 8)
                {
                        char set[8] = "12345678";
                        char scratch;
                        int lastpermutation = 0;
                        int i, j, k, l;

                        printf("%s\n", set);

                        while (!lastpermutation)
                        {
                                j = -1;
                                for (i = 0; i < 8; i++)
                                {
                                        if (set[i + 1] > set[i])
                                        {
                                                j = i;
                                        }
                                }

                                if (j == -1)
                                {
                                        lastpermutation = 1;
                                }

                                if (!lastpermutation)
                                {
                                        for (i = j + 1; i < 8; i++)
                                        {
                                                if (set[i] > set[j])
                                                {
                                                        l = i;
                                                }
                                        }

                                        scratch = set[j];
                                        set[j] = set[l];
                                        set[l] = scratch;

                                        k = (7 - j) / 2;

                                        for (i = 0; i < k; i++)
                                        {
                                                scratch = set[j + 1 + i];
                                                set[j + 1 + i] = set[7 - i];
                                                set[7 - i] = scratch;
                                        }

                                        for (int z = 0; z < arr_num; z++)
                                        {
                                                printf("%c ", set[z]);
                                        }

                                        printf("\n");
                                }
                        }
                        return;
                }

                char set[arr_num];

                for (int p = 0; p < arr_num; p++)
                {
                        char value = ((p + 1) + '0');
                        set[p] = value;
                        printf("%c ", set[p]);
                }

                printf("\n");

                char scratch;
                int lastpermutation = 0;
                int lownum = (arr_num - 1);
                int i, j, k, l;

                while (!lastpermutation)
                {
                        j = -1;
                        for (i = 0; i < arr_num; i++)
                        {
                                if (set[i + 1] > set[i])
                                {
                                        j = i;
                                }
                        }

                        if (j == -1)
                        {
                                lastpermutation = 1;
                        }

                        if (!lastpermutation)
                        {
                                for (i = j + 1; i < arr_num; i++)
                                {
                                        if (set[i] > set[j])
                                        {
                                                l = i;
                                        }
                                }

                                scratch = set[j];
                                set[j] = set[l];
                                set[l] = scratch;
                                k = ((lownum - j) / 2);

                                for (i = 0; i < k; i++)
                                {
                                        scratch = set[j + 1 + i];
                                        set[j + 1 + i] = set[lownum - i];
                                        set[lownum - i] = scratch;
                                }

                                for (int z = 0; z < arr_num; z++)
                                {
                                        printf("%c ", set[z]);
                                }

                                printf("\n");
                        }
                }
                return;
        }

        if (!is_number(arr_len))
        {
                puts("invalid input");
                return;
        }

        srand((unsigned)time(NULL));

        int len = atoi(arr_len);
        int fin_outp[arr_num];
        int lower = 1;

        for (int k = 0; k < len; k++)
        {
                fin_outp[0] = (rand() % (arr_num + 1 - lower) + lower);
                printf("%d ", fin_outp[0]);

                for (int i = 1; i < arr_num; i++)
                {
                        fin_outp[i] = (rand() % (arr_num + 1 - lower) + lower);

                        int j = 0;
                        while (j < i)
                        {
                                if (fin_outp[i] == fin_outp[j])
                                {
                                        fin_outp[i] = (rand() % (arr_num + 1 - lower) + lower);
                                        j = 0;
                                }
                                else
                                {
                                        j++;
                                }
                        }
                        printf("%d ", fin_outp[i]);
                }
                printf("\n");
        }
}

int main()
{
        int number_of_arrs;
        char length_of_arr[256];

        puts("Podaj liczbe zbiorow oraz ich dlugosc:");

        scanf("%d", &number_of_arrs);
        scanf("%s", length_of_arr);

        print_permutations(number_of_arrs, length_of_arr);

        return 0;
}
