//Programmer: PIlkyu Han
//Programmer's ID: 1492141

#ifndef FP_AssociativeArray_h
#define FP_AssociativeArray_h

#include <vector>
using namespace std;

// class declaration
template <typename K, typename V>
class AssociativeArray
{
    // struct definition
    struct Node
    {
        K key;
        V value;
        Node *next;
    };

    Node *firstNode;
    int siz;

public:
    AssociativeArray(){firstNode = 0; siz = 0;}
    AssociativeArray(const AssociativeArray<K, V> &);
    AssociativeArray<K, V> &operator=(const AssociativeArray<K, V> &);
    ~AssociativeArray();
    V operator[](const K &) const;
    V &operator[](const K &);
    bool containsKey(const K &) const;
    void deleteKey(const K &);
    vector<K> keys() const;
    int size() const { return siz; }
    void clear();
};

// copy constructor
template <typename K, typename V>
AssociativeArray<K, V>::AssociativeArray(const AssociativeArray<K, V> &original)
{
    firstNode = 0;      // stack version
    Node *lastNode = 0; // temporary tail
    siz = original.siz;
    for (Node *p = original.firstNode; p; p = p->next)
    {
        Node *temp = new Node;
        temp->key = p->key;
        temp->value = p->value;
        temp->next = 0;
        if (lastNode)
            lastNode->next = temp;
        else
            firstNode = temp;
        lastNode = temp;
    }
}

// assignment operator
template <typename K, typename V>
AssociativeArray<K, V> &AssociativeArray<K, V>::operator=(const AssociativeArray<K, V> &original)
{
    if (this != &original)
    {   // stack version
        // deallocate existing list
        while (firstNode)
        {
            Node *p = firstNode->next;
            delete firstNode;
            firstNode = p;
        }
        // build new AssociativeArray
        Node *lastNode = 0; // temporary tail
        for (Node *p = original.firstNode; p; p = p->next)
        {
            Node *temp = new Node;
            temp->key = p->key;
            temp->value = p->value;
            temp->next = 0;
            if (lastNode)
                lastNode->next = temp;
            else
                firstNode = temp;
            lastNode = temp;
        }
        siz = original.siz;
    }
    return *this;
}

// destructor
template <typename K, typename V>
AssociativeArray<K, V>::~AssociativeArray()
{
    while (firstNode)
    {
        Node *p = firstNode;
        firstNode = firstNode->next;
        delete p;
    }
}

// getter function
template <typename K, typename V>
V AssociativeArray<K, V>::operator[](const K &key) const
{
    for (Node *p = firstNode; p; p = p->next)
    {
        if (p->key == key)
        {
            return p->value;
        }
    }
    return V();
}

// setter function
template <typename K, typename V>
V &AssociativeArray<K, V>::operator[](const K &key)
{
    for (Node *p = firstNode; p; p = p->next)
    {
        if (p->key == key)
        {
            return p->value;
        }
    }

    Node *temp = new Node;
    temp->key = key;
    temp->value = V();
    temp->next = firstNode;
    firstNode = temp;
    siz++;
    return firstNode->value;
}

template <typename K, typename V>
bool AssociativeArray<K, V>::containsKey(const K &key) const
{
    for (Node *p = firstNode; p; p = p->next)
    {
        if (p->key == key)
        {
            return true;
        }
    }
    return false;
}

template <typename K, typename V>
void AssociativeArray<K, V>::deleteKey(const K &key)
{
    Node *p = 0;
    Node *previous = 0;
    for (p = firstNode; p; previous = p, p = p->next)
    {
        if (p->key == key)
        {
            break;
        }
    }
    if (p)
    {
        siz--;
        if (previous)
        {
            previous->next = p->next;
        }
        else
        {
            firstNode = p->next;
        }
        delete p;
    }
}

template <typename K, typename V>
vector<K> AssociativeArray<K, V>::keys() const
{
    vector<K> keysVec;
    for (Node *p = firstNode; p; p = p->next)
    {
        keysVec.push_back(p->key);
    }
    return keysVec;
}

template <typename K, typename V>
void AssociativeArray<K, V>::clear()
{
    while (firstNode)
    {
        Node *p = firstNode;
        firstNode = firstNode->next;
        delete p;
        siz--;
    }
}

#endif