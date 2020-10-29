#include "gtest/gtest.h"
#include <string> 
#include "../sequential.h"
 

class MapTest : public ::testing::Test {
 protected:
    using value_type = Map::value_type;
    std::vector<value_type> & getData() { return map.mData;}
    Map map;
};


TEST_F(MapTest, 1) { 
    ASSERT_EQ(map.size(), 0);
}
TEST_F(MapTest, 2) {
    Map a; 
    auto ret = a.find("x");
    ASSERT_EQ(ret.has_value(), false);
}
TEST_F(MapTest, 3) { 

    auto ret = map.insert(std::pair<std::string, int>("h",100));
    ASSERT_EQ(ret, true);
    ret = map.insert(std::make_pair("c",200));
    ASSERT_EQ(ret, true);
    ret = map.insert({"l",300});
    ASSERT_EQ(ret, true);
    ASSERT_EQ(map.size(),3);
    ASSERT_EQ(getData()[0], value_type("c",200));
    ASSERT_EQ(getData()[1], value_type("h",100));
    ASSERT_EQ(getData()[2], value_type("l",300));
    
    auto fnd =  map.find("c");
    ASSERT_EQ(fnd.has_value(), true);
    ASSERT_EQ(fnd.value(), 200);

    fnd =  map.find("h");
    ASSERT_EQ(fnd.has_value(), true);
    ASSERT_EQ(fnd.value(), 100);

    fnd =  map.find("l");
    ASSERT_EQ(fnd.has_value(), true);
    ASSERT_EQ(fnd.value(), 300);

    bool e = map.erase("zu");
    ASSERT_EQ(e, false);
    e = map.erase("h");
    ASSERT_EQ(e, true);
    ASSERT_EQ(map.size(),2);
    ASSERT_EQ(getData()[0], value_type("c",200)); 
    ASSERT_EQ(getData()[1], value_type("l",300));

    e = map.erase("c");
    ASSERT_EQ(e, true);
    ASSERT_EQ(map.size(),1); 
    ASSERT_EQ(getData()[0], value_type("l",300));

    e = map.erase("l");
    ASSERT_EQ(e, true);
    ASSERT_EQ(map.size(),0); 
}

TEST_F(MapTest, 4) {
 //   Map map;
    bool ret = map.insert(std::make_pair("qwertzui",1));
    ASSERT_EQ(ret, true);
    ret = map.insert(std::make_pair("rtzu",2));
    ASSERT_EQ(ret, true);
    ret = map.insert(std::make_pair("cftzu",3));
    ASSERT_EQ(ret, true);
    ASSERT_EQ(map.size(),3);

    auto isthere = map.find("cftzu");
    ASSERT_EQ(isthere.has_value(), true);
    isthere = map.find("rtzu");
    ASSERT_EQ(isthere.has_value(), true);
    isthere = map.find("qwertzui");
    ASSERT_EQ(isthere.has_value(), true);
    isthere = map.find("qwerti");
    ASSERT_EQ(isthere.has_value(), false);
    isthere = map.find("");
    ASSERT_EQ(isthere.has_value(), false);

    ASSERT_EQ(getData()[0], value_type("cftzu",3));  
    ASSERT_EQ(getData()[1], value_type("qwertzui",1));
    ASSERT_EQ(getData()[2], value_type("rtzu",2));

    bool gone = map.erase("cftzu");
    ASSERT_EQ(gone, true);
    ASSERT_EQ(map.size(),2);
    gone = map.erase("cftzu");
    ASSERT_EQ(gone, false);
    gone = map.erase("qwertzui");
    ASSERT_EQ(gone, true);
    gone = map.erase("rtzu");
    ASSERT_EQ(gone, true);
    gone = map.erase("rtzu");
    ASSERT_EQ(gone, false);
}


TEST(LUCacheTest, 1) { 
    LUCache<3> luc;
    ASSERT_EQ(luc.size(), 0);
}

TEST(LUCacheTest, 2) { 
    LUCache<3> luc;
    auto ret = luc.find("x");
    ASSERT_EQ(ret.has_value(), false);
}

TEST(LUCacheTest, 3) { 
    LUCache<3> luc;

    bool inserted = luc.insert(std::pair<std::string,int>("a1", 200)); 
    ASSERT_EQ(inserted, true);
    ASSERT_EQ(luc.size(), 1);

    luc.insert(std::pair<std::string,int>("z2", 300)); 
    ASSERT_EQ(inserted, true);
    ASSERT_EQ(luc.size(), 2);


    auto fz2 = luc.find("z2");
    ASSERT_EQ(fz2.has_value(), true);
    ASSERT_EQ(fz2.value(), 300);
    
    luc.insert(std::pair<std::string,int>("m2", 600));
    ASSERT_EQ(inserted, true);
    ASSERT_EQ(luc.size(), 3);
    
    auto fm2 = luc.find("m2"); 
    ASSERT_EQ(fm2.has_value(), true);
    ASSERT_EQ(fm2.value(), 600);

    
    luc.insert(std::pair<std::string,int>("ff", 500));
    ASSERT_EQ(inserted, true);
    ASSERT_EQ(luc.size(), 3);

    auto fa1 = luc.find("a1");
    ASSERT_EQ(fa1.has_value(), false); // a1 je izbačen 

    luc.find("ff");
    luc.find("ff");   // ff ima 2 dohvata
    
    luc.insert(std::pair<std::string,int>("kf", 900));
    ASSERT_EQ(luc.size(), 3);
    
    auto ffz2 = luc.find("z2");
    auto ffm2 = luc.find("m2");

    ASSERT_EQ(ffm2.has_value() and ffz2.has_value(), false);
    
    bool erased =luc.erase("ff"); 
    ASSERT_EQ(erased, true);
    ASSERT_EQ(luc.size(), 2);

    erased =luc.erase("kf"); 
    ASSERT_EQ(erased, true);
    ASSERT_EQ(luc.size(), 1);

    if(luc.find("m2").has_value())
        erased =luc.erase("m2"); 
    else
        erased =luc.erase("z2");
    
    
    ASSERT_EQ(erased, true);
    ASSERT_EQ(luc.size(), 0);
    
}

TEST(LUCacheTest, 4) { 
    LUCache<1> luc;
    bool inserted = luc.insert(std::pair<std::string,int>("atzuiop", 1)); 
    ASSERT_EQ(inserted, true);
    ASSERT_EQ(luc.size(), 1);

    bool erased =luc.erase("atzuiop"); 
    ASSERT_EQ(erased, true);
    ASSERT_EQ(luc.size(), 0);
}

TEST(LUCacheTest, 5) { 
    LUCache<4> luc;
    luc.insert(std::pair<std::string,int>("ftzuiop", 1)); 
    luc.insert(std::pair<std::string,int>("ftzliop", 1));
    luc.insert(std::pair<std::string,int>("atzuiop", 1));
    luc.insert(std::pair<std::string,int>("htzuiop", 1));

    ASSERT_STREQ(luc.getKey(0).data(), "atzuiop");
    ASSERT_STREQ(luc.getKey(1).data(), "ftzliop");
    ASSERT_STREQ(luc.getKey(2).data(), "ftzuiop");
    ASSERT_STREQ(luc.getKey(3).data(), "htzuiop");

    luc.erase("ftzuiop");
    ASSERT_EQ(luc.size(), 3);
    ASSERT_STREQ(luc.getKey(0).data(), "atzuiop");
    ASSERT_STREQ(luc.getKey(1).data(), "ftzliop"); 
    ASSERT_STREQ(luc.getKey(2).data(), "htzuiop");
}
