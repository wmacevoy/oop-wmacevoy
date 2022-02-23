//
//
// [STACK v ]
///  [main]
//     [foo]
//       [bar] (automatic vars)
//   [TEST-FusedCord-Ok]
//      - fusedCord (room for Cord + bool)
//      - pFusedCord (64 bit ptr to heap)
//  air
// [HEAP ^] (new / delete) (heap allocated)
//   alloced here (pFusedCord)
// GLOBALS
// CONSTANTS
// CODE/TEXT
//
#include "gtest/gtest.h"

#include "cord.h"
#include <memory>
#include <iostream>

class FusedCord : public power::Cord {
    private: bool m_fuseOk;
    private: std::string m_fuseType;
    public: FusedCord(double length, const std::string &connector, double capacity)
        : Cord(length,connector,capacity)
    {
        m_fuseOk = true;
        m_fuseType = "funnest type!";
        std::cout << "FusedCord@" 
             << (void*) this 
             << " constructed." 
             << std::endl;
    }

    public: ~FusedCord()
    {
        std::cout << "FusedCord@" 
             << (void*) this 
             << " destructed." 
             << std::endl;
    }

    // ...
};

//   a<->b<->c<->d
using namespace power;
using namespace std;

TEST(FusedCord,Ok) {
    double length = 15.0;
    string connector = "female 3-prong";
    double capacity = 20.0;

    FusedCord fusedCord(length, connector, capacity); // automatic
    FusedCord *pFusedCord = new FusedCord(length, connector, capacity);
    Cord cord = FusedCord(length, connector, capacity);  // compiles but almost 
                              // certainly broken (object truncation)
    Cord *pCord = new FusedCord(length, connector, capacity); // better
    // .. delete pCord;
    SPCord spCord (new FusedCord(length, connector, capacity)); // correct

    spCord = SPCord(new FusedCord(length, connector, capacity));
    // ...
}