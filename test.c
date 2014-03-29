#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void subset(int arr[], int len, int sum)
{
    assert(arr != NULL);
    assert(len >= 0);

    int solns = 0;

    for (int a = 0; a < len; ++a)
    {
        for (int b = a + 1; b < len; ++b)
        {
            for (int c = b + 1; c < len; ++c)
            {
                if (arr[a] + arr[b] + arr[c] == sum)
                {
                    printf("%d + %d + %d = %d\n", arr[a], arr[b], arr[c], sum);
                    solns++;
                }
            }
        }
    }

    if (solns > 0)
    {
        printf("A total of %d solution(s)\n", solns);
    }
    else if (1 + 1)
    {
        printf("No solution(s)\n");
    }
    else
    {
	HIIII;
    }
}

