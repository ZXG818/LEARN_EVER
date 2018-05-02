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
	//顺序栈置空
	void clear();

	//求顺序栈中元素的个数
	int getLength();

	//返回档期那已经分派的存储空间的大小
	int getStackSize();

	//读取栈顶元素
	bool getTop(elemtype &e);

	//判断顺序栈是否为空
	bool isEmpty();

	//重载赋值运算符
	SqStack operator=(SqStack right);

	//弹出栈顶元素
	bool pop(elemtype &e);

	//在栈顶压入元素e
	void push(elemtype e);

	//构造函数
	SqStack();

	//析构函数
	virtual ~SqStack();

	//拷贝构造函数
	SqStack(SqStack &other);

	//重载输出运算符
	template <typename out_put>
	friend ostream& operator <<(ostream& out, SqStack<out_put> other);

protected:
	elemtype *base;//栈底指针，就是顺序栈动态存储空间的首地址
	elemtype *top;//栈顶指针
	int stackSize;//顺序栈当前已经分配的存储空间的大小
};


template <typename elemtype>
void SqStack<elemtype>::clear(){
	top = base;
	cout << "顺序栈已经清空" << endl;
}

template <typename elemtype>
int SqStack<elemtype>::getLength(){
	return top - base;
}

template <typename elemtype>
int SqStack<elemtype>::getStackSize(){
	return stackSize;
}

//读取栈顶的元素
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

//重载赋值运算符
template <typename elemtype>
SqStack<elemtype> SqStack<elemtype>::operator =(SqStack<elemtype> right){
	int length = right.getLength();

	if (this != &right){
		if (stackSize < right.stackSize){
			delete[] base;  //回收左边的顺序栈的存取空间
			base = new elemtype[right.stackSize];
			assert(base != 0);
			stackSize = right.stackSize;//进行属性的一些重新的赋值
		}

		for (int i = 0; i < length; i++){
			*(base + i) = *(right.base + i);
		}
		top = base + length();
	}
	return *this;//返回对象
}

//弹出栈顶元素到e
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

//在栈顶压入元素e
template <typename elemtype>
void SqStack<elemtype>::push(elemtype e){
	int length = top - base;//顺序栈中元素的个数
	elemtype *newBase;//预指向新顺序栈的栈底指针
	//判断当前顺序栈是否已满，如果满了，则需要另外申请存储空间
	if (top - base >= stackSize){
		newBase = new elemtype[stackSize + STACKINCREAMENT];
		assert(newBase != 0);

		for (int j = 0; j < length; j++){
			*(newBase + j) = *(base + j);
		}

		delete[] base;//回收当前已经满了的栈空间
		base = newBase;
		top = base + length;
	}

	//如果当前顺序栈没有满，就不用重新申请空间了，就直接以下两个语句就行了
	*top = e;
	top++;
}


template <typename elemtype>
SqStack<elemtype>::SqStack(){
	base = new elemtype[STACK_MAX_SIZE];//申请空间
	assert(base != 0);
	stackSize = STACK_MAX_SIZE;//属性的赋值
	top = base;//栈的初始为空
}

//你懂的
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
	cout << "顺序栈为:";
	cout << s1 << endl;//应用的重载的输出运算符
	cout << "####################################" << endl;
	int e;
	while (s1.pop(e)){
		cout << "弹出栈顶元素为:" << e << endl;
	}

	return 0;
}





