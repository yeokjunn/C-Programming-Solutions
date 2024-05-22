#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int memoization[100];

int top_down_dp(int n)
{
    // Base Case
    switch (n)
    {
    case 0:
        return 0;
    case 1:
        return 1;
    case 2:
        return 2;
    }

    // Check if n is in memory
    if (memoization[n] != NULL)
    {
        return memoization[n];
    }
    else
    {
        // Recursive memoization
        memoization[n] = top_down_dp(n-1) + (2*top_down_dp(n-2)) - (3*top_down_dp(n-3));
        return memoization[n];
    }
}


 
int main ()
{
    int n;
    int function;
    int i;
    printf("Enter the value of n:\n");
    scanf("%d",&n);
    
    printf("The value of F(%d) is: %d \n", n, top_down_dp(n));
        
}