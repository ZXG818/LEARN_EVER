#include <iostream>
using namespace std;

template <typename elemtype>
class Rectangle{
private:
    elemtype number;//序号
    elemtype length;//长方形的长
    elemtype width;//长方形的宽
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
    Rectangle();//默认构造函数声明y
    Rectangle(elemtype n,elemtype l,elemtype w);//构造函数声明

    elemtype operator +(Rectangle other);//重载  ‘+’号运算符,返回两个长方形的面积之和

    template <typename fuck>
    friend istream& operator >>(istream& in,Rectangle<fuck> &other);//重载输入运算符
    template <typename fuck>
    friend ostream& operator <<(ostream& out,Rectangle<fuck> &other);//重载输出运算符

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
    cout<<"请输入序号:";
    in>>other.number;
    cout<<"请输入长:";
    in>>other.length;
    cout<<"请输入宽:";
    in>>other.width;
    return in;
}

template <typename fuck>
ostream& operator<<(ostream& out,Rectangle<fuck> &other){
    out<<"序号:"<<other.number<<endl;
    out<<"长:"<<other.length<<endl;
    out<<"宽:"<<other.width<<endl;
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

    elemtype operator +(MyRectangle other);//重载  ‘+’号运算符,返回两个长方形的面积之和

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
    cout<<"请输入序号:";
    in>>other.number;
    cout<<"请输入长:";
    in>>other.length;
    cout<<"请输入宽:";
    in>>other.width;
    return in;
}

template <typename fuck>
ostream& operator<<(ostream& out,MyRectangle<fuck> other){
    out<<"序号:"<<other.number<<endl;
    out<<"长:"<<other.length<<endl;
    out<<"宽:"<<other.width<<endl;
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





















