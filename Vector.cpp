#include <iostream>
#include <cassert>
using namespace std;

class Vector
{
private:
    int *arr = nullptr;
    int size = 0;
    int capacity{};

public:
    Vector()
    {
        arr = nullptr;
        size = 0;
    }

    // constructor

    Vector(int capacity) : capacity(capacity)
    {
        if (capacity < 0)
            capacity = 1;
        // capacity = size * 2;
        arr = new int[capacity]{};
    }

    // destructor
    ~Vector()
    {
        delete[] arr;
        arr = nullptr;
    }

    // return value of arr[index]
    int get(int index)
    {
        if (index >= size || index < 0)
            return -1;
        return arr[index];
    }

    // set arr[index] = value
    void set(int index, int value)
    {
        assert(index >= 0 && index < size);
        arr[index] = value;
    }

    // print whole vector
    void print()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << "\n";
    }

    // return index of ceratain value
    int find(int value)
    {
        for (int i = 0; i < size; i++)
            if (arr[i] == value)
                return i;
        cout << "Not found \n";
    }

    // return first element
    int get_front()
    {
        return arr[0];
    }

    // return last element
    int get_back()
    {
        return arr[size - 1];
    }

    // add element at the end of array
    void push_back(int value)
    {
        if (size == capacity)
            expand();
        arr[size++] = value;
    }

    // double the capacity of Vector
    void expand()
    {
        capacity *= 2;
        int *temp = new int[capacity];
        for (int i = 0; i < size; i++)
            temp[i] = arr[i];
        swap(temp, arr);
        delete[] temp;
    }

    // insert certian value at certain index
    void insert(int index, int value)
    {
        if (size == capacity)
            expand();
        for (int i = size; i > index; i--)
            arr[i] = arr[i - 1];
        arr[index] = value;
        size++;
    }

    // rotate Vector one step to right
    void rotate_right_once()
    {
        int temp = arr[size - 1];
        for (int i = size - 1; i > 0; i--)
            arr[i] = arr[i - 1];
        arr[0] = temp;
    }

    // rotate Vector one step to left
    void rotate_left_once()
    {
        int temp = arr[0];
        for (int i = 1; i < size; i++)
            arr[i - 1] = arr[i];
        arr[size - 1] = temp;
    }

    // rotate Vector nth step(s) to right
    void rigth_rotaion_nth_times(int n)
    {
        while (n--)
            rotate_right_once();
    }

    // return last element and remove it
    int pop(int idx)
    {
        assert(idx > 0 && idx < size);
        int deleted = arr[idx];
        for (int i = idx; i < size - 1; i++)
            arr[i] = arr[i + 1];
        size--;
        return deleted;
    }

    // return index of certain value and shift it one step left
    int find_transposition(int value)
    {
        for (int i = 0; i < size; i++)
            if (arr[i] == value)
            {
                arr[i] = arr[i - 1];
                arr[i - 1] = value;
                return i - 1;
            }
        return -1;
    }
};

int main()
{
    Vector v(10);
    for (int i = 1; i <= 10; i++)
        v.push_back(i);
    v.print();
    cout << v.find_transposition(5) << endl;
    v.print();
    return 0;
}
