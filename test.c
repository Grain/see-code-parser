#include "atree.h"
#include <assert.h>
#include <stdlib.h>

const int EMPTY = INT_MIN;

// expt(x, n) returns the value of x^n
// PRE: n > 0
// POST: returns an integer
// TIME: O(n), where n = n
int expt(int x, int n)
{
	assert(n > 0);

	int value = x;

	for (int i = 1; i < n; ++i)
	{
		value *= x;
	}

	return value;
}

// refer to interface
struct atree *create_atree(int maxheight)
{
	assert(maxheight >= 1);

	struct atree * new = malloc(sizeof(struct atree));
	new->maxheight = maxheight;

	int size = expt(2, maxheight);

	new->data = malloc(sizeof(int) * size);

	for (int i = 0; i < size; ++i)
	{
		new->data[i] = EMPTY;
	}

	return new;
}

// refer to interface
void destroy_atree(struct atree *at)
{
	free(at->data);
	free(at);
}

// refer to interface
void atree_add(struct atree *at, int i)
{
	assert(at != NULL);
	assert(i != EMPTY);

	int current = 0;
	int max = expt(2, at->maxheight) - 1;

	while (true)
	{
		if (current >= max)	//resize and spot found
		{
			at->maxheight++;
			at->data = realloc(at->data, sizeof(int) * (max + 1) * 2);

			for (int a = max; a < (max + 1) * 2; ++a)
			{
				at->data[a] = EMPTY;
			}

			at->data[current] = i;
			return;
		}

		if (at->data[current] == EMPTY)	//empty spot for i found
		{
			at->data[current] = i;
			return;
		}

		if (i == at->data[current])	//i already in at
		{
			return;
		}
		else if (i < at->data[current])
		{
			current = 2 * current + 1;
		}
		else if (i > at->data[current])
		{
			current = 2 * current + 2;
		}
	}

}

// refer to interface
bool atree_search(struct atree *at, int i)
{
	assert(at != NULL);
	assert(i != EMPTY);

	int current = 0;
	int max = expt(2, at->maxheight);

	while (current < max && at->data[current] != EMPTY)
	{
		if (i == at->data[current])
		{
			return true;
		}
		else if (i < at->data[current])
		{
			current = 2 * current + 1;
		}
		else
		{
			current = 2 * current + 2;
		}
	}

	return false;
}


