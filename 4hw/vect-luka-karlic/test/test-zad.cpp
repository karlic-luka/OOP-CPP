#include "gtest/gtest.h"
#include "../src/vect.h"
#include "test-vect.h"
#include <sstream>
#include <string>

using namespace std;

// Lista tipova za koje ćemo vršiti testove
typedef ::testing::Types<int, double> MyTypes;
TYPED_TEST_CASE(VectTest, MyTypes);


TYPED_TEST(VectTest, construction) {
    Vect<TypeParam> vec;
    ASSERT_EQ(vec.size(), 0u);
    ASSERT_EQ(vec.capacity(), 0u);
    ASSERT_EQ(this->get_mdata(vec), nullptr);
    ASSERT_EQ(this->get_mff(vec), nullptr);
    ASSERT_EQ(this->get_mend(vec), nullptr);

    Vect<TypeParam> v(10);
    ASSERT_EQ(v.size(), 10u);
    ASSERT_EQ(v[9], TypeParam{});

    size_t n = 1000000;
    Vect<TypeParam> v1(n, 3);
    ASSERT_EQ(v1.size(), n);
    ASSERT_EQ(v1[n-1], 3);
}


TEST_F(VectTestPair, pair_construction) {
    Vect<std::pair<int,char> > vec;
    ASSERT_EQ(vec.size(), 0u);
    ASSERT_EQ(vec.capacity(), 0u);
    ASSERT_EQ(this->get_mdata(vec), nullptr);
    ASSERT_EQ(this->get_mff(vec), nullptr);
    ASSERT_EQ(this->get_mend(vec), nullptr);

    Vect<std::pair<int,char> > v(10);
    ASSERT_EQ(v.size(), 10u);
    ASSERT_EQ(v[9].first, 0);

    size_t n = 100000;
 //   TypeParam p0;
 //   if constexpr std::is
    Vect<std::pair<int,char> > v1(n, std::make_pair(3,'a'));
    ASSERT_EQ(v1.size(), n);
    ASSERT_EQ(v1[n-1].second, 'a');
}



TYPED_TEST(VectTest, indexing) {
    size_t n = 10;
    Vect<TypeParam> v1(n, 3);
    const Vect<TypeParam> v2(n, 4);

    ASSERT_EQ(v1[n-1], 3);
    ASSERT_EQ(v2[n-1], 4);
}

TEST_F(VectTestPair, indexing) {
    size_t n = 10;
    Vect<std::pair<int,char> > v1(n, std::make_pair(3,'a'));
    const Vect<std::pair<int,char> > v2(n, std::make_pair(4,'a'));

    ASSERT_EQ(v1[n-1].first, 3);
    ASSERT_EQ(v2[n-1].second, 'a');
}

TYPED_TEST(VectTest, copyconst) {
    size_t n = 10;
    Vect<TypeParam> v1(n, 3);
    Vect<TypeParam> v2(v1);

    ASSERT_EQ(v1.size(), v2.size());
    for(size_t i=0; i < v1.size(); ++i)
        ASSERT_EQ(v1[i], v2[i]);

    ASSERT_NE(this->get_mdata(v1), this->get_mdata(v2));
}

TYPED_TEST(VectTest, copyop) {
    size_t n = 10;
    Vect<TypeParam> v1(n, 3);
    Vect<TypeParam> v2;
    v2 = v1;

    ASSERT_EQ(v1.size(), v2.size());
    for(size_t i=0; i < v1.size(); ++i)
        ASSERT_EQ(v1[i], v2[i]);
}

TYPED_TEST(VectTest, moveconst) {
    size_t n = 10;
    Vect<TypeParam> v1(n, 3);
    TypeParam * data = this->get_mdata(v1);
    Vect<TypeParam> v2(std::move(v1));

    ASSERT_EQ(v1.size(), 0u);
    ASSERT_EQ(this->get_mdata(v1), nullptr);
    ASSERT_EQ(this->get_mff(v1), nullptr);
    ASSERT_EQ(this->get_mend(v1), nullptr);
    ASSERT_EQ(this->get_mdata(v2), data);
}

TYPED_TEST(VectTest, moveop) {
    size_t n = 10;
    Vect<TypeParam> v1(n, 3);
    TypeParam * data = this->get_mdata(v1);
    Vect<TypeParam> v2;
    v2 = std::move(v1);

    ASSERT_EQ(v1.size(), 0u);
    ASSERT_EQ(this->get_mdata(v1), nullptr);
    ASSERT_EQ(this->get_mff(v1),   nullptr);
    ASSERT_EQ(this->get_mend(v1),  nullptr);
    ASSERT_EQ(this->get_mdata(v2), data);
}

TYPED_TEST(VectTest, selfassign) {
    size_t n = 10;
    Vect<TypeParam> v1(n, 3);
    TypeParam * data = this->get_mdata(v1);
    v1 = std::move(v1);

    ASSERT_EQ(this->get_mdata(v1), data);
}

TYPED_TEST(VectTest, push_back) {
    Vect<TypeParam> vec;
    ASSERT_EQ(this->get_mdata(vec), nullptr);

    vec.push_back(1);
    ASSERT_EQ(vec.size(), 1u);
    ASSERT_EQ(vec.capacity(), 1u);
    auto * data = this->get_mdata(vec);

    vec.push_back(2);
    ASSERT_EQ(vec.size(), 2u);
    ASSERT_EQ(vec.capacity(), 2u);
    ASSERT_NE(this->get_mdata(vec), data);
    data = this->get_mdata(vec);

    vec.push_back(3);
    ASSERT_EQ(vec.size(), 3u);
    ASSERT_EQ(vec.capacity(), 4u);
    ASSERT_NE(this->get_mdata(vec), data);
    data = this->get_mdata(vec);

    vec.push_back(4);
    ASSERT_EQ(vec.size(), 4u);
    ASSERT_EQ(vec.capacity(), 4u);
    ASSERT_EQ(this->get_mdata(vec), data);
    data = this->get_mdata(vec);

    vec.push_back(5);
    ASSERT_EQ(vec.size(), 5u);
    ASSERT_EQ(vec.capacity(), 8u);
    ASSERT_NE(this->get_mdata(vec), data);

}

TYPED_TEST(VectTest, oppluseq){
    Vect<TypeParam> vec1(3,5);
    Vect<TypeParam> vec2(3,5);
    vec1+=vec2;
    ASSERT_EQ(vec1.size(), 3u);
    for(size_t i=0; i < vec1.size(); ++i)
        ASSERT_EQ(vec1[i], 10);
}

TYPED_TEST(VectTest, opmineq){
    Vect<TypeParam> vec1(3,5);
    Vect<TypeParam> vec2(3,5);
    vec1-=vec2;
    ASSERT_EQ(vec1.size(), 3u);
    for(size_t i=0; i < vec1.size(); ++i)
        ASSERT_EQ(vec1[i], 0);
}

TYPED_TEST(VectTest, opplus){
    Vect<TypeParam> vec1(3,5);
    Vect<TypeParam> vec2(3,5);
    Vect<TypeParam> vec;
    vec = vec1 + vec2;
    ASSERT_EQ(vec.size(), 3u);
    for(size_t i=0; i < vec.size(); ++i)
        ASSERT_EQ(vec[i], 10);
}

TYPED_TEST(VectTest, opmin){
    Vect<TypeParam> vec1(3,5);
    Vect<TypeParam> vec2(3,5);
    Vect<TypeParam> vec;
    vec = vec1 - vec2;
    ASSERT_EQ(vec.size(), 3u);
    for(size_t i=0; i < vec.size(); ++i)
        ASSERT_EQ(vec[i], 0);
}

TYPED_TEST(VectTest, output){
    Vect<TypeParam> vec1(3,5);
    stringstream out;
    string result1("[5,5,5]");
    out << vec1;
    ASSERT_EQ(out.str(),result1);

    Vect<TypeParam> vec2;
    string result2("[]");
    out.str("");
    out.clear();
    out << vec2;
    ASSERT_EQ(out.str(),result2);
}

TYPED_TEST(VectTest, norm){
    Vect<TypeParam> vec1(3,1);
    double n = vec1.two_norm();
    ASSERT_NEAR(n,sqrt(3.0),1e-10);

    Vect<TypeParam> vec2;
    n = vec2.two_norm();
    ASSERT_NEAR(n,0.0,1e-10);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
