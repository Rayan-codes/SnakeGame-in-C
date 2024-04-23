//this code help in handling of console(it clear required part of console)
#include<iostream>
#include <windows.h>//header file for functions used in fun console_handle
using namespace std;
void consol_set_handle()//handle console setter
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get handle to console
    CONSOLE_CURSOR_INFO cursorInfo; 
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // Hide cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
    COORD position = {0, 0}; // Set the cursor position to (0, 0)
    SetConsoleCursorPosition(hConsole, position);
}
int main()
{
	cout<<"This is example of handling console. "<<endl;
	cout<<"Wait 10 sec"<<endl;
	Sleep(10000);
	consol_set_handle();
	cout<<"Now this has been over write on previous one by removing it."<<endl;
	cout<<"Team AL_FAEDA"<<endl;

	return 0;
}

