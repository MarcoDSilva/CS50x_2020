#include <stdio.h>
#include <cs50.h>

//function to print spaces
void print_spaces(int i)
{
    while (i > 1)
    {
        printf(" ");
        i--;
    }
}

//function to print hashes
void print_hashes(int i)
{
    while (i > 0)
    {
        printf("#");
        i--;
    }
}

int main(void)
{
    int h = 0;

    // we ask input while the input isn't a digit between 1 and 8 inclusive
    do
    {
        h = get_int("Height: ");
    }
    while (h <= 0 || h > 8);

    //outside loop is for the lines
    //since we have functions to print the spaces/hashes, we just call them
    for (int i = 0; i < h; i++)
    {
        print_spaces(h - i); //the value passed is size of height minus iteration, to reduce spaces by iteration
        print_hashes(i + 1); //the value passed is iteration + 1, to print the hashes

        printf("  ");

        print_hashes(i + 1);
        printf("\n");
    }
}