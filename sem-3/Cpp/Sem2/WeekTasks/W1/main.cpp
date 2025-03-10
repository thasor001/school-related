#include "iostream"
#include "string"


template<typename T>
class Vector {
private:
    int vec_size, vec_capacity, vec_reserve;
    T* data;
public:
    Vector() { vec_size = vec_reserve = 0, vec_capacity = 1, data = new T[vec_capacity]; }

    // When Allocating memory for an array in cpp "[]" it is crucial to de-allocate this memory with [],
    // this ensures that the destructor for each and every elementin the array is called.
    ~Vector() {delete [] data;}


    void insert(const T t, const int pos) {
        if (pos < 0 || pos > vec_size) {
            throw std::out_of_range("Index out of range for class Vector");
        } else if (vec_size >= vec_capacity)
                resize(vec_capacity * 2);

        for (int i = vec_size; i > pos; i--) {
            data[i] = data[i - 1];
        }
        data[pos] = t;

        vec_size++;
    }

    void display() {
        for (int i = 0; i < vec_size; i++)
            std::cout << data[i] << std::endl;
    }

    void reserve(const int t) { vec_reserve = t; }

    int size() { return vec_size; }

    bool empty() { return vec_size; }

    bool resize(const int size) {
        if (size < 0 || size == vec_size)
            return false;

        T* buffer = new T[size];

        int element_to_copy = (vec_size > size) ? size : vec_size;
        for (int i = 0; i < element_to_copy; i++)
            buffer[i] = data[i];

        delete [] data;
        data = buffer;
        vec_capacity = size;

        if (size < vec_size)
            vec_size = size;

        if (vec_capacity < vec_reserve)
            vec_reserve = vec_capacity;

        return true;
    }

    void push_back(const T t) { Vector::insert(t, vec_size); }

    void push_front(const T t) { Vector::insert(t, 0); }

    bool pop_back() {
        if (vec_size < 1)
            return false;

        vec_size--;
        return true;
    }

    bool pop_front() {
        if (vec_size < 1)
            return false;

        for (int i = 0; i < vec_size - 1; i++)
            data[i] = data[i + 1];

        vec_size--;
        return true;
    }

    int capacity() { return vec_capacity; }

};


int main() {

    Vector <int> test;

    test.push_back(2);
    test.push_back(3);
    test.push_front(1);

    for (int i = 4; i <= 11; i++)
        test.push_back(i);


    test.pop_back();
    test.pop_front();

    test.resize(4);
    test.display();

    std::cout <<"\n" << test.size() << std::endl;+

    std::cin.get();
    return 0;
}