#include <stdio.h>//标准化输入与输出。 
#include <stdlib.h>// 
#include <conio.h>
#include <windows.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")

#define high 20 
#define width 50// 游戏画面大小


void SetColor(int a=1,int c=10)
{
	HANDLE b=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(b,c) ;
	
}


void gotoxy(int x,int y)//类似于清屏函数
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

int startup(int*bird_x,int*bird_y,int*bar1_y,int*bar1_xDown,int*bar1_xTop,int*score)  // 数据初始化 
{
	int i;
	*bird_x = high/2;
	*bird_y = 10;
	*bar1_y = 50;
	*bar1_xDown =high/2-3;
	*bar1_xTop= high/2+3;
	*score = 0;
	i=rand()%10;
	return i;
}
int barshow(int q,int i,int*bird_x, int*bird_y, int *score)
{
	Sleep(75);
	int a,f,w=0;
		if(q>=0)
	    {
	       f=i;
	       for(;f>=1;f--)
	       {
		    gotoxy(q+1,f); 
		    printf(" ");
	       }
		   a=i+6;
	       for(;a<=high;a++)
	       {
	        gotoxy(q+1,a); 
	        printf(" ");
	       }
	       f=i;
           for(;f>=1;f--)
	       {
		    gotoxy(q,f); 
		    printf("*");
	       }
	       a=i+6;
	       for(;a<=high;a++)
	       {
	        gotoxy(q,a); 
	        printf("*");
	       }
	       f=i;
	       for(;f>=1;f--)
	       {
		    gotoxy(0,f); 
		    printf(" ");
	       }
		   a=i+6;
	       for(;a<=high;a++)
	       {
	        gotoxy(0,a); 
	        printf(" ");
	       }
	               if(*bird_y==(q+1))
	       {
	       	    if((*bird_x>i)&&(*bird_x<(i+6)))
	       	         (*score)++;
	       	    else
	       	    {
					gotoxy(0, 28);
	       	    	printf("defeat，若想继续\n");
	       	    	system("pause");
					w = 1;
					//exit(0);
				}
			
		   }
		   gotoxy(0,30);
		   printf("score:%d",*score);

        }
        return w;
	
}

void show(int*bird_y, int*bird_x)  // 显示画面
{
	char input=1;
		
	Sleep(75);
	gotoxy(*bird_y,*bird_x); 
	printf(" ");
	(*bird_x) ++;
	if(_kbhit())
     input=_getch();
	else input = 1;
    if (input == ' ')  
	{
	    *bird_x = (*bird_x) - 5;
	    if((*bird_x)-1<=0)
	       *bird_x=(*bird_x)+5;
	}
    gotoxy(*bird_y,*bird_x);	
	printf("@");
}

int main()
{ 
	int bird_x, bird_y; // 小鸟的坐标
	int bar1_y, bar1_xDown, bar1_xTop; // 障碍物
	int score = 0;
	int q=15,u,p=30,n;
	srand(time(0));
	SetColor();
	u=startup(&bird_x, &bird_y, &bar1_y, &bar1_xDown, &bar1_xTop,&score);
	n=rand()%10;
	PlaySound(TEXT("A.wav"), NULL, SND_FILENAME | SND_ASYNC);
	gotoxy(0, 29);
	//printf("按下“R”重新开始");
	while (1)  
	{        
		show(&bird_y, &bird_x);
		if (barshow(q, u, &bird_x, &bird_y, &score))
		{
			u = startup(&bird_x, &bird_y, &bar1_y, &bar1_xDown, &bar1_xTop, &score);
			system("cls");
		}
			
		if(q==0)
	    {
	       q=30;
	       u=rand()%10;
		}
		else q--;
		if (barshow(p, n, &bird_x, &bird_y, &score))
		{
			n= startup(&bird_x, &bird_y, &bar1_y, &bar1_xDown, &bar1_xTop, &score);
			system("cls");
		}
		
		if(p==0)
	    {
	       p=30;
	       n=rand()%10;
		}
		else p--;
		
	}
}

