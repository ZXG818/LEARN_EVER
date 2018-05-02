#include <iostream>
#include <assert.h>
#include <cstdbool>
#include <cstdlib>
#define DEFAULT_SEQTREE 100

using namespace std;

template <typename elemtype>
class SeqTree{
public:
	//顺序存储的树置空
	void clear();

	//取最后一个结点在顺序存储空间的下标
	int getFinalIndex();

	//返回树采用顺序存储的首地址
	elemtype *getInitialAddress();

	//取下标为i的结点（就是第i+1个结点)
	elemtype getNode(int i);

	//重载赋值运算符
	SeqTree operator=(SeqTree<elemtype> right);

	//设置最后一个结点在顺序存储空间的下标
	void setFinalIndex(int i);

	//设置下标为i的结点（就是第i+1个结点）的值
	void setNode(int i, elemtype value);

	//构造函数
	SeqTree();

	//析构函数
	virtual ~SeqTree();

	//拷贝初始化构造函数
	SeqTree(const SeqTree<elemtype> &seqT);

	//重载输出运算符
	template <typename out_put>
	friend ostream& operator<<(ostream& out,SeqTree<out_put> other);


protected:
	elemtype *initialAddress;		//树的顺序存储空间的首地址
	int finalIndex;					//按层次存放，最后一个结点在顺序存储空间的下标
};


//把一棵树顺序存储的空间置空
template <typename elemtype>
void SeqTree<elemtype>::clear(){
	if (initialAddress){
		delete[] initialAddress;
	}
	initialAddress = NULL;
	finalIndex = -1;
}

//取最后一个结点在顺序存储空间的下标
template <typename elemtype>
int SeqTree<elemtype>::getFinalIndex(){
	return finalIndex;
}

//返回树的存储的首地址
template <typename elemtype>
elemtype* SeqTree<elemtype>::getInitialAddress(){
	return initialAddress;
}

//取下标为i的结点
template <typename elemtype>
elemtype SeqTree<elemtype>::getNode(int i){
	if (i<0 || i>finalIndex){		//如果溢出就退出
		cerr << OVERFLOW;
		exit(0);
	}

	return initialAddress[i];
}


//重载赋值运算符
template <typename elemtype>
SeqTree<elemtype> SeqTree<elemtype>::operator=(SeqTree<elemtype> right){
	if (this != &right){
		finalIndex = right.finalIndex;
		if (finalIndex != -1){
			// 给左边的树申请一个一样大的存储空间
			initialAddress = new elemtype[finalIndex + 1];
			assert(initialAddress != 0);
			//把右边树的每个结点的数据域赋值给左边
			for (int i = 0; i <= finalIndex; i++){
				initialAddress[i] = right.initialAddress[i];
			}
		}
	}

	return *this;		// 返回对象
}


//设置最后一个结点在顺序存储空间的下标
template <typename elemtype>
void SeqTree<elemtype>::setFinalIndex(int i){
	finalIndex = i;
}

//设置下标为i的结点的值
template <typename elemtype>
void SeqTree<elemtype>::setNode(int i, elemtype value){
	initialAddress[i] = value;
	if (i > finalIndex){
		finalIndex = i;
	}
}

//构造函数
template <typename elemtype>
SeqTree<elemtype>::SeqTree(){
	initialAddress = new elemtype[DEFAULT_SEQTREE];
	finalIndex = -1;
}

//析构函数
template <typename elemtype>
SeqTree<elemtype>::~SeqTree(){
	clear();
	cout << "清除完毕" << endl;
}

//拷贝初始化构造函数
template <typename elemtype>
SeqTree<elemtype>::SeqTree(const SeqTree<elemtype>& other){
	initialAddress = NULL;
	finalIndex = other.finalIndex;

	if (finalIndex != -1){
		initialAddress = new elemtype[finalIndex + 1];
		assert(initialAddress != 0);

		for (int i = 0; i < finalIndex + 1; i++){
			initialAddress[i] = other.initialAddress[i];
		}
	}
}

//重载输出运算符
template <typename out_put>
ostream& operator<<(ostream& out, SeqTree<out_put> other){
	if (other.finalIndex != -1){
		for (int i = 0; i <= other.finalIndex; i++){
			out << other.initialAddress[i] << "\t";
		}
		return out;
	}
	else{
		cout << "树为空" << endl;
	}
}





int main(void){
	SeqTree<int> seq1;
	for (int i = 0; i < 10; i++){
		seq1.setNode(i, i * 10);
	}
	cout << seq1 << endl;


	cout << seq1.getNode(0) << endl;
	cout << seq1.getNode(3) << endl;

	SeqTree<int> seq2;
	seq2 = seq1;
	cout << seq2 << endl;//测试赋值运算符的重载
	return 0;
}



