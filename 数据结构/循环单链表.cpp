//���������
//ѭ����������head�Ե���Ϊ��Ҫ����Ȼ�������ͱȽ���Ҫ
#include <iostream>
#include <assert.h>
#include <cstdlib>
using namespace std;

template <typename elemtype>
class CircularLinkList{
public:
	//ѭ��������Ľ������
	class LinkNode{
	public:
		elemtype data;
		LinkNode *next;
	};
	typedef LinkNode* NodePointer;
	////////////////////////////////////////////////////
	//�Լ���ӵ�
	//////����Ԫ��
	void insert(elemtype number);
	//////�������
	void display();
	////////////////////////////////////////////////////
	void clear();//ѭ���������ÿ�

	//ɾ����i����㣬ͷָ���ƶ�����һ�����
	void deleteElem(int i, elemtype &e);

	//ȡѭ���������һ������������
	elemtype getHeadElem();

	//�ж�ѭ���������Ƿ�Ϊ��
	bool isEmpty();

	//��ѭ���������ͷָ���ƶ�����i�����
	void moveHead(int i);

	//���ظ�ֵ���������
	CircularLinkList<elemtype> operator=(CircularLinkList<elemtype> rightL);

	//ѭ��������Ĺ��캯��
	CircularLinkList();
	//��������
	virtual ~CircularLinkList();
	//ѭ������������ʼ�����캯��
	CircularLinkList(const CircularLinkList& other);
protected:
	NodePointer head;
};

template <typename elemtype>
void CircularLinkList<elemtype>::clear(){
	NodePointer p;//Ԥָ��ѭ��������ڶ�������ָ��
	//ÿ�λ���ѭ��������ĵڶ������Ĵ洢�ռ䣬֪����ʣ�µ�һ�����Ϊֹ
	while (head != head->next){
		p = head->next;//ָ��ڶ������
		head->next = p->next;//�޸ĵ�һ�������ָ����next��ʹ���ƹ��ڶ������
		delete p;//���յڶ������Ĵ洢�ռ�
	}
	delete head;
	head = NULL;
}

template <typename elemtype>
void CircularLinkList<elemtype>::deleteElem(int i, elemtype &e){
	int j = 1;//��ǰ�����ź�,��ʼ��Ϊ1
	NodePointer r;//Ԥָ��ǰ������ָ��
	NodePointer p = head;//ָ��ǰ��㣬��ʼ��ָ���һ�����

	//��ָ��p��ѭ��������ĵ�һ����㿪ʼ��������������ֱ���ҵ���i�����
	while (j < i){
		r = p;//ǰ�����
		p = p->next;
		j++;
	}

	e = p->data;
	if (p == p->next){
		head = NULL;//���ֻʣ��һ����㣬��head�ÿ�
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


//��ͷָ��head���Ƶ���i�����
template <typename elemtype>
void CircularLinkList<elemtype>::moveHead(int i){
	int j = 1;
	while (j < i){
		head = head->next;
		j++;
	}
}


//���ظ�ֵ�����
template <typename elemtype>
CircularLinkList<elemtype> CircularLinkList<elemtype>::operator=(CircularLinkList<elemtype> rightL){
	NodePointer p = NULL;//Ԥָ���ѭ��������ǰ���
	NodePointer rp = rightL.head;//��дע��Ҳ֪�������ʲô��˼
	NodePointer s;

	//�ж���������Ƿ�����ұߵ�
	if (this != &rightL){
		clear();//��������ÿգ�׼�����ܱ���ֵ

		while (rp->next != rightL.head){
			s = new (LinkNode);
			assert(s != 0);
			s->data = rp->data;

			//���½�����ӵ���ߵ�������
			if (!head){
				head = s;
			}
			else{
				p->next = s;
			}
			p = s;
			rp = rp->next;
		}
		if (head)//����������Ϊ��
		{
			p->next = head;
		}
	}
	return *this//���ض���
}


//���캯��
template <typename elemtype>
CircularLinkList<elemtype>::CircularLinkList(){
	head = NULL;
}


//��������
template <typename elemtype>
CircularLinkList<elemtype>::~CircularLinkList(){
	clear();
}

//������ʼ������
template <typename elemtype>
CircularLinkList<elemtype>::CircularLinkList(const CircularLinkList<elemtype> &other){
	NodePointer p;//Ԥָ��ǰ���
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
		p->next = head;//�γ�ѭ��������
	}
}

//����Ԫ��
template <typename elemtype>
void CircularLinkList<elemtype>::insert(elemtype number){
	NodePointer s;//���ڴ���ָ��
	NodePointer p;
	head = p = new LinkNode;//Ҫ����洢�ռ�
	for (int i = 0; i < number; i++){
		elemtype value;
		cout << "������ֵ:";
		cin >> value;
		//β�巨��������
		s = new LinkNode;
		s->data = value;
		p->next = s;
		p = s;
	}
	p->next = head;//�γ�ѭ������
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
	cout << "����������ĸ���:";
	cin >> number;
	c1.insert(number);
	cout << "������Ϊ:" << endl;
	c1.display();
	return 0;
}







