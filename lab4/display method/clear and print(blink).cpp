#include<iostream>
#include<Windows.h>
using namespace std;

int main()
{
	int i,j;
	while(1)
	{
		for(i=0;i<20;i++)
		{
			for(j=0;j<100;j++)
				cout<<"*";
			cout<<endl;
		}
		system("cls");
	}
}
