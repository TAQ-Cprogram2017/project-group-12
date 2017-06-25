#ifndef _SNAKE_
#define _SNAKE_


void gotoxy(int x,int y);
void textcolor(int color);
void delay(int msec);
int move(int* i,int* j,int dir,int a[22][32]);
int initialize(int a[22][32]);
int process(int a[22][32],int b[600],int *i,int *j,int *p1,int *p2,int dir,int t0);

#endif
