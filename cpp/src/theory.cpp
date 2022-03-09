// what's going on in C++ for OO stuff?
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Equipment;
struct Cord;

struct Cord {
    int x;
    bool compatible(Equipment &equipment);
    Cord(int _x) : x(_x) {} 
};

struct Equipment {
    bool plugged;
    Equipment() { plugged = false; }
    void plug(Cord &cord) {
        if (cord.compatible(*this)) {
            plugged = true;
        }
    }
};

bool Cord::compatible(Equipment &equipment) {
    if (!equipment.plugged  && x != 3) {
        // ...
        return true;
    }
    return false;
}

struct FusedCord : Cord {
    bool fuseOk;
    FusedCord(int x) : Cord(x) { fuseOk = true; }

    // override
    bool compatible(Equipment &equipment) {
        cout << "FusedCord::compatible()" << endl;
        if (!fuseOk) return false;
        return Cord::compatible(equipment);
    }
};

struct CCord;
struct CCord_vftbl {
   bool (*compatible)(CCord *me, Equipment &equipment);
   void (*destructor)(CCord *me);
};

struct CCord {
    CCord_vftbl *vftbl;
    int x;
};

bool CCord_compatible(CCord *me, Equipment &equipment) {
   if (!equipment.plugged && me->x != 3) {
       return true;
   }
   return false;
}

void CCord_destructor(CCord *me) {
    free(me);
}

CCord_vftbl cCord_vftbl = {
    &CCord_compatible,
    &CCord_destructor
};

CCord *CCord_constructor(int _x) {
    CCord *me = (CCord*) malloc(sizeof(CCord));

    me->vftbl=&cCord_vftbl;
    me->x=_x;
    return me;
}

void foo() {
    Cord *cppCord = new Cord(3);
    FusedCord *cppFusedCord = new FusedCord(33);
    CCord *cCord = CCord_constructor(3);

    Equipment *equipment = new Equipment();
    cout << cppCord->compatible(*equipment) << endl;
    cout << ((FusedCord*)cppFusedCord)->compatible(*equipment) << endl;
    cout << ((Cord*)cppFusedCord)->compatible(*equipment) << endl;

    cout << cCord->vftbl->compatible(cCord,*equipment) << endl;


}