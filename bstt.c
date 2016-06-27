//To display the given numbers and to delete any given no. in a bst
//Dotty representation
#include<stdio.h>
#include<stdlib.h>
struct node
{
    int data;
    struct node *left,*right;
};
struct node *root=NULL;
static int gName=0;
int val;

struct node  *createnode(int data)
{
    struct node *new;
    new=(struct node *)malloc(sizeof(struct node));
    new->data=data;
    new->left=NULL;
    new->right=NULL;
    return (new);
}

void  insertion(struct node **N, int data)
{
    if(*N==NULL)
    {
        *N=createnode(data);
    }
    else if (data<(*N)->data)
    {
        insertion(&(*N)->left,data);
    }
    else if (data>(*N)->data)
    {
        insertion(&(*N)->right,data);
    }
}


void deletion(struct node **N ,struct node **parent,int data)
{
    struct node *tempnode,*tempparent;
    if(*N==NULL)
        return;
    if((*N)->data==data)
    {
        if(!(*N)->left&&!(*N)->right)
        {
            if(parent)
            {
                if((*parent)->left==*N)
                    (*parent)->left=NULL;
                else
                    (*parent)->right=NULL;
                free(*N);
            }
            else
            {
                free(*N);
            }
        }
        else if(!(*N)->right && (*N)->left)
        {
            tempnode=*N;
            (*parent)->right=(*N)->left;
            free(tempnode);
            *N=(*parent)->right;
        }
        else if((*N)->right && !(*N)->left)
        {
            tempnode=*N;
            (*parent)->left=(*N)->right;
            free(tempnode);
            *N=(*parent)->left;
        }

        else if(!(*N)->right->left)
        {
            tempnode=*N;
            (*N)->right->left=(*N)->left;
            (*parent)->left=(*N)->right;
            free(tempnode);
            *N=(*parent)->left;
        }
        else
        {
            tempnode=(*N)->right;
            while(tempnode->left)
            {
                tempparent=tempnode;
                tempnode=tempnode->left;
            }
            tempparent->left=tempnode->right;
            tempnode->left=(*N)->left;
            tempnode->right=(*N)->right;
            free(*N);
            *N=tempnode;
        }
    }
    else if(data<(*N)->data)
    {
        deletion(&(*N)->left,N,data);
    }
    else if(data>(*N)->data)
    {
        deletion(&(*N)->right,N,data);
    }
}



void traverseDotDump(struct node *N,FILE* outputFile)
{

    if (N != NULL)

    {
        // traverseDotDump(N->left,outputFile);
        fprintf (outputFile, "%d [label=%d,color=black];\n",N->data,N->data);
        if (N->left != NULL)

            fprintf (outputFile, "%d -> %d ;\n", N->data, (N->left)->data);



        if (N->right != NULL)

            fprintf (outputFile, "%d -> %d;\n", N->data, (N->right)->data);

        traverseDotDump(N->right,outputFile);

        traverseDotDump (N->left, outputFile);

    }


    return;
}

void dotDump(struct node *N, FILE *outFile)

{

    gName++;

    fprintf (outFile, "digraph BST {\n",gName);



    traverseDotDump (N, outFile);

    fprintf (outFile, "}\n");

}

FILE *outFile;





int main(int argc, char** argv)
{



    FILE *outputFile;
    FILE *pipe;

    struct node *N,temp;

    int ch,i,data;





    if (argc != 2)

    {

        printf(" need one argument  \n");

        exit(0);

    }



    outputFile = fopen ("bstt.dot", "w");

    fclose (outputFile);

    val = atoi(argv[1]);

    for(i=0; i<val; i++)

    {

        data=random()%1000;

        printf("%d\t",data);

        insertion(&root,data);



        outputFile = fopen ("bstt.dot", "a");

        if (outputFile != NULL)

        {



            dotDump (root,  outputFile);

        }

        fclose (outputFile);

    }









    while(1)

    {

        printf("\n1.Delete\n2.Display dotty \n3.Exit\n");

        printf("Enter your choice\n");

        scanf("%d",&ch);

        switch(ch)

        {







        case 1:
            printf("Enter element to be deleted\n");

            scanf("%d",&data);

            deletion(&root,NULL,data);

            printf("\nElement deleted\n");

            outputFile = fopen ("bst.dot", "a");

            dotDump (root,  outputFile);

            fclose (outputFile);

            break;



        case 2:

            pipe=popen("dot -Tps bst.dot -o bst.ps","w");

            pclose(pipe);

            pipe=popen("evince bst.ps","r");

            pclose(pipe);



            break;

        case 3:
            exit(0);
            break;

        default:
            printf("wrong choice\n");

            break;



        }





    }

    return 0;

}


