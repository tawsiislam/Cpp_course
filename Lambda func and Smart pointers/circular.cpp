#include <iostream>
#include <thread> //Needed to use shared_ptr as template type
#include <functional>   //Needed to use function<void(B*)>

using namespace std;


struct BhasA;

struct AhasB {
    AhasB(shared_ptr<BhasA> b) : m_b(b)  {
        resource = new int[4];
    };

    shared_ptr<BhasA> m_b;
    int * resource;

    ~AhasB() {delete [] resource;}
    AhasB(const AhasB &) = delete;
    void operator=(const AhasB &) = delete;
};

struct BhasA {
    BhasA() {resource = new int[4];};

    shared_ptr<AhasB> m_a;
    int * resource;

    ~BhasA() {delete [] resource;}
    BhasA(const BhasA &) = delete;
    void operator=(const BhasA &) = delete;
};

struct B {
    B() { b = new int[4]; }

    int * b;
    ~B() { delete [] b; }
    B(const B &) = delete;
    void operator= (const B & ) = delete;
};

void circular(){
    shared_ptr<BhasA> bptr(new BhasA);
    weak_ptr<AhasB> aptr = shared_ptr<AhasB> (new AhasB(bptr)); // Create a shared pointer object with AhasB 
                                                                //struct and assign weak_ptr with this shared_ptr.
    
    bptr->m_a=aptr.lock();  //No leak
}

void deleteFunc(){
    auto deleter = [](auto B){delete[] B;}; //Take in B and delete B as if it is an array
    //unique_ptr<B> pb(new B[2]);  //Causes memory leak
    unique_ptr<B, decltype(deleter)> pb2(new B[2], deleter);    //No leak

    //function<void(B*)> fb = [](auto B){delete[] B;};
    unique_ptr<B, function<void(B*)> > pb1(new B[2], [](auto B){delete[] B;});  //One liner using a lambda function whilst declaring 
}

int main(int argc, const char * argv[]){
    deleteFunc();
    return 0;
}