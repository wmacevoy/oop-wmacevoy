// what's going on in C++ for OO stuff?
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <functional>

using namespace std;

struct Equipment;
struct Cord;

struct Cord {
    const int capacity;
    Cord(int _capacity) : capacity(_capacity) {} 
    virtual bool compatible(const Equipment &equipment) const;
    virtual int watts() const { return 120*capacity; }
    virtual ~Cord() { cout << "~Cord()" << endl; }
};

struct Equipment {
    const int consumption;
    Equipment(int _consumption) : consumption(_consumption) { }
};

bool Cord::compatible(const Equipment &equipment) const {
  cout << "Cord::compatible()" << endl;
  return (capacity >= equipment.consumption);
}

struct CCord;
struct CCord_vftbl {
   void (*destructor)(CCord *me);
   bool (*compatible)(const CCord *me, const Equipment &equipment);
   int (*watts)(const CCord *me);
};

struct CCord {
    CCord_vftbl *vftbl;
    int capacity;
};


void CCord_destructor(CCord *me) {
  cout << "CCord_destructor()" << endl;    
  free(me);
}

bool CCord_compatible(const CCord *me, const Equipment &equipment) {
  cout << "CCord_compatible()" << endl;  
  return (me->capacity >= equipment.consumption);
}

int CCord_watts(const CCord *me) {
  return me->capacity*120;
}

CCord_vftbl cCord_vftbl = {
    &CCord_destructor,
    &CCord_compatible,
    &CCord_watts
};

CCord *CCord_constructor(CCord *me, int _capacity) {
  if (me == NULL) {
    me = (CCord*) malloc(sizeof(CCord));
  }

  me->vftbl=&cCord_vftbl;
  me->capacity=_capacity;
  return me;
}

struct FusedCord : Cord {
    bool fuseOk;
    FusedCord(int capacity) : Cord(capacity), fuseOk(true) { }

    virtual bool compatible(const Equipment &equipment) const override {
        cout << "FusedCord::compatible()" << endl;
        if (!fuseOk) return false;
        return Cord::compatible(equipment);
    }

    virtual void reset() { fuseOk = true; }
    virtual void trip() { fuseOk = false; }
    virtual ~FusedCord() { cout << "~FusedCord()" << endl; }
};

struct CFusedCord;
struct CFusedCord_vftbl {
  void (*destructor)(CFusedCord *me);
  bool (*compatible)(const CFusedCord *me, const Equipment &equipment);
  int (*watts)(const CFusedCord *me);
  void (*reset)(CFusedCord *me);
  void (*trip)(CFusedCord *me);  
};

struct CFusedCord {
  CFusedCord_vftbl *vftbl;
  int capacity;
  bool fuseOk;
};

void CFusedCord_destructor(CFusedCord *me) {
  cout << "CFusedCord_destructor" << endl;
  CCord_destructor((CCord*)me);
}

bool CFusedCord_compatible(const CFusedCord *me, const Equipment &equipment) {
  cout << "CFusedCord_compatible()" << endl;
  if (!me->fuseOk) { return false; }
  return CCord_compatible((const CCord*)me,equipment);
}

void CFusedCord_reset(CFusedCord *me) {
  me->fuseOk = true;
}

void CFusedCord_trip(CFusedCord *me) {
  me->fuseOk = false;
}

CFusedCord_vftbl cFusedCord_vftbl =
  {
   &CFusedCord_destructor,
   &CFusedCord_compatible,
   (int (*)(const CFusedCord*))&CCord_watts, // not overriden
   &CFusedCord_reset,
   &CFusedCord_trip
  };


CFusedCord *CFusedCord_constructor(CFusedCord *me, int capacity) {
  if (me == NULL) {
    me = (CFusedCord*) malloc(sizeof(CFusedCord));
  }
  CCord_constructor((CCord*)me,capacity);
  me->vftbl=&cFusedCord_vftbl;
  me->fuseOk=true;
  return me;
}
struct __lastly__
{
  static void nothing() {}
  std::function<void()> fini;
  __lastly__(const std::function <void()> &_fini=nothing) : fini(_fini) {}
  __lastly__ &operator=(const std::function<void()> &_fini) {
     fini=_fini;
   return *this;
  }
  ~__lastly__() { fini(); }

  __lastly__(const __lastly__ &copy) = delete;
  __lastly__ &operator=(const __lastly__ &assign) = delete;  
};

#define lastly_suffix(suffix) __lastly__ __lastly_ ## suffix; __lastly_ ## suffix = [&]
#define lastly_counter(counter) lastly_suffix(counter)
#define lastly lastly_counter(__COUNTER__)

void foo() {
    Cord *cppCord = new Cord(10);
        lastly { delete cppCord; };
    FusedCord *cppFusedCord = new FusedCord(15); 
        lastly { delete cppFusedCord; };
    CCord *cCord = CCord_constructor(NULL,10); 
        lastly { cCord->vftbl->destructor(cCord); };
    CFusedCord *cFusedCord = CFusedCord_constructor(NULL,15); 
        lastly { cFusedCord->vftbl->destructor(cFusedCord); };

    cout << cppCord->watts() << endl;
    cout << cppFusedCord->watts() << endl;    
    cout << cCord->vftbl->watts(cCord) << endl;
    cout << cFusedCord->vftbl->watts(cFusedCord) << endl;    

    Equipment *equipment = new Equipment(15);

    cout << cppCord->compatible(*equipment) << endl;
    cout << cppFusedCord->compatible(*equipment) << endl;
    cout << cCord->vftbl->compatible(cCord,*equipment) << endl;
    cout << cFusedCord->vftbl->compatible(cFusedCord,*equipment) << endl;

    cppFusedCord->trip();
    cFusedCord->vftbl->trip(cFusedCord);

    Cord *cppFusedCordAsCord = dynamic_cast<Cord*>(cppFusedCord);
    CCord *cFusedCordAsCCord = (CCord*)(cFusedCord);
    cout << cppFusedCordAsCord->compatible(*equipment) << endl;
    cout << cFusedCordAsCCord->vftbl->compatible(cFusedCordAsCCord,*equipment) << endl;    

}

int main() {
  foo();
  return 0;
}
