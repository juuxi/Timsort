#include <cstddef>
#include <iostream>

template<typename V>
class Vector
{
    V* arr;
    size_t size; 
    size_t full_size;
public:
    Vector() {arr = nullptr; size = 0;}
    Vector(size_t _size){arr = new V[_size]; full_size = _size; size = 0;}
    void add(size_t, V);
    void push_back(V);
    void remove(size_t);
    size_t get_size() {return size;}
    V& operator[] (size_t index);
    template <typename V2>
    friend std::ostream& operator<<(std::ostream&, Vector<V>&);
private:
    void ensure_capacity();
};

template<typename V>
void Vector<V>::add(size_t index, V _value)
{ 
    ensure_capacity();
    for (int i = size; i > int(index)-1; i--)
        arr[i] = arr[i - 1];
    arr[index] = _value;
    size++;
}

template<typename V>
void Vector<V>::push_back(V _value)
{ 
    this->add(size, _value);
}

template<typename V>
void Vector<V>::remove(size_t _pos)
{
    for (int i = _pos - 1; i < full_size; i++)
        arr[i] = arr[i+1];
    size--;
}

template<typename V>
void Vector<V>::ensure_capacity()
{
    if (size >= full_size - 1)
    {
        V* new_arr = new V[full_size * 2];
        for (int i = 0; i < size; i++)
            new_arr[i] = arr[i];
        delete[] arr;
        arr = new_arr;
        full_size *= 2;
    }
}

template<typename V>
V& Vector<V>::operator[](size_t index)
{
    return arr[index];
}

template<typename V>
std::ostream& operator<< (std::ostream& os, Vector<V>& vec)
{
    for (size_t i = 0; i < vec.get_size(); i++)
        os << vec[i] << " ";
    os << std::endl;
    return os;
}
