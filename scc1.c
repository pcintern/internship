//given adjacency matrix(GRAPH) to find strongly connected 

#include<stdio.h>
#include<malloc.h>

struct node

{


    int no;

    int x, y;

    struct node* next;
    struct node* link;
}*top = NULL, *p = NULL, *np = NULL,*head=NULL,*m=NULL,*n=NULL,*np1=NULL;


int c = 0;

void push(struct node* ptr)

{
    struct node* np;

    np=(struct node*)malloc(sizeof(struct node));

    np= ptr;

    np->next = NULL;

    if (top == NULL)

    {

        top = np;

    }

    else

    {

        np->next = top;

        top = np;

    }

}

struct node* pop()

{

    if (top == NULL)

    {

        printf("underflow\n");

    }

    else

    {

        p = top;

        top = top->next;

        return(p);

        free(p);

    }

}

void store(struct node* ptr1)

{
    struct node* np1;
    np1 = (struct  node*)malloc(sizeof(struct node));

    np1= ptr1;

    np1->link = NULL;

    if (c == 0)

    {

        head = np1;

        m = head;

        m->link = NULL;

        c++;

    }

    else

    {

        m = head;

        np1->link = m;

        head = np1;

    }

}

void del(int x)

{

    m = head;

    if (m->no == x)

    {

        head = head->link;

        free(m);

    }

    else

    {

        while ((m->no != x && m->link != NULL))

        {

            n = m;

            m = m->link;

        }

        if (m->no == x)

        {

            n->link = m->link;

            free(m);

        }

        else if (m->link == NULL)

        {

            printf("error\n");

        }

    }

}

void dfs(int *v, int am[][20], int i,int n)

{   int j;
    struct node* q;
    q = (struct node*)malloc(sizeof(struct node));

    q->no = i;

    q->y = c;

    push(q);

    v[i] = 1;

    for (j = 0; j < n; j++)

    {

        if (am[i][j] == 0  || (am[i][j] == 1 && v[j] == 1))

            continue;

        else if (am[i][j] == 1 && v[j] == 0)

        {

            c++;

            dfs(v,am,j,n);

        }

    }

    c++;

    q = pop();

    q->x= c;

    store(q);

    return;

}

void dfs1(int *v, int am[][20], int i,int n)

{
    int j;
    v[i] = 1;

    del(i);

    printf("%d\n",i);

    for (j = 0; j < n; j++)

    {

        if (am[i][j] == 0  || (am[i][j] == 1 && v[j] == 1))

        {

            continue;

        }

        else if (am[i][j] == 1 && v[j] == 0)

        {

            dfs1(v,am,j,n);

        }

    }

    return;

}

int main()

{
    int i,j,n;

    int v[20], am[20][20], amt[20][20];
    scanf("%d",&n);
    for (i = 0; i < n; i++)

        v[i] = 0;

    for (i = 0; i < n; i++)

    {

        printf("enter the values for adjacency matrix row:=%d\n",i + 1);

        for (j = 0; j < n; j++)

        {

            scanf("%d",&am[i][j]);

        }

    }

    dfs(v, am, 0,n);

    for (i = 0; i < n; i++)

    {

        v[i] = 0;

        for (j = 0; j < n; j++)

            amt[j][i] = am[i][j];

    }

    while (head != NULL)

    {

        printf("Strongly Connected Components:\n");

        dfs1(v, amt,head->no,n);

    }

}
