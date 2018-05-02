#include <stdio.h>
int main()
{
	int i, j, k, row;
	int m, p, n;

	//定义第一个矩阵
	printf("请输入第一个矩阵的尺寸(M * P)：");
	scanf("%d * %d", &m, &p);
	int **matrix_in_1;
	matrix_in_1 = (int**)malloc(sizeof(int*)*m);//第一个矩阵申请m行
	for (i = 0; i < m; i++){
		matrix_in_1[i] = (int)malloc(sizeof(int)*p);//第一个矩阵申请p列
	}

	// 定义第二个矩阵
	printf("请输入第一个矩阵的尺寸(P * N)：");
	scanf("%d * %d", &p, &n);
	int **matrix_in_2;
	matrix_in_2 = (int**)malloc(sizeof(int*)*p);//第二个矩阵申请p行
	for (i = 0; i < p; i++){
		matrix_in_2[i] = (int)malloc(sizeof(int)*n);//第二个矩阵申请n行
	}


	// 初始化存放乘积的二维数组
	// VAL数组不支持直接初始化操作
	//int matrix_out[m][n];
	int **matrix_out;
	matrix_out = (int **)malloc(sizeof(int*)*m);//申请空间的原理同上
	for (i = 0; i < m; i++){
		matrix_out[i] = (int)malloc(sizeof(int)*n);
	}

	//初始化，就是全部元素为零
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			matrix_out[i][j] = 0;//这里要指定到具体的元素哇
		}
	}

	// 让用户输入第一个矩阵
	printf("请输入第一个矩阵的值：\n");
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < p; j++)
		{
			scanf("%d", &matrix_in_1[i][j]);//这里也是要具体到一个元素
		}
	}

	// 让用户输入第二个矩阵
	printf("请输入第二个矩阵的值：\n");
	for (i = 0; i < p; i++)
	{
		for (j = 0; j < n; j++)
		{
			scanf("%d", &matrix_in_2[i][j]);//原因同上
		}
	}

	// 计算乘积并保存
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

	printf("计算结果如下：\n");

	// row 取行数最大值
	row = m > p ? m : p;

	for (i = 0; i < row; i++)
	{
		printf("|  ");
		// 打印 matrix_in_1
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
		// 打印 * 号
		if (i == row / 2)
		{
			printf(" * ");
		}
		else
		{
			printf("   ");
		}
		printf("|  ");
		// 打印 matrix_in_2
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
		// 打印 = 号
		if (i == row / 2)
		{
			printf(" = ");
		}
		else
		{
			printf("   ");
		}
		// 打印 matrix_out
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
	//下面为释放malloc申请的三个矩阵的空间
	///////////////////////////////////
	//先释放第一个矩阵的空间
	for (i = 0; i < m; i++){
		free(matrix_in_1[i]);
	}
	free(matrix_in_1);
	
	//释放第二个矩阵的空间
	for (i = 0; i < p; i++){
		free(matrix_in_2[i]);
	}
	free(matrix_in_2);

	//释放存储结果的矩阵
	for (i = 0; i < m; i++){
		free(matrix_out[i]);
	}
	free(matrix_out);

	return 0;//程序正常结束
}