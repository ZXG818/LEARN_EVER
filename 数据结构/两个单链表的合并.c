# include<stdio.h>
# include<stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node, *linklist;

void initlist(linklist *L)
{
	(*L) = (linklist)malloc(sizeof(Node));
	if (!(*L))
	{
		printf("�Բ��𣬳�ʼ��ʧ�ܡ�\n");
	}
	else
	{
		(*L)->next = NULL;
		printf("��ʼ���ɹ���\n");
	}
}

void creatlist(linklist L) //β�巨����������
{
	int num, i;
	linklist r, q;
	r = L;
	printf("��������Ҫ��������Ԫ�صĵ�����\n");
	scanf("%d", &num);
	for (i = 0; i<num; i++)
	{
		q = (linklist)malloc(sizeof(Node));
		if (!q)
		{
			printf("�Բ��𣬴洢�ռ����ʧ�ܡ�\n");
		}
		else
		{
			printf("�������%d��Ԫ�أ�", i + 1);
			scanf("%d", &q->data);
			q->next = NULL;
			r->next = q;
			r = q;
		}
	}
	printf("����������ϡ�\n");
}

void printlist(linklist L)
{
	linklist p;
	p = L->next;
	while (p != NULL)
	{
		printf("%d ", p->data);
		p = p->next;
	}
	printf("�������ӡ��ϡ�\n");
}

linklist unionlist(linklist L1, linklist L2, linklist L3)
{
	linklist p1, p2, p3;
	p3 = L3 = L1;//p3�����ָ��Ҫ��ʼ����Ҫ������Ұָ��
	p1 = L1->next;
	p2 = L2->next;

	while (p1&&p2)
	{
		if (p1->data <= p2->data)
		{
			p3->next = p1;
			p3 = p1;
			p1 = p1->next;
		}
		else
		{
			p3->next = p2;
			p3 = p2;
			p2 = p2->next;
		}
	}
	p3->next = p1 ? p1 : p2;
	free(L2);
	return L3;
}



int main()
{
	linklist L1, L2, L3;
	printf("�봴����һ������");
	initlist(&L1);
	creatlist(L1);        printlist(L1);
	printf("�봴���ڶ�������");
	initlist(&L2);
	creatlist(L2);        printlist(L2);
	initlist(&L3);//���Ҫд�ϣ���Ϊ¥��˵���е���ģ�����Ҫ�½�һ����������ռ䣬��ʼ��
	printf("�ϲ���������");
	L3 = unionlist(L1, L2, L3);//����ǵ�Ҫ�з���ֵ������
	printlist(L3);
	return 0;
}