#include <iostream>

class B {
public:
    void f() { std::cout << "B.f "; }
    virtual ~B() {}
};

class D1 : public B {
public:
    virtual void f() { std::cout << "D1.f "; }
    virtual ~D1() {}
};

class D2 : public D1 {
public:
    void f() { std::cout << "D2.f "; }
};

int main() {
    B* b1 = new B();  b1->f(); delete b1;
    B* b2 = new D1(); b2->f(); delete b2;
    B* b3 = new D2(); b3->f(); delete b3;
    D1* d = new D2(); d->f();  delete d;
    return 0;
}
