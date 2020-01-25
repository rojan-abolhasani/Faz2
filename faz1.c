#include<stdio.h>
#include<windows.h>
#include<conio.h>
#define N 4
typedef struct
{
	int x;
	int y;
}Location;
int findPath (int x, int y, Location end, int path[N][N], int map[N][N])
{
	if (!map[y][x])
		return 0;
	path[y][x]=1;
	if (x==end.y && y==end.x)
		return 1;
	if (y+1<N)
		if (!path[y+1][x])
			if (findPath(x,y+1,end,path,map))
				return 1;

	if (x+1<N)
		if (!path[y][x+1])
			if (findPath(x+1,y,end,path,map))
				return 1;
				
	if (x>0)
		if (!path[y][x-1])
			if (findPath(x-1,y,end,path,map))
				return 1;
				
	if (y>0)
		if (!path[y-1][x])
			if (findPath(x,y-1,end,path,map))
				return 1;
	
	path[y][x]=0;
	return 0;
}
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleCursorPosition( handle, coord);
}
void move (Location start, int path[N][N], int food[N][N])
{
	Location end=start;
	int flag=0;
	do
	{
		flag=0;
		path[start.x][start.y]=0;
		if (path[start.x+1][start.y]==1 && start.x+1<N)
		{
			end.x=start.x+1;
			flag=1;
			goDown(end,food);
		}
		else if (path[start.x-1][start.y]==1 && start.x>0)
		{
			end.x=start.x-1;
			flag=1;
			goUp(end,food);
		}
		else if (path[start.x][start.y+1]==1 && start.y+1<N)
		{
			end.y=start.y+1;
			flag=1;
			goRight(end,food);
		}
		else if (path[start.x][start.y-1]==1 && start.y>0)
		{
			end.y=start.y-1;
			flag=1;
			goLeft(end,food);
		}
		start=end;
	}while (flag);		
}
void goRight(Location end, int food[N][N])
{
	if (food[end.x][end.y]==1)
		food[end.x][end.y]=0;
	int temp=end.x;
	end.x=end.y*4;
	end.y=temp*2;
	sleep(1);
	gotoxy(end.x,end.y);
	printf("\b\b\b\b%s","1   0");
}
void goLeft(Location end, int food[N][N])
{
	if (food[end.x][end.y]==1)
		food[end.x][end.y]=0;
	int temp=end.x;
	end.x=end.y*4;
	end.y=temp*2;
	sleep(1);
	gotoxy(end.x,end.y);
	printf("0   1");
}
void goUp(Location end, int food[N][N])
{
	if (food[end.x][end.y]==1)
		food[end.x][end.y]=0;
	int temp=end.x;
	end.x=end.y*4;
	end.y=temp*2;
	sleep(1);
	gotoxy(end.x,end.y+2);
	printf("1");
	gotoxy(end.x,end.y);
	printf("0");
}
void goDown(Location end, int food[N][N])
{
	if (food[end.x][end.y]==1)
		food[end.x][end.y]=0;
	int temp=end.x;
	end.x=end.y*4;
	end.y=temp*2;
	sleep(1);
	gotoxy(end.x,end.y-2);
	printf("1");
	gotoxy(end.x,end.y);
	printf("0");
}
int main()
{
	FILE *fp=fopen("testcase01.txt","w");
	fprintf(fp,"1   #   0   #\n\n1   1   1   1\n\n*   #   *   #\n\n1   *   1   *\n\n");
	fclose(fp);
	Location start, end;
	char Matrix[N][N], ch;
	int i, j, food[N][N]={0}, path[N][N]={0}, map[N][N], l , k;
	for (i=0;i<N;i++)
		for (j=0;j<N;j++)
			map[i][j]=1;
	fp=fopen("testcase01.txt","r");
	for (i=0;i<N;i++)
	{
		for (j=0;j<N;j++)
		{
			fscanf(fp," %c", &Matrix[i][j]);
			if (Matrix[i][j]=='*')
				food[i][j]=1;
			if (Matrix[i][j]=='#')
				map[i][j]=0;
			if (Matrix[i][j]=='0')
			{
				start.x=i;
				start.y=j;
			}
			printf("%c   ", Matrix[i][j]);	
		}
		printf("\n\n");
	}
	fclose(fp);
	for (i=0;i<N;i++)
		for (j=0;j<N;j++)
		{
			if (food[i][j]==1)
			{
				end.x=i;
				end.y=j;
				findPath(start.y,start.x,end,path,map);
				gotoxy(0,13);
				/*for (l=0;l<N;l++)
				{
					for (k=0;k<N;k++)
						printf("%d   ", path[l][k]);
					printf("\n\n");
				}*/
						
				move(start,path,food);
				start=end;
				for (l=0;l<N;l++)
					for (k=0;k<N;k++)
						path[l][k]=0;
			}
		}
	gotoxy(12,6);
}
//

