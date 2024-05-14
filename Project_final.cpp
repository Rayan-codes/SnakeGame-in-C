#include<iostream>
#include<conio.h>//for if _kbhit() & for _getch()
#include <windows.h> // For Sleep() function
#include<cstdlib>//library for srand
#include<ctime>//to include time
using namespace std;

int height=15,width=15;//box boundries
int s_x=7,s_y=13;//snakes head dimension
int f_x=4,f_y=3;//fruit dimensions
char move='a',move1='w';//direction of movement
int size=1;//size of snake
int body_x[100],body_y[100];//dimension of body of snake except head
char game_pause;

void control();//cotrol loops and snake head + control most of functions
void snake_movement(int rigid_boundry);//control snake's body and also control head movement
int srand_check();//restrict new fruit to render on snake's body
void srand_fun();//set fruit dimension
void consol_set_handler();//colsole control(remove every thing in console) 
void input();//contain conio's function _kbhit and _getch
int set_level();//take input of level
int game_over(int rigid_boundry);//control game over conditions
int rigid_boundry_fun();//input of walls of container/box

void control()//cotrol loops and snake head + control most of functions
{
	for(int i=1;i<=height;i++)
	{
		for(int j=1;j<=width;j++)
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
			else if(f_x==s_x&&f_y==s_y)//check wheather snake had eaten the fruit or not
			{
				srand_fun();
				size++;
			}
			else if(f_x==j&&f_y==i)//deploy fruit
			{
				cout<<"\033[1;31mF\033[0m";
			}
			else//make snake's body 
			{
				bool body = false;//bool to check how many spaces are needed in current row(for example if snake is taking space of 2 boxes then empty space of 2 box should be reduced. if condition on cout<<" " is given below)
				for(int k=0;k<size;k++)
				{
					if(body_x[k]==j&&body_y[k]==i)
					{
						cout<<"\033[1;33m@\033[0m";
						body = true;//if bool become true 2 times then 2 empty spaces will be reduced
					}
				}
				if(!body)
				{
					cout<<" ";
				}
			}
		}
		cout<<endl;
	}
	cout<<"Your score is: "<<size*10<<endl<<endl;
	cout<<"Snake Head: ("<<s_x<<", "<<s_y<<")"<<endl;//printing snake's dimension to make it easier to find issue in future if needed
    cout<<"Fruit: ("<<f_x<<", "<<f_y<<")"<<endl;//same as above
}
void snake_movement(int rigid_boundry)//control snake's body and also control head movement
{
	static bool isPaused = false;
	if(game_pause==' ')
	{
		
	}
	else
	{
		for (int i = size - 1; i > 0; --i)
   		{		//every body box of snake should follow box next to it(forexample if position of head is 2,2 then in next movement position of body should be 2,2)
        	body_x[i] = body_x[i - 1];
    		body_y[i] = body_y[i - 1];
    	}
	}
	
	
	switch(move)//setting snake movement 
	{
		case 'w':
			s_y--;
			break;
		case 's':
			s_y++;
			break;
		case 'a':
			s_x--;
			break;
		case 'd':
			s_x++;
			break;
		case ' '://to pause game
			isPaused = !isPaused;
			move= move1;
			break;
		default:
			break;
	}
	if(rigid_boundry==2)//to check which type of boundry user had selected
	{		//it should only teleport snake if bounder is teleportable
		switch(s_x)//if snakes dimension on x-axis goes out of the box
		{
			case 15:
				s_x=2;
				break;
			case 1:
				s_x=14;
				break;
		}
		switch(s_y)//if snakes dimension on y-axis goes out of the box
		{
			case 15:
				s_y=2;
				break;
			case 1:
				s_y=14;
				break;
		}
	}
	body_x[0] = s_x;
    body_y[0] = s_y;
}
int srand_check()//restrict new fruit to render on snake's body
{
	for(int i=0;i<size;i++)
	{
		if(f_x==body_x[i]&&f_y==body_y[i]||f_x==s_x&&f_y==s_y)//checking dimension of snake's head and body along with fruit dimension
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
void consol_set_handler()//handle console setter
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console
    CONSOLE_CURSOR_INFO cursorInfo; 
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Hide cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    COORD position = {0, 0}; // Set the cursor position to (0, 0)
    SetConsoleCursorPosition(hConsole, position);
}
void input()//contain conio's function _kbhit and _getch
{
	if(_kbhit())//if keyboard hit(pre defined function in conio)
		{
			move1=_getch();//save input to char(pre defined function in conio)
			game_pause=move1;
		}
		if(move=='w'&&move1=='s'||move=='s'&&move1=='w'||move=='a'&&move1=='d'||move=='d'&&move1=='a')
		{
			system("cls");//clear whole console
			cout<<"\n\n\n\t\tYou can not do in opposite direction!!!";
			Sleep(2000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
			system("cls");//clear whole console
			cout<<"\n\n\n\t\t\tResuming Game in: \n\t\t\t\t3";
			Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
			system("cls");//clear whole console
			cout<<"\n\n\n\t\t\tResuming Game in: \n\t\t\t\t2";
			Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
			system("cls");//clear whole console
			cout<<"\n\n\n\t\t\tResuming Game in: \n\t\t\t\t1";
			Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
			system("cls");//clear whole console
			move1=move;
		}
		else
		{
			move=move1;
		}
}
int set_level()//take input of level
{
	int level;
	cout<<"\n\t\t\tPlease Select Level:\n\t\t\t1.Press '1' for v.easy\n\t\t\t2.Press '2' for easy\n\t\t\t3.Press '3' for medium\n\t\t\t4.Press '4' for dificult\n\t\t\t";
	cin>>level;
	if(level==1)
	{
		level=200;
	}
	else if(level==2)
	{
		level=150;
	}
	else if(level==3)
	{
		level=100;
	}
	else if(level==4)
	{
		level=70;
	}
	else
	{
		cout<<"\n\n\n\t\t\tInvalid Input!!!\n\n";
		Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
		set_level();
	}
	
	system("cls");//clear whole console
	cout<<"\n\n\n\t\t\tStarting Game in: \n\t\t\t\t3";
	cout<<"\n\n\t\t\tUse WASD to move snake\n\t\t\tPress Space Key to Pause Game"<<endl;
	Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
	system("cls");//clear whole console
	cout<<"\n\n\n\t\t\tStarting Game in: \n\t\t\t\t2";
	cout<<"\n\n\t\t\tUse WASD to move snake\n\t\t\tPress Space Key to Pause Game"<<endl;
	Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
	system("cls");//clear whole console
	cout<<"\n\n\n\t\t\tStarting Game in: \n\t\t\t\t1";
	cout<<"\n\n\t\t\tUse WASD to move snake\n\t\t\tPress Space Key to Pause Game"<<endl;
	Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
	system("cls");//clear whole console
	
	return level;
}
int game_over(int rigid_boundry)//control game over conditions
{
	for(int i=1;i<size;i++)
	{
		if(body_x[i]==s_x&&body_y[i]==s_y)//if snake's head conside with its body
		{
			system("color 4");
			Sleep(2000);
			system("color F");
			system("cls");//to clear console
			cout<<"\n\n\n\t\t\033[1;31mGAME OVER!\033[0m\n";
			return 2;
		}
	}
	if(rigid_boundry==1)//checking type of box walls selected by user
		{
			if(s_x==1||s_x==15||s_y==1||s_y==15)//if snake hit boundry of box
			{
				system("color 4");
				Sleep(2000);
				system("color F");
				system("cls");//to clear console
				cout<<"\n\n\n\t\t\033[1;31mGAME OVER!\033[0m\n";
				return 2;
			}
		}
	return 1;
}
int rigid_boundry_fun()//input of walls of container/box
{
	int a;
	cout<<"\t\t\tWhat type of boundry you want: "<<endl;
	cout<<"\t\t\t1.Press '1' for Fix Boundries\n\t\t\t2.Press'2' for Teleportable Boundries\n\t\t\t";
	cin>>a;
	return a;
}

int main()
{
	int i=1,level=0,rigid_boundry;
	rigid_boundry = rigid_boundry_fun();//rigid_boundry_fun() called and is set equal to varible rigid_boundry
	system("cls");
	level=set_level();//set varible level equal to value returned from function set_level()
	
	do//do while loop to make snake repeatedly so it seems like moving
	{
		consol_set_handler(); // Clear the console
		input();
		control();//function called
		snake_movement(rigid_boundry);//setting dimension of snake accourding to input
		Sleep(level);//it stop program accourding to level set(control the speed of do-while loop)
		consol_set_handler(); // Clear the console
		i=game_over(rigid_boundry);// i control do-while loop
	}while(i==1);
	
	//program ends here
	return 0;
}
