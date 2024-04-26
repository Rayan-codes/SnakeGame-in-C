#include<iostream>
#include <windows.h>//for using pre-defined function Sleep()

#include<conio.h>//for if _kbhit() & for _getch() 
//(_kbhit() & _getch() are explained next in code)

using namespace std;

int height =14;
int width=14;
int b_x=5;
int b_y=5;
char move='w';

void snake_movement()
{
	for(int i=1;i<15;i++)
	{
		for(int j=1;j<15;j++)
		{
			if(i==1)//first row
			{
				cout<<"_";
			}
			else if(i==height&&i<=width)//last row
			{
				cout<<"-";
			}
			else if(j==1||j==width)//for columns
			{
				cout<<"|";
			}
			else//make snake's body 
			{
				bool body = false;//bool to check how many spaces are needed in current row(for example if snake is taking space of 2 boxes then empty space of 2 box should be reduced. if condition on cout<<" " is given below)
				if(b_x==j&&b_y==i)
				{
					cout<<"*";
					body = true;//if bool become true 2 times then 2 empty spaces will be reduced
				}
				if(!body)
				{
					cout<<" ";
				}
			}
		}
		cout<<endl;
	}
	if(_kbhit())//if keyboard hit(pre defined function in conio)
	{
		move=_getch();//save input value to char(pre defined function in conio);
	}
	switch(move)//setting snake movement 
	{
		case 'w':
			b_y--;
			break;
		case 's':
			b_y++;
			break;
		case 'a':
			b_x--;
			break;
		case 'd':
			b_x++;
			break;
	}
	switch(b_x)//if snakes dimension on x-axis goes out of the box
		{
			case 15:
				b_x=2;
				break;
			case 1:
				b_x=14;
				break;
		}
		switch(b_y)//if snakes dimension on y-axis goes out of the box
		{
			case 15:
				b_y=2;
				break;
			case 1:
				b_y=14;
				break;
		}
	Sleep(250);//stop console for 250 miliseconds
	system("cls");//clear whole console
	snake_movement();//recursion for infinity loop
}
int main()
{
	snake_movement();

	return 0;
}

