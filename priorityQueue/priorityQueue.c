#include <stdio.h>
#include <stdlib.h>

void minHeapify(int *arr, int i, int size)
{
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	int min, t;

	if (l < size && arr[l] < arr[i])
		min = l;
	else
		min = i;

	if (r < size && arr[r] < arr[min])
		min = r;

	if (min != i)
	{
		t = arr[i];
		arr[i] = arr[min];
		arr[min] = t;
		minHeapify(arr, min, size);
	}
}

void enqueue(int *arr, int size, int *i, int x)
{
	(*i)++;
	if ((*i) >= size)
	{
		printf("Overflow\n");
		(*i)--; // Prevent out-of-bounds issues
		return;
	}

	arr[*i] = x; // Insert new element at the end
	int child = *i;
	int parent = (child - 1) / 2;

	// Bubbling up to restore min-heap property
	while (child > 0 && arr[parent] > arr[child])
	{
		// Swap parent and child
		int temp = arr[parent];
		arr[parent] = arr[child];
		arr[child] = temp;

		// Move up the heap
		child = parent;
		parent = (child - 1) / 2;
	}
}

void dequeue(int *arr, int size, int *i)
{
	if ((*i) < 0)
	{
		printf("Underflow\n");
		return;
	}
	int max = arr[0];
	arr[0] = arr[(*i)];
	(*i)--;
	minHeapify(arr, 0, (*i) + 1);

	printf("Dequeued = %d\n", max);
}

void heapDecreaseKey(int *arr, int i, int newKey, int heapSize)
{
	if (i < 0 || i > heapSize - 1)
	{
		printf("Invalid Index\n");
		return;
	}

	if (newKey > arr[i])
	{
		printf("New key is larger than the current key! Invalid operation.\n");
		return;
	}

	arr[i] = newKey; // Setting new key

	// Bubbling up to restore min-heap property
	int child = i;
	int parent = (child - 1) / 2;
	while (child > 0 && arr[parent] > arr[child])
	{
		int temp = arr[parent];
		arr[parent] = arr[child];
		arr[child] = temp;

		child = parent;
		parent = (child - 1) / 2;
	}
}

void display(int *arr, int i)
{
	if (i < 0)
		return;

	int j;
	for (j = 0; j <= i; j++)
		printf("%d ", arr[j]);
	printf("\n");
}

int main()
{
	int i = -1, n, ch, k, idx;
	printf("Enter the size\n");
	scanf("%d", &n);
	int *arr = (int *)malloc(n * sizeof(int));

	while (1)
	{
		printf("Enter\n 1. Enqueue\n 2. Dequeue\n 3. Heap Decrease key\n 4. Exit\n");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			printf("Enter Ele\n");
			scanf("%d", &k);
			enqueue(arr, n, &i, k);
			display(arr, i);
			break;
		case 2:
			dequeue(arr, n, &i);
			display(arr, i);
			break;
		case 3:
			printf("Enter index & new value\n");
			scanf("%d%d", &idx, &k);
			heapDecreaseKey(arr, idx, k, n);
			display(arr, i);
			break;
		case 4:
			printf("EOP\n");
			free(arr);
			exit(0);
		default:
			printf("Wrong Choice!\n");
		}
	}

	return 0;
}