#ifndef MAP_H
#define MAP_H

#include <string>

typedef std::string KeyType;
typedef double ValueType;

class Map
{
public:
	Map();
	~Map();
	Map(const Map& rhs);
	const Map& operator=(const Map& rhs);

	bool empty() const;

	int size() const;

	bool insert(const KeyType& key, const ValueType& value);

	bool update(const KeyType& key, const ValueType& value);

	bool insertOrUpdate(const KeyType& key, const ValueType& value);

	int Convert_Key(std::string key) const;

	int Convert_Key(double key) const;

	bool erase(const KeyType& Key);

	bool contains(const KeyType& key) const;

	bool get(const KeyType& key, ValueType& value) const;

	bool get(int i, KeyType& key, ValueType& value) const;

	void swap(Map& other);


	void dump() const;//only to cerr


private:
	struct Node {
		KeyType m_key;
		ValueType m_value;

		Node* m_left;
		Node* m_right;

		Node(KeyType k, ValueType v) {
			m_key = k;
			m_value = v;
			m_left = nullptr;
			m_right = nullptr;
			//do i need this-> here??
		}
	};

	/*int rehash(double key);
	int rehash(std::string key);*/

	static const int tableSize = 3;
	Node** bucket;

	//will it be better to create a private class for all these tree functions??
	int count(Node* &p) const;
	bool find(Node* &p, const KeyType& key, ValueType& value) const;
	bool add(Node* &p, const KeyType& key, const ValueType& value);
	bool deleteNode(Node* &p, const KeyType& key);
	void deleteTree(Node* &p);
	void printTree(Node* &p) const;
	bool trav(Node* &p, int& i, KeyType& key, ValueType& value) const;

	void append(const Map& rhs);
};

//--------------------------------------------
//Non member functions

inline bool combine(const Map& m1, const Map& m2, Map& result)
{
	bool smooth = true;

	result = m1;

	KeyType tempKey;
	ValueType tempVal;

	for (int i = 0; i < m2.size(); i++) {
		m2.get(i, tempKey, tempVal);
		if (!result.insert(tempKey, tempVal))
			smooth = false;
	}

	return smooth;
}


inline void subtract(const Map& m1, const Map& m2, Map& result)
{
	result = m1;

	KeyType tempKey;
	ValueType tempVal;

	for (int i = 0; i < m2.size(); i++) {
		m2.get(i, tempKey, tempVal);
		result.erase(tempKey);
	}

}



#endif
