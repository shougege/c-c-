/*
 ���벻ͬ����һ��ʹ��ʱ,Static �ؼ��־��в�ͬ�ĺ��塣���ǿ���ʹ��static�ؼ���:
 ��̬����: �����еı��������еı���
 ��̬��ĳ�Ա: ���������еĺ���

 ��̬����
  * �����еľ�̬����

     ����������Ϊstaticʱ���ռ佫�ڳ�������������ڷ��䡣��ʹ��ε��øú�������̬�����Ŀռ�Ҳֻ
     ����һ�Σ�ǰһ�ε����еı���ֵͨ����һ�κ������ô��ݡ��������
     c/c++����Ҫ�洢��ǰ����״̬���κ�����Ӧ�ó���ǳ����á�

#include<iostream>
#include<string>
using namespace std;

void demo()
{
    // static variable
    static int count = 0;
    cout << count << " ";

    // value is update and
    // will be carried to next
    // function calls
    count++;

}

int main()
{

    for(int i = 0; i < 5; i++)
        demo();
    return 0;
}
  ������ĳ����п�������count������Ϊstatic����ˣ�����ֵͨ���������������ݡ�
  ÿ�ε��ú���ʱ��������Ա����������г�ʼ����
*/
/*

  * ���еľ�̬����
   ��������Ϊstatic�ı���ֻ����ʼ��һ�Σ���Ϊ�����ڵ����ľ�̬�洢�з����˿ռ䣬
   ������еľ�̬�����ɶ��������ڲ�ͬ�Ķ��󣬲�������ͬ��̬�����Ķ��������
   Ҳ����Ϊ���ԭ�򣬾�̬��������ʹ�ù��캯����ʼ����

#include<iostream>
using namespace std;

class Apple{

public:
    static int i;

    Apple()
    {

       // Do nothing
    };
};

int main()
{
    Apple obj1;
    Apple obj2;
    obj1.i = 2;
    obj2.i = 3;

    cout << obj1.i << " " << obj2.i;
}
 ����ĳ����п��������Ѿ�����Ϊ������󴴽���̬����i�Ķ��������
 ���Ⲣû�з�������ˣ����еľ�̬����Ӧ���û�ʹ������������ͷ�Χ�����������ʾ��ʼ����
 ����

 #include<iostream>
 using namespace std;

 class Apple
 {
 public :
    static int i;
    Apple()
    {
        // Do nothing
    };

 };

 int Apple::i = 1;

 int main()
 {
     Apple obj;
    // prints value of o
    cout << obj.i;

 }
*/
/*
    ��̬��Ա

    * �����Ϊ��̬
    �������һ��������Ҳ������Ϊstaticʱ���з�Χ��ֱ��������������ڡ�

    �������³������ж����ǷǾ�̬�ġ�

#include<iostream>
using namespace std;

class Apple
{

    int i;
public:
    Apple()
    {
        i = 0;
        cout << "Inside Constructor\n";
    }
    ~Apple()
    {
        cout << "Inside Destruvtor\n";
    }
};

int main()
{
    int x = 0;
    if(0 == x){
        Apple obj;

    }
    cout  << "Nnd of main\n";

}
������ĳ�����,������if��������Ϊ�Ǿ�̬����ˣ������ķ�Χ����if���ڡ�
��ˣ�����������ʱ�������ö���ʱ�������ù��캯����������if��Ŀ���Ȩ
Խ������������ͬʱ���ã���Ϊ����ķ�Χ������������if���ڡ�������ǽ�����
����Ϊ��̬�����������ǿ�������ı仯��

#include<iostream>>
using namespace std;

class Apple{
    int i;
public:
    Apple()
    {

        i = 0;
        cout << "Inside Constructor\n";
    }
    ~Apple()
    {
        cout << "Inside Destructor\n";
    }
};

int main()
{
    int x = 0;
    if(0 == x)
    {

        static Apple obj;
    }
    cout << "End of main\n";

}
 ���ڣ���main�������������������������Ϊ��̬����ķ�Χ��
 �ᴩ������������ڡ�
 */
/*
    ���еľ�̬����
    �������еľ�̬���ݳ�Ա��̬����һ������̬��Ա����Ҳ����������Ķ���
    ���Ǳ�����ʹ�ö����'.'�����þ�̬��Ա������
    ������ʹ�������ͷ�Χ������������þ�̬��Ա��

    ����̬��Ա���������ʾ�̬���ݳ�Ա��������̬��Ա�����������޷�������ķ�
    ��̬���ݳ�Ա���Ա������

*/
#include<iostream>
using namespace std;

class Apple{

public:
    // staic member function
    static void printMsg()
    {
        cout << "Welcome to Apple";
    }
};
// main function
int main()
{
    // invoking a static member function
    Apple::printMsg();

}
