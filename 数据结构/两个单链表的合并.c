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
		printf("对不起，初始化失败。\n");
	}
	else
	{
		(*L)->next = NULL;
		printf("初始化成功。\n");
	}
}

void creatlist(linklist L) //尾插法建立单链表
{
	int num, i;
	linklist r, q;
	r = L;
	printf("请问你想要建立几个元素的单链表：\n");
	scanf("%d", &num);
	for (i = 0; i<num; i++)
	{
		q = (linklist)malloc(sizeof(Node));
		if (!q)
		{
			printf("对不起，存储空间分配失败。\n");
		}
		else
		{
			printf("请输入第%d个元素：", i + 1);
			scanf("%d", &q->data);
			q->next = NULL;
			r->next = q;
			r = q;
		}
	}
	printf("单链表创建完毕。\n");
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
	printf("单链表打印完毕。\n");
}

linklist unionlist(linklist L1, linklist L2, linklist L3)
{
	linklist p1, p2, p3;
	p3 = L3 = L1;//p3这里的指针要初始化，要不就是野指针
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
	printf("请创建第一个链表：");
	initlist(&L1);
	creatlist(L1);        printlist(L1);
	printf("请创建第二个链表：");
	initlist(&L2);
	creatlist(L2);        printlist(L2);
	initlist(&L3);//这句要写上，因为楼上说的有道理的，这里要新建一个链表，分配空间，初始化
	printf("合并两个链表：");
	L3 = unionlist(L1, L2, L3);//这里记得要有返回值。。。
	printlist(L3);
	return 0;
}