#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

char scan(char a[18][32],char b[18][32]);

#define t1 150  //interval time
#define t2 150

void gotoxy(int x,int y)
{
	HANDLE hOutput;
	COORD loc;
	loc.X=x;
	loc.Y=y;
	hOutput=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput,loc);
}

void textcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void delay(int msec)
{
	time_t now,start;
	start=clock();
	do
	    now=clock();
	while(now-start<msec);
}

void display()
{
	int i,j;
	system("cls");
	textcolor(7); 
  	printf("     ");
    for(i=1;i<=30;i++)
  	    printf(" %2d ",i);
  	printf("\n    ");
  	for(i=1;i<=30;i++)
	    printf("----");
    printf("-\n");
	for(i=1;i<=16;i++)
	{
		printf("%2d  |",i);
		for(j=1;j<=30;j++)
		    printf("   |");			
		printf("\n    ");
		for(j=1;j<=30;j++)
		    printf("----");
		printf("-\n");
	}
}

int check1(char a[18][32],int i, int j)   //check when initializing
{
	int n1,n2,x,y;
	x=i;y=j;n1=1;
	while(a[x-1][y]==a[i][j])		//check upwards
	{
		x--;n1++;
	}
	x=i;y=j;n2=1;
	while(a[x][y-1]==a[i][j])		//check tiles to the left
	{
		y--;n2++;
	}
	if(n1>=n2) return n1; else return n2;
}

void highlight(int x, int y,char z)		//print the frame 
{
	if(z=='w') textcolor(7); else if(z=='b') textcolor(9); else if(z=='r') textcolor(4); else textcolor(10);
	gotoxy(4*y,2*x-1);
	printf("-----");
	gotoxy(4*y,2*x);
	printf("|");
	gotoxy(4*y+4,2*x);
	printf("|");
	gotoxy(4*y,2*x+1);
	printf("-----");
}

void swapblocks(char a[18][32],int x, int y, char input)
{
	int temp;
	highlight(x,y,'b');		//change the red frame to blue
	switch(input)
	{
		case 'w':
		{
			highlight(x-1,y,'b'); delay(t2); 				//highlight the tile to the left
			temp=a[x-1][y];a[x-1][y]=a[x][y];a[x][y]=temp;		//swap colors
			gotoxy(4*y+2,2*x); printf(" ");					//the two tiles disappear for a moment
			gotoxy(4*y+2,2*x-2); printf(" ");
			delay(t2);
			textcolor(a[x][y]); gotoxy(4*y+2,2*x); printf("%d",a[x][y]-10);		//the swapped tiles appear again 
			textcolor(a[x-1][y]); gotoxy(4*y+2,2*x-2); printf("%d",a[x-1][y]-10);
			delay(t2); highlight(x,y,'w');			//the frame turns to white
			highlight(x-1,y,'w'); 
			break;	
		}
		case 's':
		{
			highlight(x+1,y,'b'); delay(t2); 
			temp=a[x+1][y];a[x+1][y]=a[x][y];a[x][y]=temp;
			gotoxy(4*y+2,2*x); printf(" ");
			gotoxy(4*y+2,2*x+2); printf(" ");
			delay(t2);
			textcolor(a[x][y]); gotoxy(4*y+2,2*x); printf("%d",a[x][y]-10);
			textcolor(a[x+1][y]); gotoxy(4*y+2,2*x+2); printf("%d",a[x+1][y]-10);
			delay(t2); highlight(x,y,'w');
			highlight(x+1,y,'w'); 
			break;	
		}
		case 'a':
		{
			highlight(x,y-1,'b'); delay(t2); 
			temp=a[x][y-1];a[x][y-1]=a[x][y];a[x][y]=temp;
			gotoxy(4*y+2,2*x); printf(" ");
			gotoxy(4*y-2,2*x); printf(" ");
			delay(t2);
			textcolor(a[x][y]); gotoxy(4*y+2,2*x); printf("%d",a[x][y]-10);
			textcolor(a[x][y-1]); gotoxy(4*y-2,2*x); printf("%d",a[x][y-1]-10);
			delay(t2); highlight(x,y,'w');
			highlight(x,y-1,'w'); 
			break;	
		}
		case 'd':
		{
			highlight(x,y+1,'b'); delay(t2); 
			temp=a[x][y+1];a[x][y+1]=a[x][y];a[x][y]=temp;
			gotoxy(4*y+2,2*x); printf(" ");
			gotoxy(4*y+6,2*x); printf(" ");
			delay(t2);
			textcolor(a[x][y]); gotoxy(4*y+2,2*x); printf("%d",a[x][y]-10);
			textcolor(a[x][y+1]); gotoxy(4*y+6,2*x); printf("%d",a[x][y+1]-10);
			delay(t2); highlight(x,y,'w');
			highlight(x,y+1,'w'); 
			break;	
		}
	}
}

void fall(char a[18][32], char b[18][32])		//new tiles fall after eliminating 
{
	int i,j,f;		//f£¨=0£© as a sign of the end of falling
	do
	{
		for(j=1;j<=30;j++)
			if(b[1][j]==1)			//it indicates that this colum has vacant tiles
			{
				i=1;					//check the first vacant tile from above 
				while(a[i][j]!=0) i++;
				if(i!=17)		//i=17 means there's actually no vacant tiles 
				{
					while(i>1)			//the tiles above this vacant tile fall 1 unit
					{
						a[i][j]=a[i-1][j];
						textcolor(a[i][j]);
						gotoxy(4*j+2,2*i);
						printf("%d",a[i][j]-10);
						i--;
					}
					a[1][j]=rand()%5+10;		//a new tile is created from above
					textcolor(a[1][j]);
					gotoxy(4*j+2,2*1);
					printf("%d",a[i][j]-10);
				}
			}
		delay(t1);		
		f=0;
		for(i=16;i>=1&&!f;i--)
			for(j=1;j<=30&&!f;j++)
				if(a[i][j]==0) f=1;
	}while(f);
}

void eliminate(char a[18][32],char b[18][32])		//move away the marked tiles
{
	int i,j,k;
	delay(t2);
	for(i=1;i<=16;i++)
		for(j=1;j<=30;j++)
			if(b[i][j]==2) 
			{
				highlight(i,j,'g');		//the eliminated tiles are marked with green frame
				a[i][j]=0;	
				gotoxy(4*j+2,2*i);
				printf(" ");
			}
	delay(t2);
	for(i=1;i<=16;i++)
		for(j=1;j<=30;j++)
			if(b[i][j]==2) highlight(i,j,'w');		//change the frame back to white 
	delay(t2);
	for(i=16;i>=1;i--)
		for(j=1;j<=30;j++)
			if(b[i][j]==2)
			{
				for(k=i;k>=1;k--) b[k][j]=1;		//all the upper tiles of the eliminated tile needs to be checked next time, marked with 1
			}
	fall(a,b);		//the tiles fall
	scan(a,b);		//the fallen tiles might make other matches
}

char check2(char a[18][32],char b[18][32],int i, int j)		//check during the game
{
	int n1,n2,x,y,f=0;
	x=i;y=j;n1=1;
	while(a[x-1][y]==a[i][j])			//check upwards
	{
		x--;n1++;
	}
	x=i;y=j;
	while(a[x+1][y]==a[i][j])			//check downwards
	{
		x++;n1++;
	}
	x=i;y=j;n2=1;
	while(a[x][y-1]==a[i][j])			//check tiles to the left
	{
		y--;n2++;
	}
	x=i;y=j;
	while(a[x][y+1]==a[i][j])			//check tiles to the right
	{
		y++;n2++;
	}
	if(n1>=3)						//if there are at least 3 identical tiles in a colum 
	{
		x=i;y=j;b[i][j]=2;
		while(a[x-1][y]==a[i][j])			//mark the tiles that will be removed
		{
			x--;b[x][y]=2;
		}
		x=i;y=j;
		while(a[x+1][y]==a[i][j])
		{
			x++;b[x][y]=2;
		}
		f=1;
	}
	if(n2>=3)						//if there are at least 3 identical tiles in a row
	{
		x=i;y=j;b[i][j]=2;
		while(a[x][y-1]==a[i][j])
		{
			y--;b[x][y]=2;
		}
		x=i;y=j;
		while(a[x][y+1]==a[i][j])
		{
			y++;b[x][y]=2;
		}
		f=1;
	}
	if(!f) b[i][j]=0;		//if a tile can't be eliminated after examination, remove the mark 
	return f;			//return a sign of whether any tiles can be removed
}

char scan(char a[18][32],char b[18][32])		//check all tiles that need examination and return a sign of whether any tiles can be removed
{
	char f;
	int i,j;
	for(i=1;i<=16;i++)
		for(j=1;j<=30;j++)
			if(b[i][j]==1) f+=check2(a,b,i,j);
	if(f) eliminate(a,b);
	return f;	
}

int main()
{
	char a[18][32]={0},b[18][32]={0};//16*30 there are additional 2 rows and colums for convenience
	char input='w';
	int i,j,n,x,y;
	srand(time(0));
	display();// print the grid 
	for(i=1;i<17;i++)
		for(j=1;j<31;j++)
		{
			do
			{
				a[i][j]=rand()%5+10;//randomly create colors£º10-14 
				n=check1(a,i,j);//check whether there are a match-3, n is the number of identical tiles
			}while(n>=3);
			textcolor(a[i][j]);
			gotoxy(4*j+2,2*i);
			printf("%d",a[i][j]-10);
		} 
	x=8;y=15;
	highlight(x,y,'b');//mark the tile with blue frame
	while(1)
	{
		do //choose the first tile, marked with red frame
		{
			if(kbhit())
			{
				input=getch();
				switch(input)
				{
					case 'w':highlight(x,y,'w'); if(x>1) x--; highlight(x,y,'b'); break;
					case 's':highlight(x,y,'w'); if(x<16) x++; highlight(x,y,'b'); break;
					case 'a':highlight(x,y,'w'); if(y>1) y--; highlight(x,y,'b'); break;
					case 'd':highlight(x,y,'w'); if(y<30) y++; highlight(x,y,'b'); break;
					case ' ':highlight(x,y,'r'); break;
				}
			}
		}while(input!=' ');
		do //choose the second tile 
		{
			if(kbhit()) input=getch();
		}while(!(input=='w'&&x>1||input=='a'&&y>1||input=='s'&&x<16||input=='d'&&y<30));
		swapblocks(a,x,y,input);//swap the two tiles
		b[x][y]=1;			//the two tiles are to be examined
		switch(input)
		{
			case 'w':b[x-1][y]=1;break;
			case 's':b[x+1][y]=1;break;
			case 'a':b[x][y-1]=1;break;
			case 'd':b[x][y+1]=1;break;
		}
		if(!scan(a,b)) swapblocks(a,x,y,input);		//if the swap doesn't make a match-3, swap back 
		highlight(x,y,'b');//recover the blue frame
	}
}
