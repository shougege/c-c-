/*
    �������ܽ�:
    * ����Ĵ�СΪ1�ֽ�
    * һ�����У��麯��������Ա������������̬�ڷǾ�̬���;�̬����
        ���ǲ�ռ�������Ĵ洢�ռ�
    * ���ڰ����麯�����࣬�����ж��ٸ��麯����ֻ��һ����ָ�룬vptr�Ĵ�С
    * ��ͨ�̳У�������̳������л���ĺ����ͳ�Ա��Ҫ�����ֽڶ����������С
    * �麯���̳У������ǵ��̳л��Ƕ�̳У����Ǽ̳��˻����vptr.(32λos 4�ֽڣ�64λos 8�ֽ�)
    * ��̳У��̳л����vptr.

*/
/*
  ԭ��1 ����Ĵ�СΪ1�ֽ�
#include<iostream>
using namespace std;


class A{};
int main()
{
    cout << sizeof(A) << endl;
    return 0;
}

*/

/*
  ��̬���ݳ�Ա���������ڳ����һ��global data members�У��������һ�����ݳ�Ա������Ӱ����Ĵ�С��
  �������������˶��ٸ�ʵ�������������˶����µ��࣬��̬���ݳ�Աֻ��һ��ʵ������̬���ݳ�Ա��һ�������������Ѿ����ڡ�

#include<iostream>
using namespace std;

class A
{
public:
    char b;
    virtual void fun(){};
    static int c;
    static int d;
    static int f;

};
int main()
{
    // 8  �ֽڶ��� ��̬���ݲ�Ӱ����Ĵ�С cptrָ�� = 4
    cout << sizeof(A)  << endl;
    return 0;
}
*/

/*

  ���ڰ����麯�����࣬�����ж��ٸ��麯����ֻ��һ����ָ�룬vptr�Ĵ�С
#include<iostream>
using namespace std;


class A
{

    virtual void fun();
    virtual void fun1();
    virtual void fun2();
    virtual void fun3();
};

int main()
{

    cout << sizeof(A) << endl; // 4
    return 0;
}


/*

  1 ��ͨ���̳У��̳о��ǻ���+����������Ĵ�С��ע���ֽڶ��룩
     ע�⣺ ������ݳ�Ա��������˳������ڴ棬�����Ȩ���޹أ�ֻ������˳��
  2 �鵥�̳У�������̳л���vptr

#include<iostream>
using namespace std;


class A
{
public:
    char a;
    int b;
};

class B:A
{

public:
    short a;
    long b;
};
class C
{

    A a;
    char c;
};

class A1
{

    virtual void fun(){}
};
class C1:public A
{

};

int main()
{

    cout << sizeof(A) << endl; //8
    cout << sizeof(B) << endl; // 16
    cout << sizeof(C) << endl; // 12
    // �����鵥�����̳У�������Ҳ�̳��˻����vptr��������8�ֽ�
    cout << sizeof(C1) << endl;// 8
    return 0;
}
*/

#include<iostream>
using namespace std;

class A
{

    virtual void fun(){}
};

class B
{

    virtual void fun2(){}
};

class C : virtual public A, virtual public B
{

public:
    virtual void fun3(){} // ��ռ �ڴ�
};

int main()
{
    // 4 4 8 ��������̳ж���麯������̳������麯����vptr
    cout << sizeof(A) << " " << sizeof(B) << " " << sizeof(C);
    return 0;
}
