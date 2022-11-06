#include <iostream>
using namespace std;
struct Node
{
    int data{};
    Node *next{};
    Node(int data) : data(data) {}

    ~Node() {}
};
class LinkedList
{
private:
    Node *head{};
    Node *tail{};
    int length = 0;

public:
    // Destructor
    ~LinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    // print with while loop
    void print1()
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << "\n";
    }
    // print with for loop
    void print2()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }

    // insert node at end of linked list
    void insert_end(int value)
    {
        Node *last = new Node(value);
        if (!head)
            head = tail = last;
        else
        {
            tail->next = last;
            tail = last;
        }
        length++;
    }

    // insert node at beggining of linked list
    void insert_front(int value)
    {
        Node *temp = new Node(value);
        temp->next = head;
        head = temp;
        length++;
        if (length == 1)
            tail = head;
    }

    // return node of index n with 1 based indexing
    Node *get_nth(int n)
    {
        int index = 1;
        for (Node *cur = head; cur; cur = cur->next, index++)
        {
            if (index == n)
                return cur;
        }
        return nullptr;
    }

    // return node of index n with 1 based indexing from the back
    Node *get_nth_from_back(int n)
    {
        if (n > length)
            return nullptr;
        return get_nth(length - n + 1);
    }

    // find the index of node(value)
    int search(int value)
    {
        int index = 0;
        for (Node *cur = head; cur; cur = cur->next, index++)
        {
            if (cur->data == value)
                return index;
        }
        return -1;
    }
    // find the index of node(value) and shift it one step to left
    int improved_search(int value)
    {
        int index = 0;
        for (Node *cur = head, *prev = nullptr; cur; prev = cur, cur = cur->next, index++)
        {
            if (cur->data == value)
            {
                if (!prev)
                    return index;
                swap(prev->data, cur->data);
                return index - 1;
            }
        }
        return -1;
    }

    // delete first node
    void delete_front()
    {
        Node *temp = head->next;
        delete head;
        head = temp;
        length--;
    }

    // check whether two lists are same or not(with respect to their length and value of each tow corresponding nodes)
    bool is_same(const LinkedList &list)
    {
        if (length != list.length)
            return false;
        Node *list_head = list.head;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->data != list_head->data)
            {
                return false;
            }
            list_head = list_head->next;
        }
        return true;
    }

    // check whether two lists are same or not(with respect to their length and value of each tow corresponding nodes) without using of length variable
    bool is_same_without_length(const LinkedList &list)
    {
        Node *head1 = head, *head2 = list.head;
        while (head1 && head2)
        {
            if (head1->data != head2->data)
                return false;
            head1 = head1->next;
            head2 = head2->next;
        }
        return !head1 && !head2;
    }
};

int main()
{

    return 0;
}
