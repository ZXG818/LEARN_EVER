#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cstdbool>
#define STACK_MAX_SIZE 100
#define STACKINCREAMENT 10
using namespace std;

template <typename elemtype>
class SqStack{
public:
	//˳��ջ�ÿ�
	void clear();

	//��˳��ջ��Ԫ�صĸ���
	int getLength();

	//���ص������Ѿ����ɵĴ洢�ռ�Ĵ�С
	int getStackSize();

	//��ȡջ��Ԫ��
	bool getTop(elemtype &e);

	//�ж�˳��ջ�Ƿ�Ϊ��
	bool isEmpty();

	//���ظ�ֵ�����
	SqStack operator=(SqStack right);

	//����ջ��Ԫ��
	bool pop(elemtype &e);

	//��ջ��ѹ��Ԫ��e
	void push(elemtype e);

	//���캯��
	SqStack();

	//��������
	virtual ~SqStack();

	//�������캯��
	SqStack(SqStack &other);

	//������������
	template <typename out_put>
	friend ostream& operator <<(ostream& out, SqStack<out_put> other);

protected:
	elemtype *base;//ջ��ָ�룬����˳��ջ��̬�洢�ռ���׵�ַ
	elemtype *top;//ջ��ָ��
	int stackSize;//˳��ջ��ǰ�Ѿ�����Ĵ洢�ռ�Ĵ�С
};


template <typename elemtype>
void SqStack<elemtype>::clear(){
	top = base;
	cout << "˳��ջ�Ѿ����" << endl;
}

template <typename elemtype>
int SqStack<elemtype>::getLength(){
	return top - base;
}

template <typename elemtype>
int SqStack<elemtype>::getStackSize(){
	return stackSize;
}

//��ȡջ����Ԫ��
template <typename elemtype>
bool SqStack<elemtype>::getTop(elemtype &e){
	if (isEmpty()){
		return false
	}
	else{
		e = *(top - 1);
	}
	return true;
}

template <typename elemtype>
bool SqStack<elemtype>::isEmpty(){
	return top == base ? true : false;
}

//���ظ�ֵ�����
template <typename elemtype>
SqStack<elemtype> SqStack<elemtype>::operator =(SqStack<elemtype> right){
	int length = right.getLength();

	if (this != &right){
		if (stackSize < right.stackSize){
			delete[] base;  //������ߵ�˳��ջ�Ĵ�ȡ�ռ�
			base = new elemtype[right.stackSize];
			assert(base != 0);
			stackSize = right.stackSize;//�������Ե�һЩ���µĸ�ֵ
		}

		for (int i = 0; i < length; i++){
			*(base + i) = *(right.base + i);
		}
		top = base + length();
	}
	return *this;//���ض���
}

//����ջ��Ԫ�ص�e
template <typename elemtype>
bool SqStack<elemtype>::pop(elemtype &e){
	if (isEmpty()){
		return false;
	}
	else{
		e = *--top;
	}
	return true;
}

//��ջ��ѹ��Ԫ��e
template <typename elemtype>
void SqStack<elemtype>::push(elemtype e){
	int length = top - base;//˳��ջ��Ԫ�صĸ���
	elemtype *newBase;//Ԥָ����˳��ջ��ջ��ָ��
	//�жϵ�ǰ˳��ջ�Ƿ�������������ˣ�����Ҫ��������洢�ռ�
	if (top - base >= stackSize){
		newBase = new elemtype[stackSize + STACKINCREAMENT];
		assert(newBase != 0);

		for (int j = 0; j < length; j++){
			*(newBase + j) = *(base + j);
		}

		delete[] base;//���յ�ǰ�Ѿ����˵�ջ�ռ�
		base = newBase;
		top = base + length;
	}

	//�����ǰ˳��ջû�������Ͳ�����������ռ��ˣ���ֱ������������������
	*top = e;
	top++;
}


template <typename elemtype>
SqStack<elemtype>::SqStack(){
	base = new elemtype[STACK_MAX_SIZE];//����ռ�
	assert(base != 0);
	stackSize = STACK_MAX_SIZE;//���Եĸ�ֵ
	top = base;//ջ�ĳ�ʼΪ��
}

//�㶮��
template <typename elemtype>
SqStack<elemtype>::~SqStack(){
	if (base){
		delete[]base;
	}
	stackSize = 0;
	top = base = NULL;
}

template <typename elemtype>
SqStack<elemtype>::SqStack(SqStack &other){
	int length = other.top - other.base;
	base = new elemtype[other.stackSize];

	assert(base != 0);

	stackSize = other.stackSize;
	for (int i = 0; i < length; i++){
		*(base + i) = *(other.base + i);
	}
	top = base + length;
}

template <typename out_put>
ostream& operator<<(ostream& out, SqStack<out_put> other){
	int length = other.top - other.base;
	for (int i = 0; i < length; i++){
		out << *(other.base + i) << "\t";
	}

	return out;
}


int main(void){
	SqStack<int> s1;
	for (int i = 1; i <= 10; i++){
		s1.push(i);
	}
	cout << "˳��ջΪ:";
	cout << s1 << endl;//Ӧ�õ����ص���������
	cout << "####################################" << endl;
	int e;
	while (s1.pop(e)){
		cout << "����ջ��Ԫ��Ϊ:" << e << endl;
	}

	return 0;
}





