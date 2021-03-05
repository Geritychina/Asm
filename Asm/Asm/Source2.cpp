#include<iostream>
using namespace std;

static int first[10];
static short second[10];
static short third[10];
int *fourth;
int *fifth;

int do_test_direct_addressing() {
	static int thevar, thevar2; // variables thevar and thevar2 are in memory
	thevar = 3;
	thevar2 = 4;
	_asm {
		mov eax, thevar; eax = thevar - enter the 32 - bit memory value in the eax register.
		mov eax, thevar + 4; eax = thevar + 4 = thevar2 - enter the eax register 32 - bit value from the thevar + 4 = thevar2
	}

	//  If the thevar is a static or global variable, then both commands do the same, so the thevar variable is assigned to AX.
	_asm {
		mov eax, thevar; ax = [address_value_thevar]
		mov eax, [thevar]; ax = [[address_value_thevar]] = [address_value_thevar]
	}
}

int do_test_indirect_addressing() {
	char * thepointer; // 32-bit pointer variable to 8-bit value
	char myChar1 = 'A', myChar2 = 'B', myChar3 = 'C';
	thepointer = &myChar1;
	_asm {
		mov ebx, thepointer; ebx = thepointer - direct addressing
		mov esi, 0; esi = 2
		mov al, [ebx + esi]; al = *(thepointer + 2) = thepointer[2] - indirect addressing
	}
}

int use_lea_4_calc(unsigned a) {
	// lea - load efective address
	// The address calculation is performed during instruction decoding phase. This is the fastest possible calculation. 
	// This instruction can also be used for quick multiplication. E.g. multiplication of nine
	_asm {
		mov eax, a
		lea eax, [eax + 8 * eax]
	}
}

//Create a static field of 10 int elements.Write function void multiples(short n), which stores multiples of n in the field.
void multiples(short n) {
	_asm {
		mov eax, 0;
		mov ax, n;
		mov ecx, 0;
		for:
		mov[first + 4 * ecx], eax;
		add ax, n;
		inc ecx;
		cmp ecx, 10;
		jl for;
	}
}


//Create a static field of 10 int elements.Write function void countdown(), which stores a sequence of 10, 9, 8, ..., 1 (in this order) into the field.
void countdown() {
	_asm {
		mov ax, 10;
		mov ecx, 0;
		for:
		mov[second + 2 * ecx], ax;
		dec ax;
		inc ecx;
		cmp ecx, 10;
		jl for;
	}
}


//Create a static field of 10 short elements.Write the function void powers(), which will store numbers 1 to power of 2, 2 to power of 2, ..., 10 to power of 2 in the field.
void powers() {
	_asm {
		mov ecx, 0;
		mov dx, 0;
		for:
		mov ax, cx;
		inc ax;
		mul ax;
		mov[third + 2 * ecx], ax;
		inc ecx;
		cmp ecx, 10;
		jl for;
	}
}

//Create a field(using a malloc call from C) of 10 int types.Write the function void powers2(), which will store numbers 2 to the power of 0, 2 to the power of 1, ..., 2 to the power of 9 in the field.
void powers2() {
	const int two = 2;
	_asm {
		mov ebx, fourth; // fourth is a pointer to an array
		mov ecx, 0;
		mov eax, 1;
		mov edx, 0;
		for:
		mov[ebx + 4 * ecx], eax;
		mul two;
		inc ecx;
		cmp ecx, 10;
		jl for;
	}
}

//Create a field(using a malloc call from C language) of n size of short elements, where n is a constant.Write int avg(unsigned int n) function to calculate the arithmetic average of the numbers in this field.Try that it works correctly for both positive and negative numbers(including their mix).
int avg(unsigned int n) {
	_asm {
		mov ebx, fifth;
		mov ecx, 0;
		mov eax, 0;
		for:
		add eax, [ebx + 4 * ecx];
		inc ecx;
		cmp ecx, n;
		jl for;
		mov edx, 0;
		div n;
	}
}

//Write int minimum() function that returns the smallest array element.In the body of this function in C, create a local variable of the field type of the size of 10 int elements from which the values will be selected.Try that the function works correctly for both positive and negative numbers.
int minimum() {
	int local[10] = { 10, 15, 1, 28, 16, -18, 5, 20, 1, 3 };
	_asm {
		movsx eax, [local];// this is the first element of the array // we need negative signed
		mov ecx, 0; // index
		for:
		cmp ecx, 10;
		jge return;
		mov edx, [local + 4 * ecx];
		inc ecx;
		cmp eax, edx;
		jle for;
		mov eax, edx;
		jmp for;
		return:
	}
}

void print_array(int *array, int length)
{
	for (int i = 0; i < length; i++) {
		/* whatever */
		cout << array[i] << ", ";
	}
	cout << endl;
}

void print_array_short(short *array, int length)
{
	for (int i = 0; i < length; i++) {
		/* whatever */
		cout << array[i] << ", ";
	}
	cout << endl;
}

int main()
{
	std::cout << "Hello, world!\n";
	char answer = 0;
	//cout << avg_int(2, -1, 5) << endl; //2
	//cout << avg_short(-1, 2, 5) << endl; // 2
	//cout << sgn(-10) << ", " << sgn(0) << ", " << sgn(10) << endl;
	//cout << min3(1, -4, 5) << endl; // -4
	//cout << positive(-1, 2, 5) << ", " << positive(1, 2, 3) << ", " << positive(0, 1, 0) << endl; // -1, 1, 1
	//cout << power(2, 4) << endl; // 16

	cout << do_test_direct_addressing() << endl;

	cout << (char)do_test_indirect_addressing() << endl;

	cout << use_lea_4_calc(3) << endl; // 27

	multiples(4);
	print_array(first, 10);

	countdown();
	print_array_short(second, 10);

	powers();
	print_array_short(third, 10);

	fourth = (int*)malloc(10 * sizeof(int));
	powers2();
	print_array(fourth, 10);

	fifth = (int*)malloc(10 * sizeof(int));
	fifth[0] = 11;
	fifth[1] = 6;
	fifth[2] = 2;
	fifth[3] = 11;
	fifth[4] = 6;
	fifth[5] = 6;
	fifth[6] = 18;
	fifth[7] = 4;
	fifth[8] = -11;
	fifth[9] = -1;
	cout << avg(10) << endl; // 5 -> 55 /10 = 5 remainder 5 in edx

	cout << minimum() << endl; // -18

	cin >> answer;
}
//WEEK 7