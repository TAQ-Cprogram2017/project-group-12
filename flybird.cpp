#include <stdio.h>//标准化输入与输出。 
#include <stdlib.h>// 
#include <conio.h>
#include <windows.h>
#include <time.h>


// 全局变量
void SetColor(int a=1,int c=10)
{
	HANDLE b=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(b,c) ;
	
}
int high,width; // 游戏画面大小
int bird_x,bird_y; // 小鸟的坐标
int bar1_y,bar1_xDown,bar1_xTop; // 障碍物
int score=0;

void gotoxy(int x,int y)//类似于清屏函数
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle,pos);
}

int startup()  // 数据初始化 
{
	int i;
	high = 20;
	width = 50;
	bird_x = high/2;
	bird_y = 10;
	bar1_y = 50;
	bar1_xDown =high/2-3;
	bar1_xTop= high/2+3;
	i=rand()%10;
	return i;
}
int barshow(int q,int i)
{
	int a,f;
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
	               if(bird_y==(q+1))
	       {
	       	    if((bird_x>i)&&(bird_x<(i+6)))
	       	         score++;
	       	    else
	       	    {
	       	    	printf("defeat\n");
	       	    	system("pause");
					exit(0);
				}
			
		   }
		   gotoxy(0,30);
		   printf("score:%d",score);

        }
        return q;
	
}

void show()  // 显示画面
{
	char input;
		
	Sleep(100);
	gotoxy(bird_y,bird_x); 
	printf(" ");
	bird_x ++;
    if(kbhit())
       input=getch();
    else input='1';
    if (input == ' ')  
	{
	    bird_x = bird_x - 5;
	    if(bird_x-1<=0)
	       bird_x=bird_x+5;
	}
    gotoxy(bird_y,bird_x);	
	printf("@");
}

int main()
{
	int q=15,u,p=30,n;
	srand(time(0));
	SetColor();
	u=startup();
	n=rand()%10;
	while (1)  
	{
		
		show();
		barshow(q,u);
		if(q==0)
	    {
	       q=30;
	       u=rand()%10;
		}
		else q--;
		barshow(p,n);
		if(p==0)
	    {
	       p=30;
	       n=rand()%10;
		}
		else p--;
		
	}
}

