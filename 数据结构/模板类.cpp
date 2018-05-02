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

    elemtype operator +(Student other);//成员函数的声明
};

template <typename elemtype>//在类外定义的时候记得写上这句
elemtype Student<elemtype>::operator +(Student<elemtype> other){//在外面写的时候记得类模板的形式:Student<elemtype>
    return this->number + other.number;
}

template <typename elemtype>
Student<elemtype>::Student(elemtype n){//构造函数在外面定义的时候写成Student<elemtype>::Student(elemtype n)
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
