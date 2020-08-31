
/*#include<iostream>

using namespace std;
//  ������
class A
{
    // Data member of class
private:
    int a;
public:
    virtual void show() = 0; // ���麯��
};

// 1 �ڻ����г���һ���������Ҹû���ֻ�������̳У������ܱ�ʵ����
// 2  ������������������ࣨderived class���б�ʵ��
// ������ֻ����Ϊ��������������ʹ�ã����ܴ���������Ķ��󣬳������ָ�������->�ɳ�����������������Ķ���

int main()
{

     //   1 ������ֻ����Ϊ��������������ʹ��
    //   2 �������ָ�������->�ɳ�����������������Ķ���


//    A a; // error �����࣬���ܴ�������
    A *a1; // ok ���Զ���������ָ��

//    A *a2 = new A(); // error, A�ǳ����࣬���ܴ�������
    return 0;
}
*/
/**
  * @brif ��������: �ڳ�Ա�����ڿ��Ե��ô��麯���� �ڹ��캯��/���������ڲ�����ʹ�ô��麯��
  * ���һ����ӳ���������������������ʵ���˻����е����д��麯�������ܳ�Ϊ�ǳ�����

*/

/*
#include<iostream>

using namespace std;

class A
{
public:
    virtual void f() = 0; // ���麯��
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

// @brief ���麯��ʹһ�����ɳ�����
/*
#include<iostream>
using namespace std;

// @brief ���������ٰ���һ�����麯��
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
    //   Base b; // ���ܴ���������Ķ���
    //    Base *b = new Base(); error
    Base *bp = new Derived(); // �������ָ������� -> �ɳ�����������������Ķ���
    bp->show();

    return 0;

}

*/

// @ brief ������ǲ����������и��Ǵ��麯������ô������Ҳ���ɳ����ࡣ

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

    Derived d; // error�� ������û��ʵ�ִ��麯������ô������Ҳ���Ϊ�����࣬���ܴ���������Ķ���
    return 0;
}
*/
// @brief ����������й��캯��
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
// @ brief ���캯�������ǹ��캯������������������������������
 // ���磺 ������ָ��ָ�����������ɾ������ʱ�����ǿ���ϣ������
 // �ʵ��������������������������������ģ���ֻ�ܵ��û�����������

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
    // ���������� ���� �����඼����
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
    // ʵ��fun() ����
};

int main(void)
{

    Derived d;
    d.fun();
    return 0;
}
/*
    ���������������ã�Ϊ�˱����ڴ�й¶�������ǵ������л���ָ���Ա�����ǲŻ�ʹ�õ���
    ������������ʹ��ɾ��ָ���������Ļ���ָ��ʱ�����Ե������������������
    ʵ���ͷ������ж��ڴ��Ŀ�ģ��Ӷ���ֹ�ڴ�й¶��

*/
