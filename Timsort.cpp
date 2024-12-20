#include <iostream>
#include <cstddef>
#include "vector.cpp"

int count_minrun(int N)
{
    if(N < 64) 
    return N;
    int r = 0;
    while(N > 64)
    {
        r |= N&1;
        N>>=1;
    }
    return N + r;
}

void insert_sort(Vector<int> &arr, size_t left, size_t right)
{
    for(size_t i = left + 1; i < right; i++)
    {
        int value = arr[i];
        for (int j = i-1; j >= left && value < arr[j]; j--)
        {
            int temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
        }
    } 
} 

void galloping(Vector<int> &arr, Vector<int> &sub, int &left_curr, int &right_curr, const int _right, int &arr_curr, bool is_left)
{
    int galloping_curr = -1;
    //binary search
    if (is_left)
    {
        int left = left_curr;
        int right = sub.get_size();
        while (galloping_curr != left && galloping_curr != right)
        {
            galloping_curr = (right + left)/2;
            if (sub[galloping_curr] < arr[right_curr])
            {
                for (size_t i = left; i <= galloping_curr; i++)
                {
                    arr[arr_curr] = sub[i];
                    arr_curr++;
                }
                left = galloping_curr;
                left_curr = galloping_curr;
            }
            else 
                right = galloping_curr;
        }
    }
    else 
    {
        int left = right_curr;
        int right = _right;
        while (galloping_curr != left && galloping_curr != right)
        {
            galloping_curr = (right + left)/2;
            if (arr[galloping_curr] < sub[left_curr])
            {
                for (size_t i = left; i <= galloping_curr; i++)
                {
                    arr[arr_curr] = arr[i];
                    arr_curr++;
                }
                left = galloping_curr;
                right_curr = galloping_curr;
            }
            else 
                right = galloping_curr;
        }
    }
}
//left = 0; mid = 32; right = 64;
void merge(Vector<int> &arr, size_t left, size_t mid, size_t right)
{
    Vector<int> sub(1);
    for (size_t i = left, j = 0; i < mid; i++, j++)
    {
        sub.push_back(arr[i]);
    }
    int left_curr = 0; //sub
    int right_curr = mid; //arr
    int arr_curr = left; //arr
    size_t right_counter = 0, left_counter = 0;
    while (true) 
    {
        if (sub[left_curr] <= arr[right_curr])
        {
            arr[arr_curr] = sub[left_curr];
            left_curr++;
            left_counter++;
            right_counter = 0;
        }
        else 
        {
            arr[arr_curr] = arr[right_curr];
            right_curr++;
            right_counter++;
            left_counter = 0;
        }
        arr_curr++;

        if (left_curr == sub.get_size()) //mid-left = size(sub)
        {
            break;
        }
        if (right_curr == right)
        {
            while(left_curr != sub.get_size())
            {
                arr[arr_curr] = sub[left_curr];
                left_curr++;
                arr_curr++;
            }
            break;
        }

        if (left_counter == 7)
            galloping(arr, sub, left_curr, right_curr, right, arr_curr, true);
        if (right_counter == 7)
            galloping(arr, sub, left_curr, right_curr, right, arr_curr, false);
    }
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
    /* int loop_counter = 0;
    for (size_t multiplier = 1; ; multiplier++)
    {
        if (loop_counter == 1)
            break;
        loop_counter = 0;
        for (size_t i = multiplier * minrun; i < arr.get_size(); i+= multiplier * minrun * 2)
        {
            if (i + multiplier * minrun < arr.get_size())
                merge(arr, i - multiplier * minrun, i, i + multiplier * minrun - 1);
            else 
                merge(arr, i - multiplier * minrun, i, arr.get_size() - 1);
            std::cout << multiplier << " merge:" << std::endl;
            std::cout << arr;
            loop_counter++;
        }
    } */
    std::cout << "insert: " << std::endl;
    std::cout << arr;
    for (int size = minrun; size < arr.get_size(); size = 2 * size) 
    { 
        for (int left = 0; left < arr.get_size(); left += 2 * size) 
        { 
            int mid = left + size; 
            int right;
            if ((left + 2 * size) < (arr.get_size()))
                right = (left + 2 * size);
            else 
                right = arr.get_size();
            if (mid < right) 
                merge(arr, left, mid, right); 
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
        vec.push_back(rand() % 1000);
    }
    std::cout << "Начальный массив:" << std::endl;
    std::cout << vec;
    int minrun = count_minrun(size);
    timsort(vec, minrun);
    std::cout << "Отсоритированный массив:" << std::endl;
    std::cout << vec;    
    return 0;
}