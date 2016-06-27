//display the given no. of elements in avl tree
//dotty representation

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
static int gName=0;
int val;
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

    // Perform rotation

    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
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

void preOrderDotDump(struct node *node,FILE* outputFile)
{
    if(node!= NULL)
    {
        fprintf(outputFile,"%d[label=%d,color=black];\n",node->key,node->key);
        if(node->left!=NULL)
            fprintf(outputFile,"%d->%d;\n",node->key,(node->left)->key);
        if(node->right!=NULL)
            fprintf(outputFile,"%d->%d;\n",node->key,(node->right)->key);

        preOrderDotDump(node->right,outputFile);
        preOrderDotDump(node->left,outputFile);

    }
}

void dotDump(struct node *node,FILE *outFile)
{
    gName++;
    fprintf(outFile,"digraph AVL2PUN {\n",gName);
    preOrderDotDump(node,outFile);
    fprintf(outFile,"}\n");
}
FILE *outputFile;

int main(int argc, char** argv)
{
    FILE *pipe;
    struct node *node;
    node=NULL;
    int ch,i,key;
    if (argc != 2)
    {
        printf(" need one argument  \n");
        exit(0);
    }

    outputFile = fopen ("avl2pun.dot", "w");
    fclose (outputFile);
    val = atoi(argv[1]);
    for(i=0; i<val; i++)
    {
        key=random()%1000;
        printf("%d\t",key);
        node=insert(node,key);

        outputFile = fopen ("avl2pun.dot", "a");
        if (outputFile != NULL)
        {

            dotDump (node,  outputFile);
        }
        fclose (outputFile);
    }

    while(1)
    {
        printf("\n1.Display dotty \n2.exit");
        printf("Enter your choice\n");
        scanf("%d",&ch);
        switch(ch)
        {

        case 1:
            pipe=popen("dot -Tps avl2pun.dot -o avl2pun.ps","w");
            pclose(pipe);
            pipe=popen("evince avl2pun.ps","r");
            pclose(pipe);

            break;

        case 2:
            printf("wrong choice\n");
            exit(0);

        }


    }
    return 0;
}

