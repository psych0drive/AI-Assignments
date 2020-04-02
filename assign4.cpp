#include <bits/stdc++.h>
using namespace std;

#define AI 2
#define P 1
#define loss - 100
#define win 100
int allowed_moves(int n, int s)
{
	if (n <= s - 3)
		return 3;
	else if (n == s - 2)
		return 2;
	else if (n == s - 1)
		return 1;
	else return 0;
}

pair<int, int> minmaxalphabeta(int n, int marker, int winner, int depth, int alpha, int beta, int s)
{
	int best_move = 0;
	int best_score = (marker == AI) ? loss : win;
	if (n == s && marker == winner)
	{
		best_score = win;
		return make_pair(best_score, best_move);
	}

	int lm = allowed_moves(n, s);
	for (int i = 0; i < lm; i++)
	{
		int cm = n + i + 1;
		if (marker == AI)
		{
			int score = minmaxalphabeta(cm, P, winner, depth + 1, alpha, beta, s).first;
			if (best_score < score)
			{
				best_score = score - depth * 10;
				best_move = cm;
				alpha = max(alpha, best_score);
				cm = n;
				if (beta <= alpha) break;
			}
		}
		else
		{
			int score = minmaxalphabeta(cm, AI, winner, depth + 1, alpha, beta, s).first;
			if (best_score > score)
			{
				best_score = score + depth * 10;
				best_move = cm;
				beta = min(beta, best_score);
				cm = n;
				if (beta <= alpha) break;
			}
		}

		cm = n;
	}

	return make_pair(best_score, best_move);
}

pair<int, int> minmaxalphabeta2(int n, int marker, int winner, int depth, int alpha, int beta, int s)
{
	int best_move = 0;
	int best_score = (marker == P) ? loss : win;
	if (n == s && marker == winner)
	{
		best_score = win;
		return make_pair(best_score, best_move);
	}

	int lm = allowed_moves(n, s);
	for (int i = 0; i < lm; i++)
	{
		int cm = n + i + 1;
		if (marker == P)
		{
			int score = minmaxalphabeta2(cm, AI, winner, depth + 1, alpha, beta, s).first;
			if (best_score < score)
			{
				best_score = score - depth * 10;
				best_move = cm;
				alpha = max(alpha, best_score);
				cm = n;
				if (beta <= alpha) break;
			}
		}
		else
		{
			int score = minmaxalphabeta2(cm, P, winner, depth + 1, alpha, beta, s).first;
			if (best_score > score)
			{
				best_score = score + depth * 10;
				best_move = cm;
				beta = min(beta, best_score);
				cm = n;
				if (beta <= alpha) break;
			}
		}

		cm = n;
	}

	return make_pair(best_score, best_move);
}

int main()
{
	srand(time(0));
	int n, c, pr;
	cout << "Enter number of sticks(14,21,53) \n";
	cin >> n;
	if (n != 14 && n != 21 && n != 53)
	{
		cout << "incorrect selection(enter 14/21/53) \nclosing\n";
		return 0;
	}

	cout << "1. computer vs computer \n2. Player vs computer \n";
	cin >> c;
	pair<int, int> ai, p;
	ai.second = 0;
	p.second = 0;
	int sticks = n;
	if (c == 1)
	{
		pr = rand() % 100;
		if (pr < 50)
		{
			while (1)
			{
				cout << "no. of sticks left: " << sticks << endl << endl;
				p = minmaxalphabeta2(ai.second, P, P, 0, loss, win, n);
				cout << "Sticks picked by Player 1: ";
				cout << p.second - ai.second << endl << endl;
				sticks = sticks - p.second + ai.second;
				if (p.second == n)
				{
					cout << "Player 2 wins\n";
					return 0;
				}

				cout << "no. of sticks left: " << sticks << endl << endl;
				ai = minmaxalphabeta(p.second, AI, AI, 0, loss, win, n);
				cout << "Sticks picked by Player 2: ";
				cout << ai.second - p.second << endl << endl;
				sticks = sticks + p.second - ai.second;
				if (ai.second == n)
				{
					cout << "Player 1 wins\n";
					return 0;
				}
			}
		}
		else
		{
			while (1)
			{
				cout << "no. of sticks left: " << sticks << endl << endl;
				ai = minmaxalphabeta(p.second, AI, AI, 0, loss, win, n);
				cout << "Sticks picked by Player 2: ";
				cout << ai.second - p.second << endl << endl;
				sticks = sticks + p.second - ai.second;
				if (ai.second == n)
				{
					cout << "Player 1 wins\n";
					return 0;
				}

				cout << "no. of sticks left: " << sticks << endl << endl;
				p = minmaxalphabeta2(ai.second, P, P, 0, loss, win, n);
				cout << "Sticks picked by Player 1: ";
				cout << p.second - ai.second << endl << endl;
				sticks = sticks - p.second + ai.second;
				if (p.second == n)
				{
					cout << "Player 2 wins\n";
					return 0;
				}
			}
		}
	}
	else if (c == 2)
	{
		c = 0;
		pr = rand() % 100;
		if (pr < 50)
		{
			while (1)
			{
				cout << "no. of sticks left: " << sticks << endl << endl;
				cout << "Stickes picked by Player 1: ";
				cin >> c;
				cout << endl;
				sticks = sticks - c;
				if (c < 1 || c > 3)
				{
					cout << "Wrong Input. Try Again\n";
					continue;
				}

				c = ai.second + c;
				if (c == n)
				{
					cout << "computer wins\n";
					return 0;
				}
				cout << "no. of sticks left: " << sticks << endl << endl;
				pair<int, int> ai = minmaxalphabeta(c, AI, AI, 0, loss, win, n);
				cout << "Sticks picked by Player 2: ";
				cout << ai.second - c << endl << endl;
				sticks = sticks + c - ai.second;
				if (ai.second == n)
				{
					cout << "Player 1 wins\n";
					return 0;
				}
			}
		}
		else
		{
			int flag = 0;
			while (1)
			{
				if (flag == 0)
				{
					cout << "no. of sticks left: " << sticks << endl << endl;
					ai = minmaxalphabeta(c, AI, AI, 0, loss, win, n);
					cout << "Sticks picked by Player 2: ";
					cout << ai.second - c << endl << endl;
					sticks = sticks + c - ai.second;
					if (ai.second == n)
					{
						cout << "Player wins\n";
						return 0;
					}
				}

				flag = 0;
				cout << "no. of sticks left: " << sticks << endl << endl;
				cout << "Stickes picked by Player 1: ";
				cin >> c;
				cout << endl;
				sticks = sticks - c;
				if (c < 1 || c > 3)
				{
					cout << "Wrong Input. Try Again\n";
					flag = 1;
					continue;
				}

				if (c == n)
				{
					cout << "AI wins\n";
					return 0;
				}

				c = ai.second + c;
			}
		}
	}
	else
	{
		cout << "incorrect selection \nclosing..";
		return 0;
	}
}
