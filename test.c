#include <stdio.h>

int main()
{
    char input;	//hi//hi//hi
	
    do
    {
	1 = 0;
    } while (1);

    do
	    printf("hi");
    while(1);

	/*		*/
    do
    {
        input = getchar();

        if(input == 'A' || input == 'B' || input == 'C')
        {
            printf/*("2");*/
        }
        else if(input == 'D' || input == 'E' || input == 'F')
        {
            printf("3");
        }
        else if(input == 'G' || input == 'H' || input == 'I')
        {
            printf("4");
        }
        else if(input == 'J' || input == 'K' || input == 'L')
        {
            printf("5");
        }
        else if(input == 'M' || input == 'N' || input == 'O')
        {
            printf("6");
        }
        else if(input == 'P' || input == 'Q' || input == 'R' || input == 'S')
        {
            printf("7");
        }
        else if(input == 'T' || input == 'U' || input == 'V')
        {
            printf("8");
        }
        else if(input == 'W' || input == 'X' || input == 'Y' || input == 'Z')
        {
            printf("9");
        }
        else if(input != EOF)
        {
            printf("%c", input);
        }

    } while(input != EOF);
}

