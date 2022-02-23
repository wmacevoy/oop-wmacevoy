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
    public: FusedCord(int line, double length, const std::string &connector, double capacity)
        : Cord(line,length,connector,capacity)
    {
        m_fuseOk = true;
        m_fuseType = "funnest type!";
        std::cout << "FusedCord@" 
             << (void*) this 
             << " from " << m_constructedOn << " constructed." 
             << std::endl;
    }

    public: ~FusedCord()
    {
        std::cout << "FusedCord@" 
             << (void*) this 
             << " from " << m_constructedOn << " destructed." 
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

    FusedCord fusedCord(__LINE__,length, connector, capacity); // automatic
    FusedCord *pFusedCord = new FusedCord(__LINE__,length, connector, capacity);
    Cord cord = FusedCord(__LINE__,length, connector, capacity);  // compiles but almost 
                              // certainly broken (object truncation)
    Cord *pCord = new FusedCord(__LINE__,length, connector, capacity); // better
    // .. delete pCord;
    SPCord spCord (new FusedCord(__LINE__,length, connector, capacity)); // correct

    spCord = SPCord(new FusedCord(__LINE__,length, connector, capacity));
    // ...
}