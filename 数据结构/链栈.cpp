#include <iostream>
#include <cstdlib>
#include <assert.h>
#include <cstdbool>
using namespace std;

template <typename elemtype>
class LinkStack{
public:
	class LinkNode{
	public:
		elemtype data;
		LinkNode *next;
	};

	typedef LinkNode* NodePointer;

	//把链栈置空
	void clear();

	//求链栈中结点的个数
	int getLength();

	//判断链栈是否为空
	bool isEmpty();

	//读取栈顶结点的数据域
	bool getTop(elemtype &e);

	//重载赋值运算符
	LinkStack operator=(LinkStack right);

	//弹出栈顶结点
	bool pop(elemtype &e);

	//在栈顶压入一个数据域为e的结点
	void push(elemtype e);

	LinkStack();//链栈构造函数

	//析构函数
	virtual ~LinkStack();

	//链栈拷贝构造函数
	LinkStack(LinkStack &other);

	template <typename out_put>
	friend ostream& operator<<(ostream& out, LinkStack<out_put> other);

protected:
	NodePointer top;//链栈栈顶指针
};

template <typename elemtype>
void LinkStack<elemtype>::clear(){
	NodePointer s;

	while (top){
		s = top;
		top = top->next;
		delete s;
	}
	top = NULL;
}

template <typename elemtype>
int LinkStack<elemtype>::getLength(){
	int length = 0;
	NodePointer p = this->top;

	while (p){
		length++;
		p = p->next;
	}
	return length;
}

template <typename elemtype>
bool LinkStack<elemtype>::getTop(elemtype &e){
	if (!top){
		return false;
	}
	else{
		e = top->data;
		return true;
	}
}

//判断链栈是否为空
template <typename elemtype>
bool LinkStack<elemtype>::isEmpty(){
	return top ? false : true;
}

//重载赋值运算符
template <typename elemtype>
LinkStack<elemtype> LinkStack<elemtype>::operator=(LinkStack<elemtype> right){
	NodePointer p;//左边链栈当前处理结点的指针

	NodePointer rp = right.top;
	NodePointer s;//预指向左边链栈新节点的指针

	if (this != &right){
		clear();
		while (rp){
			s = new LinkNode;
			assert(s != 0);
			s->data = rp->data;

			if (!top){
				top = s;
			}
			else{
				p->next = s;
			}
			p = s;
			rp = rp->next;
		}
		if (p){
			p->next = NULL;
		}
	}
	return *this;//返回对象
}

//弹栈
template <typename elemtype>
bool LinkStack<elemtype>::pop(elemtype &e){
	NodePointer s = top;
	if (!top){
		return false;
	}
	else{
		e = top->data;
		top = top->next;
		delete s;
	}
	return true;
}


//压栈
template <typename elemtype>
void LinkStack<elemtype>::push(elemtype e){
	NodePointer s;

	s = new LinkNode;
	assert(s != 0);
	s->data = e;
	s->next = top;
	top = s;
}

template <typename elemtype>
LinkStack<elemtype>::LinkStack(){
	top = NULL;
}

template <typename elemtype>
LinkStack<elemtype>::~LinkStack(){
	clear();
	cout << "清理栈完毕" << endl;
}

//链栈拷贝构造函数
template <typename elemtype>
LinkStack<elemtype>::LinkStack(LinkStack<elemtype> &other){
	NodePointer p;
	NodePointer op = other.top;

	NodePointer s;

	top = p = NULL;

	while (op){//这些代码你懂的
		s = new LinkNode;
		assert(s != 0);
		s->data = op->data;
		if (!top){
			top = s;
			cout << "第一个结点插入中" << endl;
		}
		else{
			p->next = s;
			cout << "结点插入中" << endl;
		}
		p = s;
		op = op->next;
	}
	if (p){
		p->next = NULL;//链栈栈底结点的指针置空
	}
}

//输出运算符重载
template <typename out_put>
ostream& operator<<(ostream& out, LinkStack<out_put> other){
	LinkStack<out_put>::NodePointer s = other.top;
	while (s){
		out << "值:" << s->data << endl;
		s = s->next;
	}
	return out;
}

int main(void){
	LinkStack<int> s1;
	for (int i = 1; i < 11; i++){
		s1.push(i);//测试压栈成员函数
	}
	cout << "链栈插入完毕:" << endl;
	cout << "链栈为:" << endl;
	cout << s1 << endl;//测试重载输出运算符
	cout << "弹栈:" << endl;
	for (int i = 1; i < 11; i++){
		int e;
		if (s1.pop(e)){//测试弹栈成员函数
			cout << e << endl;
		}
	}

	LinkStack<int> s2;
	for (int i = 1; i <= 5; i++){
		s2.push(i);
	}

	s1 = s2;//测试赋值运算符的重载

	cout << "s1为:" << endl;
	cout << s1;


	return 0;
}



