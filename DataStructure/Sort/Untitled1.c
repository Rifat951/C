
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#define N 20
typedef struct node//when use radix sort,data should be saved in list, this is node define of the list
{
	int data;
	struct node *next;
}LI;
void getdata(int *a,int n);//get n random data
void showdata(int *a,int n);//show data
void showlist(LI *head);//show the list
void heapsort(int *a,int n);//heap sort function
void adjust(int *a,int n,int index);//to do adjustment in heap in the place of "index"
void quicksort(int *a,int n);//to do quick sort
int pivot(int *a,int low,int high);//in the range from low to high, divide array into three part,
                                   //first all elements are smaller or equal to the pivot, the pivot,
                                   //and the last part in which all elements are larger or equal to pivot,
                                   //and return the position of the pivot finally
void Qsort(int *a,int low,int high);//recursive function to realize the quick sort
void mergesort(int *a,int n);// to do merge sort
void Msort(int *a,int *t,int low,int high);//recursive function to realize the merge sort
void Merge(int *a,int *t,int low,int high);//use t as aided array to merge (low,m),(m+1,high)this two ordered part together
                                           //m=(low+hig)/2
void radixsort(LI *head,int n);//to do radix sort
void distrbute(LI *head,LI *L[10],LI *rear[10],int i);//for the ith time, to distribute the data
void collect(LI *head,LI *L[10],LI *rear[10]);//to collect data

main()
{
	int a[N+1];//a is original array, when we do sort,we begin from 1 to N.a[0] sometime is used as guard.
	LI *head=(LI *)malloc(sizeof(LI));//when use radix sort,data should be saved in list, this is head of the list.
	head->next=NULL;//create an empty list at first
	printf("heap sort is:\n");
	heapsort(a,N);// to do heap sort
	printf("quick sort is:\n");
	quicksort(a,N);//to do quick sort
	printf("merge sort is:\n");
	mergesort(a,N);// to do merge sort
	printf("radix sort is:\n");
	radixsort(head,N);	//to do radix sort
}

//////////////////////get random data///////////////////////////////////////////////
void getdata(int *a,int n)
{
	int i;
	srand(time(0));
	for(i=1;i<=n;i++)
		a[i]=rand()%100;//all the random data is smaller than 100
}


//////////////////////////show the array//////////////////////////////////////////
void showdata(int *a,int n)
{
	int i,j;
	for(i=1,j=0;i<=n;i++)
	{
		printf("%d, ",a[i]);
		j++;
		if(j%18==0)
			printf("\n");
	}
	printf("\n");
}

////////////////////////show the list//////////////////////////////////////////////
void showlist(LI *head)
{
	LI *p;
	int j=0;
	p=head->next;
	while(p)
	{
		printf("%d, ",p->data);
		j++;
		if(j%18==0)
			printf("\n");
		p=p->next;
	}
	printf("\n");
}

/////////////////////////////heap sort/////////////////////////////////////////////
void heapsort(int *a,int n)
{
	int i,t;
	getdata(a,n);//get random data
	for(i=n/2;i>=1;i--)
    {
        adjust(a,n,i);
    }
    for(i=1;i<n;i++)
    {
        t=a[1];
        a[1]=a[n-i+1];
        a[n-i+1]=t;
        adjust(a,n-i,1);
    }
    //adjust(a,n-i,1);
	showdata(a,n);//show sort result
}
void adjust(int *a,int n,int index)
{
    int i,j,t;
	i=index;
	j=2*i;
	while(j<=n)
    {
        if(j+1<=n && a[j]>a[j+1])
        {
            j++;

        }
        if(a[i]>a[j])
        {
            t=a[j];
            a[i]=a[j];
            a[j]=t;
            i=j;
            j=2*i;
        }
        else
            break;
    }

}

/////////////////////////////quick sort////////////////////////////////////////////////////
void quicksort(int *a,int n)
{
	getdata(a,n);//get random data
	Qsort(a,1,n);//call the function to do quick sort
	showdata(a,n);//show sort result

}
int pivot(int *a,int low,int high)
{
    if(low<high)
    {
        a[0]=a[low];

        while(low<high)
        {
            while(low<high && a[high]>=a[0])
            {
                high --;
            }
                a[low]=a[high];

            while(low<high && a[low]<=a[0])
            {
                low++;
            }
                a[high]=a[low];
        }
        a[low]=a[0];

        return low; //low her is the right place for pivot//
    }

}
void Qsort(int *a,int low,int high)
{
	int m;

	if(low<high)
    {
        m=pivot(a,low,high);
        Qsort(a,low,m-1);
        Qsort(a,m+1,high);
    }
}

////////////////merge sort/////////////////////////////////////////////////////////////
void mergesort(int *a,int n)
{
	int t[N+1];//aided array
	getdata(a,n);//get random data
	Msort(a,t,1,n);//call the function to do merge sort
	showdata(a,n);//show sort result

}
void Msort(int *a,int *t,int low,int high)
{
	int m;
	if(low==high)
    {
        t[low]=a[low];
    }
    else
    {
        m=(low+high)/2;
        Msort(a,t,low,m);
        Msort(a,t,m+1,high);
        Merge(a,t,low,high);
    }
}
void Merge(int *a,int *t,int low,int high)
{
	int i,j,k,m;

	m=(low+high)/2;

	for(i=low,j=m+1,k=low;i<=m && j<=high;) //they need to be written in the same time otherwise it will cross its limit
    {
        if(a[i]<a[j])
        {
            t[k]=a[i];
            i++;
            k++;
        }
        else if(a[i]>a[j])
        {
            t[k]=a[j];
            j++;
            k++;
        }
        else
        {
            t[k]=a[i];
            k++;
            i++;
            t[k]=a[j];
            k++;
            j++;
        }
    }
        while(i<=m)
        {
            t[k]=a[i];
            i++;
            k++;
        }
        while(j<=high)
        {
            t[k]=a[j];
            j++;
            k++;
        }
        for(i=low;i<=high;i++)
        {
            a[i]=t[i];
        }

}

///////////////////////////radix sort//////////////////////////////////////////////////////
void radixsort(LI *head,int n)
{
	int i;
	LI *p,*L[10],*rear[10];
	srand(time(0));
	for(i=1;i<=n;i++)//get random data and insert these data into the list(at first, the list is empty)
	{
		p=(LI *)malloc(sizeof(LI));
		p->data=rand()%100;
		p->next=head->next;
		head->next=p;
	}
	for(i=0;i<10;i++)//create 10 empty list
	{
		L[i]=(LI *)malloc(sizeof(LI));
		L[i]->next=NULL;
		rear[i]=L[i];// this is pointer which points to the end of each list, since all the lists are empty, so the rear points to head
	}
	for(i=1;i<=2;i++)//all the data is smaller than 100, so after 2 times of distribute and collect, sort work can be done
	{
		distrbute(head,L,rear,i);
		collect(head,L,rear);
	}
	showlist(head);//show the radix sort result
}
void distrbute(LI *head,LI *L[10],LI *rear[10],int i)
{

}
void collect(LI *head,LI *L[10],LI *rear[10])
{

}
