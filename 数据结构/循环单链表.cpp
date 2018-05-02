//具体事项看书
//循环单链表中head显得尤为重要，虽然他本来就比较重要
#include <iostream>
#include <assert.h>
#include <cstdlib>
using namespace std;

template <typename elemtype>
class CircularLinkList{
public:
	//循环单链表的结点声明
	class LinkNode{
	public:
		elemtype data;
		LinkNode *next;
	};
	typedef LinkNode* NodePointer;
	////////////////////////////////////////////////////
	//自己添加的
	//////插入元素
	void insert(elemtype number);
	//////输出链表
	void display();
	////////////////////////////////////////////////////
	void clear();//循环单链表置空

	//删除第i个结点，头指针移动到下一个结点
	void deleteElem(int i, elemtype &e);

	//取循环单链表第一个结点的数据域
	elemtype getHeadElem();

	//判断循环单链表是否为空
	bool isEmpty();

	//把循环单链表的头指针移动到第i个结点
	void moveHead(int i);

	//重载赋值运算符定义
	CircularLinkList<elemtype> operator=(CircularLinkList<elemtype> rightL);

	//循环单链表的构造函数
	CircularLinkList();
	//析构函数
	virtual ~CircularLinkList();
	//循环单链表拷贝初始化构造函数
	CircularLinkList(const CircularLinkList& other);
protected:
	NodePointer head;
};

template <typename elemtype>
void CircularLinkList<elemtype>::clear(){
	NodePointer p;//预指向循环单链表第二个结点的指针
	//每次回收循环单链表的第二个结点的存储空间，知道仅剩下第一个结点为止
	while (head != head->next){
		p = head->next;//指向第二个结点
		head->next = p->next;//修改第一个几点的指针域next，使其绕过第二个结点
		delete p;//回收第二个结点的存储空间
	}
	delete head;
	head = NULL;
}

template <typename elemtype>
void CircularLinkList<elemtype>::deleteElem(int i, elemtype &e){
	int j = 1;//当前结点的信号,初始化为1
	NodePointer r;//预指向前驱结点的指针
	NodePointer p = head;//指向当前结点，初始化指向第一个结点

	//让指针p从循环单链表的第一个结点开始，沿着链表滑动，直到找到第i个结点
	while (j < i){
		r = p;//前驱结点
		p = p->next;
		j++;
	}

	e = p->data;
	if (p == p->next){
		head = NULL;//如果只剩下一个结点，将head置空
	}
	else{
		head = r->next = p->next;
	}
	delete p;
}

template <typename elemtype>
elemtype CircularLinkList<elemtype>::getHeadElem(){
	return head->data;
}

template <typename elemtype>
bool CircularLinkList<elemtype>::isEmpty(){
	return head ? false : true;
}


//把头指针head后移到第i个结点
template <typename elemtype>
void CircularLinkList<elemtype>::moveHead(int i){
	int j = 1;
	while (j < i){
		head = head->next;
		j++;
	}
}


//重载赋值运算符
template <typename elemtype>
CircularLinkList<elemtype> CircularLinkList<elemtype>::operator=(CircularLinkList<elemtype> rightL){
	NodePointer p = NULL;//预指左边循环单链表当前结点
	NodePointer rp = rightL.head;//不写注释也知道这个是什么意思
	NodePointer s;

	//判定左边链表是否等于右边的
	if (this != &rightL){
		clear();//左边链表置空，准备接受被赋值

		while (rp->next != rightL.head){
			s = new (LinkNode);
			assert(s != 0);
			s->data = rp->data;

			//把新结点链接到左边的链表中
			if (!head){
				head = s;
			}
			else{
				p->next = s;
			}
			p = s;
			rp = rp->next;
		}
		if (head)//如果左边链表不为空
		{
			p->next = head;
		}
	}
	return *this//返回对象
}


//构造函数
template <typename elemtype>
CircularLinkList<elemtype>::CircularLinkList(){
	head = NULL;
}


//析构函数
template <typename elemtype>
CircularLinkList<elemtype>::~CircularLinkList(){
	clear();
}

//拷贝初始化函数
template <typename elemtype>
CircularLinkList<elemtype>::CircularLinkList(const CircularLinkList<elemtype> &other){
	NodePointer p;//预指向当前结点
	NodePointer op = other.head;

	NodePointer s;
	head = p = NULL;

	while (op != other.head){
		s = new LinkNode;
		assert(s != 0);
		s->data = op->data;

		if (!head){
			head = s;
		}
		else{
			p->next = s;
		}

		p = s;
		op = op->next;
	}
	if (head){
		p->next = head;//形成循环单链表
	}
}

//插入元素
template <typename elemtype>
void CircularLinkList<elemtype>::insert(elemtype number){
	NodePointer s;//用于创建指针
	NodePointer p;
	head = p = new LinkNode;//要分配存储空间
	for (int i = 0; i < number; i++){
		elemtype value;
		cout << "请输入值:";
		cin >> value;
		//尾插法创建链表
		s = new LinkNode;
		s->data = value;
		p->next = s;
		p = s;
	}
	p->next = head;//形成循环链表
}



template <typename elemtype>
void CircularLinkList<elemtype>::display(){
	NodePointer p = head->next;

	while (p != head){
		cout << p->data << "\t";
		p = p->next;
	}
	cout << endl;
}


int main(void){
	CircularLinkList<int> c1;
	int number;
	cout << "请输入参数的个数:";
	cin >> number;
	c1.insert(number);
	cout << "链表结果为:" << endl;
	c1.display();
	return 0;
}







