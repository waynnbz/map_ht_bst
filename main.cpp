#include "Map.h"
#include <iostream>
#include <cassert>


//int main(){

//	//Map m1;
//
//	//m1.insert("aa", 11);
//	//m1.insert("cc", 33);
//	//m1.insert("bb", 22);
//	//m1.insert("a", 111);
//	//m1.insert("acs", 44);
//	//m1.insert("dd", 55);
//
//	///*std::cout << (int)"aa" << std::endl;
//	//std::cout << (int)"aa" << std::endl;*/
//
//	//m1.dump();
//
//	//std::cout << std::endl;
//
//	//std::string a;
//	//double b;
//	//for (int i = 0; i < 6; i++) {
//	//	m1.get(i, a, b);
//	//	std::cout << "Key: " << a
//	//		<< "   Value: " << b << std::endl;
//	//}
//
//
//	//--------------------------------------------
//	// first get case passed(g++)
//
//	/*Map m;
//	m.insert("A", 10);
//	m.insert("B", 44);
//	m.insert("C", 10);
//	std::string all;
//	double total = 0;
//	for (int n = 0; n < m.size(); n++)
//	{
//		std::string k;
//		double v;
//		m.get(n, k, v);
//		all += k;
//		total += v;
//	}
//	std::cout << all << total;*/
//
//	//--------------------------------
//	//second get case passed(g++)
//
//	Map gpas;
//	gpas.insert("Fred", 2.956);
//	gpas.insert("Ethel", 3.538);
//	double v;
//	std::string k1;
//	assert(gpas.get(1, k1, v) && (k1 == "Fred" || k1 == "Ethel"));
//	std::string k2;
//	assert(gpas.get(1, k2, v) && k2 == k1);

	//-------------------------------------------------------
	//test for empty string passed(g++)

	/*Map gpas;
	gpas.insert("Fred", 2.956);
	assert(!gpas.contains(""));
	gpas.insert("Ethel", 3.538);
	gpas.insert("", 4.000);
	gpas.insert("Lucy", 2.956);
	assert(gpas.contains(""));
	gpas.erase("Fred");
	assert(gpas.size() == 3 && gpas.contains("Lucy") && gpas.contains("Ethel") &&
		gpas.contains(""));*/


		//-------------------------------------
		//swap passed (g++)

		// Map m1;
	 //   m1.insert("Fred", 2.956);
	 //   Map m2;
	 //   m2.insert("Ethel", 3.538);
	 //   m2.insert("Lucy", 2.956);
	 //   m1.swap(m2);
	 //   assert(m1.size() == 2  &&  m1.contains("Ethel")  &&  m1.contains("Lucy")  &&
	 //          m2.size() == 1  &&  m2.contains("Fred"));



	// 	return 0;
	// }




	//------------------------------------------
	//compile check passed(g++)


#include "Map.h"
#include <type_traits>

#define CHECKTYPE(f, t) { auto p = (t)(f); (void)p; }

static_assert(std::is_default_constructible<Map>::value,
	"Map must be default-constructible.");
static_assert(std::is_copy_constructible<Map>::value,
	"Map must be copy-constructible.");

void ThisFunctionWillNeverBeCalled()
{
	CHECKTYPE(&Map::operator=, Map& (Map::*)(const Map&));
	CHECKTYPE(&Map::empty, bool (Map::*)() const);
	CHECKTYPE(&Map::size, int  (Map::*)() const);
	CHECKTYPE(&Map::insert, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::update, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::insertOrUpdate, bool (Map::*)(const KeyType&, const ValueType&));
	CHECKTYPE(&Map::erase, bool (Map::*)(const KeyType&));
	CHECKTYPE(&Map::contains, bool (Map::*)(const KeyType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(const KeyType&, ValueType&) const);
	CHECKTYPE(&Map::get, bool (Map::*)(int, KeyType&, ValueType&) const);
	CHECKTYPE(&Map::swap, void (Map::*)(Map&));

	//CHECKTYPE(combine, bool(*)(const Map&, const Map&, Map&));
	//CHECKTYPE(subtract, void(*)(const Map&, const Map&, Map&));
}

int main()
{}

//---------------------------------------------
//non member function check 




// combine function paased(g++)



// int main()
// {
// 	bool flag;

// 	Map m1;
// 	m1.insert("Fred", 2.956);
// 	m1.insert("something", 4444);
// 	Map m2;
// 	m2.insert("Ethel", 3.538);
// 	m2.insert("Lucy", 2.956);
// 	m2.insert("something", 4444);

// 	Map m3(m1);
// 	m3.insert("something", 7777);
	

	//subtract(m1, m2, m1);
	//m3.dump();
	/*if (combine(m1, m2, m3)) {
		std::cout << "its true" << std::endl;
	}
	else {
		std::cout << "its False" << std::endl;
	}*/

	// m1.dump();
	// flag = combine(m1, m2, m3);
	
	
	// assert(m3.size() == 4 && m3.contains("Fred") &&  m3.contains("Lucy")  &&
	// 		m3.contains("something") &&  m3.contains("Ethel") && flag == false);

	//assert(m3.size() == 0);
		//&& m3.contains("Fred"));
			//&&  m3.contains("Lucy")  &&
			//m3.contains("something") &&  m3.contains("Fred") );
			
			
	//-----------------------------
	//test for data type switch string and double
	
	
	// 	Map m1;
	// m1.insert(2.956, "Fred");
	// m1.insert(4444, "something");
	// Map m2;
	// m2.insert(3.2, "Ethel");
	// m2.insert(2.889, "Lucy");
	// m2.insert(4444, "something");

	// Map m3(m1);
	// m3.insert(1221, "something");

	// flag = combine(m1, m2, m3);
	
	// m3.dump();
	
	// 	assert(m3.size() == 4 && m3.contains(2.956) &&  m3.contains(4444)  &&
	// 		m3.contains(3.2) &&  m3.contains(2.889) && flag == false);



// 	return 0;
// }
