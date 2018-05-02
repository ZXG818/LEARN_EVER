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

	//非循环链队列置空
	void clear();

	//出队列(删除头节点)
	bool deQueue(elemtype &e);

	//进队列
	void enQueue(elemtype e);

	//读取头节点的数据域
	bool getFront(elemtype &e);

	//判断是否为空
	bool isEmpty();

	//求结点个数
	int getLength();

	//重载赋值运算符
	LinkQueue operator=(LinkQueue right);

	//构造函数
	LinkQueue();

	//析构函数
	virtual ~LinkQueue();

	//拷贝初始化构造函数
	LinkQueue(LinkQueue &other);

	//重载输出函数
	template <typename out_put>
	friend ostream& operator<<(ostream& out, LinkQueue<out_put> &other);

protected:
	NodePointer front;//对头指针
	NodePointer rear;//队尾指针
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

//出队列
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
		rear = NULL;//如果该队列未空，那么尾指针也要设置为空
	}

	return true;
}


//进队列
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

//重载赋值运算符
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
	return *this;//返回对象
}

template <typename elemtype>
LinkQueue<elemtype>::LinkQueue(){
	front = rear = NULL;
}

template <typename elemtype>
LinkQueue<elemtype>::~LinkQueue(){
	clear();
	cout << "链队列清除完毕" << endl;
}

template <typename elemtype>
LinkQueue<elemtype>::LinkQueue(LinkQueue<elemtype> &other){
	NodePointer s;
	NodePointer op = other.front;

	rear = front = NULL;//当前队列置空，准备接受other的初始化
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


//重载输出函数
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

	cout << "链队列为:" << endl;
	cout << s1 << endl;
	return 0;
}
