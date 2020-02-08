#include<bits/stdc++.h>
using namespace std;
int SIZE = 8;
int opt_cost = SIZE;
struct ChessBoardData
{
    string board;
    int cost;
    long int heuristic;
   ChessBoardData(string board,int cost,long int heuristic)
        :board(board),cost(cost),heuristic(heuristic)
        {
        }
};

	//some utility functions
	long int factorial(int x)
	{
	long int fact = 1;
	for(long int i = 1;i<=x;i++)
	fact*=x;
	return fact;
	}

	long int comb(int a, int b)
	{
	return factorial(a)/(factorial(b)*factorial(a-b));
	}

	//Creating initial state
ChessBoardData initChessBoard()
{
    string arr;
		for(int i=0;i<SIZE;++i)
			for(int j=0;j<SIZE;++j)
				arr+='0';
		return ChessBoardData(arr,0,0);
}

	int find(string arr)
	{
	    int i;
		for(i=0;i<SIZE;i++)
		{
			int flag = 0;
			for(int j=0;j<SIZE;j++)
			{
				if(arr[SIZE*i+j] == '1')
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
				return i;
		}
		return i;
	}

	long int gen_heuristic(string arr)
	{
	long int conf = 0;
	for(int i=0;i<SIZE;i++)
	{
	int rowSum = 0;
    int colSum = 0;
	for(int j=0;j<SIZE;j++)
			{
				rowSum+=arr[SIZE*i+j]-'0';
				colSum+=arr[SIZE*j+i]-'0';
			}
	conf+=comb(rowSum, 2) + comb(colSum, 2);
	}
	for(int i=0;i<SIZE;i++)
	{
		int leftSum = 0;
			int rightSum = 0;
			for(int j=0;j+i<SIZE;j++)
			{
				leftSum+=arr[SIZE*j+j+i]-'0';
				rightSum+=arr[SIZE*(j+i)+j]-'0';
			}
	conf+=comb(leftSum, 2) + comb(rightSum, 2);
	}
	for(int i=0;i<2*SIZE-1;i++)
	{
	int leftSum = 0;
			int rightSum = 0;
			if(i<SIZE)
			{
			   for(int j=0;i-j>=0;j++)
			   {
				   leftSum+=arr[SIZE*j+i-j]-'0';
			   }
			}
	else
			{
			   for(int j=i-SIZE+1;j<SIZE;j++)
			   {
			       rightSum+=arr[SIZE*j+i-j]-'0';
			   }
			}
	conf+=comb(leftSum, 2) + comb(rightSum, 2);
	}
	return conf;
	}

	//display valid state
	void display(string arr)
	{
		for(int i=0;i<SIZE;i++)
		{
			for(int j=0;j<SIZE;j++)
			{
				if(arr[SIZE*i+j]=='1')
                    printf("* ");
				else
                    printf("_ ");
			}
		printf("\n");
		}
	}
struct compareBoard
{
    bool operator()(ChessBoardData const& c1, ChessBoardData const& c2)
    {
        return c1.cost > c2.cost;
    }
};

int main()
	{
	ChessBoardData sol = initChessBoard();

	        priority_queue<ChessBoardData, vector<ChessBoardData>,compareBoard> ucs;
	 int count = 1;
        ucs.push(sol);


	while(!(ucs.empty()))
	{
	//dequeue head of the queue
	ChessBoardData c = ucs.top();
                ucs.pop();
                string probableAns = c.board;

	//check if the current state is valid
	if(c.cost + c.heuristic > opt_cost)continue;

	//find where to insert the queen
	int i = find(probableAns);

	//if the state is valid and solution is complete
	if(i==SIZE)
	{
	 cout<<"Solution Number"<<count<<"\n";
                        display(probableAns);
                        cout<<"\n\n";
                        count++;
	}
	else
	{
	//explore the current node and enqueue it
	for(int j=0;j<SIZE;j++)
	{
	probableAns = probableAns.substr(0, SIZE*i+j)+"1"+probableAns.substr(SIZE*i+j+1);
	ucs.push(ChessBoardData(probableAns,c.cost+1,gen_heuristic(probableAns)));
                        probableAns = c.board;
	}
	}
	}
	return 0;
	} 
