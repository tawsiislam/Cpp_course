#include <cxxtest/TestSuite.h>
#include "Complex.h"
#include <iostream>
#include <math.h>
using namespace std;

class MyTestSuite : public CxxTest::TestSuite
{

public:
    void testComplex(void){
        Complex z;
        TS_ASSERT_EQUALS(z.real(),0);
        TS_ASSERT_EQUALS(z.imag(),0);
        Complex y(6,2);
        TS_ASSERT_EQUALS(y.real(),6);
        TS_ASSERT_EQUALS(y.imag(),2);
        Complex u(-5.2,-5);
        TS_ASSERT_EQUALS(u.real(),-5.2);
        TS_ASSERT_EQUALS(u.imag(),-5);
        Complex x(2.0);
        TS_ASSERT_EQUALS(x.real(),2);
        TS_ASSERT_EQUALS(x.imag(),0);
    }

    void testComplex_accessor(void){
        Complex z(3.2,-1.3);
        Complex y(-9.0);
        TS_ASSERT_EQUALS(z.real(),3.2);
        TS_ASSERT_EQUALS(z.imag(),-1.3);
        TS_ASSERT_EQUALS(y.real(),-9);
        TS_ASSERT_EQUALS(y.imag(),0);
        TS_ASSERT_EQUALS(y.real(),real(y));
        TS_ASSERT_EQUALS(y.imag(),imag(y));
    }

    void testComplex_assign(void){
        Complex x2 = 5;
        TS_ASSERT_EQUALS(x2.real(),5);
        TS_ASSERT_EQUALS(x2.imag(),0);
    }

    void testComplex_literal(void){
        Complex z = 3.4_i;
        Complex y = 3.2 + 5_i;
        TS_ASSERT_EQUALS(z.real(),0);
        TS_ASSERT_EQUALS(z.imag(),3.4);
        TS_ASSERT_EQUALS(y.real(),3.2);
        TS_ASSERT_EQUALS(y.imag(),5);
    }

    void testComplex_addtion(void){
        Complex z = 1 + 2_i;
        Complex y = 1.3 + 3 + 2_i;
        Complex u = 1 + 4.3_i + 1.6 +3_i;
        TS_ASSERT_EQUALS(z.real(),1);
        TS_ASSERT_EQUALS(z.imag(),2);
        TS_ASSERT_EQUALS(y.real(),4.3);
        TS_ASSERT_EQUALS(y.imag(),2);
        TS_ASSERT_EQUALS(u.real(),2.6);
        TS_ASSERT_EQUALS(u.imag(),7.3);
        Complex x = z+y;
        TS_ASSERT_EQUALS(x.real(),5.3);
        TS_ASSERT_EQUALS(x.imag(),4);
        Complex a(2,4);
        Complex b(-1,2);
        a += b;
        TS_ASSERT_EQUALS(a.real(),1);
        TS_ASSERT_EQUALS(a.imag(),6);
    }

    void testComplex_subtraction(void){
        Complex z = 1 - 2_i;
        Complex y = 1 - 3 - 2_i;
        Complex u = 1.1 + 4_i - 1 -3_i;
        TS_ASSERT_EQUALS(z.real(),1);
        TS_ASSERT_EQUALS(z.imag(),-2);
        TS_ASSERT_EQUALS(y.real(),-2);
        TS_ASSERT_EQUALS(y.imag(),-2);
        TS_ASSERT_LESS_THAN(abs(0.1-u.real()),0.00005); //Error to correct answer (0.1) should be small
        TS_ASSERT_EQUALS(u.imag(),1);
        Complex a(2,4.2);
        Complex b(-1,2);
        a -= b;
        TS_ASSERT_EQUALS(a.real(),3);
        TS_ASSERT_EQUALS(a.imag(),2.2);
    }

    void testComplex_multiplication(void){
        Complex z(1.2,2);
        Complex y(2,-3.1);
        Complex x = z*y;
        TS_ASSERT_EQUALS(x.real(),8.6);
        TS_ASSERT_LESS_THAN(abs(0.28-x.imag()),0.00005);
        Complex a(1.2,2);
        Complex b(2,-3.1);
        a *= b;
        TS_ASSERT_EQUALS(a.real(),8.6);
        TS_ASSERT_LESS_THAN(abs(0.28-a.imag()),0.00005);
        Complex k(3,5);
        k -= 5 + 1_i + Complex(5,3);
        TS_ASSERT_EQUALS(k.real(),-7);
        TS_ASSERT_EQUALS(k.imag(),1);
    }

    void testComplex_division(void){
        Complex z(3,4);
        Complex y(8,-2);
        Complex x = z/y;
        TS_ASSERT_LESS_THAN(abs(0.235294-x.real()),0.00005);
        TS_ASSERT_LESS_THAN(abs(0.558824-x.imag()),0.00005);
        z/=y;
        TS_ASSERT_LESS_THAN(abs(0.235294-z.real()),0.00005);
        TS_ASSERT_LESS_THAN(abs(0.558824-z.imag()),0.00005);
        TS_ASSERT_THROWS_ANYTHING(z/0);
    }

    void testComplex_abs(void){
        Complex a(1,0);
        Complex b(-2,0);
        Complex c(0,2);
        Complex d(0,-1);
        Complex e;
        TS_ASSERT_EQUALS(abs(a),1);
        TS_ASSERT_EQUALS(abs(b),2);
        TS_ASSERT_EQUALS(abs(c),2);
        TS_ASSERT_EQUALS(abs(d),1);
        TS_ASSERT_EQUALS(abs(e),0); //Test z=0
        TS_ASSERT_EQUALS(abs(a+c),sqrt(5)); //Test 1+2i
        TS_ASSERT_EQUALS(abs(a+d),sqrt(2)); //Test 1-1i
        TS_ASSERT_EQUALS(abs(b+c),sqrt(8)); //Test -2+2i
        TS_ASSERT_EQUALS(abs(b+d),sqrt(5)); //Test -2-1i
    }

    void testComplex_equal(void){
        Complex z(2.3,-4.1);
        Complex y;
        y = 2.3 - 4.1_i;
        Complex x = 3;
        Complex a = 0-3.1_i;
        TS_ASSERT_EQUALS(z,y);  //Calls operator==
        TS_ASSERT_EQUALS(z.real(),2.3);
        TS_ASSERT_EQUALS(z.imag(),-4.1);
        TS_ASSERT_DIFFERS(z,x); //Calls operator !=
        TS_ASSERT_DIFFERS(z,a);
        a = y = x;  //Check chaining
        TS_ASSERT_EQUALS(a.real(),3);
        TS_ASSERT_EQUALS(y.real(),3);
    }

    void testComplex_lessthan(void){
        Complex z(1,1);
        Complex y(3.1,-2.1);
        Complex x(1,0);
        TS_ASSERT_LESS_THAN(z,y);
        TS_ASSERT_LESS_THAN(x,z);
        TS_ASSERT_LESS_THAN(x,y);
        TS_ASSERT_EQUALS(y<z,false);
        TS_ASSERT_EQUALS(y<x,false);
    }

    void testComplex_in(void){
        Complex z;
        istringstream is("(1,3)");
        operator>>(is,z);
        TS_ASSERT_EQUALS(z.real(),1);
        TS_ASSERT_EQUALS(z.imag(),3);
        Complex y;
        istringstream is1("(2.0)");
        operator>>(is1,y);
        TS_ASSERT_EQUALS(y.real(),2.0);
        TS_ASSERT_EQUALS(y.imag(),0);
        Complex x;
        istringstream is2("-3");
        operator>>(is2,x);
        TS_ASSERT_EQUALS(x.real(),-3);
        TS_ASSERT_EQUALS(x.imag(),0);
    }

    void testComplex_out(void){
        Complex z = 4 + 1.1_i;
        stringstream ss;
        operator<<(ss,z);
        string output = "(4,1.1)\n";
        TS_ASSERT_EQUALS(ss.str(),output)
        Complex y = -4 - 1.1_i;
        stringstream ss1;
        operator<<(ss1,y);
        string output1 = "(-4,-1.1)\n";
        TS_ASSERT_EQUALS(ss1.str(),output1)
        Complex x = -4;
        stringstream ss2;
        operator<<(ss2,x);
        string output2 = "(-4)\n";
        TS_ASSERT_EQUALS(ss2.str(),output2)
    }

};