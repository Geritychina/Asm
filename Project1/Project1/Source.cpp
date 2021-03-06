#include<iostream>;

using namespace std;

int testasm(int a, int b) {
	int res = 0;
	__asm {
		mov eax, a; akdshjakdsh akjsdh asjkdh
		add eax, b
		mov res, eax
	}
	return res;
}

//Perimeter triangle
int ptriangle(int a, int b, int c) {
	_asm {
		mov eax, a
		add eax, b
		add eax, c
	}
}

//Perimeter triangle 2 
int ptriangle1(int a, int b) {
	_asm {
		mov eax, a
		imul eax, 2
		add eax, b
	}
}

//Perimeter square
int sqr(int a) {
	_asm {
		mov eax, a
		mov ebx, 4
		mul ebx
	}
}
//Perimeter trapezoid
int perimetyrChetiriygylnik(int a, int b) {
	_asm {
		mov eax, a
		imul eax, 2
		mov ebx, b
		imul ebx, 2
		add eax, ebx
	}
}

// (((a++)*b)/((a--)-b))*c
int func(int a, int b, int c) {
	_asm {
		mov eax, a
		inc eax
		mul b
		mov ebx, a
		dec ebx
		sub ebx, b
		mov edx, 0
		div ebx
		mul c
	}
}

int main() {
	//cout << testasm(2, 2)<<endl;
	//cout << ptriangle(3, 4, 6)<<endl;
	//cout << ptriangle1(2, 3)<<endl;
	//cout << sqr(2)<<endl;
	//cout << perimetyrChetiriygylnik(2, 3)<<endl;

	cout << func(4, 2, 3)<<endl;
	system("pause");
	return 0;
}
//WEEK 6
