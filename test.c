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

void swap(char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *a, int l, int r, int len)
{
    if (l == r)
    {
        for (int i = 0; i < len; i++) {
            printf("%c ", a[i]);
        }
        putchar('\n');

        return;
    }

    for (int i = l; i <= r; i++)
    {
        swap(a + l, a + i);
        permute(a, l + 1, r, len);
        swap(a + l, a + i);
    }
}

void print_permutations(int arr_num, char *arr_len)
{
    if (!strcmp(arr_len, "A"))
    {
        char str[arr_num];
        for (int i = 0; i < arr_num; i++)
        {
            char value = ((i + 1) + '0');
            str[i] = value;
        }
        printf("\n");

        permute(str, 0, arr_num - 1, arr_num);
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
