#include <cxxtest/TestSuite.h>
#include "Matrix.h"
#include <string>
#include <iostream>
#include <typeinfo>
#include <exception>
#include <sstream>
using namespace std;

class MyTestSuite : public CxxTest::TestSuite
{

public:
    void testMatrix_Construct(void){
        try{
            Matrix<int> m;
        }
        catch(exception &e){
            TS_FAIL("Constructing matrix type int failed");
            std::cout << "Exception message:" << e.what() << std::endl;
        }
        try{
            Matrix<float> f;
        }
        catch(exception &e){
            TS_FAIL("Constructing matrix type float failed");
            std::cout << "Exception message:" << e.what() << std::endl;
        }
        try{
            Matrix<string> s;
        }
        catch(exception &e){
            TS_FAIL("Constructing matrix type string failed");
            std::cout << "Exception message:" << e.what() << std::endl;
        }
    }

    void testMatrix_Destruct(void){
        Matrix<int> m;
        TS_ASSERT_THROWS_NOTHING(m.~Matrix());
    }

    void testMatrix_getElement(void){
        Matrix<int> m(1);
        TS_ASSERT_EQUALS(m(0,0),0);
        TS_ASSERT_EQUALS(typeid(m(0,0)).name(),"i");    //Checks type is integer
        Matrix<float> f(1);
        TS_ASSERT_EQUALS(f(0,0),0.0);
        TS_ASSERT_EQUALS(typeid(f(0,0)).name(),"f");    //Checks type is float
        Matrix<string> s(1);
        TS_ASSERT_EQUALS(s(0,0),"");
    }

    void testMatrix_setElement(void){
        Matrix<int> m(1);
        m(0,0) = 1;
        TS_ASSERT_EQUALS(m(0,0),1);
        Matrix<float> f(1);
        f(0,0) = 1.1;
        TS_ASSERT_EQUALS(f(0,0),1.1f);
        Matrix<string> s(1);
        s(0,0) = "a";
        TS_ASSERT_EQUALS(s(0,0),"a");
    }

    void testMatrix_InitializerList(void){
        Matrix<int> m({1,2,3,4});
        TS_ASSERT_EQUALS(m(0,0),1);
        TS_ASSERT_EQUALS(m(0,1),2);
        TS_ASSERT_EQUALS(m(1,0),3);
        TS_ASSERT_EQUALS(m(1,1),4);
        try{
            try{
                Matrix<int> n({1,2,3});
                TS_FAIL("Test initializer list failed. No thrown exceptions when expected"); //In case no exceptions are thrown
            }
            catch(exception &e){
                string errorString = e.what();
                if(errorString != "Insert square matrices only"){  //If it's not an expected exception
                    throw;
                }
            }
        }
        catch(exception &f){
            TS_FAIL("Expected exception with initializer list not occured");
            cout << "Exception message: "<< f.what() << endl;
        }
    }

    void testMatrix_copy(void){ //Needs to be checked
        Matrix<int> m({1,2,3,4});
        Matrix<int> n;
        Matrix<int> p(m);   //Calls copy constructor
        n = m;  //Calls copy assignment
        TS_ASSERT_EQUALS(m,n);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_move(void){ //Needs to be checked
        Matrix<int> m1({1,2,3,4});
        Matrix<int> m2({1,2,3,4});
        Matrix<int> ref({1,2,3,4});
        Matrix<int> p;
        Matrix<int> n(std::move(m1));    //Calls Move constructor
        p = std::move(m2);   //Calls Move assignment
        TS_ASSERT_EQUALS(ref,p);
        TS_ASSERT_EQUALS(ref,n);
    }

    void testMatrix_getRows(void){
        Matrix<int> m({1,2,3,4});
        TS_ASSERT_EQUALS(m.rows(),2);
    }

    void testMatrix_getCols(void){
        Matrix<int> m({1,2,3,4});
        TS_ASSERT_EQUALS(m.cols(),2);
    }

    void testMatrix_notSquare(void){
        Matrix<int> m(1,2);
        m(0,0) = 1;
        m(0,1) = 2;
        TS_ASSERT_EQUALS(m(0,0),1);
        TS_ASSERT_EQUALS(m(0,1),2);
        TS_ASSERT_EQUALS(m.rows(),1);
        TS_ASSERT_EQUALS(m.cols(),2);
    }

    void testMatrix_square(void){
        Matrix<int> m(2);
        Matrix<int> n({0,0,0,0});
        TS_ASSERT_EQUALS(m, n);
        TS_ASSERT_EQUALS(m.rows(),2);
        TS_ASSERT_EQUALS(m.cols(),2);
    }

    void testMatrix_addition(void){
        Matrix<int> m({1,2,3,4});
        Matrix<int> n({1,2,3,4});
        Matrix<int> p({2,4,6,8});
        TS_ASSERT((m+n) == p);
    }

    void testMatrix_additionChainable(void){
        Matrix<int> m({1,2,3,4});
        Matrix<int> p({2,4,6,8});
        m+=m;
        TS_ASSERT(m == p);
    }

    void testMatrix_subtraction(void){
        Matrix<int> m({1,2,3,4});
        Matrix<int> n({1,2,3,4});
        Matrix<int> p({0,0,0,0});
        TS_ASSERT((m-n) == p);
    }

    void testMatrix_subtractionChainable(void){
        Matrix<int> m({1,2,3,4});
        Matrix<int> p({0,0,0,0});
        m-=m;
        TS_ASSERT(m == p);
    }

    void testMatrix_multiplication(void){
        Matrix<int> m(1,2);
        m(0,0) = 1;
        m(0,1) = 2;
        Matrix<int> n(2,1);
        n(0,0) = 1;
        n(1,0) = 2;
        Matrix<int> p({5});
        TS_ASSERT_EQUALS((m*n),p);
    }

    void testMatrix_multiplicationChainable(void){
        Matrix<int> m(1,2);
        m(0,0) = 1;
        m(0,1) = 2;
        Matrix<int> n(2,1);
        n(0,0) = 1;
        n(1,0) = 2;
        m*=n;
        Matrix<int> p({5});
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_insertRow(void){
        Matrix<int> m(1,2);
        Matrix<int> p({0,0,1,2});
        m(0,0) = 1;
        m(0,1) = 2;
        TS_ASSERT_THROWS_ANYTHING(m.insert_row(1)); //Throws exception for wrong row
        m.insert_row(0);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_appendRow(void){
        Matrix<int> m(1,2);
        Matrix<int> p({1,2,0,0});
        m(0,0) = 1;
        m(0,1) = 2;
        TS_ASSERT_THROWS_ANYTHING(m.append_row(1));  //Throws exception with wrong row
        m.append_row(0);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_removeRow(void){
        Matrix<int> m({1,2,0,0});
        Matrix<int> p(1,2);
        p(0,0) = 1;
        p(0,1) = 2;
        TS_ASSERT_THROWS_ANYTHING(m.remove_row(2)); //Throws exception with wrong row
        m.remove_row(1);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_insertColumn(void){
        Matrix<int> m(2,1);
        Matrix<int> p({0,1,0,2});
        m(0,0) = 1;
        m(1,0) = 2;
        TS_ASSERT_THROWS_ANYTHING(m.insert_column(1));  //Throws exception for wrong column
        m.insert_column(0);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_appendColumn(void){
        Matrix<int> m(2,1);
        Matrix<int> p({1,0,2,0});
        m(0,0) = 1;
        m(1,0) = 2;
        TS_ASSERT_THROWS_ANYTHING(m.append_column(1));  //Throws exception for wrong column
        m.append_column(0);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_removeColumn(void){
        Matrix<int> m({1,0,2,0});
        Matrix<int> p(2,1);
        p(0,0) = 1;
        p(1,0) = 2;
        TS_ASSERT_THROWS_ANYTHING(m.remove_column(2));  //Throws exception for wrong column
        m.remove_column(1);
        TS_ASSERT_EQUALS(m,p);
    }

    void testMatrix_reset(void){
        Matrix<int> m({1,2,3,4});
        Matrix<int> p({0,0,0,0});
        m.reset();
        TS_ASSERT(m == p);
    }

    void testMatrix_begin(void){
        Matrix<int> m({1,2,3,4});
        TS_ASSERT_EQUALS(*((int*)m.begin()),1);
    }

    void testMatrix_end(void){
        Matrix<int> m({1,2,3,4});
        TS_ASSERT_EQUALS(*((int*)m.end()),4);
    }

    void testMatrix_in(void){
        Matrix<int> m;
        Matrix<int> n({1,2,3,4});
        istringstream is("[1 2\n 3 4]\n");
        operator>>(is,m);
        TS_ASSERT_EQUALS(m,n);
    }

    void testMatrix_out(void){
        Matrix<int> m({1,2,3,4});
        stringstream ss;
        operator<<(ss,m);
        string output = "[1 2\n 3 4]\n";
        TS_ASSERT_EQUALS(ss.str(),output)
    }

    void testMatrix_identity(void){
        Matrix<int> m({1,0,0,1});
        TS_ASSERT_EQUALS(identity<int>(2),m)
    }
};