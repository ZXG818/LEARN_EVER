#include <stdio.h>
int main()
{
	int i, j, k, row;
	int m, p, n;

	//�����һ������
	printf("�������һ������ĳߴ�(M * P)��");
	scanf("%d * %d", &m, &p);
	int **matrix_in_1;
	matrix_in_1 = (int**)malloc(sizeof(int*)*m);//��һ����������m��
	for (i = 0; i < m; i++){
		matrix_in_1[i] = (int)malloc(sizeof(int)*p);//��һ����������p��
	}

	// ����ڶ�������
	printf("�������һ������ĳߴ�(P * N)��");
	scanf("%d * %d", &p, &n);
	int **matrix_in_2;
	matrix_in_2 = (int**)malloc(sizeof(int*)*p);//�ڶ�����������p��
	for (i = 0; i < p; i++){
		matrix_in_2[i] = (int)malloc(sizeof(int)*n);//�ڶ�����������n��
	}


	// ��ʼ����ų˻��Ķ�ά����
	// VAL���鲻֧��ֱ�ӳ�ʼ������
	//int matrix_out[m][n];
	int **matrix_out;
	matrix_out = (int **)malloc(sizeof(int*)*m);//����ռ��ԭ��ͬ��
	for (i = 0; i < m; i++){
		matrix_out[i] = (int)malloc(sizeof(int)*n);
	}

	//��ʼ��������ȫ��Ԫ��Ϊ��
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrix_out[i][j] = 0;//����Ҫָ���������Ԫ����
		}
	}

	// ���û������һ������
	printf("�������һ�������ֵ��\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < p; j++)
		{
			scanf("%d", &matrix_in_1[i][j]);//����Ҳ��Ҫ���嵽һ��Ԫ��
		}
	}

	// ���û�����ڶ�������
	printf("������ڶ��������ֵ��\n");
	for (i = 0; i < p; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &matrix_in_2[i][j]);//ԭ��ͬ��
		}
	}

	// ����˻�������
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < p; k++)
			{
				matrix_out[i][j] += matrix_in_1[i][k] * matrix_in_2[k][j];
			}
		}
	}

	printf("���������£�\n");

	// row ȡ�������ֵ
	row = m > p ? m : p;

	for (i = 0; i < row; i++)
	{
		printf("|  ");
		// ��ӡ matrix_in_1
		for (j = 0; j < p; j++)
		{
			if (i < m)
			{
				printf("\b%d ", matrix_in_1[i][j]);
				printf("|");
			}
			else
			{
				printf("\b\b\b     ");
			}
		}
		// ��ӡ * ��
		if (i == row / 2)
		{
			printf(" * ");
		}
		else
		{
			printf("   ");
		}
		printf("|  ");
		// ��ӡ matrix_in_2
		for (j = 0; j < n; j++)
		{
			if (i < p)
			{
				printf("\b%d ", matrix_in_2[i][j]);
				printf("|");
			}
			else
			{
				printf("\b\b\b     ");
			}
		}
		// ��ӡ = ��
		if (i == row / 2)
		{
			printf(" = ");
		}
		else
		{
			printf("   ");
		}
		// ��ӡ matrix_out
		printf("|  ");
		for (j = 0; j < n; j++)
		{
			if (i < m)
			{
				printf("\b%d ", matrix_out[i][j]);
				printf("|");
			}
			else
			{
				printf("\b\b\b      ");
			}
		}
		printf("\n");
	}

	////////////////////////////////////
	//����Ϊ�ͷ�malloc�������������Ŀռ�
	///////////////////////////////////
	//���ͷŵ�һ������Ŀռ�
	for (i = 0; i < m; i++){
		free(matrix_in_1[i]);
	}
	free(matrix_in_1);
	
	//�ͷŵڶ�������Ŀռ�
	for (i = 0; i < p; i++){
		free(matrix_in_2[i]);
	}
	free(matrix_in_2);

	//�ͷŴ洢����ľ���
	for (i = 0; i < m; i++){
		free(matrix_out[i]);
	}
	free(matrix_out);

	return 0;//������������
}