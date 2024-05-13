#include<iostream>
#include<conio.h>//for if _kbhit() & for _getch()
#include <windows.h> // For Sleep() function
#include<cstdlib>//library for srand
#include<ctime>//to include time
using namespace std;

class data{
	private:
		static const int height=15;
		static const int width=15;//box boundries areconstant because they are needed not to be changed
		int s_x;
		int s_y;//snakes head dimension
		int f_x;
		int f_y;//fruit dimensions
		char move;
		char move1;//direction of movement
		int size;//size of snake
		int *body_x;
		int *body_y;//dimension of body of snake except head
		char game_pause;
		//------
	
	public:
		data(): s_x(7),s_y(13),f_x(4),f_y(3),move('a'),move1('w'),size(1) 
		{
			body_x=new int[100];//memory allocated to dynamic arrays
			body_y=new int[100];
		}
		
		int get_height()
		{
			return height;
		}
		int get_width()
		{
			return width;
		}
		int get_s_x()
		{
			return s_x;
		}
		int get_s_y()
		{
			return s_y;
		}
		int get_f_x()
		{
			return f_x;
		}
		int get_f_y()
		{
			return f_y;
		}
		char get_move()
		{
			return move;
		}
		char get_move1()
		{
			return move1;
		}
		int get_size()
		{
			return size;
		}
		int get_body_x(int i)
		{
			return body_x[i];
		}
		int get_body_y(int i)
		{
			return body_y[i];
		}
		char get_game_pause()
		{
			return game_pause;
		}
		//----------------
		void set_s_x(int i)
		{
			s_x=i;
		}
		void set_s_y(int i)
		{
			s_y=i;
		}
		void set_f_x(int i)
		{
			f_x=i;
		}
		void set_f_y(int i)
		{
			f_y=i;
		}
		void set_move(char i)
		{
			move=i;
		}
		void set_move1(char i)
		{
			move1=i;
		}
		void set_size(int i)
		{
			size=i;
		}
		void set_body_x(int i,int j)
		{
			body_x[j]=i;
		}
		void set_body_y(int i,int j)
		{
			body_y[j]=i;
		}
		void set_game_pause(char i)
		{
			game_pause=i;
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
};
class snake_movements: public data {//inheritance from class data
	private:
		
	public:
		void srand_fun()//set fruit dimension
		{
			int x;
			do
			{
				srand(time(0));
				set_f_x(rand()% 13+2);
				//f_x=rand()% 13+2;
				set_f_y(rand()% 13+2);
				//f_y=rand()% 13+2;
				x=srand_check();//calling srand_check
			}while(x==1);//it should generate new dimension fir fruit if fruit is rendring on snake
		
		}
		void control()//cotrol loops and snake head + control most of functions
		{
			for(int i=1;i<=get_height();i++)
			{
				for(int j=1;j<=get_width();j++)
				{
					if(i==1)//first row
					{
						cout<<"_";
					}
					else if(i==get_height()&&i<=get_width())//last row
					{
						cout<<"-";
					}
					else if(j==1||j==get_width())//for columns
					{
						cout<<"|";
					}
					else if(get_f_x()==get_s_x()&&get_f_y()==get_s_y())//check wheather snake had eaten the fruit or not
					{
						srand_fun();
						set_size(get_size()+1);
					}
					else if(get_f_x()==j&&get_f_y()==i)//deploy fruit
					{
						cout<<"\033[1;31mF\033[0m";
					}
					else//make snake's body 
					{
						bool body = false;//bool to check how many spaces are needed in current row(for example if snake is taking space of 2 boxes then empty space of 2 box should be reduced. if condition on cout<<" " is given below)
						for(int k=0;k<get_size();k++)
						{
							if(get_body_x(k)==j&&get_body_y(k)==i)
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
			cout<<"Your score is: "<<get_size()*10<<endl<<endl;
			cout<<"Snake Head: ("<<get_s_x()<<", "<<get_s_y()<<")"<<endl;//printing snake's dimension to make it easier to find issue in future if needed
  		 	cout<<"Fruit: ("<<get_f_x()<<", "<<get_f_y()<<")"<<endl;//same as above
		}

int main()
{
	snake_movements s1;
	int i=1,level=0,rigid_boundry;
	rigid_boundry = s1.rigid_boundry_fun();//rigid_boundry_fun() called and is set equal to varible rigid_boundry
	system("cls");
	level=s1.set_level();//set varible level equal to value returned from function set_level()
	

	
	do{
		s1.consol_set_handler(); // Clear the console
		s1.input();
		s1.control();//function called
		s1.snake_movement(rigid_boundry);//setting dimension of snake accourding to input
		Sleep(level);//it stop program accourding to level set(control the speed of do-while loop)
		s1.consol_set_handler(); // Clear the console
		i=s1. game_over(rigid_boundry);// i control do-while loop
	} while(i==1);
	


	return 0;
}


