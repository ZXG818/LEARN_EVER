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

	//����ջ�ÿ�
	void clear();

	//����ջ�н��ĸ���
	int getLength();

	//�ж���ջ�Ƿ�Ϊ��
	bool isEmpty();

	//��ȡջ������������
	bool getTop(elemtype &e);

	//���ظ�ֵ�����
	LinkStack operator=(LinkStack right);

	//����ջ�����
	bool pop(elemtype &e);

	//��ջ��ѹ��һ��������Ϊe�Ľ��
	void push(elemtype e);

	LinkStack();//��ջ���캯��

	//��������
	virtual ~LinkStack();

	//��ջ�������캯��
	LinkStack(LinkStack &other);

	template <typename out_put>
	friend ostream& operator<<(ostream& out, LinkStack<out_put> other);

protected:
	NodePointer top;//��ջջ��ָ��
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

//�ж���ջ�Ƿ�Ϊ��
template <typename elemtype>
bool LinkStack<elemtype>::isEmpty(){
	return top ? false : true;
}

//���ظ�ֵ�����
template <typename elemtype>
LinkStack<elemtype> LinkStack<elemtype>::operator=(LinkStack<elemtype> right){
	NodePointer p;//�����ջ��ǰ�������ָ��

	NodePointer rp = right.top;
	NodePointer s;//Ԥָ�������ջ�½ڵ��ָ��

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
	return *this;//���ض���
}

//��ջ
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


//ѹջ
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
	cout << "����ջ���" << endl;
}

//��ջ�������캯��
template <typename elemtype>
LinkStack<elemtype>::LinkStack(LinkStack<elemtype> &other){
	NodePointer p;
	NodePointer op = other.top;

	NodePointer s;

	top = p = NULL;

	while (op){//��Щ�����㶮��
		s = new LinkNode;
		assert(s != 0);
		s->data = op->data;
		if (!top){
			top = s;
			cout << "��һ����������" << endl;
		}
		else{
			p->next = s;
			cout << "��������" << endl;
		}
		p = s;
		op = op->next;
	}
	if (p){
		p->next = NULL;//��ջջ�׽���ָ���ÿ�
	}
}

//������������
template <typename out_put>
ostream& operator<<(ostream& out, LinkStack<out_put> other){
	LinkStack<out_put>::NodePointer s = other.top;
	while (s){
		out << "ֵ:" << s->data << endl;
		s = s->next;
	}
	return out;
}

int main(void){
	LinkStack<int> s1;
	for (int i = 1; i < 11; i++){
		s1.push(i);//����ѹջ��Ա����
	}
	cout << "��ջ�������:" << endl;
	cout << "��ջΪ:" << endl;
	cout << s1 << endl;//����������������
	cout << "��ջ:" << endl;
	for (int i = 1; i < 11; i++){
		int e;
		if (s1.pop(e)){//���Ե�ջ��Ա����
			cout << e << endl;
		}
	}

	LinkStack<int> s2;
	for (int i = 1; i <= 5; i++){
		s2.push(i);
	}

	s1 = s2;//���Ը�ֵ�����������

	cout << "s1Ϊ:" << endl;
	cout << s1;


	return 0;
}



