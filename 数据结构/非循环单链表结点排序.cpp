#include <iostream>
#include <cstdlib>
#include <cstring>
#include <assert.h>
using namespace std;

class Student{
public:
	class LinkNode{
	public:
		int data;
		char name[128];
		LinkNode* next;
	};
	typedef LinkNode* NodePointer;

	Student();//����Ĭ�Ϻ���
	void insert(int i, char *inputName, int value);
	friend ostream& operator<<(ostream& out, Student &other);
	friend void sortTheData(Student s1);
	
private:
	NodePointer head;
};

Student::Student(){
	head = NULL;
}

void Student::insert(int i, char *inputName, int value){
	if (i == 1){
		NodePointer s = new LinkNode;
		strcpy(s->name, inputName);
		s->data = value;
		s->next = head;
		head = s;
		cout << "ͷ������ɹ�" << endl;
		return;
	}

	int j = 1;
	NodePointer p = head;
	NodePointer s;
	while (p && j < i - 1){
		j++;
		p = p->next;//�ҵ�ǰ��
	}
	s = new LinkNode;
	strcpy(s->name, inputName);
	s->data = value;
	s->next = p->next;
	p->next = s;
	cout << "����ɹ�" << endl;
	return;
}


ostream& operator<<(ostream& out, Student &other){
	Student::NodePointer p = other.head;
	while (p){
		out << "����:" << p->name << "\t" << "����:" << p->data << endl;
		p = p->next;
	}
	return out;
}

void sortTheData(Student s1){
	Student::NodePointer p = s1.head;
	while (p){
		Student::NodePointer s = p;
		while (s){
			if (s->data > p->data){
				int temp = s->data;
				s->data = p->data;
				p->data = temp;

				char tempName[128];
				strcpy(tempName, s->name);
				strcpy(s->name, p->name);
				strcpy(p->name, tempName);
			}
			s = s->next;
		}
		p = p->next;
	}
}


int main(void){
	Student s1;
	int data;
	char name[128];
	for (int i = 1; i <= 3; i++){
		cout << "����������:";
		cin >> name;
		cout << "����������:";
		cin >> data;

		s1.insert(i, name, data);
	}

	cout << "*****************************" << endl;
	cout << "s1��:" << endl;
	cout << s1 << endl;

	cout << "*****************************" << endl;
	cout << "������s1��:" << endl;
	sortTheData(s1);
	cout << s1;
	return 0;
}



