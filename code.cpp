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
