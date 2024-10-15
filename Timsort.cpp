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

void insert_sort(Vector<int> &arr)
{
  for(size_t i = 1; i < arr.get_size(); i++)
  {
    int value = arr[i];
    int j;
    for (j = i-1; j >= 0 && value < arr[j]; j--)
      arr[j+1] = arr[j];
    arr[j] = value;
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
        vec.push_back(rand());
    }
    return 0;
}