#include <iostream>
using namespace std;

template <typename elemtype>
class Student{
private:
    elemtype number;
public:
    Student();
    Student(elemtype i);
    Student operator +(Student other);


    template <typename fuck>//要声明友元函数或者类外函数，得再加上一个template <typename fuck>
    friend istream& operator>>(istream& in,Student<fuck> &other);
    template <typename fuck>
    friend ostream& operator<<(ostream& out,Student<fuck> other);
};
////////////////////////////////////////////

template <typename elemtype>
Student<elemtype> Student<elemtype>::operator +(Student<elemtype> other){
    this->number = this->number + other.number;
    return *this;
}


template <typename fuck>
istream& operator>>(istream& in,Student<fuck> &other){
    cout<<"请输入你的学号:";
    in>>other.number;
    return in;
}


template <typename fuck>
ostream& operator<<(ostream& out,Student<fuck> other){
    cout<<other.number<<endl;
    return out;
}

////////////////////////////////////////////


template <typename elemtype>
Student<elemtype>::Student(){
    number = 0;
}

template <typename elemtype>
Student<elemtype>::Student(elemtype i){
    number = i;
}

int main(void)
{
    Student<int> a1;
    cout<<a1;
    Student<int> a2;
    cin>>a2;
    cout<<a2;

    Student<int> a3 = a1 + a2;

    cout<<a3;
    return 0;
}
//更多详情请见百度或者:https://www.zhihu.com/question/51705633?from=profile_question_card
