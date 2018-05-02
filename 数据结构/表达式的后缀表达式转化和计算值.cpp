#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cstdbool>
#define STACK_MAX_SIZE 100
#define STACKINCREAMENT 10
using namespace std;
///////////////////////////////////////////////////////////
//栈的结构定义和一些方法的应用
template <typename elemtype>
class SqStack{
public:
	//顺序栈置空
	void clear();

	//求顺序栈中元素的个数
	int getLength();

	//返回档期那已经分派的存储空间的大小
	int getStackSize();

	//读取栈顶元素
	bool getTop(elemtype &e);

	//判断顺序栈是否为空
	bool isEmpty();

	//重载赋值运算符
	SqStack operator=(SqStack right);

	//弹出栈顶元素
	bool pop(elemtype &e);

	//在栈顶压入元素e
	void push(elemtype e);

	//构造函数
	SqStack();

	//析构函数
	virtual ~SqStack();

	//拷贝构造函数
	SqStack(SqStack &other);

	//重载输出运算符
	template <typename out_put>
	friend ostream& operator <<(ostream& out, SqStack<out_put> other);

protected:
	elemtype *base;//栈底指针，就是顺序栈动态存储空间的首地址
	elemtype *top;//栈顶指针
	int stackSize;//顺序栈当前已经分配的存储空间的大小
};


template <typename elemtype>
void SqStack<elemtype>::clear(){
	top = base;
	cout << "顺序栈已经清空" << endl;
}

template <typename elemtype>
int SqStack<elemtype>::getLength(){
	return top - base;
}

template <typename elemtype>
int SqStack<elemtype>::getStackSize(){
	return stackSize;
}

//读取栈顶的元素
template <typename elemtype>
bool SqStack<elemtype>::getTop(elemtype &e){
	if (isEmpty()){
		return false;
	}
	else{
		e = *(top - 1);
	}
	return true;
}

template <typename elemtype>
bool SqStack<elemtype>::isEmpty(){
	return top == base ? true : false;
}

//重载赋值运算符
template <typename elemtype>
SqStack<elemtype> SqStack<elemtype>::operator =(SqStack<elemtype> right){
	int length = right.getLength();

	if (this != &right){
		if (stackSize < right.stackSize){
			delete[] base;  //回收左边的顺序栈的存取空间
			base = new elemtype[right.stackSize];
			assert(base != 0);
			stackSize = right.stackSize;//进行属性的一些重新的赋值
		}

		for (int i = 0; i < length; i++){
			*(base + i) = *(right.base + i);
		}
		top = base + length();
	}
	return *this;//返回对象
}

//弹出栈顶元素到e
template <typename elemtype>
bool SqStack<elemtype>::pop(elemtype &e){
	if (isEmpty()){
		return false;
	}
	else{
		e = *--top;
	}
	return true;
}

//在栈顶压入元素e
template <typename elemtype>
void SqStack<elemtype>::push(elemtype e){
	int length = top - base;//顺序栈中元素的个数
	elemtype *newBase;//预指向新顺序栈的栈底指针
	//判断当前顺序栈是否已满，如果满了，则需要另外申请存储空间
	if (top - base >= stackSize){
		newBase = new elemtype[stackSize + STACKINCREAMENT];
		assert(newBase != 0);

		for (int j = 0; j < length; j++){
			*(newBase + j) = *(base + j);
		}

		delete[] base;//回收当前已经满了的栈空间
		base = newBase;
		top = base + length;
	}

	//如果当前顺序栈没有满，就不用重新申请空间了，就直接以下两个语句就行了
	*top = e;
	top++;
}


template <typename elemtype>
SqStack<elemtype>::SqStack(){
	base = new elemtype[STACK_MAX_SIZE];//申请空间
	assert(base != 0);
	stackSize = STACK_MAX_SIZE;//属性的赋值
	top = base;//栈的初始为空
}

//你懂的
template <typename elemtype>
SqStack<elemtype>::~SqStack(){
	if (base){
		delete[]base;
	}
	stackSize = 0;
	top = base = NULL;
}

template <typename elemtype>
SqStack<elemtype>::SqStack(SqStack &other){
	int length = other.top - other.base;
	base = new elemtype[other.stackSize];

	assert(base != 0);

	stackSize = other.stackSize;
	for (int i = 0; i < length; i++){
		*(base + i) = *(other.base + i);
	}
	top = base + length;
}

template <typename out_put>
ostream& operator<<(ostream& out, SqStack<out_put> other){
	int length = other.top - other.base;
	for (int i = 0; i < length; i++){
		out << *(other.base + i) << "\t";
	}

	return out;
}



/////////////////////////////////////////////////////////////////
//下面开始写中缀表达式向后缀表达式的函数

//判断是运算符，数字字符或者是其他的字符
int isOpMember(char ch){
	if (ch == '0' || ch == '1' ||
		ch == '2' || ch == '3' ||
		ch == '4' || ch == '5' ||
		ch == '6' || ch == '7' ||
		ch == '8' || ch == '9'){
		return 0;
	}
	else if (ch == '+' || ch == '-' ||
		ch == '*' || ch == '/' ||
		ch == '(' || ch == ')' ||
		ch == '\0'){
		return 1;
	}
	else{
		return -1;
	}
}


//各种运算符在运算符优先级矩阵的对应的下标
int order(char m){
	switch (m){
	case '+':return 0;
	case '-':return 1;
	case '*':return 2;
	case '/':return 3;
	case '(':return 4;
	case ')':return 5;
	case '\0':return 6;
	default:return 7;
	}
}


//判定两个运算符的优先级的高低
int precede(char op1, char op2){
	//运算符优先级矩阵
	int inCmpOut[7][7] = { { 1, 1, -1, -1, -1, 1, 1 },
	{ 1, 1, -1, -1, -1, 1, 1 },
	{ 1, 1, 1, 1, -1, 1, 1 },
	{ 1, 1, 1, 1, -1, 1, 1 },
	{ -1, -1, -1, -1, -1, 0, 0 },
	{ 1, 1, 1, 1, 2, 1, 1 },
	{ -1, -1, -1, -1, -1, 2, 0 } };
	int i, j;
	i = order(op1);//op1在矩阵中的下标，作为行号
	j = order(op2);//op2在矩阵中的下标，作为列号
	return inCmpOut[i][j];
}

//中缀表达式转化为后缀表达式
//输入：函数的参数midS为待转换的中缀表达式
//输出：函数的参数suffixS为midS对应的后缀表达式
void transform(char *midS, char *suffixS){
	int i = 0;//后缀表达式当前处理字符的下标，初始化为0
	int j = 0;//中缀表达式当前处理字符的下标，初始化为0
	char ch = midS[0];//中缀表达式当前处理字符，初始化为第一个字符
	//中缀表达式转化为后缀的过程中，遇到运算符是不能直接进入到后缀表达式中的
	//他们要让后面较高级别的运算符先进入，所以用运算符栈S先暂存这些
	//还不能进入到后缀表达式的运算符
	SqStack<char> S;
	char op;//预存放运算符栈S弹出的栈顶元素

	//把运算符'\0'压栈，它是最低级别的运算符，如果最后弹出此运算符，则表明已经完成转化
	S.push('\0');

	//从中缀表达式的第一个字符开始，知道结束，逐一扫描，分别转化
	while (!S.isEmpty()){
		if (!isOpMember(ch)){//如果是操作数
			if (i > 0 && isOpMember(suffixS[i - 1]) == 1){
				suffixS[i++] = ' ';//如果是新操作数，就添加空格
			}
			suffixS[i++] = ch;//直接进入后缀表达式
		}
		else{//如果是运算符
			if (i > 0 && suffixS[i - 1] != ' '){
				suffixS[i++] = ' ';
			}
			switch (ch){
			case '('://左括号直接入栈
				S.push(ch);
				break;
			case ')':
				S.pop(op);
				while (op != '('){
					suffixS[i++] = op;
					suffixS[i++] = ' ';
					S.pop(op);
				}
				--i;//回到原来i的位置
				break;
			default://其他情况的运算符例如+-*/等
				while (S.getTop(op)){
					if (precede(op, ch) == 1 || precede(op, ch) == 0){
						suffixS[i++] = op;
						suffixS[i++] = ' ';
					}
					else{
						break;
					}
					S.pop(op);//写入后缀表达式后要弹栈
				}
				//如果中缀表达式当前字符不是'\0',则压入运算符栈
				if (ch != '\0'){
					S.push(ch);
				}
			}
		}
		if (ch != '\0'){
			ch = midS[++j];
		}
	}
	suffixS[i] = '\0';//放入最后一个单元，完成转化
}

//指定运算符的运算
double caculate(double a, char ch, double b){
	switch (ch){
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a*b;
	case '/':return a / b;
	default:return -1;
	}
}


//后缀表达式的计算
double evaluation(char *suffixS){
	int i = 0;//后缀表达式的当前字符的下标，初始化为0
	char ch = suffixS[i];//后缀表达式当前字符，初始化为第一个字符
	double x;//预存放当前操作数

	SqStack<double> S;//后缀表达式中计算的时候要用到顺序栈来进行运算
	double a, b;

	//从后缀表达式的第一个字符开始，直到结束，分别处理
	while (ch != '\0'){
		if (isOpMember(ch) == 0){
			x = 0;
			while (isOpMember(ch) == 0){//如果当前是操作数
				x = 10 * x + (ch - '0');
				ch = suffixS[++i];
			}
			S.push(x);
		}
		else if (isOpMember(ch) == 1){//如果当前是运算符
			S.pop(b);
			S.pop(a);
			S.push(caculate(a, ch, b));
		}
		ch = suffixS[++i];
	}
	S.pop(x);//从栈中弹出结果
	return x;//返回结果
}


int main(void){
	char midS[128];
	char suffixS[128];
	cout << "请输入一个表达式:" << endl;
	cin >> midS;
	transform(midS, suffixS);//调用中缀表达式转化为后缀表达式的函数
	cout << "后缀表达式为:" << endl;
	cout << suffixS << endl;
	cout << "计算结果为:" << endl;
	cout << evaluation(suffixS) << endl;
	return 0;
}



