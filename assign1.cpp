#include <iostream>
#include<stdlib.h>
#define N 8
using namespace std;

struct node{
int array[8];
struct node *next;
};
struct node *fwd = NULL;
struct node *back = NULL;
struct node* tmp;
void push(int value,int ar[N]) {
int check =0;
   if (back == NULL) {
      back = (struct node *)malloc(sizeof(struct node));
      back->next = NULL;
      for(int i=0;i<N;i++)
      {
		  if(ar[i]==0 && check==0)
		  {
			  back->array[i]=value;
			  check++;
		  }
		  else
		  {
			  back->array[i]=ar[i];
		  }
      }
      fwd = back;
   } else {
      tmp=(struct node *)malloc(sizeof(struct node));
      back->next = tmp;
       for(int i=0;i<N;i++)
      {
      if(ar[i]==0 && check==0)
      {
      tmp->array[i]=value;
      check++;
 }
else
{
tmp->array[i]=ar[i];
}
 }
      tmp->next = NULL;
      back = tmp;
   }
}
int *pop() {
   tmp = fwd;
   if (tmp->next != NULL) {
      fwd=fwd->next;
      return tmp->array;
   } else {
     tmp = fwd;
      fwd = NULL;
      back = NULL;
      return tmp->array;
     
   }
   
}
void printSolution(int board[N][N],int ls[N])
{
	for(int i=0;i<N;i++)
	{
	board[i][ls[i]-1]=1;
	}
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << " | " << board[i][j];
        cout << "\n";
    }
    exit(0);

}

bool clear(int board[N][N], int cols, int l[N])
{
int check = 0;

    int i, j,rows,b[8][8]={0};

    for(int i=0;i<N;i++)
    {
    if(l[i]==0 && check==0)
    {
    rows=i;
    break;
}
if(l[i]!=0)
{
b[i][l[i]-1]=1;
}
}
    for (i = 0; i < rows; i++)
        if (b[i][cols])
            return false;

    for (i = rows, j = cols; i >= 0 && j >= 0; i--, j--)
        if (b[i][j])
            return false;

    for (i = rows, j = cols; i >= 0 && j < N; i--, j++)
        if (b[i][j])
            return false;
           
    if(rows==7)
    {
    l[rows]=cols+1;
    printSolution(board,l);
}

    return true;
}

void solve(int board[N][N],bool cond)
{
int array[N]= {0};
    if(!cond)
    {
		int *ptr;
		ptr = pop();
		for(int i=0;i<N;i++)
		{
		array[i]=*ptr;
		ptr++;
		}

		for(int i=0;i<N;i++)
		{
			if(clear(board,i,array))
				{
					push(i+1,array);
				}
		}
	}

		if(cond)
		{
			for (int i = 0; i < N; i++)
			{
				  push(i+1,array);
			}
			cond=false;
		}
		solve(board,cond);
}

int main()
{

    int board[N][N] = {{0,0,0,0,0,0,0,0},
    {0, 0, 0, 0,0, 0, 0, 0},
    {0, 0, 0, 0,0, 0, 0, 0},
    {0, 0, 0, 0,0, 0, 0, 0},
    {0, 0, 0, 0,0, 0, 0, 0},
    {0, 0, 0, 0,0, 0, 0, 0},
    {0, 0, 0, 0,0, 0, 0, 0},
    {0, 0, 0, 0,0, 0, 0, 0} };

    solve(board, true);
   
    return 0;
}
