#include<iostream>
using namespace std;
int arrone[6];
int arrtwo[6];

void print_array(int* arr, int lengh) {
	for (int i = 0; i < lengh; ++i) {
		cout << arr[i] << ", ";
	}
	cout << endl;
}

int reverse(int a) {
	_asm {
		mov ecx, 0
		mov edx, a
		dec edx;
		for:
		mov eax, [arrone + 4 * ecx]
			mov[arrtwo + 4 * edx], eax
			inc ecx
			dec edx
			cmp ecx, a
			jl for
	}
}

int main() {

	arrone[0] = 0;
	arrone[1] = 1;
	arrone[2] = 2;
	arrone[3] = 3;
	arrone[4] = 4;
	arrone[5] = 5;

	print_array(arrone, 6);
	reverse(6);
	print_array(arrtwo, 6);
	system("pause");
}










