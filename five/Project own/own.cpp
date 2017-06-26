#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<windows.h>
#define Q 19
void Gobangboard()//��ӡ����
{
	system("cls");
	printf("\n");
	int i, j;
	for (i = 0; i < Q; i++)
	{
		printf("  ");
		if (i == 0)
			printf("����");
		for (j = 1; i == 0 && j < Q - 1; j++)
			printf("�ө�");
		if (i == 0 && j == Q - 1)
			printf("��\n  ");
		if (i == 0)
			printf("��  ");
		for (j = 1; i == 0 && j < Q - 1; j++)
			printf("��  ");
		if (i == 0)
			printf("��\n");

		if (i < Q - 1 && i != 0)
			printf("�ġ�");
		for (j = 1; i<Q - 1 && i != 0 && j < Q - 1; j++)
			printf("�ࡪ");
		if (i < Q - 1 && i != 0)
			printf("��\n  ");
		if (i < Q - 1 && i != 0)
			printf("��  ");

		for (j = 1; i < Q - 1 && i != 0 && j < Q - 1; j++)
			printf("��  ");
		if (i < Q - 1 && i != 0)
			printf("��\n");
		if (i == Q - 1)
			printf("����");
		for (j = 1; i == Q - 1 && j < Q - 1; j++)
			printf("�۩�");
		if (i == Q - 1)
			printf("��\n");
	}

}


void initialize(int p[Q][Q],int* Cx,int* Cy,int* Now,int* count)//��ʼ������
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

void gotoxy(int x, int y)//��Ҫ���õ�gotoxy����
{
	HANDLE hOutput;
	COORD loc;
	loc.X = x;
	loc.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, loc);
}


void cursor(int Cx,int Cy)//��꺯��
{
	gotoxy(4*Cx, 2*Cy);
		printf("��");
		gotoxy(4 * Cx, 2 * Cy+2);
		printf("��"); 
		gotoxy(4* Cx+4, 2* Cy);
		printf("��");
		gotoxy(4* Cx+4, 2* Cy+2);
		printf("��");
		gotoxy(1, 2 * Q );
		printf(" ");
			
		
}

int changechess(int p[Q][Q],int Cx,int Cy,int Now)//���ӱ任
{	
	if (p[Cx][Cy] == 0)
	{
		p[Cx][Cy] = Now;
		if (p[Cx][Cy] == 1)
		{
			gotoxy(4 * Cx+2, 2 * Cy+1);
			printf("��");
		}

		if (p[Cx][Cy] == 2)
		{
			gotoxy(4 * Cx + 2, 2 * Cy + 1);
			printf("��");
			
		}
		return 1;
	}
	else 
		return 0;
	
}

int Rule(int p[Q][Q],int Cx,int Cy,int Now)//�ж�����
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

void control(int*count, int p[Q][Q], int *Cx, int *Cy, int *Now)//���̿��Ƽ��ж����
{
	char input='1';
	int victor;
	int f = 1;
	while (f)//ѭ�����������һ����Ϸ�ж��������򲻻�����ж�
	{
		if (_kbhit())
		{
			input = _getch();//����input����������ӦASCII�����룬��ʵ�ּ��̿���
			if (input == 27)
				exit(0);
			if (input == 32)
			{		
				if (changechess(p, *Cx, * Cy, * Now))
				{
					(*count)++;//��¼������
					
					if (*count == Q*Q)//ƽ���ж�
					{
						gotoxy( Q*2,  Q);
						printf("ƽ��");
						if (_getch() == 224)//��һ����Ϸ�����󣬰����������
						{
							_getch();
						}
												
					}
					victor = Rule(p,* Cx,* Cy, *Now);
					if (victor == 1)//����ʤ�ж�
					{
						gotoxy(Q*2, Q);
						printf("����ʤ");
						if (_getch() == 224)
						{
							_getch();
						}
						
					}

					if (victor == 2)//����ʤ�ж�
					{
						gotoxy(Q*2, Q);
						printf("����ʤ");
						if (_getch() == 224)
						{
							_getch();
						}
						
					}
						*Now = 3 - *Now;
					if (*count == Q*Q || victor == 1 || victor == 2)//�ı�ѭ������������ѭ��
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
		system("title ���ư�������");//���ñ���
		system("color B6");//������ɫ
		while (1)
		{
			Start();

		}
			
			getchar();
	}
