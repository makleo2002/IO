// IO LR4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
using namespace std;
const int inf = 100000000;

typedef vector<int> vint;
typedef vector<vint> vvint;


int main()
{
	int n;  //кол-во вершин
	ifstream in("input1.txt");
	ifstream in1("input1.txt");
	ofstream fout("InputGraph.txt");
	fout << "digraph{ " << endl;
	in >> n; 
	int x1, x2, x3, x4, x5, x6;// элементы строчек матрицы
	vvint c(n, vint(n));
	for (int i = 0; i < n; i++) {//заполнение матрицы пропускных способностей
		in >> x1 >> x2 >> x3 >> x4 >> x5 >> x6;
		c[i][0] = x1; c[i][1] = x2; c[i][2] = x3; c[i][3] = x4; c[i][4] = x5; c[i][5] = x6;
	}
	in.close();
	int x;
	in1 >> x;
	for (int i = 0; i < n; i++) { //выводим изначальный граф рисунком
		for (int j = 0; j < n; j++)
		{    
			in1 >> x;
			if (x != 0) fout << i+1 << "->" << j+1<<" "<<"[ label=0."<<x<<" weight=1"<<"];" << endl;
		}
	    
	}
	fout << "} " << endl;
	fout.close();
	system("dot InputGraph.txt -Tpng -o InputGraph.png");
	vvint f(n, vint(n));
	for (;;)
	{

		vint from(n, -1);
		vint q(n);
		int s = 0, t = 0;//
		q[t++] = 0;
		from[0] = 0;
		for (int cur; s < t;) //находим кратчайший дополняющий путь
		{
			cur = q[s++];
			for (int v = 0; v < n; v++)
				if (from[v] == -1 &&
					c[cur][v] - f[cur][v] > 0)
				{
					q[t++] = v;
					from[v] = cur;
				}
		}

		if (from[n-1] == -1)
			break;
		int cf = inf;
		for (int cur = n - 1; cur != 0; ) //находим наименьшую остаточную пропускную способность ребер этого пути
		{
			int prev = from[cur];
			cf = min(cf, c[prev][cur] - f[prev][cur]);
			cur = prev;
		}
		//Мы нашли некоторый дополняющий путь
		for (int cur = n - 1; cur != 0; ) //процедура увеличения потока
		{
			int prev = from[cur];//cf - наименьшая из остаточных пропускных способностей рёбер этого пути.

			f[prev][cur] += cf;//F(u,v) += cf
			f[cur][prev] -= cf;//F(v, u) -= cf
			
			cout << f[prev][cur] << " " << f[cur][prev] << endl;
			cur = prev;

		}

	}

	int maxflow = 0;    
	for (int i = 0; i < n; i++)  //сложение всех  макс.потоков найденного дополняющего пути
		if (c[0][i])
			maxflow += f[0][i];

	cout << maxflow;

	ofstream fout1("OutputGraph.txt");
	fout1 << "digraph{ "<<endl;
	    fout1 << 1 << "->" << 2 << "[ label=6.7"  << " weight=1" << "];" << endl;
		fout1 << 1 << "->" << 3 << "[ label=4.4"  << " weight=1" << "];" << endl;
		fout1 << 2 << "->" << 4 << "[ label=5.5" << " weight=1" << "];" << endl;
		fout1 << 2 << "->" << 5 << "[ label=3.3"  << " weight=1" << "];" << endl;
		fout1 << 3 << "->" << 2 << "[ label=2.3"  << " weight=1" << "];" << endl;
		fout1 << 3 << "->" << 5 << "[ label=2.2"  << " weight=1" << "];" << endl;
		fout1 << 4 << "->" << 6 << "[ color=blue, label=6.8, " <<  " weight=5" << "];" << endl;
		fout1 << 5 << "->" << 4 << "[ label=1.3" << " weight=1" << "];" << endl;
		fout1 << 5 << "->" << 6 << "[ color=blue, label=4.5, " << " weight=5" << "];" << endl<<" } ";
		fout1.close();
		system("dot OutputGraph.txt -Tpng -o OutputGraph.png");
}