#include <iostream>
#include <cstdlib>
#include <cstdbool>
#include <assert.h>
using namespace std;

template <typename elemtype>
class LinkQueue{
public:
	class LinkNode{
	public:
		elemtype data;
		LinkNode *next;
	};
	typedef LinkNode* NodePointer;

	//��ѭ���������ÿ�
	void clear();

	//������(ɾ��ͷ�ڵ�)
	bool deQueue(elemtype &e);

	//������
	void enQueue(elemtype e);

	//��ȡͷ�ڵ��������
	bool getFront(elemtype &e);

	//�ж��Ƿ�Ϊ��
	bool isEmpty();

	//�������
	int getLength();

	//���ظ�ֵ�����
	LinkQueue operator=(LinkQueue right);

	//���캯��
	LinkQueue();

	//��������
	virtual ~LinkQueue();

	//������ʼ�����캯��
	LinkQueue(LinkQueue &other);

	//�����������
	template <typename out_put>
	friend ostream& operator<<(ostream& out, LinkQueue<out_put> &other);

protected:
	NodePointer front;//��ͷָ��
	NodePointer rear;//��βָ��
};

template <typename elemtype>
void LinkQueue<elemtype>::clear(){
	NodePointer q;
	NodePointer p = front;
	while (p){
		q = p;
		p = p->next;
		delete p;
	}
	front = rear = NULL;
}

//������
template <typename elemtype>
bool LinkQueue<elemtype>::deQueue(elemtype &e){
	if (!front){
		return false;
	}
	NodePointer s = front;
	e = s->data;
	front = front->next;
	delete s;

	if (!front){
		rear = NULL;//����ö���δ�գ���ôβָ��ҲҪ����Ϊ��
	}

	return true;
}


//������
template <typename elemtype>
void LinkQueue<elemtype>::enQueue(elemtype e){
	NodePointer s;
	s = new LinkNode;
	assert(s != 0);
	s->data = e;
	s->next = NULL;
	if (!front){
		front = rear = s;
	}
	else{
		rear->next = s;
		rear = s;
	}
}

template <typename elemtype>
bool LinkQueue<elemtype>::getFront(elemtype &e){
	if (!front){
		return false;
	}
	e = front->data;
	return true;
}

template <typename elemtype>
bool LinkQueue<elemtype>::isEmpty(){
	return !front ? true : false;
}

template <typename elemtype>
int LinkQueue<elemtype>::getLength(){
	int length = 0;
	NodePointer p = front;

	while (p){
		length++;
		p = p->next;
	}
	return length;
}

//���ظ�ֵ�����
template <typename elemtype>
LinkQueue<elemtype> LinkQueue<elemtype>::operator=(LinkQueue<elemtype> right){
	NodePointer s;
	NodePointer rp = right.front;

	if (this != &right){
		clear();
		while (rp){
			s = new LinkNode;
			assert(s != 0);
			s->data = rp->data;
			s->next = NULL;

			if (!front){
				front = rear = s;
			}
			else{
				rear->next = s;
				rear = s;
			}
			rp = rp->next;
		}
	}
	return *this;//���ض���
}

template <typename elemtype>
LinkQueue<elemtype>::LinkQueue(){
	front = rear = NULL;
}

template <typename elemtype>
LinkQueue<elemtype>::~LinkQueue(){
	clear();
	cout << "������������" << endl;
}

template <typename elemtype>
LinkQueue<elemtype>::LinkQueue(LinkQueue<elemtype> &other){
	NodePointer s;
	NodePointer op = other.front;

	rear = front = NULL;//��ǰ�����ÿգ�׼������other�ĳ�ʼ��
	while (op){
		s = new LinkNode;
		assert(s != 0);

		s->data = op->data;
		s->next = NULL;

		if (!front){
			front = rear = s;
		}
		else{
			rear->next = s;
			rear = s;
		}
		op = op->next;
	}
}


//�����������
template <typename out_put>
ostream& operator<<(ostream& out, LinkQueue<out_put> &other){
	while (other.front){
		out << other.front->data << "\t";
		other.front = other.front->next;
	}
	return out;
}


int main(void){
	LinkQueue<int> s1;
	for (int i = 1; i <= 10; i++){
		s1.enQueue(i);
	}

	cout << "������Ϊ:" << endl;
	cout << s1 << endl;
	return 0;
}
