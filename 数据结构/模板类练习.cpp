#include <iostream>
using namespace std;

template <typename elemtype>
class Complex{
private:
    elemtype real;
    elemtype image;
public:
    Complex();//Ĭ�ϵĹ��캯����Ϊ��
    Complex(elemtype input_real);//ʵ������ֵ���鲿��Ϊ0
    Complex(elemtype input_real,elemtype input_image);//ʵ�����鲿������ֵ

    Complex operator+(Complex other);//���ؼӺ������
    Complex operator-(Complex other);//���ؼ��������

    template <typename input>
    friend istream& operator >>(istream& in,Complex<input> &other);

    template <typename output>
    friend ostream& operator <<(ostream& out,Complex<output> other);
};


template <typename elemtype>
Complex<elemtype>::Complex(){
    real = 0;
    image = 0;
}

template <typename elemtype>
Complex<elemtype>::Complex(elemtype input_real){
    real = input_real;
    image = 0;
}

template <typename elemtype>
Complex<elemtype>::Complex(elemtype input_real,elemtype input_image){
    real = input_real;
    image = input_image;
}


template <typename elemtype>
Complex<elemtype> Complex<elemtype>::operator +(Complex<elemtype> other){
    this->real += other.real;
    this->image += other.image;
    return *this;
}

template <typename elemtype>
Complex<elemtype> Complex<elemtype>::operator -(Complex<elemtype> other){
    this->real -= other.real;
    this->image-= other.image;
    return *this;
}

template <typename input>
istream& operator>>(istream& in,Complex<input> &other){
    cout<<"������ʵ��:";
    in>>other.real;
    cout<<"�������鲿:";
    in>>other.image;
    return in;
}

template <typename output>
ostream& operator<<(ostream& out,Complex<output> other){
    out<<other.real<<"+"<<other.image<<"i"<<endl;
    return out;
}




int main(void)
{
    Complex<float> c1;
    cout<<"c1="<<c1;
    Complex<float> c2(1.2);
    cout<<"c2="<<c2;
    Complex<float> c3(1.2,3.4);
    cout<<"c3="<<c3;

    Complex<float> c4;
    cin>>c4;
    cout<<c4;

    cout<<"c3+c4 = "<<c3+ c4;
    cout<<"c3-c4 = "<<c3-c4;
    return 0;
}
