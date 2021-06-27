#include <cs50.h>
#include <stdio.h>

int arr[] = {5, 2, 1, 3 , 6, 4};
int size = 6;


void merge(int array[], int left_idx, int half_idx, int right_idx)
{
    int temp_array[right_idx - left_idx + 1];
    int i = left_idx, j = half_idx + 1, k = 0;

    // Merge sub arrays
    while ((i <= half_idx) && (j <= right_idx))
    {
        if (array[i] <= array[j])
        {
            temp_array[k] = array[i];
            i++;
        }
        else
        {
            temp_array[k] = array[j];
            j++;
        }
        k++;
    }

    // Flush remainder from left sub array 
    for (; i < half_idx + 1; i++)
    {
        temp_array[k] = array[i];
        k++;
    }
    // Flush remainder from right sub array 
    for (; j < half_idx + 1; j++)
    {
        temp_array[k] = array[j];
        k++;
    }

    for (k = left_idx; k < right_idx + 1; k++)
    {
        array[k] = temp_array[k - left_idx];
    }

}

void merge_sort(int array[], int left_idx, int right_idx)
{

    if (left_idx < right_idx)
    {
        int half_idx = (left_idx + right_idx) / 2;
        // sort left half
        merge_sort(array, left_idx, half_idx);
        // sort right half
        merge_sort(array, half_idx + 1, right_idx);

        merge(array, left_idx, half_idx, right_idx);

    
    }
}

int main(void)
{
    merge_sort(arr, 0, size - 1);
    for (int i = 0; i < size; i++)
    {
        printf("%i: %i\n", i, arr[i]);
    }
    
    return 0;
}
