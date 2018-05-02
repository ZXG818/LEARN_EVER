#include <iostream>
#include <cstdlib>
using namespace std;

template <typename elemtype>
class Student{
private:
    elemtype number;
public:
    Student(elemtype n);
    friend ostream& operator<<(ostream& out,Student other){
        out<<other.number<<endl;
        return out;
    }

    elemtype operator +(Student other);//��Ա����������
};

template <typename elemtype>//�����ⶨ���ʱ��ǵ�д�����
elemtype Student<elemtype>::operator +(Student<elemtype> other){//������д��ʱ��ǵ���ģ�����ʽ:Student<elemtype>
    return this->number + other.number;
}

template <typename elemtype>
Student<elemtype>::Student(elemtype n){//���캯�������涨���ʱ��д��Student<elemtype>::Student(elemtype n)
    this->number = n;
}

int main(void)
{
    Student<int> c1(123);
    cout<<c1;
    Student<int> c2(234);
    cout<<c2;
    cout<<c1+c2<<endl;
    return 0;
}
