#include <iostream>
#include <assert.h>
using namespace std;
//�й�KMP�㷨��һƪ����:https://blog.csdn.net/lee18254290736/article/details/77278769
class SqString{
public:
	//��˳���ÿ�
	void clear();

	//��ȡ��i���ַ�
	bool getChar(int i, char &c);

	//��˳�򴮵ĳ���
	int getLength();

	//��ģʽ����next����
	void get_next(int *next, int display = 1);

	//��������ƥ��(�л��ݲ���)
	int index(SqString p, int pos);

	//ģʽƥ��(�޻���KMP����)
	int index_KMP(SqString p, int pos);

	//�ڵ�i���ַ�ǰ������һ���ַ���
	bool insert(int i, SqString t);

	//�ж�˳���Ƿ�Ϊ��
	bool isEmpty();

	//���ظ�ֵ�����   char�����ַ���
	SqString operator=(char *s);

	//���ظ�ֵ�����  SqString����˳��
	SqString operator=(SqString s);

	//���ؼӷ������    ������char����
	SqString operator+(char* s);

	//���ؼӷ������   SqString����˳��
	SqString operator+(SqString s);

	//�����Ƿ�С�������  SqString����
	bool operator <(SqString s);

	//�����Ƿ���������  char
	int operator ==(char *s);

	//�����Ƿ���������   SqString
	int operator==(SqString s);

protected:
	//��char���͵�˳�򴮸�ֵ����ǰ˳�򴮵ĸ�ֵ����
	void strAssign_aux(char *s);

public:
	//ɾ����i���ַ���ĳ���Ϊlen���Ӵ�
	bool strDelete(int i, int len);

	//ȡ˳�򴮵��Ӵ�
	bool subString(SqString& sub, int i, int len);

	SqString();
	virtual ~SqString();

	SqString(char* s);
	SqString(SqString &s);


	//�����������
	friend ostream& operator <<(ostream& out, SqString s);

protected:
	int length;//˳�򴮳���
	char *ch;//˳�򴮶�̬�洢�ռ���׵�ַ
};

void SqString::clear(){
	if (ch){
		delete[]ch;
		ch = NULL;
		length = 0;
	}
}

bool SqString::getChar(int i, char &c){
	if (i<1 || i>length){
		return false;
	}
	c = ch[i - 1];
	return true;
}

int SqString::getLength(){
	return length;
}


void SqString::get_next(int *next, int display){
	int j = -1, i = 0;//ǰ���ַ�ָ�룬��ʼ��Ϊ-1��0
	int first_i;//��ǰ���һ��Ԫ�ص��±�
	char no[5] = "[ i]";

	//����next����ÿ��Ԫ�ص�ֵ
	next[0] = -1;//-1Ϊ��ֹ��־
	while (i < length){
		if (j == -1 || ch[j] == ch[i]){
			j++;
			i++;
			next[i] = j;
		}
		else{
			j = next[j];
		}
	}
	if (display == 1){
		cout << "   ��ǰģʽ����next[]����Ϊ:" << endl;
		first_i = 0;
		while (first_i < length){
			i = first_i;
			cout << "       ";
			do{
				//����Ԫ���±���ַ���ʾ
				if (i < 10){
					no[2] = i + '0';//������Ԫ�ص�С��С��10
				}
				else{
					no[1] = i / 10 + '0';//������Ԫ�ص��±���ڵ���10
					no[2] = i % 10 + '0';
				}
				//ÿ��Ԫ�ص������ʾռ5���ַ��������Կո��룬���Ҷ���
				cout.width(5);
				cout.fill(' ');
				cout.setf(ios::right, ios::adjustfield);
				cout << no;
				i++;
			} while (i % 10 && i < length);

			cout << endl;
			cout << "      ";//��ʾģʽ���е��ַ�
			i = first_i;
			do{
				cout.width(5);
				cout.fill(' ');
				cout.setf(ios::right, ios::adjustfield);
				cout << ch[i];
				i++;
			} while (i % 10 && i < length);
			cout << endl;

			//��ʾnext[]������ÿ��Ԫ�ص�ֵ
			cout << "    ";
			i = first_i;
			do{
				cout.width(5);
				cout.fill(' ');
				cout.setf(ios::right, ios::adjustfield);
				cout << ch[i];
				i++;
			} while (i % 10 && i < length);

			first_i = i;//��һ���һ��Ԫ�ص��±�
			cout << endl << endl;
		}
	}
}


//���ز���
int SqString::index(SqString p, int pos){
	int i = pos - 1;//ָ���pos���ַ����±�
	int j = 0;

	while (i < length && j < p.length){
		if (ch[i] == p.ch[j]){
			i++;
			j++;
		}
		else{//�±������
			i = i - j + 1;
			j = 0;
		}

	}
	if (j == p.length){
		return i - p.length + 1;//�ҵ���
	}
	else{
		return 0;//û�ҵ�
	}
}


//KMP����
int SqString::index_KMP(SqString p, int pos){
	int i = pos - 1;
	int j = -1;//ģʽ����ǰ�ַ�����ʼ��Ϊ-1������û��ָ��

	int *next;
	next = new int[p.length];
	assert(next != 0);

	p.get_next(next, 0);//��ģʽ����next����������

	//�������ĵ�pos���ַ���ʼ����ģʽ���Ķ�Ӧ�ַ���һ�Ƚ�
	while (i < length && j < p.length){
		if (j == -1 || ch[i] == p.ch[j]){
			i++;
			j++;
		}
		else{
			j = next[j];//���ã��޻���
		}
	}
	if (j == p.length){
		return i - p.length + 1;//�ҵ���
	}
	else{
		return 0;//û�ҵ�
	}
}


bool SqString::insert(int i, SqString t){
	char *temp;
	if (i<1 || i>length || t.isEmpty()){
		return false;

	}
	temp = new char[length + t.length];
	assert(temp != 0);

	//��ʵ����о���ָ��Ҳ�ǱȽϷ���
	int j;
	for (j = 0; j < i - 1; j++){
		temp[j] = ch[j];
	}
	for (; j < i - 1 + t.length; j++){
		temp[j] = t.ch[j - i + 1];
	}
	for (; j < length + t.length; j++){
		temp[j] = ch[j - t.length];
	}

	delete[]ch;
	ch = temp;
	length = length + t.length;
	return true;
}

bool SqString::isEmpty(){
	return length ? false : true;
}

SqString SqString::operator=(char *s){
	strAssign_aux(s);//��ֵ��������
	return *this;
}

SqString SqString::operator =(SqString right){
	if (this != &right){
		clear();
		ch = new char[right.length];
		assert(ch != 0);

		length = right.length;
		for (int i = 0; i < right.length; i++){
			ch[i] = right.ch[i];
		}
	}
	return *this;
}

SqString SqString::operator +(char* s){
	insert(length + 1, s);//����insert����
	return *this;
}

SqString SqString::operator +(SqString right){
	insert(length + 1, right);
	return *this;
}

bool SqString::operator <(SqString right){
	int i;
	for (i = 0; i < length && i < right.length; i++){
		if (ch[i] < right.ch[i]){
			return true;
		}
	}
	if (i < right.length){
		return true;
	}
	else{
		return false;
	}
}

int SqString::operator ==(char *s){
	int s_length;//��ȡs�ĳ���
	for (int i = 0; s[i]; i++){
		s_length = i;
	}
	for (int i = 0; i < length&&i < s_length; i++){
		if (ch[i] != s[i]){
			return ch[i] - s[i];
		}
	}
	return length - s_length;
}

int SqString::operator ==(SqString right){
	for (int i = 0; i < length&&i < right.length; i++){
		if (ch[i] != right.ch[i]){
			return ch[i] - right.ch[i];
		}
	}
	return length - right.length;
}



//��ֵ��������
void SqString::strAssign_aux(char *s){
	clear();
	length = 0;
	for (int i = 0; s[i]; ++i){
		length++;
	}
	cout << length << endl;

	ch = new char[length];
	assert(ch != 0);
	for (int i = 0; i < length; i++){
		ch[i] = s[i];
	}
}

//ɾ����i���ַ��𳤶�Ϊlen���ַ���
bool SqString::strDelete(int i, int len){
	char *temp;

	if (i<1 || i>length + 1){
		return false;
	}
	temp = new char[length - len];

	assert(temp != 0);
	for (int j = 0; j < i - 1; j++){//ǰ���
		temp[j] = ch[j];
	}
	for (int j = i - 1 + len; j < length; j++){//����
		temp[j - len] = ch[j];
	}
	delete[]ch;
	ch = temp;
	length -= len;
	return true;
}


//ȡ�Ӵ�
bool SqString::subString(SqString &sub, int i, int len){
	if (i<1 || i>length || len < 0 || len>length - i + 1){
		return false;
	}
	sub.clear();

	sub.ch = new char[len];
	assert(sub.ch != 0);
	for (int j = 0; j < len; j++){
		sub.ch[j] = ch[i - 1 + j];
	}
	sub.length = len;
	return true;
}


//���캯��
SqString::SqString(){
	ch = NULL;
	length = 0;
}

SqString::~SqString(){
	clear();
}

//�������캯��char����
SqString::SqString(char *s){
	ch = NULL;
	strAssign_aux(s);
}

//�������캯��
SqString::SqString(SqString &other){
	ch = new char[other.length];
	assert(ch != 0);
	length = other.length;
	for (int i = 0; i < length; i++){
		ch[i] = other.ch[i];
	}
}



ostream& operator<<(ostream& out, SqString s){
	for (int i = 0; i < s.length; i++){
		out << s.ch[i] << "  ";
	}
	cout << endl;
	return out;
}

int main(int argc, char* argv[]){
	SqString s1("Hello World!");
	cout << s1;
	SqString s2("haha,welcome to the program world,Hello World!,enjoy it");
	cout << s2;
	cout << "���ݷ�����:";
	cout << s2.index(s1, 0) << endl;

	cout << "KMP����:";
	cout << s2.index_KMP(s1, 0) << endl;
	return 0;
}
