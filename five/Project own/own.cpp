#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#define Q 19
void Gobangboard()//打印函数
{
	system("cls");
	printf("\n");
	int i, j;
	for (i = 0; i < Q; i++)
	{
		printf("  ");
		if (i == 0)
			printf("┏━");
		for (j = 1; i == 0 && j < Q - 1; j++)
			printf("┯━");
		if (i == 0 && j == Q - 1)
			printf("┓\n  ");
		if (i == 0)
			printf("┃  ");
		for (j = 1; i == 0 && j < Q - 1; j++)
			printf("│  ");
		if (i == 0)
			printf("┃\n");

		if (i < Q - 1 && i != 0)
			printf("┠—");
		for (j = 1; i<Q - 1 && i != 0 && j < Q - 1; j++)
			printf("┼—");
		if (i < Q - 1 && i != 0)
			printf("┨\n  ");
		if (i < Q - 1 && i != 0)
			printf("┃  ");

		for (j = 1; i < Q - 1 && i != 0 && j < Q - 1; j++)
			printf("│  ");
		if (i < Q - 1 && i != 0)
			printf("┃\n");
		if (i == Q - 1)
			printf("┗━");
		for (j = 1; i == Q - 1 && j < Q - 1; j++)
			printf("┷━");
		if (i == Q - 1)
			printf("┛\n");
	}

}


void initialize(int p[Q][Q],int* Cx,int* Cy,int* Now,int* count)//初始化函数
{

	int a, b;
	for (a = 0; a < Q; a++)
		for (b = 0; b <Q; b++)
			p[a][b] = 0;
	*Cx = Q/ 2;
	*Cy = Q/ 2;
	*Now = 1;
	*count = 0;
	a = 0;
	b = 0;
	
}

void gotoxy(int x, int y)//需要引用的gotoxy函数
{
	HANDLE hOutput;
	COORD loc;
	loc.X = x;
	loc.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
}


void cursor(int Cx,int Cy)//光标函数
{
	gotoxy(4*Cx, 2*Cy);
		printf("┏");
		gotoxy(4 * Cx, 2 * Cy+2);
		printf("┗"); 
		gotoxy(4* Cx+4, 2* Cy);
		printf("┓");
		gotoxy(4* Cx+4, 2* Cy+2);
		printf("┛");
		gotoxy(1, 2 * Q );
		printf(" ");
			
		
}

int changechess(int p[Q][Q],int Cx,int Cy,int Now)//棋子变换
{	
	if (p[Cx][Cy] == 0)
	{
		p[Cx][Cy] = Now;
		if (p[Cx][Cy] == 1)
		{
			gotoxy(4 * Cx+2, 2 * Cy+1);
			printf("●");
		}

		if (p[Cx][Cy] == 2)
		{
			gotoxy(4 * Cx + 2, 2 * Cy + 1);
			printf("○");
			
		}
		return 1;
	}
	else 
		return 0;
	
}

int Rule(int p[Q][Q],int Cx,int Cy,int Now)//判定规则
{
	int z = 0;
	int x = 0;
	int c = 0;
	int v = 0;
	int m;
	for (m = 1; m <= 4; m++)
	{
		if (Cx - m >= 0)
		{
			if (p[Cx - m][Cy] == Now)
				z++;
			else break;
		}
	}
	for (m = 1; m <= 4; m++)
	{
		if (Cx + m <= Q - 1)
		{
			if (p[Cx + m][Cy] == Now)
				z++;
			else break;
		}
	}
		if (z >=  4)
			return Now;
	for (m = 1; m <= 4; m++)
	{
			if (Cy - m >= 0)
			{
				if (p[Cx][Cy - m] == Now)
					x++;
				else break;
			}
	}
	for (m = 1; m <= 4; m++)
	{
		if (Cy + m <= Q - 1)
		{
			if (p[Cx][Cy + m] == Now)
				x++;
			else break;
		}
	}
		if (x >= 4)
			return Now;
	for (m = 1; m <= 4; m++)
	{
			if (Cx - m >= 0 && Cy - m >= 0)
			{
				if (p[Cx - m][Cy - m] == Now)
					c++;
				else break;
			}
	}
	for (m = 1; m <= 4; m++)
	{
		if (Cx + m <= Q - 1 && Cy + m <= Q - 1)
		{
			if (p[Cx + m][Cy + m] == Now)
				c++;
			else break;
		}
	}
		if (c >= 4)
			return Now;
	for (m = 1; m <= 4; m++)
	{
			if (Cx - m >= 0 && Cy + m <= Q - 1)
			{
				if (p[Cx - m][Cy + m] == Now)
					v++;
			    else break;
			}
	}
	for (m = 1; m <= 4; m++)
	{
		if (Cx + m <= Q - 1 && Cy - m >= 0)
		{
			if (p[Cx + m][Cy - m] == Now)
				v++;
			else break;
		}
	}
		
		if (v >= 4)
			return Now;
	
		return 0;
}

void control(int*count, int p[Q][Q], int *Cx, int *Cy, int *Now)//键盘控制及判定结果
{
	char input='1';
	int victor;
	int f = 1;
	while (f)//循环变量，如果一局游戏判定结束，则不会继续判定
	{
		if (_kbhit())
		{
			input = _getch();//利用input将键盘所对应ASCII码输入，以实现键盘控制
			if (input == 27)
				exit(0);
			if (input == 32)
			{		
				if (changechess(p, *Cx, * Cy, * Now))
				{
					(*count)++;//记录棋子数
					
					if (*count == Q*Q)//平局判定
					{
						gotoxy( Q*2,  Q);
						printf("平局");
						if (_getch() == 224)//当一局游戏结束后，按任意键跳出
						{
							_getch();
						}
												
					}
					victor = Rule(p,* Cx,* Cy, *Now);
					if (victor == 1)//黑棋胜判定
					{
						gotoxy(Q*2, Q);
						printf("黑棋胜");
						if (_getch() == 224)
						{
							_getch();
						}
						
					}

					if (victor == 2)//白棋胜判定
					{
						gotoxy(Q*2, Q);
						printf("白棋胜");
						if (_getch() == 224)
						{
							_getch();
						}
						
					}
						*Now = 3 - *Now;
					if (*count == Q*Q || victor == 1 || victor == 2)//改变循环变量，跳出循环
						{
							f = 0;
							
						}
				}
              
			}
				
				gotoxy(4 * (*Cx), 2 *(* Cy));
				printf("  ");
				gotoxy(4 * (*Cx), 2 * (*Cy) + 2);
				printf("  ");
				gotoxy(4 * (*Cx) + 4, 2 * (*Cy));
				printf("  ");
				gotoxy(4 * (*Cx) + 4, 2 * (*Cy) + 2);
				printf("  ");
				switch (input)
				{
				case 'w':(*Cy)--; break;
				case 'a':(*Cx)--; break;
				case 's':(*Cy)++; break;
				case 'd':(*Cx)++; break;
				}

				if (*Cx < 0)(*Cx) = Q - 1;
				if (*Cy < 0)(*Cy )= Q - 1;
				if (*Cx > Q - 1)(*Cx) = 0;
				if (*Cy > Q - 1)(*Cy) = 0;

				cursor(*Cx,*Cy);			
		}
			
	}
				
}

void Start()
{
	int p[Q][Q];
	int Now;
	int Cx, Cy;
	int count;

	Gobangboard();
	initialize(p,&Cx,&Cy,&Now,&count);
	cursor(Cx,Cy);
	control(&count,p,&Cx,&Cy,&Now);
}

void main()
	{
		system("mode con: cols=80 lines=45");
		system("title 自制版五子棋");//设置标题
		system("color B6");//设置颜色
		while (1)
		{
			Start();

		}
			
			getchar();
	}
