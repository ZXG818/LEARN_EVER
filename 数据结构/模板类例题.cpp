#include <iostream>
using namespace std;

template <typename elemtype>
class Rectangle{
private:
    elemtype number;//���
    elemtype length;//�����εĳ�
    elemtype width;//�����εĿ�
public:
    elemtype get_number(){
        return number;
    }
    elemtype get_length(){
        return length;
    }
    elemtype get_width(){
        return width;
    }
    Rectangle();//Ĭ�Ϲ��캯������y
    Rectangle(elemtype n,elemtype l,elemtype w);//���캯������

    elemtype operator +(Rectangle other);//����  ��+���������,�������������ε����֮��

    template <typename fuck>
    friend istream& operator >>(istream& in,Rectangle<fuck> &other);//�������������
    template <typename fuck>
    friend ostream& operator <<(ostream& out,Rectangle<fuck> &other);//������������

};


template <typename elemtype>
Rectangle<elemtype>::Rectangle(){
    this->number = 0;
    this->length = 0;
    this->width = 0;
}

template <typename elemtype>
Rectangle<elemtype>::Rectangle(elemtype n,elemtype l,elemtype w){
    this->number = n;
    this->length = l;
    this->width = w;
}

template <typename elemtype>
elemtype Rectangle<elemtype>::operator +(Rectangle<elemtype> other){
    elemtype square1 = this->width * this->length;
    elemtype square2 = other.width * other.length;
    return square1 + square2;
}


template <typename fuck>
istream& operator>>(istream& in,Rectangle<fuck> &other){
    cout<<"���������:";
    in>>other.number;
    cout<<"�����볤:";
    in>>other.length;
    cout<<"�������:";
    in>>other.width;
    return in;
}

template <typename fuck>
ostream& operator<<(ostream& out,Rectangle<fuck> &other){
    out<<"���:"<<other.number<<endl;
    out<<"��:"<<other.length<<endl;
    out<<"��:"<<other.width<<endl;
    return out;
}

template <typename elemtype>
class MyRectangle:private Rectangle<elemtype>{
private:
    elemtype number;
    elemtype length;
    elemtype width;
public:
    MyRectangle();
    MyRectangle(elemtype n , elemtype l, elemtype w);

    elemtype operator +(MyRectangle other);//����  ��+���������,�������������ε����֮��

    template <typename fuck>
    friend istream& operator>>(istream& in,MyRectangle<fuck> &other);
    template <typename fuck>
    friend ostream& operator<<(ostream& out,MyRectangle<fuck> other);
};

template <typename elemtype>
MyRectangle<elemtype>::MyRectangle(){
    number = 0;
    length = 0;
    width = 0;
}

template <typename elemtype>
MyRectangle<elemtype>::MyRectangle(elemtype n,elemtype l,elemtype w){
    number = n;
    length = l;
    width = w;
}

template <typename fuck>
istream& operator>>(istream& in,MyRectangle<fuck> &other){
    cout<<"���������:";
    in>>other.number;
    cout<<"�����볤:";
    in>>other.length;
    cout<<"�������:";
    in>>other.width;
    return in;
}

template <typename fuck>
ostream& operator<<(ostream& out,MyRectangle<fuck> other){
    out<<"���:"<<other.number<<endl;
    out<<"��:"<<other.length<<endl;
    out<<"��:"<<other.width<<endl;
    return out;
}

template <typename elemtype>
elemtype MyRectangle<elemtype>::operator +(MyRectangle<elemtype> other){
    elemtype square1 = this->width * this->length;
    elemtype square2 = other.width * other.length;
    return square1 + square2;
}



int main(void)
{
    MyRectangle<int> m1;
    cout<<m1;
    MyRectangle<int> m2;
    cin>>m2;
    cout<<m2;
    cout<<m1+m2;
    return 0;
}





















