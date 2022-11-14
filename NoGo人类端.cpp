//1.0.3版本更新日志：
//更新日期：2022年11月14日
//更新内容：1.优化了ai提升其对弈的胜率
//          2.优化了程序结构提高运行效率
//          3.更新了一部分操作内容从而优化操作体验
//特别鸣谢：感谢吴雨洙对本次更新中算法思路的提供
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
//#include "jsoncpp/json.h"
using namespace std;
bool oncheck[9][9]{ 0 };
int value[2][9][9]{ 0 };//价值函数，0为1，1为-1
int qipan[9][9]{ 0 };
int kexingyu[81][3]{ 0 };
int fanqipan[9][9]{ 0 };
bool av[2][9][9]{ 1 };//某位置是否可以走棋，0为1，1为-1
bool kaiju = true;
bool ifqihere[2][9][9];
int qi[2][9][9];
int p, q;
char z;
int ed = 0;
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
void ifav()//判断可走棋位置
{
	int m;
	for (int t = 0; t < 2; t++)
	{
		if (t == 0)m = 1;
		else m = -1;
		for (int a = 0; a <= 8; a++)
			for (int b = 0; b <= 8; b++)
			{
				if (qipan[a][b] != 0)
				{
					av[t][a][b] = false; continue;
				}
				if (!ifqi(a, b, m))
				{
					av[t][a][b] = false; continue;
				}
				setf(m);
				fanqipan[a][b] = m;
				if ((a+1)<=8&&qipan[a + 1][b] == -m)
					if (!ifqi(a + 1, b, -m)) { av[t][a][b] = false; continue; }
				if ((a-1)>=0&&qipan[a - 1][b] == -m)
					if (!ifqi(a - 1, b, -m)) { av[t][a][b] = false; continue; }
				if ((b+1)<=8&&qipan[a][b + 1] == -m)
					if (!ifqi(a, b + 1, -m)) { av[t][a][b] = false; continue; }
				if ((b-1)>=0&&qipan[a][b - 1] == -m)
					if (!ifqi(a, b - 1, -m)) { av[t][a][b] = false; continue; }
				av[t][a][b] = true;
			}
	}
	/*for (int t = 0; t < 2; t++)
	{
		for (int a = 0; a <= 8; a++)
		{
			for (int b = 0; b <= 8; b++)
				if (av[t][a][b])cout << "1 ";
				else cout << "0 ";
			cout << endl;
		}
		cout << endl;
	}*///调试时使用
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
	/*cout << "       1 2 3 4 5 6 7 8 9" << endl;
	for (int i = 0; i <= 8; i++)
	{
		cout << "第" << i + 1 << "行" << "  ";
		for (int j = 0; j <= 8; j++)
		{
			cout << muchqi(i, j, -1);
			if (j != 8)
				cout << ' ';
		}
		cout << endl;
	}*/
}
int randomlyset(int m)//随机走棋
{
	ifav();
	int a, b, l = 0,dd;
	if (m == 1)dd = 0;
	else dd = 1;
	do
	{
		a = rand() % 9;
		b = rand() % 9;
		//cout << a << ' ' << b << endl;
		l++;
		if (av[dd][a][b])
			break;
	} while (l <= 1000);
	if (l == 1000)
		return l;
	qipan[a][b] = m;
	p = a;
	q = b;
	return l;
}
bool hukou(int x, int y, int m)
{
	if (!av[-m][x][y]||!av[m][x][y])
		return false;
	int qi=0;
	if (x <= 7 && qipan[x + 1][y] == 0)qi++;
	if (x >= 1 && qipan[x - 1][y] == 0)qi++;
	if (y <= 7 && qipan[x][y + 1] == 0)qi++;
	if (y >= 1 && qipan[x][y - 1] == 0)qi++;
	if (qi == 1)
		return true;
	else
		return false;
}
int xiejiao(int x, int y, int m)
{
	int qi = 0;
	if (x <= 7 && y <= 7 && qipan[x + 1][y + 1] == m)qi++;
	if (x >= 1 && y <= 7 && qipan[x - 1][y + 1] == m)qi++;
	if (x >= 1 && y >= 1 && qipan[x - 1][y - 1] == m)qi++;
	if (x <= 7 && y >= 1 && qipan[x + 1][y - 1] == m)qi++;
	return qi;
}
int setvalue(int x,int y,int m)//估值函数  需要优化！！！！！
{
	int t;
	if (m == 1)t = 0;
	else t = 1;
	if (av[t][x][y])
	{
		qipan[x][y] = m;
		ifav();
		int zi[2]{ 0,0 };
		int ttt = 1;
		for (int t = 0; t < 2; t++)
		{
			for (int a = 0; a <= 8; a++)
				for (int b = 0; b <= 8; b++)
				{
					if (av[t][a][b] && (!av[(t + 1) % 2][a][b]))
						zi[t] += 10;
					if (hukou(a, b, ttt))
						zi[t] += 8;
				}
			ttt = -1;
		}
		if (m == 1)m = 0;
		if (m == -1)m = 1;
		value[m][x][y] = zi[m] - zi[(m + 1) % 2]+xiejiao(x,y,m)+xiejiao(x,y,-m);
		value[-m][x][y] = -value[m][x][y];
		qipan[x][y] = 0;
		ifav();
		return value[m][x][y];
	}
	else
		return -10000;
}
/*
估值函数设计思路：
    仅自己能下的点：（价值最高）
	对方不能下的点：价值？搏命时考虑
	虎口：价值次之，判定较难
*/
//void moni()模拟对局，深度优先
bool ifany(int m)
{
	ifav();
	int jud = 0,op=0;
	if (m == -1)op = 1;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			if (av[op][i][j])
			{
				jud = 1;
				break;
			}
		}
	if (jud == 0)return false;
	else return true;
}
void set(int m)//所需修改：优先搜索边角，加入价值函数的搜索
{
	ifav();
	int jud = 0;
	int op,ti=0,val;
	kexingyu[0][0] = -10000;
	if (m == -1)op = 1;
	else op = 0;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
			if (av[op][i][j])
			{
				jud = 1;
				break;
			}
		}
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
		{
				val=setvalue(i, j, m);
				if (val == 0)continue;
				else
				{
					if (val > kexingyu[0][0])
					{
						ti = 0;
						kexingyu[0][0] = val;
						kexingyu[0][1] = i;
						kexingyu[0][2] = j;
						ti++;
					}
					else if (val == kexingyu[0][0])
					{
						kexingyu[ti][0] = val;
						kexingyu[ti][1] = i;
						kexingyu[ti][2] = j;
						ti++;
					}
				}
		}
	ifav();
	int l;
	if (ti == 0)
	{
		if (qipan[0][0] == 0)
		{
			p = 0;
			q = 0;
			qipan[p][q] = m;
		}
		else if (qipan[0][8] == 0)
		{
			p = 0;
			q = 8;
			qipan[p][q] = m;
		}
		else if (qipan[8][0] == 0)
		{
			p = 8;
			q = 0;
			qipan[p][q] = m;
		}
		else if (qipan[8][8] == 0)
		{
			p = 8;
			q = 8;
			qipan[p][q] = m;
			kaiju = false;
		}
		else
	      randomlyset(m);
	}
	else
	{
		l = rand() % ti;
		p = kexingyu[l][1];
		q = kexingyu[l][2];
		qipan[p][q] = m;
	}
	return;
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
	srand((unsigned)time(0));
	for (int t = 0; t < 2; t++)
		for (int i = 0; i <= 8; i++)
			for (int j = 0; j <= 8; j++)
				av[t][i][j] = true;
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
			cout << endl;
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
		set(-k);
		if (!ifany(k))
		{
			cout << endl;
			prt();
			cout << "乐：你没有地方可以落子了，你输了！" << endl;
			break;
		}
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
				if (!ifqi(p + 1, q, -k))
				{
					cout << "乐： 你提走我(" << p + 1 << ',' << q << "）处的子了，不可以这样下哦。" << endl;
					continue;
				}
			if ((p - 1) >= 0 && qipan[p - 1][q] == -k)
				if (!ifqi(p - 1, q, -k))
				{
					cout << "乐： 你提走我(" << p + 1 << ',' << q << "）处的子了，不可以这样下哦。" << endl;
					continue;
				}
			if ((q + 1) <= 8 && qipan[p][q + 1] == -k)
				if (!ifqi(p, q + 1, -k))
				{
					cout << "乐： 你提走我(" << p + 1 << ',' << q << "）处的子了，不可以这样下哦。" << endl;
					continue;
				}
			if ((q - 1) >= 0 && qipan[p][q - 1] == -k)
				if (!ifqi(p, q - 1, -k))
				{
					cout << "乐： 你提走我(" << p + 1 << ',' << q << "）处的子了，不可以这样下哦。" << endl;
					continue;
				}
			break;
		}
		/*set(k);
		if (ed!=0)break;*///调试用，让ai自己与自己下棋
		if (!ifany(-k))
		{
			cout << endl;
			prt();
			cout << "乐：我打算下这里...不对，这样会提走你的子" << endl;
			cout << "乐：诶，我好像没有地方可以下了！" << endl;
			cout << "乐：好吧，你赢了。" << endl;
			break;
		}
	}
	return 0;
}
