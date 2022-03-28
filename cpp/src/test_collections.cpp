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
//         then Collection::itertor is a kind (type) of
//         iterator, which can index into that kind of collection.
//
//    3.  These iterators act like pointers.
//
//         int a[10];
//         for (iterator p=a.begin(); p != a.end(); ++p) {
//             int &ai=*p;
//             ai=3;
//         }
//
//         bag = [*begin(),...,*end())
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
#include <algorithm>

TEST(vector,strings) {
    std::vector < std::string > a(33);
    std::vector < Cord > cords(10,Cord(0));

//    Cord cord;

    a.push_back("thing");
    std::sort(a.begin(),a.end());
    std::vector < std::string > :: iterator i = 
      std::find(a.begin(),a.end(), "thing");

    std::sort(cords.begin(),cords.end(),
      [a](auto x,auto y) { a.size(); return x.length < y.length; });
    
    auto j = std::find(a.begin(),a.end(), "thing");
}