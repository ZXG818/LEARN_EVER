#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <assert.h>
using namespace std;

template <typename elemtype>
class SqQueue{
public:
	//ѭ�������ÿ�
	void clear();

	//������
	bool deQueue(elemtype &e);

	//������
	bool enQueue(elemtype e);

	//��ȡѭ�����ж�ͷԪ��
	bool getFront(elemtype &e);

	//��ѭ�����е�Ԫ�صĸ���
	int getLength();

	//�ж϶����Ƿ�Ϊ��
	bool isEmpty();

	//�ж϶����Ƿ�����
	bool isFull();

	//���ظ�ֵ�����
	SqQueue operator=(SqQueue right);

	//���캯��
	SqQueue(int size = 10);

	//��������
	virtual ~SqQueue();

	//�������캯��
	SqQueue(SqQueue &other);

	//������������
	template <typename out_put>
	friend ostream& operator <<(ostream& out, SqQueue<out_put> other);

protected:
	int rear;//��βָ��
	int front;//��ͷָ��
	int queueSize;//ѭ���������洢�ռ�
	elemtype *base;//���ж�̬�洢�ռ���׵�ַ
};


template <typename elemtype>
void SqQueue<elemtype>::clear(){
	front = rear;
}

//������
template <typename elemtype>
bool SqQueue<elemtype>::deQueue(elemtype &e){
	if (isEmpty()){
		return false;
	}
	e = base[front];
	front = (front + 1) % queueSize;//����Ҫȡģ���γ�ѭ������
	return true;
}

//������
template <typename elemtype>
bool SqQueue<elemtype>::enQueue(elemtype e){
	if (isFull()){
		return false;
	}
	base[rear] = e;
	rear = (rear + 1) % queueSize;
	return true;
}

//��ȡ��ͷԪ��
template <typename elemtype>
bool SqQueue<elemtype>::getFront(elemtype &e){
	if (isEmpty()){
		return false;
	}
	e = base[front];
	return true;
}

//�������Ԫ�صĸ���
template <typename elemtype>
int SqQueue<elemtype>::getLength(){
	return (rear - front + queueSize) % queueSize;
}

//�ж��Ƿ�Ϊ��
template <typename elemtype>
bool SqQueue<elemtype>::isEmpty(){
	return front == rear ? true : false;
}

//�ж϶����Ƿ�����
template <typename elemtype>
bool SqQueue<elemtype>::isFull(){
	return (rear + 1) % queueSize == front ? true : false;
}

//���ظ�ֵ�����
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

//������ʼ�����캯��
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

//������������
template <typename out_put>
ostream& operator<<(ostream& out, SqQueue<out_put> other){
	for (int i = other.front; i%other.queueSize != other.rear;){
		out << other.base[i] << "\t";
		i = (i + 1) % other.queueSize;
	}
	return out;
}


int main(void){
	SqQueue<int> sq1;//Ĭ�ϴ���Ĳ�����10
	for (int i = 1; i <= 10; i++){
		sq1.enQueue(i);
	}

	cout << "���ڶ���Ϊ:" << endl;
	cout << sq1 << endl;

	cout << "���ڲ��Գ����к���:" << endl;
	cout << "ֻ��ǰ���:" << endl;
	for (int i = 0; i < 5; i++){
		int e;
		sq1.deQueue(e);
		cout << "������:" << e << endl;
	}
	cout << "���ڶ���Ϊ:" << endl;
	cout << sq1 << endl;
	return 0;
}
