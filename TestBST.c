#include "stdafx.h"
#include <stdlib.h>
#include "BinarySearchTree.h"
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define XSIZE 100
#define YSIZE 1000

char* gI = "Insert : ";
char* gO = "Delete : ";
char* gQ0 = "1)Insert, 2)Delete : ";
char* gQ1 = "InsertValue : ";
char* gQ2 = "DeleteValue : ";

void IniBuffer(char* str, int size){
	for(int i = 0; i < size; ++i){
		str[i] = 0;
	}
}

int UpdateStr(char* buffer, int offset, int totalLen, char* str){
	int rv;
	if(offset + strlen(str) >= totalLen){
		return -1;
	}
	rv = sprintf(&buffer[offset], "%s", str);
	if(rv > 0){
		offset += rv;
	}
	for(int i = offset; i < totalLen; ++i){
		buffer[i] = 0;
	}
	return offset;
}

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UpdateRow(int y, char* str, int size){
	int len;
	gotoxy(0, y);
	len = printf(str);
	for(int i = len; i < size; ++i){
		printf(" ");
	}
	gotoxy(len, y);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        // The function failed. Call GetLastError() for details.
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

int _tmain(int argc, _TCHAR* argv[]){
	struct TreeNode *root = NULL;
	char I[XSIZE], O[XSIZE], tmpStr[128];
	int offset, rv, len, x, y, lastRow = 5;
	IniBuffer(I, XSIZE);
	IniBuffer(O, XSIZE);
	sprintf(I, gI);
	offset = sprintf(O, gO);

	COORD coord;
	coord.X = XSIZE;
	coord.Y = YSIZE;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	SMALL_RECT windowSize = {0, 0, XSIZE, YSIZE};
    BOOL b = SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);

	do{
		UpdateRow(1, "", XSIZE);
		UpdateRow(0, gQ0, XSIZE);
		scanf("%d", &rv);
		
		if(rv !=1 && rv != 2){
			break;
		}

		if(rv == 1){
			UpdateRow(1, gQ1, XSIZE);
			scanf("%d", &x);
			BST_InsertValue(&root, x);
			len = sprintf(tmpStr, "%d ", x);
			sprintf(&I[offset], tmpStr);
			memset(&O[offset], 0x20, len);
		}else if(rv == 2){
			UpdateRow(1, gQ2, XSIZE);
			scanf("%d", &x);
			root = BST_DeleteValue(root, x);
			len = sprintf(tmpStr, "%d ", x);
			sprintf(&O[offset], tmpStr);
			memset(&I[offset], 0x20, len);
		}
		offset += len;
		UpdateRow(3, I, XSIZE);
		UpdateRow(4, O, XSIZE);
		for(int i = 5; i < lastRow; ++i){
			UpdateRow(i, "", XSIZE);
		}
		gotoxy(0, 6);
		PrintTree(root, 0);

		coord = GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE));
		lastRow = coord.Y;
	}while(1);
}
