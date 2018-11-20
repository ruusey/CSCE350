//============================================================================
// Name        : Fib.cpp
// Author      : Robert Usey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;
void print(int n){
	cout<<"step: "<<n<<endl;
}
int fibonacci(int n){
	//print(n);
    if (n < 0){
    	return (fibonacci(n + 2) - fibonacci(n+1));
    }
    else if (n == 0 || n == 1){
    	return 1;
    }

}
int * fibonacciArr(int n){
	uint size = abs(n)+2;
	print(size);
	static int* arr;
	arr = (int*)malloc(size * sizeof(int));
	arr[0]=1;
	arr[1]=1;
	for(int i = 2; i<size;i++){

		arr[i]=arr[i-2]-arr[i-1];
		print(arr[i]);
	}
	return arr;
}

int main(){
	int tests[6]={0,-1,-2,-3,-4,-5};
	int length = sizeof(tests) / sizeof(tests[0]);
	for(int i = 0 ; i <length;i++){
		cout<<"Fibonacci("<<tests[i]<<")="<<fibonacci(tests[i])<<endl;
	}

	int *ret;
	ret=fibonacciArr(-2);
	cout<<*(ret+3)<<endl;

	return 0;
}
