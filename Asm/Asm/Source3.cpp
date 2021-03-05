#include<iostream>
using namespace std;

// https://www.tutorialspoint.com/cplusplus/cpp_strings.htm
char greeting[6] = { 'H', 'e', 'l', 'l', 'o', '\0' };
// or
// char greeting[] = "Hello";

// Important! actions that instruction ENTER, LEAVE and RET does, are in inline assembly automatically executed thanks to compiler.
// That is why we cannot explicitly execute them!

// http://www.cplusplus.com/reference/cstdio/printf/
// A format specifier follows this prototype: [see compatibility note below] 
// %[flags][width][.precision][length]specifier


// int do_tests(int n) {
int do_tests(const char* ptr_1, int n) { // only ptr is a key word
	const char* ptr_hello = "Hello world! ebp = %d\n";
	// char ptr_hello[] = "Hello world! ebp = %d\n"; // Runtime Error
	// char*    ptr_hello = "Hello world! ebp = %d\n"; // Compilation Error. A value of const can not be used to initialise ptr 
	_asm {
		mov eax, n
		; // ret - causes error. The program closes itself
		; // mov eax, ebp;
		push ebp; // the second argument of printf
		; // push ptr_1;
		push ptr_hello; // the first parameter of printf
		call printf
			add esp, 8; // !!! clean the stack othervise you get calling convention error
		mov eax, n
	}
}


//int sum(int n) { // the sum of all numbers to a given number
//  return (n <= 1) ? n : sum(n - 1) + n;
//}

int sum(int n) {
	_asm {
		mov ecx, n
		cmp ecx, 1
		jle end1; //jump for n<=1
		dec ecx
			push ecx; // push in the stack the argument of the function we call
		call sum; // recursive call
		pop ecx; // clean the stack from previously stored function argument
		add n, eax; // the returned value from the function call is in eax
	end1:
	}
	return n;
}

void factorial_iter(unsigned char a, unsigned long * b)
{
	if (a <= 1) return;
	*b *= a;
	factorial_iter(a - 1, b);
}

unsigned long factorial_variant(unsigned char a)
{
	unsigned long ret = 1, *pret = &ret;
	_asm {
		push dword ptr pret; // prepare the last function argument of function factorial_iter(unsigned char a, unsigned long * b)
		push dword ptr a; // prepare the first function argument  of function factorial_iter(unsigned char a, unsigned long * b)
		call factorial_iter; // call the function the arguments (in reverse order) are already prepared in the stack
		add esp, 8; // clean the function "factorial_variant" arguments from the stack
	}
	return ret;
}

//int main()
//{
//  printf("% u! =% lu \ n", 10, factorial(10));
//  return 0;
//}

int factorial_c(int n) {
	if (n == 0) return 1;
	return factorial_c(n - 1) * n;
}

//Write function int factorial(int n)  that recursively computes factorial of n. 0! = 1 !n=(n-1)!*n
int factorial(int n) {
	_asm {
		mov eax, n;
		cmp eax, 1;
		je return;
		dec eax;
		push eax;
		call factorial;
		add esp, 4;
		mul n;
		return:
	}
}

//Write function char *my_strdup(char *s)  which creates copy of provided string(use malloc and strlen from C++)
char *my_strdup(char *s) {
	_asm {
		push s; // prepare the argument for strlen
		call strlen; // call strlen the returned value is in 'eax'
		add esp, 4; // clean the stack from the argument s
		push eax; // save eax - the resutl from strlen (caller responsability) and send it as argument to malloc
		call malloc; // call malloc with argument the result of strlen in eax and stack 
		pop ecx; // clean the stack from argument and load it in the counter 
		mov ebx, s; // load the address of the original array in ebx
		for:
		mov dl, [ebx + ecx]; // load the last element from the original array in dl
		mov[eax + ecx], dl; // after malloc the address of the new copy is in eax. We copy each element
		dec ecx;
		cmp ecx, 0;
		jge for;
	}
	return s;
}

int fib_c(unsigned short n) {
	if (n <= 2) return 1;
	return fib_c(n - 2) + fib_c(n - 1);
}

//Write function unsigned int fib(unsigned short n), which recursively computes n - th fibonacci number. 1,1,2,3,5...
// maybe the correct way is to start from 0 -> 0,1,1,2,3,5,8...
int fib(unsigned short n) {
	_asm {
		movzx eax, n; // n is unsigned short so we spread with movzx
		cmp eax, 1; // check the bottom of the recursion
		jle return;
		dec eax; // we have to call fib 2 times with 2 previous elements fib(n-1) and fib(n-2)
		push eax; // prepare the argument
		call fib; // call the function with argument in the stack taken from eax. fib(n-1)
		pop ecx; // clean the stack from the argument and put it in ecx
		dec ecx; // prepare n-2
		push eax; // save the value of the first fib(n-1). The second call will destroy it
		push ecx; // prepare the argument for fib(n-2)
		call fib; // call fib(n-2)
		add esp, 4; // clean the stack from the argument of fib(n-2)
		pop edx; // load back the value of fib(n-1) in edx
		add eax, edx; // add the value of fib(n-1) + fib(n-2)
		return:
	}
}

//Write function void print_fact(unsigned char n), which prints "fact(n) = X".For computing and printing use functions factorial and printf.
void print_fact(unsigned char n) {
	const char *f = "fact(%d) = %d\n";
	_asm {
		movzx eax, n; // n is unsigned char so we spread with movzx
		push eax; // prepare the argument for factorial
		call factorial; // call factorial with argument eax from stack. return value is in eax
		pop edx; // clean the stack from the argument of factorial and save it in edx
		push eax; // third argument of printf - this is the factorial
		push edx; // second argument of printf the number
		push f; // first argument of printf - the formatting string
		call printf; // call printf to print the values
		add esp, 12; // clean the stack from the arguments
	}
}
//WEEK 8