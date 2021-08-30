#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define N 30



typedef struct node//define the node of BT
{
	char data;
	struct node *left,*right;
}BT;

typedef struct myqueue    //define queue, when traverse BT layer by layer queue should be used, and when find the way from leaf
{                         //to root, queue still should be used.
	BT *p;//this is used to save BT node
	int pa;//this is used to save the location of current node's father in the queue
}QU;

int menu_select();//menu function
BT *create();//to create a BT and return where the root is
void inorder(BT *T);//use inorder way to traverse BT
void preorder(BT *T);//use preorder way to traverse BT
void postorder(BT *T);//use postorder way to traverse BT
void layorder(BT *T);//to traverse BT layer by layer
void swaptree(BT *T);//exchange the left and right brantch in BT
BT *deltree(BT *T);//free all the node in the BT
void showtree(BT *T);//output BT using brackets
int height(BT *T);//compute the height of BT
int leaf(BT *T);//compute the leaf number in BT



int menu_select()
{
	char i;
	do{
		system("cls");
		printf("1.create BT\n");
		printf("2.show BT\n");
		printf("3.property of BT\n");
		printf("4.traverse BT\n");
		printf("5.swap left and right branch\n");
		printf("6.destruct BT\n");
		printf("0.exit\n");
		printf("please input number(0-6):");
		i=getchar();
	}while(i<'0' || i>'7');
	return (i-'0');
}

main()
{
	BT *T=NULL;
	for(;;)
	{
		switch(menu_select())
		{
		case 1: getchar();
			    printf("please input preorder set with space:\n");
			    T=create();
				printf("create success\n");
			    system("pause");
				break;
		case 2: if(T)
				{
					printf("the BT is \n");
				    showtree(T);
				}
			    else
				    printf("BT is empty\n");
				printf("\n");
				system("pause");
				break;
		case 3: printf("the height of BT is:%d\n",height(T));
			    printf("number of leaf in BT is:%d\n",leaf(T));
				system("pause");
				break;
		case 4:if(T)
		        {
				   printf("\npreorder output is :\n");
				   preorder(T);
				   printf("\ninorder output is :\n");
				   inorder(T);
				   printf("\npostorder output is :\n");
				   postorder(T);
				   printf("\nlayer by layer output is :\n");
				   layorder(T);
				   printf("\n");
		        }
				else
				   printf("the BT is empty\n");
				system("pause");
				break;
		case 5:	swaptree(T);
				printf("swap success\n");
				system("pause");
				break;
		case 6:
			    T=deltree(T);
				printf("destruct success\n");
				system("pause");
				break;
		case 0:
			    printf("GOOD BYE\n");
			    system("pause");
				exit(0);

		}
	}
}

BT *create()
{
	char x;
	BT *p;
	scanf("%c",&x);
	if(x==' ')
		return NULL;
	else
	{
		p=(BT *)malloc(sizeof(BT));
		p->data=x;
		p->left=create();
		p->right=create();
		return p;
	}
}
void inorder(BT *T)
{
	if(T!=NULL)
    {
        inorder(T->left);
        printf("%c",T->data);
        inorder(T->right);
    }

}
void preorder(BT *T)
{
    if(T!=NULL)
    {
        printf("%c",T->data);
	    preorder(T->left);
	    preorder(T->right);

    }
}
void postorder(BT *T)
{
    if(T!=NULL)
    {
        postorder(T->left);
        postorder(T->right);
        printf("%c",T->data);

    }
}
void layorder(BT *T)
{
	BT *QU[N], *p;
    int front=0,rear=0;
    if(T==NULL)
        return ;
    else
    {
        QU[rear]=T;
        rear++;
    }
	while (rear != front)
	{
		p = QU[front];
		printf("%c", p->data);
        front++;
		if (p->left)
		{
			QU[rear] = p->left;
			rear++;
		}
		if (p->right)
		{
			QU[rear] = p->right;
			rear++;
		}

    }

}
void swaptree(BT *T)
{

	if(T==NULL)
        return;
    else
    {
        struct BT *temp;
        temp=T->left;
        T->left=T->right;
        T->right=temp;
        //will swap the branches//
        swaptree(T->left);
        swaptree(T->right);

        //just swap from left to right//
    }
}
BT *deltree(BT *T)
{
	if(T!=NULL)
    {
        deltree(T->left);
        deltree(T->right);
        free(T);
    }
}
void showtree(BT *T)
{
	if(!T)
		return;
	printf("%c",T->data);
	if(T->left||T->right)
	{
		printf("(");
		showtree(T->left);
		printf(",");
		showtree(T->right);
		printf(")");
	}
}
int height(BT *T)
{
    int h1,h2;
	if(!T)
        {
            return 0;
        }
    else
    {
		h1 = height(T->left);
		h2 = height(T->right);
		return 1+((h1 > h2) ? h1 : h2); //1 + means that it should use root + other things

    }

}
int leaf(BT *T)
{
	if(T==NULL)
        return 0;
    if(T->left==NULL && T->right==NULL)
        return 1;
    else
        return leaf(T->left)+leaf(T->right);

}
