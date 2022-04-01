// collections framework 
// c++ collections philosophy
//
//   1. c++ makes custom objects for each specialzied type.
//
//     typedef std::vector < std::string > StringVec;
//     typedef std::vector < int > IntVec;
//
//     StringVec names,addreses;
//     IntVec numbers;
//
//     2 implementations (1 for StringVec, used twice, 
//         1 for IntVec used once).   Efficient in executoin,
//         but maybe a lot of code.
//
//    2. If Collection is a kind of bag (vector, set, map),
//         then Collection::iterator is a kind (type) of
//         iterator, which can index into that kind of collection.
//
//    3.  These iterators act like pointers.
//
//         int a[10];
//         for (const_iterator p=a.cbegin(); p != a.end(); ++p) {
//             const int &ai=*p;
//             ai=3;
//         }
//
//         bag = [ *begin(),...,*end() )
//
//         for (auto ai : a) { ai = 3; }
//

// vector

#include <gtest/gtest.h>

struct Cord {
    int length;
    Cord(int _length) : length(_length) {};
};
#include <vector> 
#include <list>
//
// a[3] value is a[key]
//
//
// O(1) on average insert time.  max insert timne is O(n)
// inserts/deletes that are not on the end are O(n)
// random access is O(1)
#include <algorithm>

typedef std::list <std::string> Strings;

bool CordSort(const Cord &a, const Cord &b) {
  return a.length < b.length;
}

TEST(vector,strings) {
    Strings  a(33);
    std::vector < Cord > cords(10,Cord(0));
    // cords[5] = *(cords.begin()+5)

    // a[5]=*(a.begin()+5);

//    Cord cord;

    a.push_back("thing");
    a.sort();
    // std::sort(a.begin(),a.end());
    Strings::iterator  i = 
      std::find(a.begin(),a.end(), "thing");

    int direction = 1;
    std::sort(cords.begin(),cords.end(),
       [direction](auto x,auto y) { return direction*x.length < direction*y.length; });
    
    auto j = std::find(a.begin(),a.end(), "thing");
}

// map is a mapping from keys (of some type) to values (of some type)
// vector/list is mapping from 0..n-1 (keys) to values.
//
// For maps, you still use m[key]=value stil holds up.
//
// Really a map is a set of ordered pairs (key,value), where,
// the set equality is based on the keys only.
//
//   pair<A,B> is the type that maps use.
//
// In C++, maps/sets are stored as balanced binary trees.
//
//     balanced binary trees are sorted on the key.  The
//     values don't matter much; they are along for the
//     ride.
//
//     O(log n) insert/delete/find
//
//     Upshot: you need to sort keys.

#include <map>
#include <set>
#include <stdint.h>

TEST(map,simple) {
  std::map<uint32_t,double> incomeBySSN;
  // std::pair<const uint32_t,double>

  incomeBySSN[133'46'7890]=33.33;
  incomeBySSN[321'33'3333]=12.00;

  for (auto &kv : incomeBySSN) {
    auto& ssn = kv.first;
    auto& income = kv.second;
    std::cout << "ssn" << ssn << " made " << income << std::endl;

    if (ssn == 321'33'3333) { 
      std::cout << "found" << std::endl; 
      income = 44.37;
    }

  }

  for (auto &kv : incomeBySSN) {
    auto ssn = kv.first;
    auto income = kv.second;
    std::cout << "ssn" << ssn << " made " << income << std::endl;
  }

  std::set<std::string> names;

  names.insert("alice");
  names.insert("zeta");

  if (names.find("alice") != names.end()) {
    std::cout << "found alice!";
  }
}

// so for your own things, you have to provide some way
// to order the keys (map) memebers (set).

// solution 1: define a consistent < and ==
