#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

template <typename elemtype>
class linklist{
public:
    class linknode{
    public:
        elemtype data;//节点的数据域
        linknode *next;//指向下一个指针类型的指针域
    };
    typedef linknode* nodepointer;
    //非循环单链表逆置
    void adverse();

    //非循环单链表的清空
    void clear();

    //删除非循环单链表中数据域为e的第一个节点
    bool delete_elem(elemtype e);

    //删除非循环单链表中的重复值
    void delete_repeat();

    //取非循环单链表中第i个节点的值
    elemtype get_elem(int i);

    //取第一个节点的指针
    //nodepointer get_head();

    //求非循环单链表的节点的个数
    int get_length();

    //在第i个结点之前插入一个数据域为e的结点
    bool insert(int i,elemtype e);

    //判断非循环单链表是否为空
    bool is_empty();

    //返回某节点的后继的数据域
    bool next_elem(elemtype e,elemtype &next_e);

    //重载赋值运算符
    linklist operator =(linklist other);

    //返回某节点的前驱的数据域
    bool prior_elem(elemtype e,elemtype &prior_e);


    //默认构造函数
    linklist();
    //非循环单链表的析构函数
    ~linklist();
    //拷贝初始化构造函数
    linklist(linklist &other);

    template <typename out_put>
    friend ostream& operator<<(ostream& out,linklist<out_put> other){
        nodepointer p = other.head;
        while(p){
            out<<p->data<<"\t";
            p = p->next;
        }
        return out;
    }


protected:
    nodepointer head;//头指针

};

template <typename elemtype>
linklist<elemtype>::linklist(){
    head = NULL;//默认初始化构造函数就要设置头指针为空
}

template <typename elemtype>
linklist<elemtype>::~linklist(){
    clear();
}

//非循环单链表的拷贝初始化构造函数
template <typename elemtype>
linklist<elemtype>::linklist(linklist<elemtype> &other){
    nodepointer p;//预指向当前非循环单链表当前结点的指针
    nodepointer op = other.head;
    nodepointer s;//预指向新节点的指针
    head = p = NULL;//指针都接受初始化为空，准备接受初始化

    //赋值other里的每个节点
    while(op){
        s = new linknode;
        assert(s!=0);

        s->data = op->data;

        if(!head){
            head = s;
        }else{
            p->next = s;
        }

        p = s;//形成链表
        op = op->next;//other链表指向下一个结点
    }
    if (head){
        p->next = NULL;//链表的末尾置空
    }
}

//逆置
template <typename elemtype>
void linklist<elemtype>::adverse(){
    nodepointer r,p,q;//预分别指向前驱结点，当前结点和后继结点
    if(!head){//如果链表中没有任何数据，则返回空
        return;
    }

    //反转每个结点的指针域
    r = NULL;
    p = head;
    q = p->next;

    while(p){
        p->next = r;//画图仔细思考
        r = p;
        p = q;
        if(q){
            q = q->next;
        }
    }
    head = r;
}

//单链表置空
template <typename elemtype>
void linklist<elemtype>::clear(){
    nodepointer p,q;
    p = NULL;
    q = head;
    while(q){
        p = q;
        q = q->next;
        delete p;
    }
    head = NULL;
}

//删除非循环链表中数据域为e的第一个结点
template <typename elemtype>
bool linklist<elemtype>::delete_elem(elemtype e){
    nodepointer r,p;
    r = NULL;
    p = head;
    while(p && !(p->data == e)){//找p->data等于e的前驱结点
        r = p;
        p = p->next;
    }
    if (p==NULL){//找到链表尾也没有找到符合的元素
        return false;
    }
    if(r == NULL){
        head = head->next;
    }else{
        r->next = p->next;//删除结点
    }
    free(p);
    return true;
}

//删除非循环单链表中的重复值
template <typename elemtype>
void linklist<elemtype>::delete_repeat(){
    nodepointer r,p;//前驱结点指针和当前结点指针
    nodepointer s;

    r = NULL;
    p = head;
    while(p){
        s = head;
        while(s!=p){
            if(s->data == p->data){
                r->next = p->next;
                delete p;
                p = r;
                break;
            }
            s = s->next;
        }
        r = p;
        if(p){
            p = p->next;
        }
    }
}

//取非循环链表的第i个结点
template <typename elemtype>
elemtype linklist<elemtype>::get_elem(int i){//链表中不能含有零
    int j = 1;
    nodepointer p;
    p = head;
    while(p && j!=i){
        p = p->next;
        j++;
    }
    if(p == NULL){
        return 0;
    }else{
        return p->data;
    }
}

//取非循环单链表头指针head
/*
template <typename elemtype>//注意这个函数定义的格式
typename linklist<elemtype>::nodepointer linklist<elemtype>::get_head(){
    return head;
}*/

//求结点的个数
template <typename elemtype>
int linklist<elemtype>::get_length(){
    int n = 0;
    nodepointer p = head;
    while(p){
        n++;
        p = p->next;
    }
    return n;
}

//插入结点
template <typename elemtype>
bool linklist<elemtype>::insert(int i ,elemtype e){
    int j = 1;
    nodepointer p = head;
    nodepointer s;//带插入结点的指针
    if(i==1){
        s = new linknode;
        s->next = head;
        head = s;
        s->data = e;
        return true;
    }

    while(p && j<i-1){
        ++j;
        p = p->next;
    }

    if(!p || j>i){
        return false;
    }
    s = new linknode;
    assert(s!=0);
    s->data = e;
    if(i==1){
        s->next = head;
        head = s;
    }else{
        s->next = p->next;
        p->next = s;
    }
    return true;
}

//判断链表是否为空
template <typename elemtype>
bool linklist<elemtype>::is_empty(){
    return head?false:true;
}

//返回结点值为e的后继的数据域
template <typename elemtype>
bool linklist<elemtype>::next_elem(elemtype e,elemtype &next_e){
    nodepointer p = head;
    while (p && p->data != e){
        p = p->next;
    }
    if (!p || !p->next){
        return false;
    }

    next_e = p->next->data;
    return true;
}

//重载赋值运算符
template <typename elemtype>
linklist<elemtype> linklist<elemtype>::operator=(linklist<elemtype> other){
    nodepointer p = NULL;
    nodepointer o = other.get_head();
    nodepointer s;

    //判断左边链表是否等于右边链表
    if(this!=&other){
        clear();//清空左边链表

        while(o){
            s = new linknode;
            assert(s!=0);
            s->data = o->data;
            //把新节点连接到左边的链表的后面
            if(!head){
                head = s;
            }
            else{
                p->next = s;
            }
            p = s;
            o = o->next;
        }
        if(p){
            p->next = NULL;//左边链表最后封底
        }
    }
    return *this;
}

//返回前驱数据域
template <typename elemtype>
bool linklist<elemtype>::prior_elem(elemtype e,elemtype &prior_e){
    nodepointer r = NULL;//指向前驱结点的指针
    nodepointer p = head;
    while(p && p->data != e){
        r = p;
        p = p->next;
    }

    if(!p || !r){
        return false;
    }
    prior_e = r->data;
    return true;
}

int main(void){
    linklist<int> t1;
    cout<<"....."<<endl;
    if(t1.is_empty()){
        cout<<"空"<<endl;
    }
    else{
        cout<<"非空"<<endl;
    }

    for(int i = 1;i<=10;i++){
        if(t1.insert(i,i)){
            cout<<"成功"<<endl;
        }
        else{
            cout<<"失败"<<endl;
        }
    }

    t1.insert(11,1);

    cout<<"现在显示链表:"<<endl;

    cout<<t1<<endl;

    cout<<"现在删除链表中的重复项:"<<endl;
    t1.delete_repeat();

    cout<<"现在的链表为:"<<endl;
    cout<<t1<<endl;

    return 0;
}






















