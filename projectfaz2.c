#include<stdio.h>
#include<windows.h>
#include<conio.h>
typedef struct
{
	int x;
	int y;
}Location;
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleCursorPosition( handle, coord);
}
int goUp(Location end, int food, int obstacle)
{
	int flag=0;
	if (food)
	{
		gotoxy(0,10);
		flag=1;
		printf("Pacman ate food!");
	}
	if (obstacle)
	{
		gotoxy(0,10);
		printf("You can't move up! There is an obstacle");
		return 2;
	}
	gotoxy(end.x,end.y+2);
	printf("1");
	gotoxy(end.x,end.y);
	printf("0");
	if (flag)
		return 1;
	return 0;
}
int goDown(Location end, int food, int obstacle)
{
	int flag=0;
	if (food)
	{
		flag=1;
		gotoxy(0,10);
		printf("Pacman ate food!");
	}
	if (obstacle)
	{
		gotoxy(0,10);
		printf("You can't move down! There is an obstacle");
		return 2;
	}
	gotoxy(end.x,end.y-2);
	printf("1");
	gotoxy(end.x,end.y);
	printf("0");
	if (flag)
		return 1;
	return 0;
}
int goLeft(Location end, int food, int obstacle)
{
	int flag=0;
	if (food)
	{
		gotoxy(0,10);
		flag=1;
		printf("Pacman ate food!");
	}
	if (obstacle)
	{
		gotoxy(0,10);
		printf("You can't move to left! There is an obstacle");
		return 2;
	}
	gotoxy(end.x,end.y);
	printf("0   1");
	if (flag)
		return 1;
	return 0;
}
int goRight(Location end, int food, int obstacle)
{
	int flag=0;
	if (food)
	{
		gotoxy(0,10);
		flag=1;
		printf("Pacman ate food!");
	}
	if (obstacle)
	{
		gotoxy(0,10);
		printf("You can't move to right! There is an obstacle");
		return 2;
	}
	gotoxy(end.x,end.y);
	printf("\b\b\b\b1   0");
	if (flag)
		return 1;
	return 0;
}
int main()
{
	FILE *fp;
	Location start, end;
	int i, j, key, foodNum=0;
	char Matrix[5][10], ch, food[5][10]={0}, obstacle[5][10]={0};
	fp=fopen("testcase02.txt","r");
	for (i=0;i<5;i++)
	{
		for (j=0;j<10;j++)
		{
			fscanf(fp,"%c", &Matrix[i][j]);
			ch=getc(fp);
			if (Matrix[i][j]=='*')
			{
				food[i][j]=1;
				foodNum++;
			}
			else if (Matrix[i][j]=='#')
				obstacle[i][j]=1;
			else if (Matrix[i][j]=='0')
			{
				start.x=j*4;
				start.y=i*2;
			}
			printf("%c   ", Matrix[i][j]);		
		}
		printf("\n\n");		
	}
	fclose(fp);
	gotoxy(start.x,start.y);
	key=getch();
	while (key==224)
		key=getch();
	while(key!=-1 && foodNum>0)
	{
		int flag=0, flagFood=0, flagObstacle=0, result;
		gotoxy(start.x,start.y);
		switch(key)
		{
			case 72:
				end.x=start.x;
				end.y=start.y-2;
				if (end.y<0)
				{
					flag=1;
					break;
				}
				result=goUp(end,food[end.y/2][end.x/4],obstacle[end.y/2][end.x/4]);
				if (result==2)
				{
					flag=1;	flagObstacle=1;
				}
				else if (result==1)
				{
					foodNum--;
					flagFood=1;
				}
				break;
			case 80:
				end.x=start.x;
				end.y=start.y+2;
				if (end.y>8)
				{
					flag=1;
					break;
				}
				result=goDown(end,food[end.y/2][end.x/4],obstacle[end.y/2][end.x/4]);
				if (result==2)
				{
					flag=1;	flagObstacle=1;
				}
				else if (result==1)
				{
					foodNum--;
					flagFood=1;
				}
				break;
			case 75:
				end.x=start.x-4;
				end.y=start.y;
				if (end.x<0)
				{
					flag=1;
					break;
				}
				result=goLeft(end,food[end.y/2][end.x/4],obstacle[end.y/2][end.x/4]);
				if (result==2)
				{
					flag=1;	flagObstacle=1;
				}
				else if (result==1)
				{
					foodNum--;
					flagFood=1;
				}
				break;
			case 77:
				end.x=start.x+4;
				end.y=start.y;
				if (end.x>36)
				{
					flag=1;
					break;
				}
				result=goRight(end,food[end.y/2][end.x/4],obstacle[end.y/2][end.x/4]);
				if (result==2)
				{
					flag=1;	flagObstacle=1;
				}
				else if (result==1)
				{
					foodNum--;
					flagFood=1;
				}
				break;		
		}
		if (foodNum==0)
		{
			gotoxy(0,10);
			printf("                                                      ");
			gotoxy(0,10);
			printf("Pacman finished eating!");
			break;
		}
		if (flag && !flagObstacle)
		{
			gotoxy(0,10);
			printf("                                                      ");
			gotoxy(start.x,start.y);
		}
		if (flag==0)
			start=end;
		do
		{
			key=getch();
		}while(key==224);
		if (key==49)
		{
			gotoxy(0,10);
			printf("                                                      ");
			gotoxy(0,10);
			printf("Finished!");
			break;			
		}
		else if (flagObstacle || flagFood)
		{
			gotoxy(0,10);
			printf("                                                      ");
			gotoxy(start.x,start.y);
		}
	}
}
