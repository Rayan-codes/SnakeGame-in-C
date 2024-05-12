#include<iostream>
#include <windows.h>
using namespace std;

int height =14;
int width=14;
int b_x=5;
int b_y=5;

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
				if(b_x==i&&b_y==j)
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
}
int main()
{
	snake_movement();

	return 0;
}

