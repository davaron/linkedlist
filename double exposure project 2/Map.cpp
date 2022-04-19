#include "Map.h"
//default map constructor implementation
Map::Map() {
	//empty map has nullptr tail and head
	mapSize = 0;
	head = nullptr;
	tail = nullptr;
}
//destructor implementation
Map::~Map() {
	Node* p = head;
	while (p != nullptr) {
		//ptr to iterate through map
		Node* n = p->next;
		//delete current node
		delete p;
		//move onto next node in the list
		p = n;
	}
}
Map::Map(const Map& old) {
	//basically make new nodes and link the nexts and prevs
	//copying size of the map
	mapSize = old.mapSize;
	//set-up for empty map
	head = nullptr;
	tail = nullptr;
	//if it's an one-item map
	if (mapSize == 1) {
		Node* p = old.head;
		Node* n = new Node;
		//copy key and value of single node over to the new map
		n->key = p->key;
		n->value = p->value;
		//one-item map, no previous/next nodes
		n->next = nullptr;
		n->prev = nullptr;

		//head and tail point to the same node
		head = n; 
		tail = n;
	}
	else if (mapSize == 2) {
		//for two-item map, head and tail point at the first and second node, respectively.
		Node* p = old.head;
		//allocating first node
		Node* first = new Node;
		//first item, no previous node
		first->prev = nullptr;
		//copy key and value from source map
		first->key = p->key;
		first->value = p->value;
		//set head to first node
		head = first;
		//move to next node
		p = p->next;
		//allocate last node
		Node* last = new Node;
		//since it's the last node, there's no node after
		last->next = nullptr;
		//node before is the first node
		last->prev = first;
		//copy key and value from old map
		last->key = p->key;
		last->value = p->value;
		//set the next of first node to this node
		first->next = last;
		//set tail to this node
		tail = last;
	}
	else if (mapSize > 2) {
		Node* p = old.head;

		//first node, no previous node
		Node* first = new Node;
		first->prev = nullptr;
		//dopy data over from source map
		first->key = p->key;
		first->value = p->value;
		head = first;
		//middle nodes
		//second node needs a reference to this first node
		Node* before = first;
		p = p->next;
		while (p->next != nullptr) {
			Node* middle = new Node;
			//set current node's previous to the node before this one
			middle->prev = before;
			//copy key and value over
			middle->key = p->key;
			middle->value = p->value;
			//set previous node's next to this new node
			before->next = middle;
			//make [before] this node, so that the next node has a reference to this node
			before = middle;
			//move onto the next node in the source map
			p = p->next;
		}
		//last node, no node after
		Node* last = new Node;
		last->next = nullptr;
		//copy key and value over from source map
		last->key = p->key;
		last->value = p->value;
		//previous node's next pointer to point to the last node
		before->next = last;
		//last node prev to point to the node before this one
		last->prev = before;
		//last node, so tail points at last
		tail = last;
	}
}
Map& Map::operator=(const Map& src)
{
	if (this != &src)
	{
		//use copy constructor to copy src to tempMap
		Map tempMap(src);
		//this map and tempMap swap essentially assigning src to this map
		swap(tempMap);
	}
	return *this;
}
bool Map::empty()  const {
	//if head is nullptr, the list is empty
	if (head == nullptr) {
		//map is empty! : true
		return true;
	}
	//map is not empty! : false
	return false;
}

//return size of the map
int Map::size() const {
	return mapSize;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
	//if the map already has the key, return false because it can't be added
	if (contains(key)) {
		return false;
	}
	//the map doesn't contain the key
	else {
		//add the item to the map and increase size by 1
		addItem(key, value);
		mapSize++;
		return true;
	}
}

bool Map::update(const KeyType& key, const ValueType& value) {
	//if map has no items or doesn't contain the key, return false because the map wasn't changed
	if (mapSize == 0 || !contains(key))
		return false;
	Node* p = head;
	//loop through the map to find the key that matches
	while (p != nullptr) {
		if (p->key == key) {
			//set the value to the new value
			p->value = value;
			return true;
		}
		//go to next node
		p = p->next;
	}
	return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
	//if it already has the key, update the value
	if (contains(key))
		update(key, value);
	//if it doesn't have the key, insert it
	else
		insert(key, value);
	return true;
}
bool Map::erase(const KeyType& key) {
	//no items to delete / key isn't in the map : map wasn't changed, so return false
	if (mapSize == 0 || !contains(key))
		return false;
	Node* p = head;
	//loop through the list to find the node that has the matching key
	while (p != nullptr) {
		if (p->key == key) {
			//key found! leave the loop
			break;
		}
		//move onto the next node
		p = p->next;
	}
	//check if the node being deleted is the head or tail, respond accordingly
	//also, one-item maps
	//one-item map, head and tail are nullptr because it's now an empty list, decrement size by 1
	if (mapSize == 1) {
		head = nullptr;
		tail = nullptr;
		delete p;
		mapSize--;
		return true;
	}
	//head of map is being deleted
	else if (p == head) {
		//new head is the succeeding node of the one being deleted
		head = p->next;
		//succeeding node is new head, so there's no previous node
		head->prev = nullptr;
		delete p;
		mapSize--;
		return true;
	}
	//tail of map is being deleted
	else if (p == tail) {
		//tail now points at the node preceding the one being deleted
		tail = p->prev;
		//preceding node is new tail, so there's no node after this one
		tail->next = nullptr;
		delete p;
		mapSize--;
		return true;
	}
	//some node in the middle is being deleted
	else {
		//link the nodes adjacent to this one together
		Node* before = p->prev;
		Node* after = p->next;
		before->next = after;
		after->prev = before;
		delete p;
		mapSize--;
		return true;
	}
}
bool Map::contains(const KeyType& key) const {
	//empty map, has no items to contain
	if (mapSize == 0) {
		return false;
	}
	//loop through the map, checking if the key matches one in the map
	Node* p = head;
	while (p != nullptr) {
		if (p->key == key) {
			return true;
		}
		p = p->next;
	}
	//key wasn't found
	return false;
}
bool Map::get(const KeyType& key, ValueType& value) const {
	//no items to get!
	if (mapSize == 0)
		return false;
	//go through list to find matching key
	Node* p = head;
	while (p != nullptr) {
		if (p->key == key) {
			//key found, change value
			value = p->value;
			return true;
		}
		p = p->next;
	}
	//key wasn't found
	return false;
}
bool Map::get(int i, KeyType& key, ValueType& value) const {
	// looking for item greater than all items including itself, empty list, negative
	if (i >= mapSize || mapSize == 0 || i < 0) {
		return false;
	}
	Node* p = head;
	int greaterCount = 0;
	//since the list is sorted alphabetically, finding i is like finding the index in an array
	while (greaterCount != i) {
		p = p->next;
		//when greaterCount and i are equivalent, then the correct item was found
		greaterCount++;
	}
	//copy key and value over
	key = p->key;
	value = p->value;
	return true;
}
void Map::swap(Map& other) {
	//swap heads
	Node* tempHead = head;
	head = other.head;
	other.head = tempHead;

	//swap tails
	Node* tempTail = tail;
	tail = other.tail;
	other.tail = tempTail;

	//swap sizes
	int tempSize = mapSize;
	mapSize = other.mapSize;
	other.mapSize = tempSize;
}
void Map::addToFront(const KeyType& key, const ValueType& value) {
	Node* p = new Node;
	//assign key and value
	p->key = key;
	p->value = value;
	//head still points at the old first node, next uses this fact to point at it
	p->next = head;
	//first node, no node before
	p->prev = nullptr;
	//one-item map, tail should also point at this node
	if (head == nullptr) {
		tail = p;
	}
	//old first node's previous should now be this node, not nullptr
	else {
		head->prev = p;
	}
	//this new node is the new head
	head = p;
}

void Map::addToRear(const KeyType& key, const ValueType& value) {
	//empty list, add to front
	if (head == nullptr) {
		addToFront(key, value);
	}
	Node* p = new Node;
	//assign key and value
	p->key = key;
	p->value = value;
	//last node, no node after
	p->next = nullptr;
	//tail still points at the old last node, prev uses this to point to it
	p->prev = tail;
	//tail still points at old last node, set its next to this node
	tail->next = p;
	//new node is now the last one, tail points here
	tail = p;
}

void Map::addItem(const KeyType& key, const ValueType& value) {
	//if adding to empty list, add to the front
	if (head == nullptr) {
		addToFront(key, value);
		return;
	}
	//first node's key is greater than new key, add item to front
	else if (head->key > key) {
		addToFront(key, value);
		return;
	}
	//last node's key is less than new key, add new item to the end of the list
	else if (tail->key < key) {
		addToRear(key, value);
		return;
	}
	else {
		Node* n = head;
		while (n->next != nullptr) {
			//see if the next node's key is greater than the key we want to add, if it's greater, then we know to insert right before it
			if (n->next->key > key) {
				//found nodes to insert between
				break;
			}
			n = n->next;
		}
		//N POINTS TO THE NODE RIGHT BEFORE WHERE WE WANT TO ADD
		//inserting p between the node and its succeeding node
		Node* p = new Node;
		p->key = key;
		p->value = value;
		//set the next of the added node 
		p->next = n->next;
		//set the previous of the added node
		p->prev = n;

		//setting corresponding next and prev of the old nodes
		n->next->prev = p;
		n->next = p;
	}
}
bool merge(const Map& m1, const Map& m2, Map& result) {
	result = Map();
	KeyType k;
	ValueType v;
	bool noSpecialKey = true;
	for (int i = 0; i < m1.size(); i++) {
		m1.get(i, k, v);
		result.insert(k, v);
	}
	for (int i = 0; i < m2.size(); i++) {
		m2.get(i, k, v);
		//if insertion failed, then combined already contains k
		if (!result.insert(k, v)) {
			ValueType comparisonValue;
			result.get(k, comparisonValue);
			// if the key and values both match, there's no special key
			if (comparisonValue == v) {
				noSpecialKey = true;
			}
			// keys match, but values don't
			else {
				result.erase(k);
				noSpecialKey = false;
			}
		}
	}
	return noSpecialKey;
}
void reassign(const Map& m, Map& result) {
	result = Map();
	//empty map, no reassignment
	if (m.size() == 0) {
		return;
	}
	//one-item map, no reassignment
	else if (m.size() == 1) {
		result = m;
		return;
	}
	//swap values add it to result
	else if (m.size() == 2) {
		KeyType k1;
		ValueType v1;
		KeyType k2;
		ValueType v2;
		m.get(0, k1, v1);
		m.get(1, k2, v2);
		result.insert(k1, v2);
		result.insert(k2, v1);
	}
	//shift values down by 1
	else {
		KeyType k1;
		ValueType v1;
		KeyType k2;
		ValueType v2;
		for (int i = 0; i < m.size()-1; i++) {	
			m.get(i, k1, v1);
			m.get(i+1, k2, v2);
			result.insert(k1, v2);
		}
		//place value of first element as the last element's value
		m.get(0, k1, v1);
		result.insert(k2, v1);
		return;
	}
}
