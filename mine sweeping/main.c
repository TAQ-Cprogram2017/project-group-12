#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include"mine sweeping.h"

int main()
{	
	int i,j,x,y,f,f1,n;
	//i,j are loop variables, x,y are coordinates, f shows what happens after a move(0 for safe, 1 for death, 2 for win, 3 for nothing happening)
	//f1 shows whether a move is done(0 for no, 1 for yes), n indicates the number of mines left
	int a[18][32],b[18][32],c[18][32];
	//a array marks mines on the map(0 for safe, 1 for mine)
	//b array marks the numbers of mines nearby, if the tile(i,j) has a mine, b[i][j]=-1 
	//c array marks whether a tile is discovered(0 for no, 1 for yes)
	char input;// obtain keyboard input
	do// repeat until the player quit
	{
		display();// print the grid
		gotoxy(0,34);// print the total number of mines
		printf("Mines left: %2d",99);
		x=8;y=15;f1=0;n=99; 
		highlight(x,y);	//highlight the tile(8,15) 
		do //the game doesn't start until the player press 'j'
		{
			if(kbhit())
			{
				input=getch();
				switch(input)
				{
					case 'w':clear(x,y); if(x>1) x--; highlight(x,y); break;
					case 's':clear(x,y); if(x<16) x++; highlight(x,y); break;
					case 'a':clear(x,y); if(y>1) y--; highlight(x,y); break;
					case 'd':clear(x,y); if(y<30) y++; highlight(x,y); break;
					case 'j':initialize(x,y,a,b,c); f1=1; break;
					//initialize after the first move to ensure the safety of the first move, mines are randomly created now
				}
			}
		}while (f1==0);
		f=0;
		reveal(x,y,input,a,b,c);//the first move is always safe and needs no judgement
		gotoxy(0,35); //move the cursor away to prevent it from flashing in the grid
		while(f==0||f==3)//the game continues only if the player is safe
		{
			if(f==3) f=0;
			do
			{
				if(kbhit())
				{
					f1=0;
					input=getch();
					switch(input)
					{
						case 'w':clear(x,y); if(x>1) x--; highlight(x,y); break;//move the location of the blue frame that marks the tile you're operating on 
						case 's':clear(x,y); if(x<16) x++; highlight(x,y); break;
						case 'a':clear(x,y); if(y>1) y--; highlight(x,y); break;
						case 'd':clear(x,y); if(y<30) y++; highlight(x,y); break;
						case 'j':f1=1; break;//pressing 'j' is the same as clicking the left side of the mouse(you think a tile as safe)
						case 'k':f1=1; break;//pressing 'k' is the same as clicking the right side of the mouse(you think there's a mine in the tile)
						case ' ':f1=1; break;//pressing ' ' is the same as clicking both sides of the mouse(you think the mines around the tiles have  
						//all been detected) this kind of move doesn't kill you
					}
				}
			}while (f1==0||input!=' '&&c[x][y]==1||input==' '&&c[x][y]==0); //some moves are invalid
			if(input==' ') f=doubleclick(x,y,a,b,c); 
			else if((input=='j'&&a[x][y]==0)||(input=='k'&&a[x][y]==1)) 
			{
				reveal(x,y,input,a,b,c);
				gotoxy(0,35);
				if(input=='k') 
				{
					n--;
					textcolor(7); 
					gotoxy(0,34);
					printf("Mines left: %2d",n);
				}
			}
			else {wrong(a,b,c);f=1;}
			if(f==0) // check if all tiles have been revealed
			{
			    f=1;
			    for(i=1;i<=16;i++)
			        for(j=1;j<=30;j++)
			            f*=c[i][j];
			    if(f) f=2;
			}
		}  
		if(f==2) 
		{
			gotoxy(0,34);
			textcolor(7);
			printf("You are impressive!");
		}
		printf("   Retry?(y/n)");
		input=' ';
		do// the player input 'y' to retry 'n' to quit
		{
			if(kbhit()) input=getch();
		}while(input!='y'&&input!='n');
	}while(input=='y');
	return 0;
}
