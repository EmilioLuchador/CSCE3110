// Fibonacci Series using Recursion
#include <bits/stdc++.h>
#include<vector>

#include <iostream>

#include<ctime>

#include<random>

#include<algorithm>

#include<unistd.h>

using namespace std;
 
int fib(int n)
{
    if (n <= 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}
 
int main()
{
    srand(time_t(0));
    clock_t _start = clock();

    int n = 50;
    cout << n << " is the Fibonacci Number: " << fib(n) << "\n";
    

    clock_t _end = clock();
    std::cout << "Time taken for " << n << " recursions: " << ((_end - _start)/CLOCKS_PER_SEC) << " seconds" << std::endl;
    return 0;
}
 