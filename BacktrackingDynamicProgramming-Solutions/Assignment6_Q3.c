#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
n = no.of items
s = size
v = value
C = capacity
*/
int bottom_up_dp(int n, int *s, int *v, int C)
{
    // Memoization Initialisation
    int M[n+1][C+1];

    // i = items, j = capacity, initialise 1st row, 1st column of tabulation table to 0
    for (int i = 0; i < n+1; i++)
    {
        M[i][0] = 0;
    }
    for (int j = 0; j < C+1; j++)
    {
        M[0][j] = 0;
    }

    // Filling up the tabulation table
    for (int i = 1; i < n+1; i++)
    {
        for (int j = 1; j < C+1; j++)
        {
            if (s[i] > j)
            {
                M[i][j] = M[i-1][j];
            }
            else
            {
                M[i][j] = fmax(M[i-1][j], M[i-1][j-s[i]] + v[i]);
            }
        }
    }
    return M[n][C];

}
 
int main ()
{
    int n,C;
    int function;
    int *s;
    int *v;
    int i,j;
    printf("Enter the number of items n:\n");
    scanf("%d",&n);
    printf("Enter the capacity C:\n");
    scanf("%d",&C);
    s = (int *) malloc(sizeof(int) * (n+1));
    v = (int *) malloc(sizeof(int) * (n+1));
    
    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&s[i]);
        
    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i=1;i<=n;i++)
        scanf("%d",&v[i]);
    
    printf("The maximum value is: %d \n", bottom_up_dp(n,s,v,C));
        
}