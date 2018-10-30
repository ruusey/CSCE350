//============================================================================
// Name        : Sort3.cpp
// Author      : Robert Usey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================
#include <vector>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
using namespace std;

void print(vector<int> ints) {
	for (auto i : ints) {
		cout << i ;
	}
	cout << endl;
}
void karatsuba_mult(char arr0[], char arr1[]) {
	//comparisons++;

}
void brute_mult(vector<int> a, vector<int> b) {
	vector<vector<int>> finalresult;
	vector<int> currentrow;
	int carry=0, workingnum=0, innerval =0, curnt=0, j=0;

	for (auto an = a.rbegin(); an != a.rend(); ++an)
	{

	    for (auto bn = b.rbegin(); bn != b.rend(); ++bn)
	    {

	        curnt = (*an) * (*bn);
	        curnt += carry;
	        //cout<<curnt<<endl;
	        carry = curnt / 10;
	        currentrow.push_back(curnt % 10);


	    }

	    finalresult.push_back(currentrow);
	    for (int i = 0; i < currentrow.capacity(); i++)
	    {
	        currentrow.pop_back();
	    }
	    for (int i=0; i < j; i++)
	    {
	        currentrow.push_back(0);
	    }
	    j++;
	}
	for (auto bn = finalresult.begin(); bn != finalresult.end(); ++bn)
		    {
				print(*bn);

		    }

}
int to_int(char ch)
{
    return((ch >= '0' && ch <= '9') ? ch - '0' : -1);
}
vector<int> to_int_vec(string line)
{
	vector<int> integers;
	char arr0[line.length()];
	strcpy(arr0, line.c_str());
    for (int i = 0; i < line.size(); i++)
    	integers.push_back(to_int(arr0[i]));

    return integers;
}

int main()
{
    vector<int> a,b;
    int ans[200]={0};
    int i,j,tmp;
    char s1[101],s2[101];
    scanf(" %s",s1);
    scanf(" %s",s2);
    int l1 = strlen(s1);
    int l2 = strlen(s2);

    for(i = l1-1,j=0;i>=0;i--,j++)
    {
         a.push_back(s1[i]-'0');
    }
    for(i = l2-1,j=0;i>=0;i--,j++)
    {
    	b.push_back(s2[i]-'0');
    }
    for(i = 0;i < l2;i++)
    {
        for(j = 0;j < l1;j++)
        {
            ans[i+j] += b[i]*a[j];
        }
    }
    for(i = 0;i < l1+l2;i++)
    {
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }
    for(i = l1+l2; i>= 0;i--)
    {
        if(ans[i] > 0)
            break;
    }
    printf("Brute Force : ");
    for(;i >= 0;i--)
    {
        printf("%d",ans[i]);
    }
    return 0;
}
