#include <iostream>


// ±º‰∏¥‘”∂»£∫O(n^2)
void RemoveRepetNum(int *buf, int n)
{
	int i = 0, j = 0;
	for (; i < n; ++i)
	{
		for (j = i + 1; j < n; ++j)
		{
			if(buf[i]== buf[j])
			{
				buf[i] = -1;
				break;
			}
		}
	}

	for (i = 0, j = 0; i < n; ++i)
	{
		if (buf[i] == -1)
			continue;
		buf[j++] = buf[i];
	}
	while(j < n)
	{
		buf[j++] = 0;
	}
}


void Qsort(int a[], int low, int high)
{
	if (low >= high)
		return;
	int privot = a[low];
	int first = low;
	int last = high;
	while(first < last)
	{
		while((first < last) && a[last] >= privot)
			--last;
		a[first] = a[last];
		while((first < last) && a[first] < privot)
			++first;
		a[last] = a[first];
	}
	a[first] = privot;
	Qsort(a, low, first - 1);
	Qsort(a, first + 1, high);
}

void RemoveRepetSortNum(int a[], int n)
{
	int tmp = a[0];
	int i = 0, j = 1;
	for(; i < n; ++i)
	{
		if (a[i] == tmp)
			continue;
		tmp = a[i];
		a[j++] = tmp;
	}
	while(j < n)
	{
		a[j++] = -1;
	}
}

void ArrayMergeSort(int a[], int b[], int c[], int a_count, int b_count, int *new_count)
{
	int i = 0, j = 0, k = 0;
	int num = 0;
	while(i < a_count && j < b_count)
	{
		if (a[i] < b[j])
		{
			c[k++] = a[i];
			i++;
			num++;
		}
		else if (a[i] == b[j])
		{
			c[k++] = a[i];
			i++;
			j++;
			num++;
		}
		else
		{
			c[k++] = b[j];
			j++;
			num++;
		}
	}
	if (i == a_count && j < b_count)
	{
		for (; j < b_count; j++)
		{	
			c[k++] = b[j];
			num++;
		}
	}
	else if (j == b_count && i < a_count)
	{
		for (; i < a_count; i++)
		{
			c[k++] = a[i];
			num++;
		}
	}
	*new_count = num;
}

int main(int argc, char **argv)
{
	//
	int tmparr[10] = {3, 44, 38, 5, 27, 15, 2, 26, 27, 2};
	int arr[8] = {12, 57, 36, 9, 25, 13, 9, 57};
	int size = sizeof(tmparr) / sizeof(int);
	int count = sizeof(arr) / sizeof(int);
	int new_arr[18];
	int new_arrcount;
	//RemoveRepetNum(tmparr, size);
	Qsort(tmparr, 0, size - 1);
	Qsort(arr, 0, count - 1);
	ArrayMergeSort(tmparr, arr, new_arr, size, count, &new_arrcount);
	RemoveRepetSortNum(new_arr, new_arrcount);
	return 0;
}
