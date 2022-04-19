#ifndef _mapIncluded_
#define _mapIncluded_
#include <string>
using KeyType = std::string;
using ValueType = double;
class Map {
public:
    Map();
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    //DESTRUCTOR
    ~Map();
    //COPY CONSTRUCTOR
    Map(const Map& old);
    //ASSIGNMENT OPERATOR
    Map& operator=(const Map& rhs);
private:
    struct Node {
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
    };
    Node *head;
    Node *tail;
    int mapSize;
    void addToFront(const KeyType& key, const ValueType& value);
    void addToRear(const KeyType& key, const ValueType& value);
    void addItem(const KeyType& key, const ValueType& value);
};
bool merge(const Map& m1, const Map& m2, Map& result);
void reassign(const Map& m, Map& result);
#endif
