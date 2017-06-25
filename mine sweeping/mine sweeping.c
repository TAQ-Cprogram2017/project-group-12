#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include"mine sweeping.h"

void gotoxy(int x,int y)	//change the cursor to a certain location
{
	HANDLE hOutput;
	COORD loc;
	loc.X=x;
	loc.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,loc);
}

void textcolor(int color) // change text color
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void delay(int msec)	// suspend for some milliseconds
{
	time_t now,start;
	start=clock();
	do
	    now=clock();
	while(now-start<msec);
}

void initialize(int x,int y, int a[18][32], int b[18][32], int c[18][32]) //randomly create mines
{
	int i,j,k=0,n;
	for(i=0;i<18;i++)
		for(j=0;j<32;j++)
		{
			a[i][j]=0;
			b[i][j]=0;
			c[i][j]=0;
		}
	srand(time(0));
	while(k<99)
	{
		n=rand()%480;
		i=n/30+1;j=n%30+1;
		if(!a[i][j]&&(i<x-1||i>x+1||j<y-1||j>y+2))
		{
			a[i][j]=1;
			k++;
		}
	}
	for(i=0;i<=17;i++)
	    for(j=0;j<=31;j++)
	    	if(i&&j&&i!=17&&j!=31)
			    if(a[i][j]) b[i][j]=-1;
	        	else b[i][j]=a[i][j-1]+a[i][j+1]+a[i+1][j-1]+a[i+1][j]+a[i+1][j+1]+a[i-1][j-1]+a[i-1][j]+a[i-1][j+1];			
			else c[i][j]=1;	
}

void reveal(int i,int j,char input,int a[18][32],int b[18][32],int c[18][32])// reveal a tile when the player judged it right
{
	if(input!=' ')
	{
		c[i][j]=1;
		textcolor(10);
		gotoxy(5*j,2*i);
		if(a[i][j]==1) printf("%2c",6); else printf("%2d",b[i][j]);
		if(input=='j'||input==' ') delay(30); else delay(200);
		switch(b[i][j])
		{
			case 0: textcolor(8); break;
			case -1:textcolor(15); break;
			case 1: textcolor(11); break;
			case 2: textcolor(10); break;
			case 3: textcolor(12); break;
			case 4: textcolor(9); break;
			case 5: textcolor(13); break;
			case 6: textcolor(14); break;
			case 7: textcolor(5); break;
			case 8: textcolor(6); break;   
		} 
		gotoxy(5*j,2*i);
		if(a[i][j]==1) printf("%2c",6); else printf("%2d",b[i][j]);
	}
	if(input=='j'&&b[i][j]==0||input==' ')//if a number '0' is revealed or the player correctly pressed ' ', the tiles around the tile will be revealed 
	{
		if(c[i-1][j]==0) reveal(i-1,j,'j',a,b,c);
		if(c[i-1][j-1]==0) reveal(i-1,j-1,'j',a,b,c);
		if(c[i-1][j+1]==0) reveal(i-1,j+1,'j',a,b,c);
		if(c[i+1][j]==0) reveal(i+1,j,'j',a,b,c);
		if(c[i+1][j-1]==0) reveal(i+1,j-1,'j',a,b,c);
		if(c[i+1][j+1]==0) reveal(i+1,j+1,'j',a,b,c);
		if(c[i][j-1]==0) reveal(i,j-1,'j',a,b,c);
		if(c[i][j+1]==0) reveal(i,j+1,'j',a,b,c);
	}
}

void display()
{
	int i,j;
	system("cls");
	textcolor(7); 
  	printf("     ");
    for(i=1;i<=30;i++)
  	    printf(" %2d  ",i);
  	printf("\n    ");
  	for(i=1;i<=30;i++)
	    printf("-----");
    printf("-\n");
	for(i=1;i<=16;i++)
	{
		printf("%2d  |",i);
		for(j=1;j<=30;j++)
		    printf("    |");			
		printf("\n    ");
		for(j=1;j<=30;j++)
		    printf("-----");
		printf("-\n");
	}
}

void clear(int x,int y)//change the frame back to white
{
	textcolor(7);
	gotoxy(5*y-1,2*x-1);
	printf("------");
	gotoxy(5*y-1,2*x);
	printf("|");
	gotoxy(5*y+4,2*x);
	printf("|");
	gotoxy(5*y-1,2*x+1);
	printf("------");
	gotoxy(0,35);
}

void highlight(int x,int y)//change the frame of a tile to blue
{
	textcolor(9);
	gotoxy(5*y-1,2*x-1);
	printf("------");
	gotoxy(5*y-1,2*x);
	printf("|");
	gotoxy(5*y+4,2*x);
	printf("|");
	gotoxy(5*y-1,2*x+1);
	printf("------");
	gotoxy(0,35);
}

void wrong(int a[18][32],int b[18][32],int c[18][32])// when the player judged wrong, all mines explodes and he's killed
{
	int i,j;
	textcolor(12);
	for(i=1;i<=16;i++)
		for(j=1;j<=30;j++)						
			if(a[i][j]) 
			{
				gotoxy(5*j,2*i);
				printf("%2c",6);
			}
	gotoxy(0,34);
	textcolor(7);
	printf("You have been slain.");
}

int doubleclick(int i,int j,int a[18][32],int b[18][32],int c[18][32])
{
	if(a[i][j-1]*c[i][j-1]+a[i][j+1]*c[i][j+1]+a[i-1][j-1]*c[i-1][j-1]+a[i-1][j]*c[i-1][j]+a[i-1][j+1]*c[i-1][j+1]+a[i+1][j-1]*c[i+1][j-1]+a[i+1][j]*c[i+1][j]+a[i+1][j+1]*c[i+1][j+1]==b[i][j])
	{
		reveal(i,j,' ',a,b,c);
		gotoxy(0,35);
		return 0;
	}
	else return 3;	
}
