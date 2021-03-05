#include<iostream>
using namespace std;
int cmp(int a, int b, int c) {
	_asm {
		mov eax, a
		cmp eax, b
		jg nextstep
		mov eax, b
		cmp eax, c
		jg return
		jmp cmax
		nextstep :
		cmp eax, c
			jg return
			cmax :
			mov eax, c
			return :
	}
}

int cmp2(int a, int b, int c) {
	_asm {
		mov eax, a
		cmp eax, b
		jg comparec;
		mov eax, b
			comparec :
		cmp eax, c
			jg return
			mov eax, c
			return :

	}
}

int increment(int a) {
	_asm {
		mov eax, a
		mov ecx, 1
		for:
		inc eax
			inc ecx
			cmp ecx, 5
			jle for
	}
}

int fact(int n) {
	_asm {
		mov eax, 1
		mov ecx, 1

		for:
		imul eax, ecx
			inc ecx
			cmp n, ecx
			jge for;
	}
}

int factnk(int n, int k) {
	_asm {
		mov eax, 1
		mov ecx, 1

		for:
		imul eax, ecx
			inc ecx
			cmp n, ecx
			jge for;

		mov ebx, 1
			mov ecx, 1
			fork:
		imul ebx, ecx
			inc ecx
			cmp k, ecx
			jge fork

			mov edx, 0
			idiv ebx

	}
}

int factnk2(int n, int k) {
	_asm {
		mov ecx, n
		mov eax, 1
		for:
		mul ecx
			dec ecx
			cmp ecx, k
			jg for;

	}
}
int main() {
	//cout << cmp2(8, 6, 7)<< cmp2(8, 9, 7)<< cmp2(8, 6, 9);

	//cout << increment(1);

	//cout << fact(5);

	cout << factnk(5, 4);
	system("pause");
	return 0;
}
//WEEK 8 