#include<iostream>//input output
#include<conio.h>//if input fails
#include<cstdlib>//srand
#include<ctime>//time for srand
#include<windows.h>//sleep and console handling
using namespace std;

int loop=1,height=15,width=15;//intergers for making boundries
int dimension_x=7,dimension_y=7;//integers for saving snakes location/axis
int size=1;//snake's size
char mov='w',mov1='w';
int fruit_x=6,fruit_y=7;//fruit dimension
int tail_x[100],tail_y[100];
int a_1,a_2,b_1,b_2;

void fruit(int x,int y)
{
	if(fruit_x==y&&fruit_y==x)
	{
		srand(time(0));
		fruit_x=rand() % 13+3;
		fruit_y=rand() % 13+3;
		size++;
	}
}
void boundries()
{
	for(int i=1;i<=height;i++)
	{
		for(int j=1;j<=width;j++)
		{
			if(i==1||i==height||j==1||j==width)
			{
				cout<<"*";
			}
			else if(dimension_x==j&&dimension_y==i)
			{
				for(int k=1;k<=size;k++)
				{
					if(size==1)
					{
						cout<<"%";//head of snake
					}
					else
					{
						for(int l=0;l<size;l++)
						{
							if(tail_x[i]==i&&tail_y[i]==j)
							{
								cout<<"%";
							}
							cout<<endl;
						}
					}
				}
				fruit(i,j);
			}
			else if(fruit_x==j&&fruit_y==i)
			{
				cout<<"F";
			}
			else
			{
				cout<<" ";
			}
			a_1=i;
			b_1=j;
		}
		cout<<endl;

	}
	if(dimension_x<=1)
    {
        dimension_x = width-1;
    }
    if(dimension_y<=1)
    {
        dimension_y=height-1;
    }
    if(dimension_x>width-1)
    {
        dimension_x = 1;
    }
    if(dimension_y>height-1)
    {
        dimension_y = 1;
    }
}
void console(HANDLE hConsole)//restrict compiler to use next lines
{
	COORD position = {0, 0}; // Set the cursor position to (0, 0)
    SetConsoleCursorPosition(hConsole, position);

}
void movements()
{
	if(_kbhit())
	{
		mov1=_getch();
	}
	mov=mov1;
	
	for (int i=0;i<size;i++) 
	{
        a_1=tail_x[i];
        a_2=tail_y[i];
        tail_x[i]=b_1;
        tail_y[i]=b_2;
        b_1=a_1;
        b_2=a_2;
    }
	
	switch(mov)
	{
		case's':
			dimension_y++;
			break;
		case'w':
			dimension_y--;
			break;
		case'a':
			dimension_x--;
			break;
		case'd':
			dimension_x++;
			break;
		default:
			break;
	}
}
int main()
{
	int level;
	cout<<"Enter Speed Level: "<<endl;
	cout<<"1 for easy"<<endl<<"2 for medium"<<endl<<"3 for hard"<<endl;
	cin>>level;
	if(level==1)
	{
		level=150;
	}
	if(level==2)
	{
		level=100;
	}
	if(level==3)
	{
		level=50;
	}
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console
    CONSOLE_CURSOR_INFO cursorInfo; 
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Hide cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    console(hConsole);
	do
	{
		
		boundries();
		movements();
		console(hConsole);
		//cout<<"Your score is: "<<(size-1)*10<<endl;
		console(hConsole);
		Sleep(level);
	}while(loop==1);
	
	
	return 0;
}
