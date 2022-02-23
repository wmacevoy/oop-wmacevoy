#include "cord.h"
#include "gtest/gtest.h"

using namespace std;
using namespace power;

// https://github.com/google/googletest/blob/master/googletest/docs/primer.md
TEST(Cord, Constructor) {
    double length = 15.0;
    string connector = "female 3-prong";
    double capacity = 20.0;
    
    Cord cord(__LINE__,length, connector, capacity);

    ASSERT_EQ(cord.length(), length);
    //ASSERT_EQ(cord.connector(), connector);
    //ASSERT_EQ(cord.capacity(), capacity);
}

TEST(Cord, Length) {
    double length = 15.0;
    string connector = "female 3-prong";
    double capacity = 20.0;
    
    Cord cord(__LINE__,length, connector, capacity);

    ASSERT_EQ(cord.length(), length);

    double newLength = 22.0;
    cord.length(newLength);

    ASSERT_EQ(cord.length(), newLength);
}

TEST(Cord, BadLength) {
    double length = 15.0;
    string connector = "female 3-prong";
    double capacity = 20.0;
    
    Cord cord(__LINE__,length, connector, capacity);

    ASSERT_EQ(cord.length(), length);

    double newLength = -22.0;
    EXPECT_THROW({
       cord.length(newLength);
    }, std::out_of_range);
    

    ASSERT_EQ(cord.length(), length);
}