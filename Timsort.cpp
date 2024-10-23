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

void merge(Vector<int> &arr, size_t left, size_t mid, size_t right)
{

}

void timsort(Vector<int> &arr, const int& minrun)
{
    for (size_t i = 0, counter = 1; i < arr.get_size(); i += minrun, counter++)
    {
        if (i + minrun < arr.get_size())
            insert_sort(arr, i, i + minrun);
        else 
            insert_sort(arr, i, arr.get_size());
    }
    for (size_t multiplier = 0; multiplier * minrun < arr.get_size(); multiplier++)
    {
        for (size_t i = 0; i < arr.get_size(); i+= multiplier * minrun)
        {
            if (i + minrun < arr.get_size())
                merge(arr, i - minrun, i, i + minrun);
            else 
                merge(arr, i - minrun, i, arr.get_size());
        }
    }
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