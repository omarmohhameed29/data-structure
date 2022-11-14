#include "deque.h"
#include <iostream>
#include <vector>
using namespace std;



Node *head{};
Node *tail{};

My_Deque::My_Deque()
{
    size  = 0;
    head = tail = nullptr;

    
}






My_Deque::~My_Deque()
{
}

// link two nodes to each other
void link(Node *first, Node *second)
{
    if (first)
        first->next = second;
    if (second)
        second->prev = first;
}

// return last number in the deque
int My_Deque::end()
{
    if (size == 0)
    {
        return -1;
    }
    return tail->data;
}

// return first number in the deque
int My_Deque::begin()
{
    if (size == 0)
    {
        return -1;
    }
    return head->data;
}

// add new element in the end of the deque
void My_Deque::push_back(int value)
{
    Node *item = new Node(value);
    if (!head)
        head = tail = item;
    else
    {
        link(tail, item);
        tail = item;
    }
    size++;
}

// add new element in the front of the deque
void My_Deque::push_front(int value)
{
    Node *item = new Node(value);
    if (!head)
        head = tail = item;
    else
    {
        link(item, head);
        head = item;
    }
    size++;
}

// return last number and remove it
int My_Deque::pop_back()
{
    if (size == 0)
    {
        return -1;
    }
    int last = tail->data;
    if (size == 1)
    {
        delete head;
        head = tail = nullptr;
        size = 0;
        return last;
    }
    Node *temp = tail->prev;
    delete tail;
    tail = temp;
    tail->next = nullptr;
    size--;
    return last;
}

// return first element and remove it
int My_Deque::pop_front()
{
    if (size == 0)
    {
        return -1;
    }
    int first = head->data;
    if (size == 1)
    {
        delete head;
        head = tail = nullptr;
        size = 0;
        return first;
    }
    Node *temp = head->next;
    delete head;
    head = temp;
    head->prev = nullptr;
    size--;
    return first;
}

// convert deque to vector
vector<int> My_Deque::toVector()
{
    vector<int> values;
    for (Node *cur = head; cur; cur = cur->next)
        values.push_back(cur->data);
    return values;
}

// print deque elements
void My_Deque::print()
{
    if (size == 0)
    {
        cout << "Empry list\n";
        return;
    }
    for (Node *cur = head; cur; cur = cur->next)
        cout << cur->data << " ";
    cout << "\n";
}

// clear the deque
void My_Deque::clear()
{
    head = tail = nullptr;
    size = 0;
}

// get the size of the deque
int My_Deque::get_size()
{
    return size;
}

void print(){
    for(Node *cur = head; cur; cur = cur->next)
        cout<<cur->data<<" ";
    cout<<"\n";
}