/*
   ������̸̸thisָ����ô�
   (1) һ�������thisָ�벢���Ƕ������һ���֣�����Ӱ��siezof(����)�Ľ����
   (2) this�������������ڲ���������ķǾ�̬��Ա�����з�����ķǾ�̬��Ա��ʱ��
   ���������Զ�������ʡ�ĵ�ַ��Ϊһ�������������ݸ�������Ҳ��˵����ʹ��û��
   д��thisָ�룬�������ڱ����ʱ��Ҳ�Ǽ���this�ģ�����Ϊ�Ǿ�̬��Ա�����������βΣ�
   �Ը���Ա�ķ��ʾ�ͨ��this���С�

   ��Σ�thisָ���ʹ�ã�
   (1) ����ķǾ�̬��Ա�����з�����������ʱ��ֱ��ʹ��return *this.
   (2) ���������Ա��������ͬʱ���� this->n = n(����д�� n = n)��

   ���⣬�����ϴ�һῴ��this�ᱻ������������ A *const, A const*, ��������һ���أ�
   ����ͨ���ϵ���Է�����


*/

#include<iostream>
#include<cstring>

using namespace std;

class Person{
public:
    typedef enum{
        BOY = 0,
        GIRL
    }SexType;
    Person(char  *n, int a, SexType s){
        name = new char[strlen(n)+1];
        strcpy(name,n);
        age =a;
        sex=s;
    }
    int get_age() const{
        return this->age;
    }
    Person& add_age(int a){
        age += a;
        return *this;
    }
    ~Person(){
        delete [] name;
    }
private:
    char * name;
    int age;
    SexType sex;
};

int main()
{
    Person p("zhangsan",20,Person::BOY);
    cout << p.get_age() << endl;
    cout << p.add_age(10).get_age() << endl;
    return 0;
}
/*
    �ᷢ�ֱ�������������this,���const A* const,������Ҳ���뵽��
    ��Ϊ���������const��������ô���const��������ֻ�ܷ���const������const������
    �����޸�����������ֵ��������Ҫһ��thisָ�����޸ĵı������Ǿ���
    const A*,�����ڱ���this��constָ����const ָ�룬���Ծ�Ϊconst A* const!

    �ܽ᣺this�ڳ�Ա�����Ŀ�ʼִ��ǰ���죬�ڳ�Ա��ִ�н����������������et_age
    �����ᱻ������get_age(const A* const this),add_age�����ᱻ������add_age(A* const this,int a).
    ��c++ ����ͽṹ��ֻ��һ������ģ���ĳ�ԱĬ��private�����ṹ��public��this�����ָ�룬
    ������ɽṹ�� ��this���ǽṹ��ָ���ˡ�

*/
