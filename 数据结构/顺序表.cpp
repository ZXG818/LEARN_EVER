#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

#define LIST_MAX_SIZE 100
#define LISTINCREAMENT 10

template <typename elemtype>
class sqlist{//顺序表
private:
    int n;//顺序表当前元素的个数
    elemtype *elem;//顺序表动态存储空间首地址
    int list_size;
public:
    sqlist();
    sqlist(sqlist &other);//拷贝初始化构造函数
    ~sqlist();//析构函数

    //有序顺序表的二分查找
    int bin_search(elemtype key);

    //顺序表置空
    void clear();

    //删除第i个元素
    bool delete_elem(int i);//返回布尔值，true为删除成功，false为删除失败

    //获取第i个元素
    elemtype get_elem(int i);

    //求顺序表中元素的个数
    int get_length();

    //获取顺序表存储空间的大小
    int get_list_size();

    //在第i个元素之前插入一个元素
    bool insert(int i,elemtype value);//插入成功返回true，返回false则表示失败

    //返回某元素的后继
    bool get_next_elem(elemtype e,elemtype &next_e);

    //返回某元素的前驱
    bool get_prior_elem(elemtype e,elemtype &prior_e);

    //顺序查找某元素
    int search(elemtype e);

    //重载=号运算符
    sqlist operator =(sqlist other);

    //重载输出运算符
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

template <typename elemtype>//定义拷贝构造函数
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
    cout<<"已经释放空间"<<endl;
    delete [] elem;
}

template <typename elemtype>
int sqlist<elemtype>::bin_search(elemtype key){
    //先排序
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
    return 0;//没有找到返回零
}


template <typename elemtype>
//顺序表置空，并不清除其申请的空间
void sqlist<elemtype>::clear(){
    n = 0;
}


template <typename elemtype>
bool sqlist<elemtype>::delete_elem(int i){//查找的(用户眼中)i是从1开始
    if(i<1 || i>n){
        return false;
    }

    for(int j = i+1;j<=n;j++){
        elem[j-2] = elem[j-1];
    }
    n--;//当前元素的个数减少1
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
    //判断当前空间是否已经满了
    if (n>=list_size){
        newbase = new elemtype[list_size + LISTINCREAMENT];
        assert(newbase != 0);

        for(int j = 1;j<=n;j++){
            newbase[j-1] = elem[j-1];//把所有元素搬到新的存储空间
        }
        delete [] elem;//回收原有的存储空间
        elem = newbase;//重新定义指针
        list_size += LISTINCREAMENT;//重新赋值
    }

    //从顺序表最后一个元素开始，知道第i个元素，每个元素向后移动一位
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
    return *this;//返回对象
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
    cout<<"请输入5个元素"<<endl;
    for(int i = 1;i<=5;i++){
        int value = 0;
        cout<<"请输入元素:";
        cin>>value;
        s1.insert(i,value);
    }
    cout<<s1;

    cout<<"下面进行二分查找实验:"<<endl;
    int value = 0;
    cout<<"请输入要查找的元素:";
    cin>>value;
    cout<<"这个值的位置是:";
    cout<<s1.bin_search(value)<<endl;

    return 0;
}



