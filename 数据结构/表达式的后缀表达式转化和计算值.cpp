#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cstdbool>
#define STACK_MAX_SIZE 100
#define STACKINCREAMENT 10
using namespace std;
///////////////////////////////////////////////////////////
//ջ�Ľṹ�����һЩ������Ӧ��
template <typename elemtype>
class SqStack{
public:
	//˳��ջ�ÿ�
	void clear();

	//��˳��ջ��Ԫ�صĸ���
	int getLength();

	//���ص������Ѿ����ɵĴ洢�ռ�Ĵ�С
	int getStackSize();

	//��ȡջ��Ԫ��
	bool getTop(elemtype &e);

	//�ж�˳��ջ�Ƿ�Ϊ��
	bool isEmpty();

	//���ظ�ֵ�����
	SqStack operator=(SqStack right);

	//����ջ��Ԫ��
	bool pop(elemtype &e);

	//��ջ��ѹ��Ԫ��e
	void push(elemtype e);

	//���캯��
	SqStack();

	//��������
	virtual ~SqStack();

	//�������캯��
	SqStack(SqStack &other);

	//������������
	template <typename out_put>
	friend ostream& operator <<(ostream& out, SqStack<out_put> other);

protected:
	elemtype *base;//ջ��ָ�룬����˳��ջ��̬�洢�ռ���׵�ַ
	elemtype *top;//ջ��ָ��
	int stackSize;//˳��ջ��ǰ�Ѿ�����Ĵ洢�ռ�Ĵ�С
};


template <typename elemtype>
void SqStack<elemtype>::clear(){
	top = base;
	cout << "˳��ջ�Ѿ����" << endl;
}

template <typename elemtype>
int SqStack<elemtype>::getLength(){
	return top - base;
}

template <typename elemtype>
int SqStack<elemtype>::getStackSize(){
	return stackSize;
}

//��ȡջ����Ԫ��
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

//���ظ�ֵ�����
template <typename elemtype>
SqStack<elemtype> SqStack<elemtype>::operator =(SqStack<elemtype> right){
	int length = right.getLength();

	if (this != &right){
		if (stackSize < right.stackSize){
			delete[] base;  //������ߵ�˳��ջ�Ĵ�ȡ�ռ�
			base = new elemtype[right.stackSize];
			assert(base != 0);
			stackSize = right.stackSize;//�������Ե�һЩ���µĸ�ֵ
		}

		for (int i = 0; i < length; i++){
			*(base + i) = *(right.base + i);
		}
		top = base + length();
	}
	return *this;//���ض���
}

//����ջ��Ԫ�ص�e
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

//��ջ��ѹ��Ԫ��e
template <typename elemtype>
void SqStack<elemtype>::push(elemtype e){
	int length = top - base;//˳��ջ��Ԫ�صĸ���
	elemtype *newBase;//Ԥָ����˳��ջ��ջ��ָ��
	//�жϵ�ǰ˳��ջ�Ƿ�������������ˣ�����Ҫ��������洢�ռ�
	if (top - base >= stackSize){
		newBase = new elemtype[stackSize + STACKINCREAMENT];
		assert(newBase != 0);

		for (int j = 0; j < length; j++){
			*(newBase + j) = *(base + j);
		}

		delete[] base;//���յ�ǰ�Ѿ����˵�ջ�ռ�
		base = newBase;
		top = base + length;
	}

	//�����ǰ˳��ջû�������Ͳ�����������ռ��ˣ���ֱ������������������
	*top = e;
	top++;
}


template <typename elemtype>
SqStack<elemtype>::SqStack(){
	base = new elemtype[STACK_MAX_SIZE];//����ռ�
	assert(base != 0);
	stackSize = STACK_MAX_SIZE;//���Եĸ�ֵ
	top = base;//ջ�ĳ�ʼΪ��
}

//�㶮��
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
//���濪ʼд��׺���ʽ���׺���ʽ�ĺ���

//�ж���������������ַ��������������ַ�
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


//�������������������ȼ�����Ķ�Ӧ���±�
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


//�ж���������������ȼ��ĸߵ�
int precede(char op1, char op2){
	//��������ȼ�����
	int inCmpOut[7][7] = { { 1, 1, -1, -1, -1, 1, 1 },
	{ 1, 1, -1, -1, -1, 1, 1 },
	{ 1, 1, 1, 1, -1, 1, 1 },
	{ 1, 1, 1, 1, -1, 1, 1 },
	{ -1, -1, -1, -1, -1, 0, 0 },
	{ 1, 1, 1, 1, 2, 1, 1 },
	{ -1, -1, -1, -1, -1, 2, 0 } };
	int i, j;
	i = order(op1);//op1�ھ����е��±꣬��Ϊ�к�
	j = order(op2);//op2�ھ����е��±꣬��Ϊ�к�
	return inCmpOut[i][j];
}

//��׺���ʽת��Ϊ��׺���ʽ
//���룺�����Ĳ���midSΪ��ת������׺���ʽ
//����������Ĳ���suffixSΪmidS��Ӧ�ĺ�׺���ʽ
void transform(char *midS, char *suffixS){
	int i = 0;//��׺���ʽ��ǰ�����ַ����±꣬��ʼ��Ϊ0
	int j = 0;//��׺���ʽ��ǰ�����ַ����±꣬��ʼ��Ϊ0
	char ch = midS[0];//��׺���ʽ��ǰ�����ַ�����ʼ��Ϊ��һ���ַ�
	//��׺���ʽת��Ϊ��׺�Ĺ����У�����������ǲ���ֱ�ӽ��뵽��׺���ʽ�е�
	//����Ҫ�ú���ϸ߼����������Ƚ��룬�����������ջS���ݴ���Щ
	//�����ܽ��뵽��׺���ʽ�������
	SqStack<char> S;
	char op;//Ԥ��������ջS������ջ��Ԫ��

	//�������'\0'ѹջ��������ͼ����������������󵯳����������������Ѿ����ת��
	S.push('\0');

	//����׺���ʽ�ĵ�һ���ַ���ʼ��֪����������һɨ�裬�ֱ�ת��
	while (!S.isEmpty()){
		if (!isOpMember(ch)){//����ǲ�����
			if (i > 0 && isOpMember(suffixS[i - 1]) == 1){
				suffixS[i++] = ' ';//������²�����������ӿո�
			}
			suffixS[i++] = ch;//ֱ�ӽ����׺���ʽ
		}
		else{//����������
			if (i > 0 && suffixS[i - 1] != ' '){
				suffixS[i++] = ' ';
			}
			switch (ch){
			case '('://������ֱ����ջ
				S.push(ch);
				break;
			case ')':
				S.pop(op);
				while (op != '('){
					suffixS[i++] = op;
					suffixS[i++] = ' ';
					S.pop(op);
				}
				--i;//�ص�ԭ��i��λ��
				break;
			default://������������������+-*/��
				while (S.getTop(op)){
					if (precede(op, ch) == 1 || precede(op, ch) == 0){
						suffixS[i++] = op;
						suffixS[i++] = ' ';
					}
					else{
						break;
					}
					S.pop(op);//д���׺���ʽ��Ҫ��ջ
				}
				//�����׺���ʽ��ǰ�ַ�����'\0',��ѹ�������ջ
				if (ch != '\0'){
					S.push(ch);
				}
			}
		}
		if (ch != '\0'){
			ch = midS[++j];
		}
	}
	suffixS[i] = '\0';//�������һ����Ԫ�����ת��
}

//ָ�������������
double caculate(double a, char ch, double b){
	switch (ch){
	case '+':return a + b;
	case '-':return a - b;
	case '*':return a*b;
	case '/':return a / b;
	default:return -1;
	}
}


//��׺���ʽ�ļ���
double evaluation(char *suffixS){
	int i = 0;//��׺���ʽ�ĵ�ǰ�ַ����±꣬��ʼ��Ϊ0
	char ch = suffixS[i];//��׺���ʽ��ǰ�ַ�����ʼ��Ϊ��һ���ַ�
	double x;//Ԥ��ŵ�ǰ������

	SqStack<double> S;//��׺���ʽ�м����ʱ��Ҫ�õ�˳��ջ����������
	double a, b;

	//�Ӻ�׺���ʽ�ĵ�һ���ַ���ʼ��ֱ���������ֱ���
	while (ch != '\0'){
		if (isOpMember(ch) == 0){
			x = 0;
			while (isOpMember(ch) == 0){//�����ǰ�ǲ�����
				x = 10 * x + (ch - '0');
				ch = suffixS[++i];
			}
			S.push(x);
		}
		else if (isOpMember(ch) == 1){//�����ǰ�������
			S.pop(b);
			S.pop(a);
			S.push(caculate(a, ch, b));
		}
		ch = suffixS[++i];
	}
	S.pop(x);//��ջ�е������
	return x;//���ؽ��
}


int main(void){
	char midS[128];
	char suffixS[128];
	cout << "������һ�����ʽ:" << endl;
	cin >> midS;
	transform(midS, suffixS);//������׺���ʽת��Ϊ��׺���ʽ�ĺ���
	cout << "��׺���ʽΪ:" << endl;
	cout << suffixS << endl;
	cout << "������Ϊ:" << endl;
	cout << evaluation(suffixS) << endl;
	return 0;
}



