#include <iostream>
#include<cassert>
using namespace std;

class Vector{
private:
    int *arr = nullptr;
    int size = 0;
    int capacity{};
public:
    Vector() {
        arr = nullptr;
        size = 0;
    }

    //construc

    Vector(int capacity) :
           capacity(capacity) {
            if(capacity < 0)
                capacity = 1;
            //capacity = size * 2;
            arr = new int[capacity] {};
    }

    ~Vector(){
        delete[] arr;
        arr = nullptr;
    }

    int get(int index){
        if(index >= size || index < 0)
            return -1;
        return arr[index];
    }

    void set(int index, int value){
        assert(index >= 0 && index < size);
        arr[index] = value;

    }

    void print(){
        for(int i = 0; i < size; i++)
            cout<<arr[i]<<" ";
        cout<<"\n";
    }

    int find(int value){
        for(int i = 0; i < size; i++)
            if(arr[i] == value)
                return i;
        cout<<"Not found \n";
    }

    int get_front(){
        return arr[0];
    }

    int get_back(){
        return arr[size-1];
    }

    void push_back(int value){
        if (size == capacity)
            expand();
        arr[size++] = value;
    }

    void expand(){
        capacity *= 2;
        int *temp = new int[capacity];
        for(int i = 0; i < size; i++)
            temp[i] = arr[i];
        swap(temp, arr);
        delete[] temp;

    }

    void insert(int index,  int value){
        if(size == capacity)
            expand();
        for(int i = size; i > index; i--)
            arr[i] = arr[i-1];
        arr[index] = value;
        size++;

    }

    void rotate_right_once(){
        int temp = arr[size-1];
        for(int i = size-1; i > 0; i--)
            arr[i] = arr[i - 1];
        arr[0] = temp;
    }

    void rotate_left_once(){
        int temp = arr[0];
        for(int i = 1; i < size; i++)
            arr[i - 1] = arr[i];
        arr[size - 1] = temp;
    }

    void rigth_rotaion_nth_times(int n){
        while(n--)
            rotate_right_once();
    }

    int pop(int idx){
        assert(idx > 0 && idx < size);
        int deleted = arr[idx];
        for(int i = idx; i < size-1; i++)
            arr[i] = arr[i+1];
        size--;
        return deleted;
    }

    int find_transposition(int value){
        for(int i = 0; i < size; i++)
            if(arr[i] == value){
                arr[i] = arr[i - 1];
                arr[i-1] = value;
                return i-1;
            }
        return -1;
    }


};

int main() {
    Vector v(10);
    for(int i = 1; i <= 10; i++)
        v.push_back(i);
    v.print();
    cout<<v.find_transposition(5)<<endl;
    v.print();
	return 0;

}


