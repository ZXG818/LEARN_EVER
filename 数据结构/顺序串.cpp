#include <iostream>
#include <assert.h>
using namespace std;
//有关KMP算法的一篇文章:https://blog.csdn.net/lee18254290736/article/details/77278769
class SqString{
public:
	//把顺序串置空
	void clear();

	//获取第i个字符
	bool getChar(int i, char &c);

	//求顺序串的长度
	int getLength();

	//求模式串的next数组
	void get_next(int *next, int display = 1);

	//串的朴素匹配(有回溯查找)
	int index(SqString p, int pos);

	//模式匹配(无回溯KMP查找)
	int index_KMP(SqString p, int pos);

	//在第i个字符前插入另一个字符串
	bool insert(int i, SqString t);

	//判断顺序串是否为空
	bool isEmpty();

	//重载赋值运算符   char类型字符串
	SqString operator=(char *s);

	//重载赋值运算符  SqString类型顺序串
	SqString operator=(SqString s);

	//重载加法运算符    被加是char类型
	SqString operator+(char* s);

	//重载加法运算符   SqString类型顺序串
	SqString operator+(SqString s);

	//重载是否小于运算符  SqString类型
	bool operator <(SqString s);

	//重载是否相等运算符  char
	int operator ==(char *s);

	//重载是否相等运算符   SqString
	int operator==(SqString s);

protected:
	//把char类型的顺序串赋值给当前顺序串的赋值函数
	void strAssign_aux(char *s);

public:
	//删除第i个字符起的长度为len的子串
	bool strDelete(int i, int len);

	//取顺序串的子串
	bool subString(SqString& sub, int i, int len);

	SqString();
	virtual ~SqString();

	SqString(char* s);
	SqString(SqString &s);


	//重载输出函数
	friend ostream& operator <<(ostream& out, SqString s);

protected:
	int length;//顺序串长度
	char *ch;//顺序串动态存储空间的首地址
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
	int j = -1, i = 0;//前后字符指针，初始化为-1和0
	int first_i;//当前组第一个元素的下标
	char no[5] = "[ i]";

	//生成next数组每个元素的值
	next[0] = -1;//-1为终止标志
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
		cout << "   当前模式串的next[]数组为:" << endl;
		first_i = 0;
		while (first_i < length){
			i = first_i;
			cout << "       ";
			do{
				//修正元素下标的字符表示
				if (i < 10){
					no[2] = i + '0';//数组中元素的小标小于10
				}
				else{
					no[1] = i / 10 + '0';//数组中元素的下标大于等于10
					no[2] = i % 10 + '0';
				}
				//每个元素的序号显示占5个字符，不足以空格补齐，靠右对齐
				cout.width(5);
				cout.fill(' ');
				cout.setf(ios::right, ios::adjustfield);
				cout << no;
				i++;
			} while (i % 10 && i < length);

			cout << endl;
			cout << "      ";//显示模式串中的字符
			i = first_i;
			do{
				cout.width(5);
				cout.fill(' ');
				cout.setf(ios::right, ios::adjustfield);
				cout << ch[i];
				i++;
			} while (i % 10 && i < length);
			cout << endl;

			//显示next[]数组中每个元素的值
			cout << "    ";
			i = first_i;
			do{
				cout.width(5);
				cout.fill(' ');
				cout.setf(ios::right, ios::adjustfield);
				cout << ch[i];
				i++;
			} while (i % 10 && i < length);

			first_i = i;//下一组第一个元素的下标
			cout << endl << endl;
		}
	}
}


//朴素查找
int SqString::index(SqString p, int pos){
	int i = pos - 1;//指向第pos个字符的下标
	int j = 0;

	while (i < length && j < p.length){
		if (ch[i] == p.ch[j]){
			i++;
			j++;
		}
		else{//下标的重置
			i = i - j + 1;
			j = 0;
		}

	}
	if (j == p.length){
		return i - p.length + 1;//找到了
	}
	else{
		return 0;//没找到
	}
}


//KMP查找
int SqString::index_KMP(SqString p, int pos){
	int i = pos - 1;
	int j = -1;//模式串当前字符，初始化为-1，就是没有指向

	int *next;
	next = new int[p.length];
	assert(next != 0);

	p.get_next(next, 0);//求模式串的next函数的数组

	//从主串的第pos个字符开始，与模式串的对应字符逐一比较
	while (i < length && j < p.length){
		if (j == -1 || ch[i] == p.ch[j]){
			i++;
			j++;
		}
		else{
			j = next[j];//重置，无回溯
		}
	}
	if (j == p.length){
		return i - p.length + 1;//找到了
	}
	else{
		return 0;//没找到
	}
}


bool SqString::insert(int i, SqString t){
	char *temp;
	if (i<1 || i>length || t.isEmpty()){
		return false;

	}
	temp = new char[length + t.length];
	assert(temp != 0);

	//其实这里感觉用指针也是比较方便
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
	strAssign_aux(s);//赋值辅助函数
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
	insert(length + 1, s);//调用insert函数
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
	int s_length;//获取s的长度
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



//赋值辅助函数
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

//删除第i个字符起长度为len的字符串
bool SqString::strDelete(int i, int len){
	char *temp;

	if (i<1 || i>length + 1){
		return false;
	}
	temp = new char[length - len];

	assert(temp != 0);
	for (int j = 0; j < i - 1; j++){//前半段
		temp[j] = ch[j];
	}
	for (int j = i - 1 + len; j < length; j++){//后半段
		temp[j - len] = ch[j];
	}
	delete[]ch;
	ch = temp;
	length -= len;
	return true;
}


//取子串
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


//构造函数
SqString::SqString(){
	ch = NULL;
	length = 0;
}

SqString::~SqString(){
	clear();
}

//拷贝构造函数char类型
SqString::SqString(char *s){
	ch = NULL;
	strAssign_aux(s);
}

//拷贝构造函数
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
	cout << "回溯法查找:";
	cout << s2.index(s1, 0) << endl;

	cout << "KMP查找:";
	cout << s2.index_KMP(s1, 0) << endl;
	return 0;
}
