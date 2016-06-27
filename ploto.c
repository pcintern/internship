//given set of random points in x-y plane and to find two nearest and two farthest points.


#include <stdlib.h>
#include <stdio.h>
#include<math.h>
#define NUM_POINTS 50
#define NUM_COMMANDS 3
long long int z;
int sq(int z)
{
    long long int x = 0,count=0,i;

    for(i=1; x<=z; i+=2)
    {
        x = x + i;
        count++;
    }
    return count;
}


int main()
{   int  x1, x2, y1, y2,xleast,yleast,c,colort=49,colort1=49,colort2=49,colort3=49,i,j,m,n,xleast1,yleast1,xfar,yfar,xfar1,yfar1;
    float  r[50],r1,r2;
    char * commandsForGnuplot[] = {"set title \"Nearest destination\"","set palette model RGB defined (0 \"red\",1 \"green\",2 \"blue\")", "plot 'data.temp' using 1:2:3 notitle with points pt 2 palette"};
    double xvals[NUM_POINTS] ;
    double yvals[NUM_POINTS] ;
    int col[NUM_POINTS],col1[NUM_POINTS];

    for (c = 1; c <= 50; c++)
    {
        x2 = rand()%100;
        y2 = rand()%100 ;
        xvals[c]=x2;
        yvals[c]=y2;
        col[c]=2;
        printf("(%d,%d)\n", x2 ,y2);
        z = (((y2)*(y2)) +((x2)*(x2)));
        r[c]=sq(z);
        printf( "Distance= %f\n\n" ,r[c]);
    }
    r1=r[1];
    // r2=r[8]-r[6];
    r2=1;
    for(i=1; i<=50; i++)
    {
        for(j=1; j<=50; j++)
        {
            m=r[i]-r[j];
            if(m<r1&&m>0)
            {
                r1=m;
                col[colort]=2;
                col[i]=1;
                xleast =xvals[i];
                yleast=yvals[i];
                colort=i;
                col[colort1]=2;
                col[j]=1;
                xleast1=xvals[j];
                yleast1=yvals[j];
                colort1=j;

            }
        }
    }
    for(i=1; i<=50; i++)
    {
        for(j=1; j<=50; j++)
        {
            n=r[i]-r[j];
            if(n>r2&&n>0)
            {
                r2=n;
                col[colort2]=2;
                col[i]=0;
                xfar=xvals[i];
                yfar=yvals[i];
                colort2=i;
                col[colort3]=2;
                col[j]=0;
                xfar1=xvals[j];
                yfar1=yvals[j];
                colort3=j;

            }


        }
    }

    printf("The nearest points are: (%d,%d),(%d,%d)\n\n",xleast,yleast,xleast1,yleast1);
    printf("The farthest points are:(%d,%d),(%d,%d)\n\n",xfar,yfar,xfar1,yfar1);
    FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    for (i=1; i <= NUM_POINTS; i++)
    {
        fprintf(temp, "%lf %lf %d %d\n", xvals[i], yvals[i],col[i],col1[i]); //Write the data to a temporary file
    }

    for (i=0; i < NUM_COMMANDS; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    return 0;
}
