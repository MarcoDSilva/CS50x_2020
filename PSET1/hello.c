#include <stdio.h>
#include <cs50.h>

//I rather use a 2 space tab than 4, and open the bracket in the same line, but since style50 complains about them, have to deliver it like style50 wants.
int main(void)
{
    string name = get_string("What is your name?\n");

    printf("hello, %s\n", name);
}