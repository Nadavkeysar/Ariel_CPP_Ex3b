/**
* An example of how to write unit tests.
* Use this as a basis to build a more complete Test.cpp file.
*
* IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
*
* AUTHORS: <207229477>
*
* Date: 2021-04-20
*/

// includes
#include "doctest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "NumberWithUnits.hpp"

// namespaces
using namespace std;
using namespace ariel;

TEST_CASE("Operator <<") {
    NumberWithUnits a{40,"KN"};
    CHECK_THROWS(cout << a);
    NumberWithUnits b{700,"kg"};
    ostringstream streamB;
    streamB << b;
    CHECK(streamB.str() == "700[kg]");    
}

TEST_CASE("Operator >>"){
    NumberWithUnits a{90,"ton"};
    istringstream sample_input1{"700 [ RL ]"};
    sample_input1 >> a;
    NumberWithUnits b{7,"ton"};
    istringstream sample_input2{"700 [ kg ]"};
    sample_input2 >> b;
}

TEST_CASE("Operator - unari"){
    NumberWithUnits possitive{1,"hour"};
    CHECK((-possitive).getNumber()==-1);
    NumberWithUnits negative{-1,"hour"};
    CHECK((-negative).getNumber()==1);
}

TEST_CASE("Operator +"){
    NumberWithUnits km{1,"km"};
    NumberWithUnits m{1,"m"};
    NumberWithUnits cm{1,"cm"};
    NumberWithUnits ILS{1,"ILS"};

    //Correct conversions
    NumberWithUnits ans1{2,"km"};
    NumberWithUnits ans2{1.001,"km"};
    NumberWithUnits ans3{1001,"m"};
    NumberWithUnits ans4{1.01,"m"};
    NumberWithUnits ans5{1.00001,"km"};
    NumberWithUnits ans6{100001,"cm"};
    CHECK((km+km)==ans1);
    CHECK((km+m)==ans2);
    CHECK((m+km)==ans3);
    CHECK((m+cm)==ans4);
    CHECK((km+cm)==ans5);
    CHECK((cm+km)==ans6);

    //Incorrect conversions
    CHECK_THROWS(m+ILS);
    CHECK_THROWS(ILS+km);
    
}

TEST_CASE("Operator + unari"){
    NumberWithUnits possitive{1,"hour"};
    CHECK((+possitive).getNumber()==1);
    CHECK((+possitive).getUnit()=="hour");
    NumberWithUnits negative{-1,"hour"};
    CHECK((+negative).getNumber()==-1);
    CHECK((+negative).getUnit()=="hour");
}

TEST_CASE("Operator +="){
    NumberWithUnits km{1,"km"};
    NumberWithUnits m{1,"m"};
    NumberWithUnits cm{1,"cm"};

    //Correct conversions
    NumberWithUnits ans1{2,"km"};
    NumberWithUnits ans2{2.001,"km"};
    NumberWithUnits ans3{2002,"m"};
    NumberWithUnits ans4{2002.01,"m"};
    NumberWithUnits ans5{2.00101,"km"};
    NumberWithUnits ans6{200102,"cm"};

    CHECK((km+=km)==ans1);
    CHECK((km+=m)==ans2);
    CHECK((m+=km)==ans3);
    CHECK((m+=cm)==ans4);
    CHECK((km+=cm)==ans5);
    CHECK((cm+=km)==ans6);

    //Incorrect conversions
    NumberWithUnits ans7{1,"ILS"};
    NumberWithUnits ans8{1,"min"};
    CHECK_THROWS(cm+=ans7);
    CHECK_THROWS(m+=ans8);
}

TEST_CASE("Operator -"){
    NumberWithUnits sec{120000,"sec"};
    NumberWithUnits hour{1,"hour"};
    NumberWithUnits min{2000,"min"};

    //Correct conversions
    NumberWithUnits ans1(1940,"min");
    NumberWithUnits ans2{240000,"sec"};
    CHECK((min-hour)==ans1);
    CHECK((sec-min)==ans2);

    //Incorrect conversions
    NumberWithUnits ans3{1,"ILS"};
    NumberWithUnits ans4{1,"km"};
    CHECK_THROWS(sec-ans3);
    CHECK_THROWS(min-ans4);
}

TEST_CASE("Operator -="){
    NumberWithUnits m{30,"m"};
    NumberWithUnits km{20,"km"};
    NumberWithUnits g{2000,"g"};
    NumberWithUnits kg{1,"kg"};

    //Correct conversions
    NumberWithUnits ans1{19.97,"km"};
    NumberWithUnits ans2{-1,"kg"};
    CHECK((km-=m)==ans1);
    CHECK((kg-=g)==ans2);
    

    //Incorrect conversions
    CHECK_THROWS(kg-=km);
    CHECK_THROWS(g-=m);

}

TEST_CASE("Operator ++")
{
    NumberWithUnits a(5, "kg");
    NumberWithUnits Pa(6, "kg");
    CHECK((++a) == Pa);
    CHECK((a++) == Pa);
    NumberWithUnits PPa(7, "kg");
    CHECK(a == PPa);

    NumberWithUnits b(3, "km");
    NumberWithUnits Pb(4, "km");
    CHECK((++b) == Pb);
    CHECK((b++) == Pb);
    NumberWithUnits PPb(5, "km");
    CHECK(b == PPb);

    NumberWithUnits c(2, "hour");
    NumberWithUnits Pc(1, "hour");
    CHECK((++c) == Pc);
    CHECK((c++) == Pc);
    NumberWithUnits PPc(1, "hour");
    CHECK(c == PPc);
}
TEST_CASE("Operator --")
{
    NumberWithUnits a(5, "kg");
    NumberWithUnits Ma(4, "kg");
    CHECK((--a) == Ma);
    CHECK((a--) == Ma);
    NumberWithUnits MMa(3, "kg");
    CHECK(a == MMa);

    NumberWithUnits b(3, "km");
    NumberWithUnits Mb(2, "km");
    CHECK((--b) == Mb);
    CHECK((b--) == Mb);
    NumberWithUnits MMb(1, "km");
    CHECK(b == MMb);

    NumberWithUnits c(2, "hour");
    NumberWithUnits Mc(1, "hour");
    CHECK((--c) == Mc);
    CHECK((c--) == Mc);
    NumberWithUnits MMc(0, "hour");
    CHECK(c == MMc);
}

TEST_CASE("Operator *"){
    double num1=3;
    double num2=-5;
    NumberWithUnits n1{2, "USD"};
    NumberWithUnits n2{1000, "m"};
    //from left
    NumberWithUnits left{6, "USD"};
    CHECK((num1*n1)==left);
    
    //from right
    NumberWithUnits right{-5000, "m"};
    CHECK((n2*num2)==right);
}

TEST_CASE("Operator *="){
    double num=3;
    NumberWithUnits n{2, "USD"};

    //num from left
    n*=num;
    NumberWithUnits ans{6,"USD"};
    CHECK(n==ans);
}

TEST_CASE("Operator <="){
    NumberWithUnits ans1{2,"km"};
    NumberWithUnits ans2{2,"m"};
    NumberWithUnits ans3{5,"km"};
    NumberWithUnits ans4{4500,"m"};
    NumberWithUnits ans5{2000000000000000,"cm"};
    NumberWithUnits ans6{1,"km"};

    CHECK_FALSE(ans1<=ans2);
    CHECK_FALSE(ans3<=ans4);
    CHECK_FALSE(ans5<=ans6);
 
    NumberWithUnits ans7{1,"km"};
    NumberWithUnits ans8{1000,"m"};
    NumberWithUnits ans9{5,"km"};
    NumberWithUnits ans10{6,"km"};
    NumberWithUnits ans11{5,"km"};
    NumberWithUnits ans12{6000,"m"};
    NumberWithUnits ans13{1000,"m"};
    NumberWithUnits ans14{1,"km"};

    CHECK(ans7<=ans8);
    CHECK(ans9<=ans10);
    CHECK(ans11<=ans12);
    CHECK(ans13<=ans14);

    NumberWithUnits ans15{2,"km"}; 
    NumberWithUnits ans16{1,"sec"};
    NumberWithUnits ans17{8,"year"}; 
    NumberWithUnits ans18{1,"m"};
    bool ans;
    CHECK_THROWS(ans=(ans15 <= ans16));
    CHECK_THROWS(ans=(ans17 <= ans18));
}

TEST_CASE("Operator >="){
    NumberWithUnits ans1{2,"km"};
    NumberWithUnits ans2{2,"m"};
    NumberWithUnits ans3{5,"km"};
    NumberWithUnits ans4{4500,"m"};
    NumberWithUnits ans5{2000000000000000,"cm"};
    NumberWithUnits ans6{1,"km"};

    CHECK_FALSE(ans2>=ans1);
    CHECK_FALSE(ans4>=ans3);
    CHECK_FALSE(ans6>=ans5);
 
    NumberWithUnits ans7{1,"km"};
    NumberWithUnits ans8{1000,"m"};
    NumberWithUnits ans9{5,"km"};
    NumberWithUnits ans10{6,"km"};
    NumberWithUnits ans11{5,"km"};
    NumberWithUnits ans12{6000,"m"};
    NumberWithUnits ans13{1000,"m"};
    NumberWithUnits ans14{1,"km"};

    CHECK(ans8>=ans7);
    CHECK(ans10>=ans9);
    CHECK(ans12>=ans11);
    CHECK(ans14>=ans13);

    NumberWithUnits ans15{2,"km"}; 
    NumberWithUnits ans16{1,"sec"};
    NumberWithUnits ans17{8,"year"}; 
    NumberWithUnits ans18{1,"m"};
    bool ans;
    CHECK_THROWS(ans=(ans16 >= ans15));
    CHECK_THROWS(ans=(ans18 >= ans17));
}

TEST_CASE("Operator <"){
    NumberWithUnits ans1{2,"km"};
    NumberWithUnits ans2{2,"m"};
    NumberWithUnits ans3{5,"km"};
    NumberWithUnits ans4{4500,"m"};
    NumberWithUnits ans5{2000000000000000,"cm"};
    NumberWithUnits ans6{1,"km"};

    CHECK_FALSE(ans1<ans2);
    CHECK_FALSE(ans3<ans4);
    CHECK_FALSE(ans5<ans6);
 
    NumberWithUnits ans9{5,"km"};
    NumberWithUnits ans10{6,"km"};
    NumberWithUnits ans11{5,"km"};
    NumberWithUnits ans12{6000,"m"};
   
    CHECK(ans9<ans10);
    CHECK(ans11<ans12);


    NumberWithUnits ans15{2,"km"}; 
    NumberWithUnits ans16{1,"sec"};
    NumberWithUnits ans17{8,"year"}; 
    NumberWithUnits ans18{1,"m"};
    bool ans;
    CHECK_THROWS(ans=(ans15 < ans16));
    CHECK_THROWS(ans=(ans17 < ans18));
}

TEST_CASE("Operator >"){
    NumberWithUnits ans1{2,"km"};
    NumberWithUnits ans2{2,"m"};
    NumberWithUnits ans3{5,"km"};
    NumberWithUnits ans4{4500,"m"};
    NumberWithUnits ans5{2000000000000000,"cm"};
    NumberWithUnits ans6{1,"km"};

    CHECK_FALSE(ans2>ans1);
    CHECK_FALSE(ans4>ans3);
    CHECK_FALSE(ans6>ans5);
 
    NumberWithUnits ans9{5,"km"};
    NumberWithUnits ans10{6,"km"};
    NumberWithUnits ans11{5,"km"};
    NumberWithUnits ans12{6000,"m"};

    CHECK(ans10>ans9);
    CHECK(ans12>ans11);
    
    NumberWithUnits ans15{2,"km"}; 
    NumberWithUnits ans16{1,"sec"};
    NumberWithUnits ans17{8,"year"}; 
    NumberWithUnits ans18{1,"m"};
    bool ans;
    CHECK_THROWS(ans=(ans16 > ans15));
    CHECK_THROWS(ans=(ans18 > ans17));
}

TEST_CASE("Operator =="){
    NumberWithUnits ans1{1, "km"};
    NumberWithUnits ans2{1000, "m"};
    NumberWithUnits ans3{1, "m"};
    NumberWithUnits ans4{100, "cm"};
    NumberWithUnits ans5{1, "kg"}; 
    NumberWithUnits ans6{1000, "g"};
    NumberWithUnits ans7{1, "hour"};
    NumberWithUnits ans8{360, "sec"};

    CHECK_EQ(ans1 , ans2);
    CHECK_EQ(ans3 , ans4);
    CHECK_EQ(ans5, ans6);
    CHECK_EQ(ans7 , ans8);                                 
}
    

TEST_CASE("Operator !="){

    CHECK_NE(NumberWithUnits{1, "km" }, NumberWithUnits{1000, "cm"});
    CHECK_NE(NumberWithUnits{1, "m"} , NumberWithUnits{1000, "km"});
    CHECK_NE(NumberWithUnits{1, "hour"} , NumberWithUnits{4000, "min"});
}