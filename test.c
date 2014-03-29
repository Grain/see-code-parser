#include "aos.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

char * my_strdup(const char * s)
{
    char * new = malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(new, s);
    return new;
}

struct aos *create_aos(int max)
{
	struct aos * new = malloc(sizeof(struct aos));
	new->strings = malloc(sizeof(char *) * max);
	new->max = max;

	for (int i = 0; i < max; ++i)
	{
		new->strings[i] = NULL;
	}

	return new;
}

void destroy_aos(struct aos *a)
{
	for (int i = 0; i < a->max; ++i)
    {
        if (a->strings[i] != NULL)
        {
            free(a->strings[i]);
        }
    }

    free(a->strings);
    free(a);
}

int aos_count(struct aos *a)
{
	int count = 0;

	for (int i = 0; i < a->max; ++i)
	{
		if (a->strings[i] != NULL)
		{
			count++;
		}
	}

	return count;
}

char *aos_get(struct aos *a, int i)
{
	if (i < 0 || i >= a->max)
		return NULL;
	return a->strings[i];
}

void aos_set(struct aos *a, const char *s, int i)
{
    if (a->strings[i] != NULL)
        free(a->strings[i]);

    if (s == NULL)
        a->strings[i] = NULL;
    else
    {
        a->strings[i] = my_strdup(s);
    }
}

int aos_add(struct aos *a, const char *s)
{
    assert(s != NULL);

	for (int i = 0; i < a->max; ++i)
	{
		if (a->strings[i] == NULL)
		{
			if (s == NULL)
				a->strings[i] = NULL;
			else
			{
				a->strings[i] = my_strdup(s);
			}
			return i;
		}
	}

	return -1;
}

void aos_sort(struct aos *a)
{
    for (int i = 0; i < a->max - 1; ++i)
    {
        int min = i;
        for (int j = i + 1; j < a->max; ++j)
        {
            if (a->strings[j] != NULL && (a->strings[min] == NULL || strcmp(a->strings[j], a->strings[min]) < 0))
            {
                min = j;
            }
        }

        char * temp = a->strings[min];
        a->strings[min] = a->strings[i];
        a->strings[i] = temp;
    }
}

