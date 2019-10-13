#include <stdio.h>
#include <iostream>
#include <Windows.h>
 using namespace std;
int main()
{
		COORD coord;
		//双缓冲处理显示
		DWORD bytes;
		//控制台屏幕缓冲区句柄

		HANDLE hOutput = CreateConsoleScreenBuffer(
			GENERIC_WRITE,//定义进程可以往缓冲区写数据
			FILE_SHARE_WRITE,//定义缓冲区可共享写权限
			NULL,
			CONSOLE_TEXTMODE_BUFFER,
			NULL
		);
		cout<<"fuck"<<endl;
		string s[3];
		s[0]="0";
		s[1]="1";
		s[2]="2";
		
		coord.X = 0;
		coord.Y = 0;
		bytes = 0;
		for (int i = 0; i < 3; i++)
		{
			coord.Y = i;
			WriteConsoleOutputCharacterA(hOutput, s[i].c_str(), s[i].size(), coord, &bytes);
		}
		SetConsoleActiveScreenBuffer(hOutput);
		Sleep(1000);
		//CloseHandle(hOutput);
		SetConsoleTextAttribute(hOutput, bInfo.wAttributes); // 恢复原来的属性
		cout<<"fuck you!"<<endl;
		
}
