#include<iostream>
using namespace std;

// absolute value |a|
int abs(int value) {
	_asm {
		mov eax, value
		cmp eax, 0
		jge skip
		neg eax
		skip :
		mov value, eax
	}
	return value;
}

// power
int power(int x) {
	_asm {
		mov eax, x
		// mul eax
		imul eax, x
		mov x, eax
	}
	return x;
}

// Write in Assembly function :  int perimeter_of_rectangle (int a, int b), which calculates perimeter of rectangle.
int perimeter_of_rectangle(int a, int b) {
	// int result;
	_asm {
		mov eax, a; // you can put ; if you like
		add eax, a; is comment
			add eax, b;
		add eax, b;
		mov a, eax; mov result, eax
	}
	return a; // return result;
}

//Write in Assembly function : int area_of_rectangle(int a, int b) that calculates the area of rectangle.
int area_of_rectangle(int a, int b) {
	// int result;
	_asm {
		mov eax, a;
		mul b;
		mov a, eax;
	}
	// return result;
	return a;
}

//Write in Assembly function : int perimeter_of_square(int a), which calculates perimeter of square.
int perimeter_of_square(int a) {
	_asm {
		mov eax, a;
		// ; mul 4; // you can not multiply by constant
		// processors works only with registers and memory
		mov ecx, 4;
		mul ecx;
		mov a, eax;
	}
	return a;
}

//Write in Assembly function : int area_of_square(int a) that calculates the area of square.
int area_of_square(int a) {
	_asm {
		mov eax, a;
		mul a; // in this case a is in memory
		mov a, eax;
	}
	return a;
}

//Write in Assembly function : int perimeter_of_triangle(int a, int b, int c), which calculates perimeter of triangle.
int perimeter_of_triangle(int a, int b, int c) {
	_asm {
		mov eax, a;
		add eax, b;
		add eax, c;
		mov a, eax;
	}
	return a;
}

//Write in Assembly function : int perimeter_of_triangle2(int a), which calculates perimeter of equilateral  triangle
int perimeter_of_triangle2(int a) {
	_asm {
		mov eax, a;
		mov ecx, 3;
		mul ecx;
		mov a, eax;
	}
	return a;
}

//Write in Assembly function : int perimeter_of_triangle3(int a, int b), which calculates perimeter of rectangular triangle.
int perimeter_of_triangle3(int a, int b) {
	int result = 0;
	int temp = 0;
	_asm {
		mov eax, a;
		mul a;
		mov ecx, eax;
		mov eax, b;
		mul b;
		add eax, ecx;
		mov temp, eax;
		mov eax, a;
		add eax, b;
		mov result, eax;
	}
	result += sqrt(temp);
	return result;
}

int area_of_triangle(int a, int b, int c) {
	// P = sqrt(s*(s-a)*(s-b)*(s-c) ); s = (a + b + c)/2;
	int result = 0;
	_asm {
		mov eax, a;
		add eax, b;
		add eax, c;
		mov ecx, 2;
		mov edx, 0;
		div ecx;
		mov ecx, eax;
		sub ecx, a;
		mul ecx;
		add ecx, a; // get back to s
		sub ecx, b;
		mul ecx;
		add ecx, b; // get back to s
		sub ecx, c;
		mul ecx;
		mov result, eax;

	}
	return sqrt(result);
}


int main()
{
	std::cout << "Hello, world!\n";
	char answer = 0;
	cout << abs(-5) << endl;
	cout << power(2) << endl;
	cout << perimeter_of_rectangle(2, 3) << endl;
	int value = 4;
	int &ref2int = value; // here you must initialise with value. You have to assign a value
	cout << ref2int << endl;
	// cout << ptr2int << endl;
	int *ptr2value; // you dont have to initialise with value
	// cout << ptr2value << endl; // use of uninitialised local variable
	ptr2value = &value; // this works
	cout << ptr2value << endl; // 0115FE70
	cout << &value << endl; // 0115FE70 returns the address of some variable in memory
	cout << *ptr2value << endl; // Dereference 4 the value of the variable


	cout << perimeter_of_rectangle(2, 3) << endl;
	cout << area_of_rectangle(2, 3) << endl;
	cout << perimeter_of_square(5) << endl;
	cout << area_of_square(5) << endl;
	cout << perimeter_of_triangle(5, 4, 3) << endl;
	cout << perimeter_of_triangle2(3) << endl;
	cout << perimeter_of_triangle3(3, 4) << endl;
	cout << area_of_triangle(5, 4, 6) << endl;

	cin >> answer;
}
//WEEK 5 