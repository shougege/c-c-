
/*#include<iostream>

using namespace std;
//  抽象类
class A
{
    // Data member of class
private:
    int a;
public:
    virtual void show() = 0; // 纯虚函数
};

// 1 在基类中抽象一个方法，且该基类只能作被继承，而不能被实例化
// 2  这个方法必须在派生类（derived class）中被实现
// 抽象类只能作为基类来派生新类使用，不能创建抽象类的对象，抽象类的指针和引用->由抽象类派生出来的类的对象！

int main()
{

     //   1 抽象类只能作为基类来派生新类使用
    //   2 抽象类的指针和引用->由抽象类派生出来的类的对象


//    A a; // error 抽象类，不能创建对象
    A *a1; // ok 可以定义抽象类的指针

//    A *a2 = new A(); // error, A是抽象类，不能创建对象
    return 0;
}
*/
/**
  * @brif 抽象类中: 在成员函数内可以调用纯虚函数， 在构造函数/析构函数内部不能使用纯虚函数
  * 如果一个类从抽象类派生而来，它必须实现了基类中的所有纯虚函数，才能成为非抽象类

*/

/*
#include<iostream>

using namespace std;

class A
{
public:
    virtual void f() = 0; // 纯虚函数
    void g() { this->f(); }
    A() {}

};

class B:public A{
public:
    void f()
    {
        cout << "B:f()" << endl;
    }

};

int main()
{
    B b;
    b.g();
    return 0;
}
*/

// @brief 纯虚函数使一个类变成抽象类
/*
#include<iostream>
using namespace std;

// @brief 抽象类至少包含一个纯虚函数
class Base
{
    int x;
public:
    virtual void show() = 0;
    int getX() {return x;}

};

class Derived: public Base
{
public:
    void show() { cout << "In Derived \n";}
    Derived(){}
};

int main(void)
{
    //   Base b; // 不能创建抽象类的对象
    //    Base *b = new Base(); error
    Base *bp = new Derived(); // 抽象类的指针和引用 -> 由抽象类派生出来的类的对象
    bp->show();

    return 0;

}

*/

// @ brief 如果我们不在派生类中覆盖纯虚函数，那么派生类也会变成抽象类。

/*
#include<iostream>
using namespace std;

class Base
{
    int x;
public:
    virtual void show() = 0;
    int getX() {return x;}

};
class Derived: public Base
{
public:
    // void show() {}
};

int main()
{

    Derived d; // error！ 派生类没有实现纯虚函数，那么派生类也会变为抽象类，不能创建抽象类的对象
    return 0;
}
*/
// @brief 抽象类可以有构造函数
/*
#include<iostream>
using namespace std;

// An abstract class with constructor
class Base
{
protected:
    int x;
public:
    virtual void fun() = 0;
    Base(int i) {x = i;}
};
class Derived: public Base
{
    int y;
public:
    Derived(int i,int j):Base(i) {y = j;}
    void fun() {cout << "x = " << x << ", y = " << y;}
};

int main(void)
{
    Derived d(4,5);
    d.fun();
    return 0;
}
*/
// @ brief 构造函数不能是构造函数，而析构函数可以是虚析构函数
 // 例如： 当基类指针指向派生类对象并删除对象时，我们可能希望调用
 // 适当的析构函数。如果析构函数不是虚拟的，则只能调用基类析构函数

/*
#include<iostream>
using namespace std;

class Base{

public:
    Base() {cout << "Constructor: Base" << endl;}
    virtual ~Base() {cout << "Destructor : Base" << endl;}
};

class Derived: public Base{

public:
    Derived() {cout << "Constructor: Derived" << endl;}
    ~Derived() {cout << "Destructor: Derived" << endl;}
    // 虚析构函数 基类 派生类都调用
};
int main()
{


    Base *Var = new Derived();
    delete Var;
    return 0;
}
*/
#include<iostream>
using namespace std;

class Base
{
    int x;
public:
    virtual void fun() = 0;
    int getX() {return x;}

};

class Derived: public Base
{

    int y;
public:
    void fun() {cout << "fun() called";}
    // 实现fun() 函数
};

int main(void)
{

    Derived d;
    d.fun();
    return 0;
}
/*
    虚析构函数的作用：为了避免内存泄露，而且是当子类中会有指针成员变量是才会使用到。
    即虚析构函数使得删除指向子类对象的基类指针时，可以调用子类的析构函数来
    实现释放子类中堆内存的目的，从而防止内存泄露。

*/
