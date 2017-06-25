#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include"snake.h"

int main()
{
	int i,j,k,x,y,dir,f,f0=0,p1,p2,n,t0=150,s;
	//i,j is the coordinate of the snake head, k,x,y are temporary variables, dir indicates the direction of the snake movement:
	//1 for up, 2 for down, 3 for left, 4 for right, f indicates whether the snake is alive: 1 for dead, 0 for not, 
	//2(this value is temporary) for reaching food, f0 indicates whether the snake has got the food, p1,p2 are for the operation of array b,
	//n stores the current length of the snake, t0(millisecond) is the interval time between each movement of snake
    float t; //t stores the current time
	char input,f1; 	
	//input stores keyboard input, f1 indicates whether the food location created by random is legal:' ' for illegal, '0' for legal
	int a[22][32]={0};// array a stores everything on the map: 0 for nothing here, 1 for snake, 2 for food, 3 for obstacles 
	int b[600]={0};	// array b stores the position of each section of the snake
	//b[*]/100 is the row number, b[*]%100 is the column number, b[p1] to b[p2] contain valid information
	//new information is stored in b[p2+1], p2++ to include it, p1++ to discard earlier information, whenever p1,p2 reaches 600, they go back to 0
	srand(time(0)); // initialization
	getchar();
	do // start the game
	{		
	   	s=initialize(a);
		i=10;j=6;dir=4;p1=0;p2=3;f=0;n=4;t=0;f1=' ';
		a[10][4]=1;a[10][5]=1;a[10][6]=1;
		b[0]=1003;b[1]=1004;b[2]=1005;b[3]=1006;
		gotoxy(30,20);	printf("%2c",6);
		gotoxy(25,20);	printf("%2c",1);
		gotoxy(20,20);	printf("%2c",1);
		gotoxy(15,20);	printf("%2c",1); // initialization, the snake is marked in special symbols
		do // create a piece of food
		{
			k=rand()%600;
			x=k/30+1;y=k%30+1;
			if(a[x][y]==0&&(b[p1]/100!=x||b[p1]%100!=y)) {a[x][y]=2;f1='0';}
		}while(f1==' ');
		textcolor(13);// print the food in purple
		gotoxy(5*y,2*x);
		printf("%2c",5);
		gotoxy(180,0); getchar();
		while(f==0)// while the snake is alive
		{
			f0=0;
			while(f0==0&&f==0)// while it's alive and hasn't got the food
			{
				gotoxy(0,42);
				if(kbhit()) // judge if keyboard is hit
				{
					input=getch();// read keyboard input
					switch(input)
					{
						case 'w':if(dir!=2) dir=1;break;// the snake can't directly go reverse
						case 's':if(dir!=1) dir=2;break;
						case 'a':if(dir!=4) dir=3;break;
						case 'd':if(dir!=3) dir=4;break;
						case ' ':// suspension
						{
							textcolor(7);
							gotoxy(40,42);
							printf("Paused.");
							input='0';
							do
							{	
								if(kbhit()) input=getch();
							}while(input!=' ');
							delay(100);
							gotoxy(40,42);
							printf("       ");
							break;
						}
					}		
					f=process(a,b,&i,&j,&p1,&p2,dir,t0);	//move the snake according to the new direction and see what happens		
				}
				else 
				{
					f=process(a,b,&i,&j,&p1,&p2,dir,t0);	//move the snake according to the direction before and see what happens
				}
				if(f!=2)delay(t0); else{f=0;f0=1;n++;}	
				t+=t0/1000.0;
				gotoxy(0,42);
				textcolor(7);
				printf("Time=%6.1fs, Length=%3d",t,n);
			}
			if(f==0)  //if the snake ate the food, a new piece of food should be created
			{
				if(n<600-s) 
				{
					f1=' ';
					do
					{
						k=rand()%600;
						x=k/30+1;y=k%30+1;
						if(a[x][y]==0&&(b[p1]/100!=x||b[p1]%100!=y)) {a[x][y]=2;f1='0';}
					}while(f1==' ');
					textcolor(13);
					gotoxy(5*y,2*x);
					printf("%2c",5);
				}
				else f=3;
				
			
			}
		}			
		gotoxy(0,42);
		textcolor(7);
		if(f==1) printf("You are dead, Time=%6.1fs, Length=%3d.  Retry?(y/n)",t,n);
		else printf("Wow, your body has filled the screen! Time=%6.1fs, Length=%3d.  Retry?(y/n)",t,n);
		input=' '; // the player input 'y' to restart the game, 'n' to quit
		do
		{
			if(kbhit()) input=getch(); 
		}while(input!='y'&&input!='n');		
	}while(input=='y'); //repeat the game until the player quit
	return 0;
}
