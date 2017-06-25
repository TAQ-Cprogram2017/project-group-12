#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include "snake.h"

void gotoxy(int x,int y)  // change cursor location to (x,y), which is row y+1, column x+1
{
	HANDLE hOutput;
	COORD loc;
	loc.X=x;
	loc.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,loc);
}

void textcolor(int color)  //change textcolor for later output
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void delay(int msec)  //suspend for some milliseconds
{
	time_t now,start;
	start=clock();
	do
	    now=clock();
	while(now-start<msec);
}

int move(int* i,int* j,int dir,int a[22][32]) //move the coordinate(i,j), which is row i, column j, of the snake head and judge what happens
{
	int f=0;
	switch(dir)
	{
		case 1:if(*i>1&&a[(*i)-1][*j]%2==0) (*i)--; else f=1;break;
		case 2:if(*i<20&&a[(*i)+1][*j]%2==0) (*i)++; else f=1;break;
		case 3:if(*j>1&&a[*i][(*j)-1]%2==0) (*j)--; else f=1;break;
		case 4:if(*j<30&&a[*i][(*j)+1]%2==0) (*j)++; else f=1;break;
	}
	if(a[*i][*j]==2) f=2;
	return f; //the meaning of the value of f: 0 means nothing happens, 1 means it collides with either its body or wall, 2 means it reaches the food
}

int initialize(int a[22][32])  //initialize the game
{
    FILE* fp=fopen("3.txt","r");   //read the map from a file
	int i,j,s;
	system("cls");  		//clear the screen
	printf("     ");		//print the white grid lines: 20*30
	for(i=1;i<=30;i++)
	    printf(" %2d  ",i);
	printf("\n     ");
	for(i=1;i<=30;i++)
	    printf("-----");
	for(i=1;i<=20;i++)
	{
		printf("\n %2d |",i);
		for(j=1;j<=30;j++)
		{
			fscanf(fp,"%d",&a[i][j]);
			if(a[i][j]==0) printf("    |"); else 
			{
				textcolor(9);	//obstacles in the middle of the map are indicated by blue '@@'
				printf(" @@ ");	
				textcolor(7);
				printf("|");
			}
		}
		printf("\n     ");
		for(j=1;j<=30;j++)
		    printf("-----");
	}
	printf("\n");
	fscanf(fp,"%d",&s);
	fclose(fp);
	return s;
}

int process(int a[22][32],int b[600],int *i,int *j,int *p1,int *p2,int dir,int t0)
{
	int f=move(i,j,dir,a),k;// k is a temporary variable
	if(f==0)// if nothing happens after the move, the snake moves one step forward, and information in array b changes accordingly
	{
		textcolor(7);
		gotoxy(5*(b[*p1]%100),2*(b[*p1]/100));
		printf("   ");
		a[b[((*p1)+1)%600]/100][b[((*p1)+1)%600]%100]=0;
		gotoxy(5*(*j),2*(*i));
		printf("%2c",6);
		gotoxy(5*(b[*p2]%100),2*(b[*p2]/100));
		printf("%2c",1);
		*p1=((*p1)+1)%600;*p2=((*p2)+1)%600;
		b[*p2]=100*(*i)+(*j);
		a[*i][*j]=1;
	}
	else if(f==1)// if the snake collides after the move, it will be printed in red and the game ends
	{
		textcolor(12);
		k=*p2+(*p2<*p1)*600;
		gotoxy(5*(b[k%600]%100),2*(b[k%600]/100));
		printf("%2c",6);k--;
		for(;k>=*p1;k--)
		{
			gotoxy(5*(b[k%600]%100),2*(b[k%600]/100));
			printf("%2c",1);
			delay(100);
		}
	}
	else// if the snake reaches the food, its color will be changed to green for a little time and then be changed back, 
	//it also grows a bit longer, array b changes accordingly
	{
		textcolor(10);
		*p2=((*p2)+1)%600;
		b[*p2]=100*(*i)+(*j);
		a[*i][*j]=1;
		k=*p2+(*p2<*p1)*600;
		gotoxy(5*(b[k%600]%100),2*(b[k%600]/100));
		printf("%2c",6);k--;
		for(;k>=*p1;k--)
		{
			gotoxy(5*(b[k%600]%100),2*(b[k%600]/100));
			printf("%2c",1);
		}
		delay(t0);
		textcolor(7);
		k=*p2+(*p2<*p1)*600;
		gotoxy(5*(b[k%600]%100),2*(b[k%600]/100));
		printf("%2c",6);k--;
		for(;k>=*p1;k--)
		{
			gotoxy(5*(b[k%600]%100),2*(b[k%600]/100));
			printf("%2c",1);
		}
	}
	return f;
}
