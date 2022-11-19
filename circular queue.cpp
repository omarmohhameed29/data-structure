#include <iostream>
#include <cassert>
using namespace std;

class Queue{
private:
    int size {};
    int added_elements {};
    int front {};
    int rear {};
    int *arr {};
public:
    Queue(int size) :
			size(size) {
		arr = new int[size];
	}

	~Queue() {
		delete[] arr;
	}

	int next(int pos){
	    pos ++;
        if(pos == size)
            pos = 0;
        return pos;
	}

	void display(){
        if(is_empty()){
            cout<<"Empty\n";
            return;
        }
        if(is_full())
            cout<<"Full\n";

        for(int cur = front, steps = 0; steps < added_elements; steps++, cur = next(cur))
            cout<<arr[cur]<<" ";
        cout<<"\n";
    }

    void enqueue(int number){
        assert(!is_full());
        arr[rear] = number;
        rear = next(rear);
        added_elements++;
    }

    int dequeue(){
        assert(!is_empty());
        int number = arr[front];
        front = next(front);
        added_elements--;
        return number;
    }

    bool is_full(){
        return added_elements == size;
    }

    bool is_empty(){
        return added_elements == 0;
    }


};

int main()
{
    Queue q(6);
    for(int i = 1; i <= 6; i++)
        q.enqueue(i);
    q.display();
    return 0;
}
