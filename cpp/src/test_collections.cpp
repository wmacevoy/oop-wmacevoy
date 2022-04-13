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
    std::string plug;
    int length;
    Cord(const std::string &_plug, int _length) 
    : plug(_plug), length(_length) {};
    virtual bool connects(const std::string &otherPlug) const {
       return plug == otherPlug;
    }
};

struct FusedCord : Cord {
   bool fuseOk;
    FusedCord(const std::string &_plug, int _length) : Cord(_plug,_length), fuseOk(true) {}

    virtual bool connects(const std::string &otherPlug) const override {
       return fuseOk && plug == otherPlug;
    }
};

#include <vector> 
#include <list>
#include <compare>

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
    std::vector < Cord > cords(10,Cord("3-prong",0));
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

TEST(vector,heirarchy) {
  std::vector<std::shared_ptr<Cord> > cords;

  cords.push_back(std::shared_ptr<Cord>(new Cord("3-prong",10)));
  cords.push_back(std::shared_ptr<Cord>(new FusedCord("3-prong",10)));
  cords.push_back(std::shared_ptr<Cord>(new Cord("2-prong",10)));

  for (auto &cord1 : cords) {
      for (auto &cord2 : cords) {
         std::cout << cord1->connects(cord2->plug);
      }
      std::cout << std::endl;
  }

  std::cout << "break fuse" << std::endl;

  // Pointers are are addresses of stuff (64 bits usuaally),
  //   they can be NULL.
  //
  //     int *x = new int; // allocate an int on the heap,
  //                       // result of "new" is that address.
  //     foo() {
  //        int y;
  //        int *x = &y;
  //        x = new int;
  //
  //        int *const z = &y;
  //        *z  = 3; // (make y 3)
  //        z = new int; // compile time error
  //        
  //        if (z != NULL) *z = 3;
  //     }
  //
  // Refrence is a const pointer to something (not null).
  //    since you can't the pointer, and it can't be null,
  //    saying *ref is redundant, so, just ref means *ref.
  //
  //          int &r = y; <-->  int * const _r = &y;
  //          r = 3;      <--->  *_r = 3;
  //
  //     
  // safely cast the Cord& in the vector to FusedCord& to access the fuse...
  
  // cords - vec<shared_ptr<Cord>>
  // cords[1] - shared_ptr<Cord> 
  //   Cord& operator*() {  return *owned; }
  // *cords[1] -- Cord&  // actually is FusedCord&
  //  dynamic_cast<FusedCord&> -- upcast from Cord& to FusedCord&
  //     this cast is run-time checked.  If you tried to upcast,
  //     and the thing wasn't FusedCord& - exception'
  //   So (ref).fuseOk = false is modifying some FusedCord.
  //
  //
  // cords[1].fuseOk = false;  // js version - no types

  dynamic_cast<FusedCord&>(*cords[1]).fuseOk = false;

  for (auto &cord1 : cords) {
      for (auto &cord2 : cords) {
         std::cout << cord1->connects(cord2->plug);
      }
      std::cout << std::endl;
  }
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

// For your own keys - how can the STL decide where to
// place a key in the balanced binary tree?
//
//  Ans: you have to provide an ordering.
//
//    1. Provide < and == for your key types.
//       bool operator<(const T& a, const T & b) { ... }
//       <,<=,==,!=,>=,>  six operators to define
//
//       <=> spaceship operator  (int +1/0/-1 for < , = , or > )
//       
//    2. Provide a custom comparator to a set/map.
//
//

std::strong_ordering operator<=>(const Cord &a, const Cord &b) {
  if (a.plug != b.plug) return a.plug <=> b.plug;
  return a.length <=> b.length;
}

std::ostream& operator<<(std::ostream &out, const Cord &cord) {
  return (((((out << "a ") << cord.length) << " meter ") << cord.plug) << "cord");
}
 
TEST(set,custom) {
  std::set<Cord> cords;
  cords.insert(Cord("3-prong",12));
  cords.insert(Cord("2-prong",10));
  cords.insert(Cord("2-prong",10));
  cords.insert(Cord("2-prong",10));
  cords.insert(Cord("2-prong",10));
  cords.insert(Cord("3-prong",10));

  for (auto& cord : cords) {
    std::cout << cord << std::endl;
  }

}

TEST(map,custom) {
  std::map<Cord, std::set < std::string > > locations;
  locations[Cord("3-prong",12)].insert("living room");
  locations[Cord("3-prong",12)].insert("kichen");
  locations[Cord("2-prong",10)].insert("garage");

  for (auto &cordLocs : locations) {
    std::cout << cordLocs.first << " may be in:";
    for (auto &loc : cordLocs.second) {
       std::cout << " " << loc;
    }
    std::cout << std::endl;
  }
}
// so for your own things, you have to provide some way
// to order the keys (map) memebers (set).

// solution 1: define a consistent < and ==
