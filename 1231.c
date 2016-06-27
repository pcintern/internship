//To display the given numbers in a diamond pattern
//Recursive way

#include<stdio.h>
void space(int n,int i,int k)
{

    if(k<=n-i)
    {
        printf(" ");
        k++;
        space(n,i,k);
    }
}
void number (int i,int j)
{
    if(j<=i)
    {
        printf("%d",j);
        j++;
        number(i,j);
    }
}

void next(int i,int j)
{
    if(j>=1)
    {
        printf("%d",j);
        j--;
        next(i,j);
    }
}

int pat(int n,int i)
{
    int k=1,j;
    space(n,i,k);
    j=1;
    number(i,j);
    j=i-1;
    next(i,j);
    printf("\n");
}

void main()
{
    int i,n;
    printf("enter number:\t");
    scanf("%d",&n);
    for(i=1; i<=n; i++)
        pat(n,i);
    for(i=n-1; i>=1; i--)
        pat(n,i);
}

