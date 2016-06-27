//To randomly delete set of numbers from given set of numbers in avl tree

#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

int max(int a, int b);

int height(struct node *N)
{
    if (N==NULL)
        return 0;
    return N->height;
}
int max(int a, int b)
{
    return (a > b)? a : b;
}
struct node* newNode(int key)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;
    return(node);
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;


    x->right = y;
    y->left = T2;


    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;


    return x;
}
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;


    y->left = x;
    x->right = T2;


    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;


    return y;
}

int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, int key)
{

    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left  = insert(node->left, key);
    else
        node->right = insert(node->right, key);


    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = getBalance(node);


    if (balance > 1 && key < node->left->key)
        return rightRotate(node);


    if (balance < -1 && key > node->right->key)
        return leftRotate(node);


    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }


    return node;
}

struct node * min(struct node* node)
{
    struct node* u = node;

    while (u->left != NULL)
        u= u->left;

    return u;
}

struct node* delete(struct node* node, int key)
{

    if (node == NULL)
        return node;

    if ( key < node->key )
        node->left = delete(node->left, key);

    else if( key > node->key )
        node->right = delete(node->right, key);

    else
    {
        if( (node->left == NULL) || (node->right == NULL) )
        {
            struct node *temp = node->left ? node->left : node->right;

            if(temp == NULL)
            {
                temp = node;
                node = NULL;
            }
            else
                *node = *temp;

            free(temp);
        }
        else
        {
            struct node* succ= min(node->right);


            node->key = succ->key;

            node->right = delete(node->right, succ->key);
        }
    }

    if (node == NULL)
        return node;

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);
    if (balance > 1 && getBalance(node->left) >= 0)
        return rightRotate(node);
    if (balance > 1 && getBalance(node->left) < 0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && getBalance(node->right) <= 0)
        return leftRotate(node);

    if (balance < -1 && getBalance(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void display(struct node *node)
{
    if(node!= NULL)
    {
        display(node->right);
        printf("%d\t",node->key);
        display(node->left);

    }
}


/*int search(int b[],int data)
{

   int i;
                           for(i=1;i<=50;i++)
                                    {
                                       if(data==b[i])
                                       return 0;
                                        else
                                        return 1;
                                     }


}*/
int main()
{
    struct node *node;
    node=NULL;
    int ch,i,key,j,a[500],b[500],data,cond;
    for(i=1; i<=100; i++)
    {
//                         a[i]=key;

        key=random()%10000;
        a[i]=key;
        printf("%d\t",key);
        node=insert(node,key);

    }






    while(1)
    {
        printf("1.delete\n 2.Display \n3.search\n4.exit");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {



        case 1://printf("Enter element for deletion:\n");
            printf("elements deleted\n");
            for(i=1; i<=50; i++)
            {
                //	scanf("%d",&a[i]);
                key=a[i];
                printf("%d\t",a[i]);
                b[i]=a[i];
                //  printf("\n%d\t",b[i]);
                node=delete(node,key);
            }

            break;

        case 2:
            printf("remaining elements after deletion\n");
            display(node);

            break;
        case 3:
            printf("enter data\n");
            scanf("%d",&data);
            for(i=1; i<=50; i++)
            {
                if(b[i]==data)
                {
                    printf("not found\n");

                    break;
                }
                if(i==50)
                    printf("found\n");
            }




            break;
        case 4:
            printf("wrong choice\n");
            exit(0);

        }


    }
    return 0;
}

