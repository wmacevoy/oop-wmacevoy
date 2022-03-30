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