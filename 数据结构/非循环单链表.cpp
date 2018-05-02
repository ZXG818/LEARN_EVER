#include <iostream>
#include <cstdlib>
#include <assert.h>
using namespace std;

template <typename elemtype>
class linklist{
public:
    class linknode{
    public:
        elemtype data;//�ڵ��������
        linknode *next;//ָ����һ��ָ�����͵�ָ����
    };
    typedef linknode* nodepointer;
    //��ѭ������������
    void adverse();

    //��ѭ������������
    void clear();

    //ɾ����ѭ����������������Ϊe�ĵ�һ���ڵ�
    bool delete_elem(elemtype e);

    //ɾ����ѭ���������е��ظ�ֵ
    void delete_repeat();

    //ȡ��ѭ���������е�i���ڵ��ֵ
    elemtype get_elem(int i);

    //ȡ��һ���ڵ��ָ��
    //nodepointer get_head();

    //���ѭ��������Ľڵ�ĸ���
    int get_length();

    //�ڵ�i�����֮ǰ����һ��������Ϊe�Ľ��
    bool insert(int i,elemtype e);

    //�жϷ�ѭ���������Ƿ�Ϊ��
    bool is_empty();

    //����ĳ�ڵ�ĺ�̵�������
    bool next_elem(elemtype e,elemtype &next_e);

    //���ظ�ֵ�����
    linklist operator =(linklist other);

    //����ĳ�ڵ��ǰ����������
    bool prior_elem(elemtype e,elemtype &prior_e);


    //Ĭ�Ϲ��캯��
    linklist();
    //��ѭ�����������������
    ~linklist();
    //������ʼ�����캯��
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
    nodepointer head;//ͷָ��

};

template <typename elemtype>
linklist<elemtype>::linklist(){
    head = NULL;//Ĭ�ϳ�ʼ�����캯����Ҫ����ͷָ��Ϊ��
}

template <typename elemtype>
linklist<elemtype>::~linklist(){
    clear();
}

//��ѭ��������Ŀ�����ʼ�����캯��
template <typename elemtype>
linklist<elemtype>::linklist(linklist<elemtype> &other){
    nodepointer p;//Ԥָ��ǰ��ѭ��������ǰ����ָ��
    nodepointer op = other.head;
    nodepointer s;//Ԥָ���½ڵ��ָ��
    head = p = NULL;//ָ�붼���ܳ�ʼ��Ϊ�գ�׼�����ܳ�ʼ��

    //��ֵother���ÿ���ڵ�
    while(op){
        s = new linknode;
        assert(s!=0);

        s->data = op->data;

        if(!head){
            head = s;
        }else{
            p->next = s;
        }

        p = s;//�γ�����
        op = op->next;//other����ָ����һ�����
    }
    if (head){
        p->next = NULL;//�����ĩβ�ÿ�
    }
}

//����
template <typename elemtype>
void linklist<elemtype>::adverse(){
    nodepointer r,p,q;//Ԥ�ֱ�ָ��ǰ����㣬��ǰ���ͺ�̽��
    if(!head){//���������û���κ����ݣ��򷵻ؿ�
        return;
    }

    //��תÿ������ָ����
    r = NULL;
    p = head;
    q = p->next;

    while(p){
        p->next = r;//��ͼ��ϸ˼��
        r = p;
        p = q;
        if(q){
            q = q->next;
        }
    }
    head = r;
}

//�������ÿ�
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

//ɾ����ѭ��������������Ϊe�ĵ�һ�����
template <typename elemtype>
bool linklist<elemtype>::delete_elem(elemtype e){
    nodepointer r,p;
    r = NULL;
    p = head;
    while(p && !(p->data == e)){//��p->data����e��ǰ�����
        r = p;
        p = p->next;
    }
    if (p==NULL){//�ҵ�����βҲû���ҵ����ϵ�Ԫ��
        return false;
    }
    if(r == NULL){
        head = head->next;
    }else{
        r->next = p->next;//ɾ�����
    }
    free(p);
    return true;
}

//ɾ����ѭ���������е��ظ�ֵ
template <typename elemtype>
void linklist<elemtype>::delete_repeat(){
    nodepointer r,p;//ǰ�����ָ��͵�ǰ���ָ��
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

//ȡ��ѭ������ĵ�i�����
template <typename elemtype>
elemtype linklist<elemtype>::get_elem(int i){//�����в��ܺ�����
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

//ȡ��ѭ��������ͷָ��head
/*
template <typename elemtype>//ע�������������ĸ�ʽ
typename linklist<elemtype>::nodepointer linklist<elemtype>::get_head(){
    return head;
}*/

//����ĸ���
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

//������
template <typename elemtype>
bool linklist<elemtype>::insert(int i ,elemtype e){
    int j = 1;
    nodepointer p = head;
    nodepointer s;//���������ָ��
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

//�ж������Ƿ�Ϊ��
template <typename elemtype>
bool linklist<elemtype>::is_empty(){
    return head?false:true;
}

//���ؽ��ֵΪe�ĺ�̵�������
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

//���ظ�ֵ�����
template <typename elemtype>
linklist<elemtype> linklist<elemtype>::operator=(linklist<elemtype> other){
    nodepointer p = NULL;
    nodepointer o = other.get_head();
    nodepointer s;

    //�ж���������Ƿ�����ұ�����
    if(this!=&other){
        clear();//����������

        while(o){
            s = new linknode;
            assert(s!=0);
            s->data = o->data;
            //���½ڵ����ӵ���ߵ�����ĺ���
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
            p->next = NULL;//������������
        }
    }
    return *this;
}

//����ǰ��������
template <typename elemtype>
bool linklist<elemtype>::prior_elem(elemtype e,elemtype &prior_e){
    nodepointer r = NULL;//ָ��ǰ������ָ��
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
        cout<<"��"<<endl;
    }
    else{
        cout<<"�ǿ�"<<endl;
    }

    for(int i = 1;i<=10;i++){
        if(t1.insert(i,i)){
            cout<<"�ɹ�"<<endl;
        }
        else{
            cout<<"ʧ��"<<endl;
        }
    }

    t1.insert(11,1);

    cout<<"������ʾ����:"<<endl;

    cout<<t1<<endl;

    cout<<"����ɾ�������е��ظ���:"<<endl;
    t1.delete_repeat();

    cout<<"���ڵ�����Ϊ:"<<endl;
    cout<<t1<<endl;

    return 0;
}






















