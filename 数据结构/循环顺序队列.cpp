#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <assert.h>
using namespace std;

template <typename elemtype>
class SqQueue{
public:
	//循环队列置空
	void clear();

	//出队列
	bool deQueue(elemtype &e);

	//进队列
	bool enQueue(elemtype e);

	//读取循环队列队头元素
	bool getFront(elemtype &e);

	//求循环队列的元素的个数
	int getLength();

	//判断队列是否为空
	bool isEmpty();

	//判断队列是否已满
	bool isFull();

	//重载赋值运算符
	SqQueue operator=(SqQueue right);

	//构造函数
	SqQueue(int size = 10);

	//析构函数
	virtual ~SqQueue();

	//拷贝构造函数
	SqQueue(SqQueue &other);

	//重载输出运算符
	template <typename out_put>
	friend ostream& operator <<(ostream& out, SqQueue<out_put> other);

protected:
	int rear;//队尾指针
	int front;//对头指针
	int queueSize;//循环队列最大存储空间
	elemtype *base;//队列动态存储空间的首地址
};


template <typename elemtype>
void SqQueue<elemtype>::clear(){
	front = rear;
}

//出队列
template <typename elemtype>
bool SqQueue<elemtype>::deQueue(elemtype &e){
	if (isEmpty()){
		return false;
	}
	e = base[front];
	front = (front + 1) % queueSize;//这里要取模，形成循环队列
	return true;
}

//进队列
template <typename elemtype>
bool SqQueue<elemtype>::enQueue(elemtype e){
	if (isFull()){
		return false;
	}
	base[rear] = e;
	rear = (rear + 1) % queueSize;
	return true;
}

//读取队头元素
template <typename elemtype>
bool SqQueue<elemtype>::getFront(elemtype &e){
	if (isEmpty()){
		return false;
	}
	e = base[front];
	return true;
}

//求队列中元素的个数
template <typename elemtype>
int SqQueue<elemtype>::getLength(){
	return (rear - front + queueSize) % queueSize;
}

//判断是否为空
template <typename elemtype>
bool SqQueue<elemtype>::isEmpty(){
	return front == rear ? true : false;
}

//判断队列是否已满
template <typename elemtype>
bool SqQueue<elemtype>::isFull(){
	return (rear + 1) % queueSize == front ? true : false;
}

//重载赋值运算符
template <typename elemtype>
SqQueue<elemtype> SqQueue<elemtype>::operator=(SqQueue<elemtype> right){
	if (this != &right){
		if (queueSize != right.queueSize){
			delete[] base;
			base = new elemtype[right.queueSize];
			assert(base != 0);
			queueSize = right.queueSize;
		}

		front = right.front;
		rear = right.rear;

		for (int i = front; i%queueSize != rear;){
			base[i] = right.base[i];
			i = (i + 1) % queueSize;
		}
	}
	return *this;
}

template <typename elemtype>
SqQueue<elemtype>::SqQueue(int size = 10){
	base = new elemtype[size];
	assert(base != 0);
	front = rear = 0;
	queueSize = size;
}

template <typename elemtype>
SqQueue<elemtype>:: ~SqQueue(){
	delete[]base;
}

//拷贝初始化构造函数
template <typename elemtype>
SqQueue<elemtype>::SqQueue(SqQueue &other){
	base = new elemtype[other.queueSize];
	assert(base != 0);
	queueSize = other.queueSize;

	front = other.front;
	rear = other.rear;

	for (int i = front; i%queueSize != rear;){
		base[i] = other.base[i];
		i = (i + 1) % queueSize;
	}
}

//重载输出运算符
template <typename out_put>
ostream& operator<<(ostream& out, SqQueue<out_put> other){
	for (int i = other.front; i%other.queueSize != other.rear;){
		out << other.base[i] << "\t";
		i = (i + 1) % other.queueSize;
	}
	return out;
}


int main(void){
	SqQueue<int> sq1;//默认传入的参数是10
	for (int i = 1; i <= 10; i++){
		sq1.enQueue(i);
	}

	cout << "现在队列为:" << endl;
	cout << sq1 << endl;

	cout << "现在测试出队列函数:" << endl;
	cout << "只出前五个:" << endl;
	for (int i = 0; i < 5; i++){
		int e;
		sq1.deQueue(e);
		cout << "出队列:" << e << endl;
	}
	cout << "现在队列为:" << endl;
	cout << sq1 << endl;
	return 0;
}
