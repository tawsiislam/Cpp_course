#include <iostream>
#include <memory> //Needed for unique_ptr

using namespace std;

struct A {
    int data;

};

void foo(unique_ptr<A> p) {
    cout << p->data << endl;
}

void foo2(shared_ptr<A> p) {
    cout << p->data << endl;
}

void uniquePtr(){
    cout << "uniquePtr running" << endl;
    unique_ptr<A> pa(new A {4} );
    cout << pa -> data << endl;
    foo(std::move(pa)); //No leak
}

void sharedPtr(){
    cout << "sharedPtr running" << endl;
    shared_ptr<A> sa(new A {5});
    cout << sa -> data << endl;
    //foo2(sa); //No leaks
    foo2(move(sa));   //No leaks

}

void weakPtr(){
    cout << "weakPtr running" << endl;
    shared_ptr<A> sa(new A {5});
    weak_ptr<A> wa = sa;
    cout << wa.lock()->data << endl;;

}

int main(int argc, const char * argv[]){
    uniquePtr();
    sharedPtr();
    weakPtr();
    return 0;
}