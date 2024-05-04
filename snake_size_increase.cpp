#include<iostream>
#include <windows.h>//for using pre-defined function Sleep()
#include<cstdlib>//library for srand
#include<ctime>//to include time
#include<conio.h>//for if _kbhit() & for _getch() 
//(_kbhit() & _getch() are explained next in code)

using namespace std;

int height =14;
int width=14;
char move='w';
int f_x=4,f_y=3;//fruit dimensions
int size=1;//size of snake
int body_x[100],body_y[100];//dimension of body of snake except head

void srand_fun();//set fruit dimension
int srand_check();//restrict new fruit to render on snake's body
void snake_movement()
{
	for(int i=1;i<15;i++)
	{
		
		for(int k=size-1;k>0;--k)
   		{		//every body box of snake should follow box next to it(forexample if position of head is 2,2 then in next movement position of body should be 2,2)
        	body_x[k]=body_x[k-1];
    		body_y[k]=body_y[k-1];
    	}
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
			else if(f_x==j&&f_y==i)//deploy fruit
			{
				cout<<"F";
			}
			else if(f_x==body_x[0]&&f_y==body_y[0])//check wheather snake had eaten the fruit or not
			{
				srand_fun();
				size++;
			}
			else//make snake's body 
			{
				bool body = false;//bool to check how many spaces are needed in current row(for example if snake is taking space of 2 boxes then empty space of 2 box should be reduced. if condition on cout<<" " is given below)
				for(int k=0;k<size;k++)
				{
					if(body_x[k]==j&&body_y[k]==i)
					{
						cout<<"@";
						body = true;//if bool become true 2 times then 2 empty spaces will be reduced
					}
				}
				if(!body)
				{
					cout<<" ";
				}
			}
		}
    	if (body_x[0] == width + 1)
		{
   			body_x[0] = 2;
  		}
		else if (body_x[0] == 1)
		{
        	body_x[0] = width;
    	}
    	if (body_y[0] == height + 1) 
		{
        	body_y[0] = 2;
    	} 
		else if (body_y[0] == 1) 
		{
        	body_y[0] = height;
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
			body_y[0]--;
			break;
		case 's':
			body_y[0]++;
			break;
		case 'a':
			body_x[0]--;
			break;
		case 'd':
			body_x[0]++;
			break;
	}
	switch(body_x[0])//if snakes dimension on x-axis goes out of the box
		{
			case 15:
				body_x[0]=2;
				break;
			case 1:
				body_x[0]=14;
				break;
		}
		switch(body_y[0])//if snakes dimension on y-axis goes out of the box
		{
			case 15:
				body_y[0]=2;
				break;
			case 1:
				body_y[0]=14;
				break;
		}
	Sleep(250);//stop console for 250 miliseconds
	system("cls");//clear whole console
	snake_movement();//recursion for infinity loop
}


int srand_check()//restrict new fruit to render on snake's body
{
	for(int i=0;i<size;i++)
	{
		if(f_x==body_x[i]&&f_y==body_y[i]||f_x==body_x[0]&&f_y==body_y[0]||f_x==width-1||f_x==2||f_y==height-1||f_y==2)//checking dimension of snake's head and body along with fruit dimension
		{
			return 1;
		}
	}
	return 0;
}


void srand_fun()//set fruit dimension
{
	int x;
	do
	{
		srand(time(0));
		f_x=rand()% 13+2;
		f_y=rand()% 13+2;
		x=srand_check();//calling srand_check
	
	}while(x==1);//it should generate new dimension fir fruit if fruit is rendring on snake
		
}
int main()
{
	
	body_x[0]=13;
	body_y[0]=7;
	snake_movement();

	return 0;
}

