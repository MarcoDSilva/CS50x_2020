#include<stdio.h>
#include<cs50.h>

int main(void)
{

    long number = 0;
    int card_digits = 0;

    // while we don't receive an input number we re-ask input from the user
    do
    {
        number = get_long("Number: ");
    }
    while (number <= 0);

    // counting the digits number
    for (long cc = number; cc > 0; cc /= 10)
    {
        card_digits += 1;
    }

    // we finish the program right away if the number has less than 13 digits or more than 16 digits
    if (card_digits < 13 || card_digits > 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // here we declare variables used for the checksum and apply the checksum logic
    int not_multiplied = 0;
    int multiplied = 0;
    int counter = 1;
    long i = number;

    // we iterate through the cc digits, and in each cycle we drop one digit of until it has no digits
    while (i > 0)
    {
        // if the counter it's not even, we are on a digit that has to not be multiplied so we just sum it
        if (counter % 2 != 0)
        {
            not_multiplied += (i % 10);
        }
        else
        {
            // otherwise we verify if the digit multiplied is greater than 9
            // if it is, we separate the digits and sum them
            if (((i % 10) * 2) > 9)
            {
                int mult = (i % 10) * 2;
                int sum = (mult % 10) + (mult / 10);
                multiplied += sum;
            }
            else
            {
                multiplied += ((i % 10) * 2);
            }
        }

        counter++;
        i = i / 10;
    }

    // we verify if the checksum got a correct cc, otherwise we finish the program
    int checksum = (multiplied + not_multiplied) % 10;

    if (checksum != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    /*
        American Express - 15 digits - starts with 34 or 37
        MasterCard - 16 digits - starts with 51 up to 55 inclusive
        Visa - 13 or 16 digits - starts with 4
    */
    if (card_digits == 15)
    {
        int amex = number / 10000000000000;

        if (amex == 34 || amex == 37)
        {
            printf("AMEX\n");
            return 0;
        }
    }
    else
    {
        if (card_digits == 13)
        {
            int card = number / 1000000000000;

            if (card == 4)
            {
                printf("VISA\n");
                return 0;
            }
        }
        else if (card_digits == 16)
        {
            int master = number / 100000000000000;
            int visa = number / 1000000000000000;

            if (master >= 51 && master <= 55)
            {
                printf("MASTERCARD\n");
                return 0;
            }

            if (visa == 4)
            {
                printf("VISA\n");
                return 0;
            }
        }
    }

    printf("INVALID\n");
    return 0;
}