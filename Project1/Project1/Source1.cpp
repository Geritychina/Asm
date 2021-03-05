#include<iostream>
using namespace std;

int func(int a, int b, int c) {
	_asm {
		mov eax, a
		add eax, b
		mov edx, 0
		div c
	}
}
int ptz(int a) {
	_asm {
		mov eax, 1
		cmp eax, a
		jle return
		mov eax, 0
		cmp eax, a
		je return
		mov eax, -1

		return:

	}
}

int cmp(int a, int b) {
	_asm {
		mov eax, a
		cmp eax, b
		je ravno
		jl malko
		mov eax, -1
		jmp return
		malko:
		mov eax, 1
			jmp return
			ravno :
			mov eax, 0
			return :
	}
}

int cmp2(int a, int b) {
	_asm {
		mov ebx, a
		cmp ebx, b
		mov eax, 0
		je return
		jl jump
		mov eax, 1
		jmp return
		jump:
		mov eax, -1
			return :
	}
}

int function(int a, int b, int c) {
	int br = 0;
	int sum = 0;
	_asm {
		mov ebx, a
		cmp ebx, 0
		jle nega; go on nega if a <= 0
		inc br
		mov sum, ebx
		nega :
		mov ebx, b
			cmp ebx, 0
			jle negb; go on negb if b <= 0
			inc br
			add sum, ebx
			negb :
		mov ebx, c
			cmp ebx, 0
			jle negc; go on negb if c <= 0
			inc br
			add sum, ebx

			negc :
	}

	cout << "Broj polojitelni = " << br << " sumata im e : " << sum;
}

int main() {


	//cout << func(2, 3, 5);

	//cout << ptz(5) << endl << ptz(0) << endl << ptz(-5);
	//cout << cmp2(-10, 10) << endl << cmp2(10, -10) << endl << cmp2(10, 10) << endl;

	int a, b, c;
	cout << "a = ";
	cin >> a;
	cout << "b = ";
	cin >> b;
	cout << "c = ";
	cin >> c;
	function(a, b, c);
	system("pause");
	return 0;
}
//WEEK 7