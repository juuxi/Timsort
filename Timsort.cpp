#include <iostream>
#include <cstddef>
#include "vector.cpp"

int count_minrun(int N)
{
    if(N < 64) 
    return N;
    int r = 0;
    while(N > 64)
    r |= N&1;
    N>>=1;
    return N + r;
}

void insert_sort(Vector<int> &arr, size_t left, size_t right)
{
    for(size_t i = left + 1; i < right; i++)
    {
    int value = arr[i];
    int j;
    for (j = i-1; j >= 0 && value < arr[j]; j--)
        arr[j+1] = arr[j];
    arr[j] = value;
    }
}

//left = 0; mid = 32; right = 64;
void merge(Vector<int> &arr, size_t left, size_t mid, size_t right)
{
    Vector<int> sub;
    for (size_t i = left, j = 0; i < mid; i++, j++)
    {
        sub[j] = arr[i];
    }
    int* left_curr = &sub[0];
    int* right_curr = &arr[mid];
    int* arr_curr = &arr[left];
    size_t right_counter = 0, left_counter = 0;
    while (true) 
    {
        if (*left_curr <= *right_curr)
        {
            *arr_curr = *left_curr;
            left_curr++;
            left_counter++;
            right_counter = 0;
        }
        else 
        {
            *arr_curr = *right_curr;
            right_curr++;
            right_counter++;
            left_counter = 0;
        }
        arr_curr++;

        if (left_curr == &sub[mid-left]) //mid-left = size(sub)
        {
            break;
        }
        if (right_curr == &arr[right])
        {
            while(left_curr != &arr[mid-left])
            {
                *arr_curr = *left_curr;
                left_curr++;
                arr_curr++;
            }
            break;
        }
    }
}

void timsort(Vector<int> &arr, const int& minrun)
{
    
}

int main()
{
    int size;
    std::cout << "Введите число элементов" << std::endl << "> ";
    std::cin >> size;
    Vector<int> vec(size+1);
    srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        vec.push_back(rand() % 65536);
    }
    int minrun = count_minrun(size);
    timsort(vec, minrun);
    std::cout << vec;    
    return 0;
}