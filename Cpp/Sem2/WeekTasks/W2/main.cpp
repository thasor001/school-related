#include "iostream"
#include "string"




template <typename key, typename value>
class map {
private:
    int map_capacity, map_size, reserve;

    std::pair<key, value> *data;
public:
    map() { map_size = 0, map_capacity = 1, data = new std::pair<key, value>[map_capacity]; }
    ~map() { delete [] data; }

    int size() { return map_size; }
    int capacity() { return map_capacity; }

    void display() {
        for (int i = 0; i < map_size; i++)
            std::cout << "Key   : " << data[i].first << std::endl
                      << "Value : " << data[i].second << std::endl;
    }

    void pair_insert(const key k, const value v) {
        int count = map::find(k);

        if (count == -1) {
            if (map_size >= map_capacity)
                map::resize(map_capacity*2);

            data[map_size] = std::make_pair(k, v);
            map_size++;
        } else
            data[count] = std::make_pair(k, v);
    }

    int find(const key k) {
        for (int i = 0; i < map_size; i++)
            if (data[i].first == k)
                return i;

        return -1;
    }

    value* get(const key k) {
        int count = map::find(k);

        if (count == -1) { return nullptr; }

        return &data[count].second;
    }

    bool remove(const key k) {
        int count = map::find(k);
        if (count == -1) { return false; }

        for (int i = count; i < map_size; i++)
            data[i] = data[i + 1];

        map_size--;
        return true;
    }

    bool resize(const int size) {
        if (size < 0 || size == map_capacity)
            return false;

        auto *buffer = new std::pair<key, value>[size];

        int elements_to_copy = (size > map_size) ? map_size : size;
        for (int i = 0; i < elements_to_copy; i++)
            buffer[i] = data[i];

        delete [] data;

        data = buffer;
        map_capacity = size;

        if (size < map_size)
            map_size = size;

        return true;
    }
};

int main() {
    map<std::string, int> test;

    test.pair_insert("Bendik", 37);
    test.pair_insert("Bendik", 32);
    test.pair_insert("Samuel", 38);
    test.pair_insert("Tharald", 39);

    test.remove("Bendik");

    test.display();

    int *number = test.get("Bendik");

    std::cout << "NUMBER OF BENDIK : " << *number << std::endl;

    std::cin.get();
    return 0;
}