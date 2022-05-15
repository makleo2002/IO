#include <iostream>
#include <cstring>
using namespace std;

#define INF INT_MAX

#define V 6   //количество вершин в графе

int G[V][V] = {    //матрица смежности
  {0,7,8,0,0,0},
  {7,0,11,2,0,0},
  {8,11,0,6,9,0},
  {0,2,6,0,11,9},
  {0,0,9,11,0,10},
  {0,0,0,9,10,0}
};

int main() {
    setlocale(LC_ALL, "Russian");
    int min_edge = 0;           // количество ребер в мин.остовном дереве


    bool selected[V+1];  //массив для отслеживания выбранной вершины

   
    memset(selected, false, sizeof(selected)); // изначально выбранное значение false

 // количество ребер в минимальном остовном дереве будет
 // всегда (V-1), где V - количество вершин в графе
 // выбераем 1-ю вершину и делаем ее истинной
    selected[0] = true;

    int x;            //  номер строки
    int y;            //  номер колонки
    int tree_weight=0; //суммарный вес остова

    cout << "Ребро" << " : " << "Вес";
    cout << endl;
    while (min_edge < V - 1) {

        int min = INF;
        x = 0;
        y = 0;

        for (int i = 0; i < V; i++) {
            if (selected[i]) {
                for (int j = 0; j < V; j++) {
                    if (!selected[j] && G[i][j]) { // не выбранное и есть ребро
                        if (min > G[i][j]) {
                            min = G[i][j];
                            x = i;
                            y = j;
                        }

                    }
                }
            }
        }
        tree_weight += G[x][y];
        cout << x+1 << " - " << y+1 << " :  " << G[x][y];
        cout << endl;
        selected[y] = true;
        min_edge++;
    }
    cout << "Вес минимального остова: "<<tree_weight;
    return 0;
}