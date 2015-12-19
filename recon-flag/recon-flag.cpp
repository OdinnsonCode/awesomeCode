/****************************
* Recon Flag Visualizer     *
* (c) Mikko Odinsson, 2015  *
* For private use only      *
*****************************/
#include "stdafx.h"
COORD * array;
void Randomize(COORD* a, int size);
void SetSize(HANDLE h, int x, int y);
void DownChar(HANDLE h,int x, int y);
void DownScreen(HANDLE h);
int main(int argc, char* argv[])
{
	DWORD len;
	HANDLE h;
	srand((unsigned int)time(NULL));
	h=GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitleA("Adventure Time");
	SetSize(h,80,40);
	WriteConsoleA(h,First,strlen(First),&len,NULL);
	WriteConsoleA(h,Second,strlen(Second),&len,NULL);
	WriteConsoleA(h,Third,strlen(Third),&len,NULL);
	DownScreen(h);	
	getchar();
	delete[] array;
	return 0;
}

void SetSize(HANDLE h, int x, int y)
{
	COORD size={x,y};
	SetConsoleScreenBufferSize(h,size);
	ShowWindow( GetConsoleWindow() , SW_MAXIMIZE);
	array = new COORD[x*y];
	for(int i=0; i<y; i++)
	{
		int k=i*x;
		for(int j=0;j<x;j++)
		{
			array[k+j].X=j;
			array[k+j].Y=i;
		}
	}
	for (int i=0; i<sizeof disp/sizeof (int); i++)
	{
		array[disp[i]].X=0;
		array[disp[i]].Y=0;
	}
    Randomize(array, x*y);
}
void Randomize(COORD* a, int size)
{
	for(int i=size-1; i>0; i--)
	{
			int r = rand()%i;
			COORD tmp = array[i];
			array[i]=array[r];
			array[r] = tmp;
	}
}

void DownScreen(HANDLE h)
{
	CONSOLE_SCREEN_BUFFER_INFO inf;
	DWORD len;
	COORD pos;
	char c;
	GetConsoleScreenBufferInfo(h,&inf);
	for (int i=0; i<inf.dwSize.X*inf.dwSize.Y;i++)
	{
		    pos=array[i];
			ReadConsoleOutputCharacterA(h,&c,1,pos,&len);
			if (c!=' ') DownChar(h,pos.X,pos.Y);
	}
}
void DownChar(HANDLE h,int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO inf;
	DWORD len;
	COORD pos={x,y};
	char c,c1;
	GetConsoleScreenBufferInfo(h,&inf);
	ReadConsoleOutputCharacterA(h,&c,1,pos,&len);
	WriteConsoleOutputCharacterA(h," ",1,pos,&len);
	while (pos.Y<inf.dwSize.Y)
	{
		pos.Y++;
		ReadConsoleOutputCharacterA(h,&c1,1,pos,&len);
		WriteConsoleOutputCharacterA(h,&c,1,pos,&len);
		Sleep(30);
		if ((pos.Y<inf.dwSize.Y-1))WriteConsoleOutputCharacterA(h,&c1,1,pos,&len);
	}
}
