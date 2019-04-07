#include "Map.h"
#include <iostream>

Map::Map()
{
	bucket = new Node*[tableSize];
	//shall i worry intializing every pointer to nullptr??
	//can i use curly braces initialization here?? like new Node* [11] {};

	for (int i = 0; i < tableSize; i++) {
		bucket[i] = nullptr;
	}
}

Map::~Map()
{
	for (int i = 0; i < tableSize; i++) {
		deleteTree(bucket[i]);
	}
	delete[] bucket;
}

void Map::append(const Map& rhs)
{
	KeyType tempKey;
	ValueType tempVal;

	for (int i = 0; i < rhs.size(); i++) {
		//using get and add function to create a new map
		rhs.get(i, tempKey, tempVal);
		//will rhs has duplicate keys?? No, my data stucture doesn't allow duplicates
		this->insert(tempKey, tempVal);
	}
}

//empty map???
Map::Map(const Map& rhs)
{
	bucket = new Node*[tableSize];
	for (int i = 0; i < tableSize; i++)
		bucket[i] = nullptr;

	append(rhs);
}

const Map& Map::operator=(const Map& rhs)
{
	if (&rhs != this) {
		//copy & swap???

		//why is it not logical to just to destructor here???
		for (int i = 0; i < tableSize; i++) {
			deleteTree(bucket[i]);
			bucket[i] = nullptr;
		}

		append(rhs);
	}

	return *this;
}


bool Map::empty() const
{
	for (int i = 0; i < tableSize; i++) {
		if (bucket[i] != nullptr)
			return false;
	}
	return true;
}

int Map::size() const
{
	int sum = 0;

	for (int i = 0; i < tableSize; i++) {
		sum += count(bucket[i]);
	}

	return sum;
}

//hashing string key value to an int
int Map::Convert_Key(std::string key) const
{
	int sum = 0;

	for (auto i : key)
		sum += i;

	return sum % tableSize;
}


//hashing double key value to an int
int Map::Convert_Key(double key) const
{
	int temp = (int)(13 * key); //a prime number feels right
	return temp % tableSize;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
	int hash = Convert_Key(key);
	//std::cerr << hash << std::endl;


	//bucket slot position open
	/*if (bucket[hash] == nullptr) {
		bucket[hash] = new Node(key, value);
		return true;
	}*/
	//unnecessary because "find" will check the root node too

	//same key exists
	ValueType temp;
	if (find(bucket[hash], key, temp))
		return false;

	//collision add to the BST chain
	return add(bucket[hash], key, value);
}

bool Map::update(const KeyType& key, const ValueType& value)
{
	int hash = Convert_Key(key);

	//key not found in bucket nor tree
	ValueType temp;
	if (!find(bucket[hash], key, temp))
		return false;

	return add(bucket[hash], key, value);
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
{
	int hash = Convert_Key(key);

	return add(bucket[hash], key, value);
}


bool Map::contains(const KeyType& key) const
{
	int hash = Convert_Key(key);

	if (bucket[hash] == nullptr)
		return false;

	//look for key in the BST
	ValueType temp; //is this a good practice???
	return find(bucket[hash], key, temp);
}

bool Map::erase(const KeyType& key)
{
	int hash = Convert_Key(key);

	return deleteNode(bucket[hash], key);
}


bool Map::get(const KeyType& key, ValueType& value) const
{
	int hash = Convert_Key(key);

	//found in bucket list
	if (bucket[hash]->m_key == key) {
		value = bucket[hash]->m_value;
		return true;
	}

	//in collision
	return find(bucket[hash], key, value);
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
	//checking which bucket slot is i falling into
	int rmd = i;
	for (int j = 0; j < tableSize; ++j) {

		if (bucket[j] != nullptr) {

			if (rmd > count(bucket[j]) - 1) {
				rmd = rmd - count(bucket[j]);
				//rmd = count(bucket[j]); took me an hour to realize i didnt change rmd at all
			}
			else {
				return trav(bucket[j], rmd, key, value);
			}
		}
	}

	return false;
}

void Map::swap(Map& other)
{
	Map* temp = new Map(other);

	other = *this;

	*this = *temp;

	delete temp;
}


//--------------------------------------------
//BST functions

//BST traverse to the nth node in the tree and copy its value and key
//in INORDER
bool Map::trav(Node* &p, int& i, KeyType& key, ValueType& value) const
{
	if (p == nullptr)
		return false;

	if (!trav(p->m_left, i, key, value)) {

		if (i == 0) {
			key = p->m_key;
			value = p->m_value;
			return true;
		}

		--i;

		return trav(p->m_right, i, key, value);
	}
	return true;

	//problem here is if both child nodes are null ptr, i still going to decrement itself
	/*if (!trav(p->m_left, --i, key, value)) {
		return trav(p->m_right, --i, key, value);
	}*/
}

//BST count how many nodes in one tree
int Map::count(Node* &p) const
{
	if (p == nullptr)
		return 0;

	return count(p->m_left) + count(p->m_right) + 1;
}


//BST find function which modifies the value parameter
bool Map::find(Node* &p, const KeyType& key, ValueType& value) const
{
	if (p == nullptr)
		return false;

	if (p->m_key == key) {
		value = p->m_value;
		return true;
	}

	//incursively serach the BST
	if (key < p->m_key)
		return find(p->m_left, key, value);
	return find(p->m_right, key, value);
}

//BST node delete and replace it with the deepest node
bool Map::deleteNode(Node* &p, const KeyType& key)
{
	if (p == nullptr)
		return false;

	if (p->m_key == key) {
		//case1: no child
		if (p->m_left == nullptr && p->m_right == nullptr) {
			delete p;
			p = nullptr;
			//AVOID DANGLING POINTER!!!
			return true;
		}
		else {
			KeyType tempKey;
			ValueType tempVal;
			int c = 0;
			//case2: has left child, replace with the greatest from left
			if (p->m_left != nullptr) {
				c = count(p->m_left) - 1;
				trav(p->m_left, c, tempKey, tempVal);
				p->m_key = tempKey;
				p->m_value = tempVal;
				return deleteNode(p->m_left, tempKey);
			}
			//case3: right child. replace with the greates from right
			else {
				trav(p->m_right, c, tempKey, tempVal);
				p->m_key = tempKey;
				p->m_value = tempVal;
				return deleteNode(p->m_right, tempKey);
			}
			//feel like better save the value from stack before recurse, in case of exception
			/*p->m_key = tempKey;
			p->m_value = tempVal;
			return true;*/
		}
	}

	if (key < p->m_key)
		return deleteNode(p->m_left, key);
	return deleteNode(p->m_right, key);
}

//BST adding node function (will replace the existing value if there is same key found)
//always return true
bool Map::add(Node* &p, const KeyType& key, const ValueType& value)
{
	//craete a new node at the leave
	if (p == nullptr) {
		p = new Node(key, value);
		return true;
	}

	//same key found, replace existing value with new value
	if (p->m_key == key) {
		p->m_value = value;
		return true;
	}

	//recursively adding
	if (key < p->m_key)
		return add(p->m_left, key, value);
	else
		return add(p->m_right, key, value);

}

//BST delete function
void Map::deleteTree(Node* &p)
{
	if (p != nullptr) {
		deleteTree(p->m_left);
		deleteTree(p->m_right);
		delete p;
	}
}

//BST print function
void Map::printTree(Node* &p) const
{
	if (p != nullptr) {
		printTree(p->m_left);
		std::cerr << "Key: " << p->m_key
			<< "   Value: " << p->m_value << std::endl;
		printTree(p->m_right);
	}
}

void Map::dump() const
{
	for (int i = 0; i < tableSize; i++) {
		printTree(bucket[i]);
	}
}
