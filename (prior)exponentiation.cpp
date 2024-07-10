#include<vector>

#include <iostream>

#include<ctime>

#include<random>

#include<algorithm>

#include<unistd.h>

using namespace std;

int maxSubSum1(const std::vector<int> & a) {
int maxSum = 0; - 1
for(int i = 0; i< a.size(); ++i)
{
    for (int j = i; j< a.size();++j )
    {
    int thisSum = 0; - 1
    for (int k=i;k<=j;++k)
        {
        thisSum += a[k]; - 1
        }
    if(thisSum > maxSum)
    maxSum = thisSum; - 1
    }
}
return maxSum; - 1

}

int main() {
    srand(time_t(0));

    std::vector<int> v(2500,0);

    generate(v.begin(), v.end(), rand);

    clock_t _start = clock();
    cout << "Result: " << maxSubSum1(v) << endl;

    //sleep(100);

    clock_t _end = clock();

    std::cout << "Time taken for 1000 items n cube: " << ((_end - _start)/CLOCKS_PER_SEC) << " seconds" << std::endl;

    return 0;
}