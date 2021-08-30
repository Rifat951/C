#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"
#include <stdbool.h>
#define N 43
typedef struct student//structure of record
{
	char name[10];
	char sex[6];
	char number[12];
	char mail[50];
}ST;

void Inittable(ST *A);//Initialize the hash table
void Readfromfile(ST *A);//Read data from txt file and build hash table
int Hashfun(char *number);// design the hash function based on the phone number
void Query(ST *A,char *number);//Hash search based on phone number
int convert(char *number);//convert the string to integer(used in hash function design)
void cutstring(char *number,int start,int length,char *result);//get the part of a srting(used in hash function design)
void reverse(char *s);//reverse a string

int main()
{
	char number[30];
	ST A[N];
	Inittable(A);
    Readfromfile(A);
	printf("please input phone number: ");
	scanf("%s",number);
	while(strcmp(number,"0")!=0)
	{

        Query(A, number);
		printf("\nplease input phone number: ");
	    scanf("%s",number);
	}
}
void Inittable(ST *A)
{
  int i;
  //A= malloc(sizeof(ST)*N);
  for(i=0; i<N; i++)
  {
    strcpy(A[i].number," ");
  }
  printf("Initialization successful....\n");
}
void Readfromfile(ST *A)
{
  FILE *head_open;
  char name[20],sex[4],number[12],mail[50]; // to make sure where to insert the data after reading
  int key,i;

  ST *p, *p1;
  head_open = fopen("info.txt", "r");
  while(fscanf(head_open,"%s%s%s%s",name,sex,number,mail)!=EOF)
  {

   key=Hashfun(number);
   if(strcmp(A[key].number," ")==0)
   {
       strcpy(A[key].name,name);
       strcpy(A[key].sex,sex);
       strcpy(A[key].number,number);
       strcpy(A[key].mail,mail);
   }
   for(i=1;i<N;i++)
   {
       if(strcmp(A[(key+i)%N)].number," "==0)// keeps it within the table's empty space
       {
           strcpy(A[(key+i)%N].name,name);
           strcpy(A[(key+i)%N].sex,sex);
           strcpy(A[(key+i)%N].number,number);
           strcpy(A[(key+i)%N].mail,mail);
           break;
       }
   }

  }

    fclose(head_open);

}

int Hashfun(char *number)// design the hash function based on the phone number
{
  
}
void Query(ST *A,char *number)//Hash search based on phone number
{
    int i,key;
    key=Hashfun(number);
    if(strcmp(A[key].number,number)==0)
    {
        printf("%s%s%s%s\n",A[key].name,A[key].sex,A[key].number,A[key].eamil);
        return 0;
    }
    else
    {
        for(i=0;i<N;i++)
        {
          if(strcmp(A[(key+i)%N)],number==0)// keeps it within the table's empty space
         {
           printf("%s%s%s%s\n",A[key].name,A[key].sex,A[key].number,A[key].eamil);
            return ;
         }
         if(strcmp(A[(key+i)%N)]," "==0)
         {
             printf("%s Doesnt exists...\n",number);
             return 0;
         }
        }

        printf("%s Doesnt exists...\n",number);
             return 0;
    }

}
