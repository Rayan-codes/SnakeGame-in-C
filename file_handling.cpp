#include<iostream>//input/output stream
#include<conio.h>//for if _kbhit() & for _getch()
#include <windows.h> // For Sleep() function
#include<cstdlib>//library for srand
#include<ctime>//to include time
#include <fstream> // file handling
#include<algorithm>//to use sort()
bool compareDescending(int a, int b) 
{
	return a > b;
}
using namespace std;
class data{
	private:
		static const int height=15;
		static const int width=15;//box boundries are constant because they are needed not to be changed
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
			int x;//varible helping in checking fruit should not be render on snakes body
			do
			{
				srand(time(0));
				set_f_x(rand()% 13+2);//fruit should be inside the box
				set_f_y(rand()% 13+2);
				x=srand_check();//calling srand_check
			}while(x==1);//it should generate new dimension for fruit if fruit is rendring on snake
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
		void snake_movement(int rigid_boundry)//control snake's body and also control head movement
		{
			static bool isPaused = false;
			if(get_game_pause()==' ')
			{
				//left empty to pause the game till next input
			}
			else
			{
				for (int i=get_size()-1;i> 0;--i)
   				{		//every body box of snake should follow box next to it(forexample if position of head is 2,2 then in next movement position of body should be 2,2)
   		     		set_body_x(get_body_x(i-1),i);//body_x[i]=body_x[i-1];
   		     		set_body_y(get_body_y(i-1),i);//body_y[i]=body_y[i-1];
   		 		}
			}
			switch(get_move())//setting snake movement 
			{
				case 'w':
					set_s_y(get_s_y()-1);
					break;
				case 's':
					set_s_y(get_s_y()+1);
					//s_y++;
					break;
				case 'a':
					set_s_x(get_s_x()-1);
					//s_x--;
					break;
				case 'd':
					set_s_x(get_s_x()+1);
					//s_x++;
					break;
				case ' '://to pause game
					isPaused = !isPaused;
					set_move(get_move1()) ;
					break;
				default:
					break;
			}
			if(rigid_boundry==2)//to check which type of boundry user had selected
			{		//it should only teleport snake if bounder is teleportable
				switch(get_s_x())//if snakes dimension on x-axis goes out of the box
				{
					case 15:
						set_s_x(2);
						break;
					case 1:
						set_s_x(14);
						break;
				}
				switch(get_s_y())//if snakes dimension on y-axis goes out of the box
				{
					case 15:
						set_s_y(2);
						break;
					case 1:
						set_s_y(14);
						break;
				}
			}
			set_body_x(get_s_x(),0);//body_x[0] = s_x;
			set_body_y(get_s_y(),0);//body_y[0] = s_y;
		}
		int srand_check()//restrict new fruit to render on snake's body
		{
			for(int i=0;i<get_size();i++)
			{
				if(get_f_x()==get_body_x(i)&&get_f_y()==get_body_y(i)||get_f_x()==get_s_x()&&get_f_y()==get_s_y())//checking dimension of snake's head and body along with fruit dimension
				{
					return 1;
				}
			}
			return 0;
		}
		void input()//contain conio's function _kbhit and _getch
		{
			if(_kbhit())//if keyboard hit(pre defined function in conio)
			{
				set_move1(_getch());
				//move1=_getch();//save input to char(pre defined function in conio)
				set_game_pause(get_move1());
				//game_pause=move1;
			}
			if(get_move()=='w'&&get_move1()=='s'||get_move()=='s'&&get_move1()=='w'||get_move()=='a'&&get_move1()=='d'||get_move()=='d'&&get_move1()=='a')
			{
				system("cls");//clear whole console
				cout<<"\n\n\n\t\tYou can not do in opposite direction!!!";
				Sleep(2000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
				system("cls");//clear whole console
				cout<<"\n\n\n\t\t\tResuming Game in: \n\n\t\t\t\t3";
				Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
				system("cls");//clear whole console
				cout<<"\n\n\n\t\t\tResuming Game in: \n\n\t\t\t\t2";
				Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
				system("cls");//clear whole console
				cout<<"\n\n\n\t\t\tResuming Game in: \n\n\t\t\t\t1";
				Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
				system("cls");//clear whole console
				set_move1(get_move());
				//move1=move;
			}
			else
			{
				set_move(get_move1());
				//move=move1;
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
			cout<<"\n\n\n\t\t\tStarting Game in: \n\n\t\t\t\t3";
			cout<<"\n\n\t\t\tUse WASD to move snake\n\t\t\tPress Space Key to Pause Game"<<endl;
			Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
			system("cls");//clear whole console
			cout<<"\n\n\n\t\t\tStarting Game in: \n\n\t\t\t\t2";
			cout<<"\n\n\t\t\tUse WASD to move snake\n\t\t\tPress Space Key to Pause Game"<<endl;
			Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			
			system("cls");//clear whole console
			cout<<"\n\n\n\t\t\tStarting Game in: \n\n\t\t\t\t1";
			cout<<"\n\n\t\t\tUse WASD to move snake\n\t\t\tPress Space Key to Pause Game"<<endl;
			Sleep(1000);//sleep fun is a pre defined function use to stop next output for given milliseconds
			system("cls");//clear whole console
	
			return level;
		}
		int game_over(int rigid_boundry)//control game over conditions
		{
			int q=1;
			for(int i=1;i<get_size();i++)
			{
				if(get_body_x(i)==get_s_x()&&get_body_y(i)==get_s_y())//if snake's head conside with its body
				{
					system("color 4");//to color console red
					Sleep(2000);
					system("color F");//to color console white again
					system("cls");//to clear console
					cout<<"\n\n\n\t\t\033[1;31mGAME OVER!\033[0m\n";
					q=2;
				}
			}
			if(rigid_boundry==1)//checking type of box walls selected by user
			{
				if(get_s_x()==1||get_s_x()==15||get_s_y()==1||get_s_y()==15)//if snake hit boundry of box
				{
					system("color 4");//to color console red
					Sleep(2000);
					system("color F");//to color console white again
					system("cls");//to clear console
					cout<<"\n\n\n\t\t\033[1;31mGAME OVER!\033[0m\n";
					q=2;
				}
			}
			if(q==2)
			{
				system("color 1");
				ifstream inputFile("high_score.txt"); //open the file for reading
				ofstream outputFile("temp.txt"); //open/create a temporary file for writing
				if (inputFile.fail())//if high_score not found
				{
					ofstream createFile("high_score.txt");//create the file if it doesn't exist
					createFile.close();//close the file after creation
					inputFile.open("high_score.txt");
       			}
				int high_score[5]={0,0,0,0,0};
				bool newRecordAdded=false;//bool to check weather high scores saved or not
				if (inputFile.is_open()&&outputFile.is_open()) 
				{
					for(int i=0;i<5;i++)
					{
						inputFile>>high_score[i];//previous high scores are being saving in array
					}
   					sort(high_score,high_score+5, compareDescending);//sort is a predefined function in algorithm which do bubble sorting
   					for(int i=0;i<5;i++)
					{
        				if(!newRecordAdded&&high_score[i]<get_size()*10)//if bool is false & current score is bigger than high scores
						{
            				cout<<"\n\n\t\tCONGRULATIONS\n\tYou had created a new record of: "<<get_size()*10<<endl;
            				high_score[i]=get_size()*10;//current scores saved in array contaning high scores
            				newRecordAdded=true;//bool is converted to true to skip if condition further
        				}
        				
						outputFile<<high_score[i]<<endl;//high scored saved are being saving in a txt document
						
					}
					inputFile.close(); // Close the input file
    				outputFile.close(); // Close the temporary file
    				
    				remove("high_score.txt"); // Remove the original file
    				rename("temp.txt", "high_score.txt"); // Rename the temporary file to the original name
				}
				else
				{
					system("color 1");
					cout<<"\n\n\t\tERROR!\n\t'High Scores' File Not Found!"<<endl;//if any one of file not found or unable to create
				}
			}
			return q;
		}
		int rigid_boundry_fun()//input of walls of container/box
		{
			int a;
			cout<<"\t\t\tWhat type of boundry you want: "<<endl;
			cout<<"\t\t\t1.Press '1' for Fix Boundries\n\t\t\t2.Press'2' for Teleportable Boundries\n\t\t\t";
			cin>>a;
			return a;
		}
};
void check_high_scores()//if user wants to check his high scores
{
	ifstream inputFile("high_score.txt");//open file in reading mode
	if (inputFile.is_open()) 
	{
		cout<<"\t\t\tHigh Scores Are: \n"<<endl;
		int line;
       	while(inputFile>> line)//while loop to print values present in all lines
		{
           	cout<<"\t\t\t\t"<<line<<endl; // Output each line from the file
       	}
       	inputFile.close(); // Close the file after reading
   	} 
	else 
	{
       	cout<<"NO High scores saved.\nPlay game to make a new record"<<endl;
   	}
}
int main()
{
	system("color 1");
	snake_movements s1;
	int i=1,level=0,rigid_boundry;
	int choice;
	cout<<"\t\t\tPress:\n\t\t\t1 to play game\n\t\t\t2 to check high score"<<endl;
	cin>>choice;
	system("cls");
	if(choice==1)
	{
		rigid_boundry=s1.rigid_boundry_fun();//rigid_boundry_fun() called and is set equal to varible rigid_boundry
		system("cls");
		level=s1.set_level();//set varible level equal to value returned from function set_level()
	
		do//do while loop to make snake repeatedly so it seems like moving
		{
			s1.consol_set_handler(); // Clear the console
			s1.input();
			s1.control();//function called
			s1.snake_movement(rigid_boundry);//setting dimension of snake accourding to input
			Sleep(level);//it stop program accourding to level set(control the speed of do-while loop)
			s1.consol_set_handler(); // Clear the console
			i=s1. game_over(rigid_boundry);// i control do-while loop
		}while(i==1);
	}
	if(choice==2)
	{
		check_high_scores();
	}
	cout<<"\033[0m"<<endl;//to color console white
	//program to war gaya

	return 0;
}

