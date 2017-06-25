#ifndef _MINE_SWEEPING_	
#define _MINE_SWEEPING_

void gotoxy(int x,int y);
void textcolor(int color);
void delay(int msec);
void initialize(int x,int y, int a[18][32], int b[18][32], int c[18][32]);
void reveal(int i,int j,char input,int a[18][32],int b[18][32],int c[18][32]);
void display();
void clear(int x,int y);
void highlight(int x,int y);
void wrong(int a[18][32],int b[18][32],int c[18][32]);
int doubleclick(int i,int j,int a[18][32],int b[18][32],int c[18][32]);

#endif
