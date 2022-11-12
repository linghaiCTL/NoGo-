#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include<stdlib.h>
//#include "jsoncpp/json.h"
using namespace std;
bool oncheck[9][9]{ 0 };
int value[9][9]{ 0 };
int qipan[9][9]{ 0 };
int fanqipan[9][9]{ 0 };
bool ed = 0;
int p, q;
char z;
int cc()
{
	char f;
	cin >> f;
	if (f >= '0'&&f <= '9')
		return (f - '0');
	else
		return -2;
}
bool ifout(int a, int b)
{
	if (a >= 0 && a <= 8 && b <= 8 && b >= 0)
		return false;
	else
	{
		return true;
	}
}
bool checkqi(int a, int b)
{
	if (ifout(a, b))
	{
		cout << a << ' ' << b << endl;
		return false;
	}
	else
	{
		oncheck[a][b] = 1;
		if (oncheck[a + 1][b] != 1)
			if (!ifout(a + 1, b))
				switch (fanqipan[a + 1][b])
				{
				case 0: {oncheck[a][b] = 0; return true; }
				case 1:if (checkqi(a + 1, b)) { oncheck[a][b] = 0; return true; }
				case -1: break;
				}
		if (oncheck[a - 1][b] != 1)
			if (!ifout(a - 1, b))
				switch (fanqipan[a - 1][b])
				{
				case 0: {oncheck[a][b] = 0; return true; }
				case 1:if (checkqi(a - 1, b)) { oncheck[a][b] = 0; return true; }
				case -1:break;
				}
		if (oncheck[a][b + 1] != 1)
			if (!ifout(a, b + 1))
				switch (fanqipan[a][b + 1])
				{
				case 0: {oncheck[a][b] = 0; return true; }
				case 1:if (checkqi(a, b + 1)) { oncheck[a][b] = 0; return true; }
				case -1:break;
				}
		if (oncheck[a][b - 1] != 1)
			if (!ifout(a, b - 1))
				switch (fanqipan[a][b - 1])
				{
				case 0: {oncheck[a][b] = 0; return true; }
				case 1:if (checkqi(a, b - 1)) { oncheck[a][b] = 0; return true; }
				case -1:break;
				}
		oncheck[a][b] = 0;
		return false;
	}
}
void setf(int m)//m代表视角，1为后手，-1为先手
{
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
			fanqipan[i][j] = m * qipan[i][j];
}
bool ifqi(int aa, int bb, int mm)//此处为判断是否有气的函数合集
{
	setf(mm);
	return (checkqi(aa, bb));
}
void randomlyset(int m)//随机走棋
{
	int a, b, l = 0;
	do
	{
		a = rand() % 9;
		b = rand() % 9;
		l++;
		if (qipan[a][b] != 0)continue;
		if (!ifqi(a, b, m))continue;
		setf(m);
		fanqipan[a][b] = m;
		if (qipan[a + 1][b] == -m)
			if (!ifqi(a + 1, b, -m))continue;
		if (qipan[a - 1][b] == -m)
			if (!ifqi(a - 1, b, -m))continue;
		if (qipan[a][b + 1] == -m)
			if (!ifqi(a, b + 1, -m))continue;
		if (qipan[a][b - 1] == -m)
			if (!ifqi(a, b - 1, -m))continue;
		break;
	} while (l <= 1000);
	if (l > 200 && l <= 500)
		cout << "乐： 可以落子的地方越来越少了，这次我想了好久。" << endl;
	else if (l > 500 && l <= 1000)
		cout << "乐： 要决出胜负了吗？我感觉我没有多少地方可以下了。" << endl;
	if (l > 1000)
	{
		cout << endl;
		cout << "乐： 呃，我可以下这里...嘶，不对,这样提走你的子。" << endl;
		cout << "乐： 我好像没有地方可以落子了。" << endl;
		cout << "乐： 好吧，你赢了。" << endl;
		cout << "You win." << endl;
		ed = 1;
		return;
	}
	qipan[a][b] = m;
	p = a;
	q = b;
	return;
}
void prt()//打印当前棋盘，调试时使用
{
	cout << "       1 2 3 4 5 6 7 8 9" << endl;
	for (int i = 0; i <= 8; i++)
	{
		cout << "第" << i + 1 << "行" << "  ";
		for (int j = 0; j <= 8; j++)
		{
			if (qipan[i][j] == 1)
				cout << 'O';
			else if (qipan[i][j] == -1)
				cout << 'X';
			else if (qipan[i][j] == 0)
				cout << " ";
			if (j != 8)
				cout << ' ';
		}
		cout << endl;
	}
}
bool checklegal(int l, int r)
{
	if (ifout(l, r))
	{
		cout << "乐：不可以这样下棋的。" << endl;
		return false;
	}
	if (qipan[l][r] != 0)
	{
		cout << "乐：这个位置已经有棋子了。" << endl;
		return false;
	}
	return true;
}
void tishiyu(int k)
{
	while (true)
	{
		if (k == 1)cout << "你的棋子是 O " << endl;
		else cout << "你的棋子是 X " << endl;
		cout << "本回合你想要下棋的位置是：" << endl;
		cout << "它在第几行？  ";
		p = cc();
		p--;
		cout << "它在第几列？  ";
		q = cc();
		q--;
		if (checklegal(p, q))
			break;
		cout << "乐：请进行正确的操作哦。" << endl;
		cout << endl;
	}
	return;
}
bool huiqi()
{
	int w;
	cout << "乐： 怎么样？你打算悔棋吗？" << endl;
	cout << "输入 314 来悔棋，否则游戏结束" << endl;
	cin >> w;
	if (w == 314)
		return true;
	else
	{
		cout << "乐： 期待与您再次对弈哦，今天就先到这里啦。" << endl;
		return false;
	}
}
int main()
{
	int k;
	cout << "      No Go!      " << endl;
	cout << "  输入0以开始游戏" << endl;
	cout << "输入1以查看游戏规则" << endl;
	cout << " 其它功能正在开发" << endl;
	cout << endl;
	k=cc();
	system("CLS");
	while (k != 0)
	{
		while (k != 0 && k != 1)
		{
			cout << endl;
			cout << "乐：诶？我没有看懂你要干什么呢。" << endl;
			cout << "乐: 请进行正确的操作哦" << endl;
			cout << "  输入0以开始游戏" << endl;
			cout << "输入1以查看游戏规则" << endl;
			k = cc();
		}
		if (k == 1)
		{
			cout << "目标：想方设法不要让自己提走对方的棋子（围住），尽可能让自己的棋子被对方提走（围住）。" << endl;
			cout << endl;
			cout << "什么是“气”：" << endl;
			cout << "   要理解“提走”，首先要理解什么是“气”。一个棋子在棋盘上，与它直线紧邻的空点是这个棋子的“气”。" << endl;
			cout << "   棋子直线紧邻的点上，如果有同色棋子存在，则 它们便相互连接成一个不可分割的整体。它们的气也应一并计算。" << endl;
			cout << endl;
			cout << "什么是“提走”：" << endl;
			cout << "   当一个棋子没有“气”的时候它就要被提走。" << endl;
			cout << "   棋子直线紧邻的点上，如果有异色棋子存在，这口气就不复存在。" << endl;
			cout << "   如所有的气均为对方所占据，便呈无气状态。" << endl;
			cout << "   无气状态的棋子不能在棋盘上存在，也就是提子。把无气之子提出盘外的手段叫“提子”。" << endl;
			cout << endl;
			cout << "落子先后：黑子先手，双方轮流落子，落子后棋子不可移动。" << endl;
			cout << endl;
			cout << "判负条件：不围棋没有平局。一方输掉比赛，当且仅当以下至少一条发生：" << endl;
			cout << "   1）如果一方落子后吃掉了对方的棋子，则落子一方判负；" << endl;
			cout << "   2）对弈禁止自杀，落子自杀一方判负；；" << endl;
			cout << "   3）对弈禁止空手(pass)，空手一方判负。" << endl;
			cout << "开局限制：黑棋第一手禁止下在棋盘正中央" << endl;
			cout << endl;
			cout << "乐：如果你已经明白规则了；就输入0来开始游戏吧！" << endl;
			k = cc();
			system("CLS");
		}
	}
	cout << endl;
	/*cout << "请选择你要对弈的对象" << endl;
	cout << "1.随机棋手（对手没有策略，本难度适用于学习规则。）" << endl;
	cout << "更多难度正在开发哦" << endl;
	cin >> k;*/
	cout << "请问您是否想要先手？" << endl;
	cout << "如果要先手请输入1" << endl;
	cout << "如果想后手请输入2" << endl;
	k = cc();
	while (k != 2 && k != 1)
	{
		cout << endl;
		cout << "乐：诶？所以你是要先手还是要后手啊？" << endl;
		cout << "乐: 请进行正确的操作哦" << endl;
		cout << endl;
		cout << "如果要先手请输入1" << endl;
		cout << "如果想后手请输入2" << endl;
		k = cc();
		system("CLS");
	}
	if (k == 2)k = -1;
	if (k == 1)
	{
		cout << endl;
		while (true)
		{
			prt();
			tishiyu(k);
			if (p != 4 || q != 4)
				break;
			cout << endl;
			cout << "先手不可以走棋盘最中央哦！" << endl;
			cout << "重新选个合适的位置吧。" << endl;
		}
		qipan[p][q] = k;
	}
	while (true)
	{
		system("CLS");
		randomlyset(-k);
		if (ed)break;
		cout << endl;
		cout << "我在第" << p+1 << "行，第" << q+1 << "列落子" << endl;
		cout << endl;
		prt();
		cout << endl;
		cout << "轮到你了" << endl;
		while (true)
		{
			tishiyu(k);
			qipan[p][q] = k;
			if (!ifqi(p, q, k))
			{
				cout << endl;
				cout << "乐： 这里没有气啦，不能落子。" << endl;
				continue;
			}
			if ((p + 1) <= 8 && qipan[p + 1][q] == -k)
			{
				if (!ifqi(p + 1, q, -k))
				{
					prt();
					cout << "乐： 你提走我(" << p + 1 << ',' << q << "）处的子了，你输了" << endl;
					if (huiqi())
					{
						qipan[p][q] = 0;
						continue;
					}
					break;
				}

			}
			if ((p - 1) >= 0 && qipan[p - 1][q] == -k)
			{
				if (!ifqi(p - 1, q, -k))
				{
					prt();
					cout << "乐： 你提走我(" << p - 1 << ',' << q << "）处的子了，你输了" << endl;
					if (huiqi())
					{
						qipan[p][q] = 0;
						continue;
					}
					break;
				}

			}
			if ((q + 1) <= 8 && qipan[p][q + 1] == -k)
			{
				if (!ifqi(p, q + 1, -k))
				{
					prt();
					cout << "乐： 你提走我(" << p << ',' << q + 1 << "）处的子了，你输了" << endl;
					if (huiqi())
					{
						qipan[p][q] = 0;
						continue;
					}
					break;
				}

			}
			if ((q - 1) >= 0 && qipan[p][q - 1] == -k)
			{
				if (!ifqi(p, q - 1, -k))
				{
					prt();
					cout << "乐： 你提走我(" << p << ',' << q - 1 << "）处的子了，你输了" << endl;
					if (huiqi())
					{
						qipan[p][q] = 0;
						continue;
					}
					break;
				}
			}
			break;
		}
	}
	return 0;
}
