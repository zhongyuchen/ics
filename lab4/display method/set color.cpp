#include <stdio.h>  
#include <windows.h>  
#include <iostream>  
using namespace std;  
  
int main(void)   
{  
   cout<<"original"<<endl;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
   cout<<"intensity"<<endl;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY |
FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
   cout<<"intensity white"<<endl;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);  
   cout<<"green no inten"<<endl;
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN|FOREGROUND_INTENSITY);  
   cout<<"green inten"<<endl;
   cout<<"zhangzhe"<<endl;  
   printf("TestA");  
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);  
   printf("TestB");  
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), /*FOREGROUND_INTENSITY | */FOREGROUND_BLUE);   
   printf("TestC");  
  
   cout<<"now"<<endl;
   
   return 0;  
}   
