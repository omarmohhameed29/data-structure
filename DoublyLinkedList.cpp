#include <iostream>
using namespace std;

struct Node
{
    int data{};
    Node *next{};
    Node *prev{}; // Previous node!

    Node(int data) : data(data) {}

    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }

    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class LinkedList
{
private:
    Node *head{};
    Node *tail{};
    int length = 0;

public:
    // print nodes values in same order
    void print()
    {
        for (Node *cur = head; cur; cur = cur->next)
            cout << cur->data << " ";
        cout << "\n";
    }
    // print nodes values in reversed order
    void print_reversed()
    {
        for (Node *cur = tail; cur; cur = cur->prev)
            cout << cur->data << " ";
        cout << "\n";
    }

    // link two nodes with each other
    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }

    // add node at the front of the list
    void insert_front(int value)
    {
        Node *item = new Node(value);
        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        length++;
    }

    // add node at the end of the list
    void insert_end(int value)
    {
        Node *item = new Node(value);
        if (!head)
            head = tail = item;
        else
        {
            link(tail, item);
            tail = item;
        }
        length++;
    }

    // add new node between two existing nodes
    void embed_after(Node *node_before, int value)
    {
        Node *middle = new Node(value);
        Node *node_after = node_before->next;
        link(node_before, middle);
        link(middle, node_after);
    }

    // insert nodes in ascending order
    void insert_sorted(int value)
    {
        if (!length || value < head->data)
            insert_front(value);
        else if (value > tail->data)
            insert_end(value);
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
                if (cur->data >= value)
                {
                    embed_after(cur->prev, value);
                    break;
                }
        }
        length++;
    }

    // delete first node
    void delete_front()
    {
        if (!head)
            return;
        Node *cur = head->next;
        delete head;
        length--;
        if (!length)
        {
            head = tail = nullptr;
            return;
        }
        head = cur;
        head->prev = nullptr;
    }

    // delete last node
    void delete_end()
    {
        if (!head)
            return;
        Node *cur = tail->prev;
        delete tail;
        length--;
        if (!length)
        {
            head = tail = nullptr;
            return;
        }
        tail = cur;
        tail->next = nullptr;
    }

    // delete a node and link its previous with its next
    Node *delete_and_link(Node *cur)
    {
        Node *ret = cur->prev;
        link(cur->prev, cur->next);
        delete cur;
        length--;
        return ret;
    }

    // delete first node with value = key
    void delete_node_with_key(int value)
    { // O(n) time - O(1) memory
        if (!length)
            cout << "Empty list!\n";
        else if (head->data == value)
            delete_front();
        else if (tail->data == value)
            delete_end();
        else
        {
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (cur->data == value)
                {
                    delete_and_link(cur);
                    return;
                }
            }
            cout << "Value not found!\n";
        }
    }

    // It will delete all nodes of the given key
    void delete_all_nodes_with_key(int value)
    {
        if (!length)
            return;
        insert_front(-value); // any dummy value to avoid RTE when deleted the head
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->data == value)
            {
                length--;
                cur = delete_and_link(cur);
                if (!cur->next)
                    tail = cur;
            }
        }
        delete_front();
    }

    // Given a list, delete all nodes at even positions (2, 4, 6, etc)
    void delete_even_positions()
    {
        if (length < 2)
            return;
        for (Node *cur = head->next; cur; cur = cur->next->next)
        {
            cur = delete_and_link(cur);
            length--;
            if (!cur->next || !cur->next->next)
            {
                tail = cur;
                return;
            }
        }
    }

    // Given a list, delete all nodes at odd positions (1, 3, 5, etc)
    void delete_odd_positions()
    {
        insert_front(-999);
        delete_even_positions();
        delete_front();
    }

    // check whether list is palindrome or not
    bool is_palindrome()
    {
        if (length < 2)
            return true;
        int index = 1;
        Node *cur1 = head;
        Node *cur2 = tail;
        while (index++ < (length / 2 + 1))
        {
            if (cur1->data != cur2->data)
                return false;
            cur1 = cur1->next;
            cur2 = cur2->prev;
        }
        return true;
    }

    // finding middle value using length variable
    int middle_value()
    {
        if (length < 2)
            return -1;
        int len = length / 2;
        Node *cur = head;
        while (len--)
        {
            cur = cur->next;
        }
        return cur->data;
    }

    // finding middle value using head and tail pointers only
    int middle_value2()
    {
        Node *start = head;
        Node *end = tail;
        while (start != end && start->next != end)
        {
            start = start->next;
            end = end->prev;
        }
        return end->data;
    }

    // finding middle value without previous pointer, using tortoise algorithm
    int middle_value3()
    {
        Node *slow = head;
        Node *fast = head;
        while (fast && fast->next)
            slow = slow->next, fast = fast->next->next;
        return slow->data;
    }

    // return node of index n
    Node *get_nth(int n)
    {
        int cnt = 0;
        for (Node *cur = head; cur; cur = cur->next)
            if (++cnt == n)
                return cur;

        return nullptr; // still more steps needed - NOT found
    }

    // Given K, find the Kth node from forward and backward
    void swap_kth(int k)
    {
        if (k > length)
            return;
        int kth_back = length - k + 1;

        if (k == kth_back)
            return; // same node

        if (k > kth_back)
            swap(k, kth_back);

        Node *first = get_nth(k);
        Node *last = get_nth(kth_back);

        Node *first_prev = first->prev;
        Node *first_next = first->next;

        Node *last_prev = last->prev;
        Node *last_next = last->next;

        if (k + 1 == kth_back)
        { // consecutive (neighbours)
            link(first_prev, last);
            link(last, first);
            link(first, last_next);
        }
        else
        {
            link(first_prev, last);
            link(last, first_next);

            link(last_prev, first);
            link(first, last_next);
        }
        if (k == 1)
            swap(head, tail);
    }

    // reverse linked list using swap_kth function
    void reverse()
    {
        int k = 0;
        while (k++ < length / 2)
        {
            swap_kth(k);
        }
    }

    // reverse linked list
    void reverse2()
    {
        if (length < 2)
            return;
        Node *first = head;
        Node *second = head->next;
        while (second)
        {
            // Take copy of next move data
            Node *first_ = second, *second_ = second->next;
            link(second, first);              // reverse
            first = first_, second = second_; // move
        }
        swap(head, tail);
        head->prev = tail->next = nullptr;
    }

    // We would like to merge them together in O(n+m) but remain sorted
    void merge_2sorted_lists(LinkedList &other)
    { // O(n+m)
        if (!other.head)
            return;

        if (head)
        {
            Node *cur1 = head;
            Node *cur2 = other.head;
            Node *last{};
            head = nullptr;

            while (cur1 && cur2)
            {
                Node *next{};
                // pick the smallest among the 2 lists and then link it
                if (cur1->data <= cur2->data)
                {
                    next = cur1;
                    cur1 = cur1->next;
                }
                else
                {
                    next = cur2;
                    cur2 = cur2->next;
                }
                link(last, next);
                last = next;
                if (!head) // first step is the head
                    head = last;
            }
            if (cur2)
            { // our tail is from 2nd
                tail = other.tail;
                link(last, cur2);
            }
            else if (cur1)
            {
                link(last, cur1);
            }
        }
        else
        { // use its data
            head = other.head;
            tail = other.tail;
        }

        length += other.length;
    }
};
int main()
{

    return 0;
}
