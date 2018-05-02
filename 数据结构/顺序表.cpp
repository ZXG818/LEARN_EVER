#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

#define LIST_MAX_SIZE 100
#define LISTINCREAMENT 10

template <typename elemtype>
class sqlist{//˳���
private:
    int n;//˳���ǰԪ�صĸ���
    elemtype *elem;//˳���̬�洢�ռ��׵�ַ
    int list_size;
public:
    sqlist();
    sqlist(sqlist &other);//������ʼ�����캯��
    ~sqlist();//��������

    //����˳���Ķ��ֲ���
    int bin_search(elemtype key);

    //˳����ÿ�
    void clear();

    //ɾ����i��Ԫ��
    bool delete_elem(int i);//���ز���ֵ��trueΪɾ���ɹ���falseΪɾ��ʧ��

    //��ȡ��i��Ԫ��
    elemtype get_elem(int i);

    //��˳�����Ԫ�صĸ���
    int get_length();

    //��ȡ˳���洢�ռ�Ĵ�С
    int get_list_size();

    //�ڵ�i��Ԫ��֮ǰ����һ��Ԫ��
    bool insert(int i,elemtype value);//����ɹ�����true������false���ʾʧ��

    //����ĳԪ�صĺ��
    bool get_next_elem(elemtype e,elemtype &next_e);

    //����ĳԪ�ص�ǰ��
    bool get_prior_elem(elemtype e,elemtype &prior_e);

    //˳�����ĳԪ��
    int search(elemtype e);

    //����=�������
    sqlist operator =(sqlist other);

    //������������
    template <typename output>
    friend ostream& operator<<(ostream& out,sqlist<output> other);

};

template <typename elemtype>
sqlist<elemtype>::sqlist(){
    n = 0;
    elem = new elemtype[LIST_MAX_SIZE];
    assert(elem!=0);
    list_size = LIST_MAX_SIZE;
}

template <typename elemtype>//���忽�����캯��
sqlist<elemtype>::sqlist(sqlist<elemtype> &other){
    this->n = other.n;
    this->list_size = other.list_size;
    this->elem = new elemtype[other.list_size];
    assert(elem!=0);
    for (int i = 0;i<n;i++){
        elem[i] = other.elem[i];
    }
}

template <typename elemtype>
sqlist<elemtype>::~sqlist(){
    cout<<"�Ѿ��ͷſռ�"<<endl;
    delete [] elem;
}

template <typename elemtype>
int sqlist<elemtype>::bin_search(elemtype key){
    //������
    for(int i = 0;i<n-1;i++){
        for(int j = i;j<n;j++){
            if (elem[i]>elem[j]){
                elemtype temp = elem[i];
                elem[i] = elem[j];
                elem[j] = temp;
            }
        }
    }

    int high,low;
    int mid;
    low = 0;
    high = this->n-1;
    while(low<=high){
        mid = (low+high) / 2;
        if(elem[mid] == key){
            return mid+1;
        }
        else if(elem[mid] < key){
            low = mid+1;
        }
        else{
            high = mid-1;
        }
    }
    return 0;//û���ҵ�������
}


template <typename elemtype>
//˳����ÿգ��������������Ŀռ�
void sqlist<elemtype>::clear(){
    n = 0;
}


template <typename elemtype>
bool sqlist<elemtype>::delete_elem(int i){//���ҵ�(�û�����)i�Ǵ�1��ʼ
    if(i<1 || i>n){
        return false;
    }

    for(int j = i+1;j<=n;j++){
        elem[j-2] = elem[j-1];
    }
    n--;//��ǰԪ�صĸ�������1
    return true;
}

template <typename elemtype>
elemtype sqlist<elemtype>::get_elem(int i){
    return elem[i-1];
}

template <typename elemtype>
int sqlist<elemtype>::get_length(){
    return n;
}

template <typename elemtype>
int sqlist<elemtype>::get_list_size(){
    return list_size;
}

template <typename elemtype>
bool sqlist<elemtype>::insert(int i,elemtype value){
    if (i<1 || i>n+1)
        return false;
    elemtype *newbase;
    //�жϵ�ǰ�ռ��Ƿ��Ѿ�����
    if (n>=list_size){
        newbase = new elemtype[list_size + LISTINCREAMENT];
        assert(newbase != 0);

        for(int j = 1;j<=n;j++){
            newbase[j-1] = elem[j-1];//������Ԫ�ذᵽ�µĴ洢�ռ�
        }
        delete [] elem;//����ԭ�еĴ洢�ռ�
        elem = newbase;//���¶���ָ��
        list_size += LISTINCREAMENT;//���¸�ֵ
    }

    //��˳������һ��Ԫ�ؿ�ʼ��֪����i��Ԫ�أ�ÿ��Ԫ������ƶ�һλ
    for(int j = n;j>=i;j--){
        elem[j] = elem[j-1];
    }
    elem[i-1] = value;
    n++;
    return true;
}

template <typename elemtype>
bool sqlist<elemtype>::get_next_elem(elemtype e,elemtype &next_e){
    if(elem[n-1] == e)
        return false;
    for (int i = 0;i<n;i++){
        if(elem[i] == e){
            next_e = elem[i+1];
            return true;
        }
    }
}

template <typename elemtype>
bool sqlist<elemtype>::get_prior_elem(elemtype e,elemtype &prior_e){
    if(elem[0] == e){
        return false;
    }
    for(int i = 0;i<n;i++){
        if (elem[i] == e){
            prior_e = elem[i-1];
            return true;
        }
    }
}


template <typename elemtype>
int sqlist<elemtype>::search(elemtype e){
    for(int i = 0;i<n;i++){
        if(elem[i] == e){
            return i+1;
        }
    }
}

template <typename elemtype>
sqlist<elemtype> sqlist<elemtype>::operator =(sqlist<elemtype> other){
    if(this!=&other){
        if(list_size < other.list_size){
            delete [] elem;
            elem = new elemtype[other.list_size];
            assert(elem!=0);
            list_size = other.list_size;
        }
        n = other.n;
        for(int i = 0;i<n;i++){
            elem[i] = other.elem[i];
        }
    }
    return *this;//���ض���
}

template <typename output>
ostream& operator<<(ostream& out,sqlist<output> other){
    for(int i = 1;i<=other.n;i++){
        out<<"["<<i<<"]"<<"\t";
    }

    cout<<endl;

    for(int i = 0;i<other.n;i++){
        out<<other.elem[i]<<"\t";
    }
    cout<<endl;
    return out;
}


int main(void)
{
    sqlist<int> s1;
    cout<<s1;
    cout<<"������5��Ԫ��"<<endl;
    for(int i = 1;i<=5;i++){
        int value = 0;
        cout<<"������Ԫ��:";
        cin>>value;
        s1.insert(i,value);
    }
    cout<<s1;

    cout<<"������ж��ֲ���ʵ��:"<<endl;
    int value = 0;
    cout<<"������Ҫ���ҵ�Ԫ��:";
    cin>>value;
    cout<<"���ֵ��λ����:";
    cout<<s1.bin_search(value)<<endl;

    return 0;
}



