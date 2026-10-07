#pragma once
#include <initializer_list>
#include <stdexcept>
#include <memory>

template<typename T>
class MyArray
{
private:
    std::unique_ptr<T[]> _data;
    int _size;
    int _capacity; 

    void resize(int new_capacity, int value = 1);

public:
    MyArray();
    MyArray(int capacity);
    MyArray(std::initializer_list<T> list);
    MyArray(const MyArray& other);
    
    void setCapacity(int new_capacity);
    
    inline int getSize() const;

    inline int getCapacity() const;


    void pushBack(T value);

    void popBack();

    bool isEmpty() const;

    void clear();

    T& front();

    T& back();

    void insert(int index, const T& value);

    void erase(int index);

    bool contains(const T& value) const;

    int indexOf(const T& value) const;

    void shrinkToFit();
     
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    MyArray& operator=(const MyArray& other);
    


    ~MyArray();
};

template<typename T>
void MyArray<T>::resize(int new_capacity, int value)
{
        if (new_capacity <= 0) 
        {
            throw std::invalid_argument("resize(): capacity must be positive!");
        }

        int temp_capacity = new_capacity * value;

        std::unique_ptr<T[]> temp_arr;

        try
        {
            temp_arr = std::make_unique<T[]>(temp_capacity);
        }
        catch (const std::bad_alloc&)
        {
            throw;
        }

        if (temp_capacity < _size)
        {
            _size = temp_capacity;
        }

        for (size_t i = 0; i < _size; i++)
        {
            temp_arr[i] = _data[i];
        }

        _data = std::move(temp_arr);
        _capacity = temp_capacity;
}

template<typename T>
MyArray<T>::MyArray() : _size(0), _capacity(1)
{
    _data = std::make_unique<T[]>(_capacity);
}

template<typename T>
MyArray<T>::MyArray(int capacity) : _size(0), _capacity(capacity)
{
    if (capacity <= 0)
    {
        throw std::invalid_argument("Constructor: capacity must be > 0 !");
    }
    _data = std::make_unique<T[]>(_capacity);
}

template<typename T>
MyArray<T>::MyArray(std::initializer_list<T> list)
    : _size(list.size()), _capacity(list.size())
{
    _data = std::make_unique<T[]>(_capacity);

    int i = 0;

    for (const T& elem : list)
    {
        _data[i++] = elem;
    }
}

template<typename T>
MyArray<T>::MyArray(const MyArray& other)
{
    _capacity = other._capacity;
    _size = other._size;
    _data = std::make_unique<T[]>(_capacity);
    for (size_t i = 0; i < _size; i++)
    {
        _data[i] = other._data[i];
    }
}

template<typename T>
MyArray<T>::~MyArray()
{
}

template<typename T>
void MyArray<T>::setCapacity(int new_capacity)
{
    if (new_capacity > 0)
    {
        resize(new_capacity);
    }
}

template<typename T>
int MyArray<T>::getSize() const
{
    return _size;
}

template<typename T>
int MyArray<T>::getCapacity() const
{
    return _capacity;
}

template<typename T>
void MyArray<T>::pushBack(T value)
{
    if (_size == _capacity)
    {
        resize(_capacity, 2);
    }

    _data[_size] = value;
    _size++;
}

template<typename T>
void MyArray<T>::popBack()
{
    if (_size > 0)
    {
        _size--;
        _data[_size] = {};
    }
}

template<typename T>
bool MyArray<T>::isEmpty() const
{
    return _size == 0;
}

template<typename T>
void MyArray<T>::clear()
{
    _size = 0;
}

template<typename T>
T& MyArray<T>::front()
{
return _data[0];
}

template<typename T>
T& MyArray<T>::back()
{
    return _data[_size - 1];
}

template<typename T>
void MyArray<T>::insert(int index, const T& value)
{
    if (index < _size)
    {
        _size++;
        if (_size >= _capacity)
        {
            resize(_capacity, 2);
        }

        for (int i = _size; i > index; i--)
        {
            _data[i] = _data[i - 1];
        }

        _data[index] = value;
    }
}

template<typename T>
void MyArray<T>::erase(int index)
{
    if (index < _size)
    {
        for (int i = index; i < _size - 1; i++)
        {
            _data[i] = _data[i + 1];
        }

        _size--;
    }
}

template<typename T>
bool MyArray<T>::contains(const T& value) const
{
    for (int i = 0; i < _size; i++)
        if (_data[i] == value)
            return true;
    return false;
}

template<typename T>
int MyArray<T>::indexOf(const T& value) const
{
    for (int i = 0; i < _size; i++)
        if (_data[i] == value)
            return i;
    return -1;
}

template<typename T>
void MyArray<T>::shrinkToFit()
{
    resize(_size);
}

template<typename T>
T& MyArray<T>::operator[](size_t index)
{
    if (_size == 0)
    {
        throw std::runtime_error("operator[] : cannot access element in empty array!");
    }

    if (index >= _size || index < 0)
    {
        throw std::out_of_range("operator[] : index out of range!");
    }

    return _data[index];
}
template<typename T>
const T& MyArray<T>::operator[](size_t index) const
{
    if (index >= _size || index < 0)
    {
        throw std::out_of_range("operator[] : index out of range!");
    }

    return _data[index];
}



template<typename T>                  
MyArray<T>& MyArray<T>::operator=(const MyArray& other)
{
    if (this != &other)
    {
        _capacity = other._capacity;
        _size = other._size;
        _data = std::make_unique<T[]>(_capacity);
        for (size_t i = 0; i < _size; i++)
        {
            _data[i] = other._data[i];
        }
    }
    return *this;
}
