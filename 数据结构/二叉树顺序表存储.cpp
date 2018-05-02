#include <iostream>
#include <assert.h>
#include <cstdbool>
#include <cstdlib>
#define DEFAULT_SEQTREE 100

using namespace std;

template <typename elemtype>
class SeqTree{
public:
	//˳��洢�����ÿ�
	void clear();

	//ȡ���һ�������˳��洢�ռ���±�
	int getFinalIndex();

	//����������˳��洢���׵�ַ
	elemtype *getInitialAddress();

	//ȡ�±�Ϊi�Ľ�㣨���ǵ�i+1�����)
	elemtype getNode(int i);

	//���ظ�ֵ�����
	SeqTree operator=(SeqTree<elemtype> right);

	//�������һ�������˳��洢�ռ���±�
	void setFinalIndex(int i);

	//�����±�Ϊi�Ľ�㣨���ǵ�i+1����㣩��ֵ
	void setNode(int i, elemtype value);

	//���캯��
	SeqTree();

	//��������
	virtual ~SeqTree();

	//������ʼ�����캯��
	SeqTree(const SeqTree<elemtype> &seqT);

	//������������
	template <typename out_put>
	friend ostream& operator<<(ostream& out,SeqTree<out_put> other);


protected:
	elemtype *initialAddress;		//����˳��洢�ռ���׵�ַ
	int finalIndex;					//����δ�ţ����һ�������˳��洢�ռ���±�
};


//��һ����˳��洢�Ŀռ��ÿ�
template <typename elemtype>
void SeqTree<elemtype>::clear(){
	if (initialAddress){
		delete[] initialAddress;
	}
	initialAddress = NULL;
	finalIndex = -1;
}

//ȡ���һ�������˳��洢�ռ���±�
template <typename elemtype>
int SeqTree<elemtype>::getFinalIndex(){
	return finalIndex;
}

//�������Ĵ洢���׵�ַ
template <typename elemtype>
elemtype* SeqTree<elemtype>::getInitialAddress(){
	return initialAddress;
}

//ȡ�±�Ϊi�Ľ��
template <typename elemtype>
elemtype SeqTree<elemtype>::getNode(int i){
	if (i<0 || i>finalIndex){		//���������˳�
		cerr << OVERFLOW;
		exit(0);
	}

	return initialAddress[i];
}


//���ظ�ֵ�����
template <typename elemtype>
SeqTree<elemtype> SeqTree<elemtype>::operator=(SeqTree<elemtype> right){
	if (this != &right){
		finalIndex = right.finalIndex;
		if (finalIndex != -1){
			// ����ߵ�������һ��һ����Ĵ洢�ռ�
			initialAddress = new elemtype[finalIndex + 1];
			assert(initialAddress != 0);
			//���ұ�����ÿ������������ֵ�����
			for (int i = 0; i <= finalIndex; i++){
				initialAddress[i] = right.initialAddress[i];
			}
		}
	}

	return *this;		// ���ض���
}


//�������һ�������˳��洢�ռ���±�
template <typename elemtype>
void SeqTree<elemtype>::setFinalIndex(int i){
	finalIndex = i;
}

//�����±�Ϊi�Ľ���ֵ
template <typename elemtype>
void SeqTree<elemtype>::setNode(int i, elemtype value){
	initialAddress[i] = value;
	if (i > finalIndex){
		finalIndex = i;
	}
}

//���캯��
template <typename elemtype>
SeqTree<elemtype>::SeqTree(){
	initialAddress = new elemtype[DEFAULT_SEQTREE];
	finalIndex = -1;
}

//��������
template <typename elemtype>
SeqTree<elemtype>::~SeqTree(){
	clear();
	cout << "������" << endl;
}

//������ʼ�����캯��
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

//������������
template <typename out_put>
ostream& operator<<(ostream& out, SeqTree<out_put> other){
	if (other.finalIndex != -1){
		for (int i = 0; i <= other.finalIndex; i++){
			out << other.initialAddress[i] << "\t";
		}
		return out;
	}
	else{
		cout << "��Ϊ��" << endl;
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
	cout << seq2 << endl;//���Ը�ֵ�����������
	return 0;
}



