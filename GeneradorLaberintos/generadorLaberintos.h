//
// Created by yerguerrero on 11/7/20.
//

#ifndef GENERADORLABERINTOS_GENERADORLABERINTOS_H
#define GENERADORLABERINTOS_GENERADORLABERINTOS_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <random>
#include <experimental/random>

#define forall(it, v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define MAXN 100000

using namespace std;
typedef pair<int, int> par;
using namespace std;
bool visitados[MAXN];
vector<par> Grafo[MAXN];
struct A{int o,d,c;} ;
vector<par> resultado;
vector<A> grafoK;
vector<int> laberinto;
int n;
struct arista{
    bool norte;
    bool oeste;
}arista;
vector<struct  arista> aristas;

priority_queue< pair<int,pair<int,int>> ,vector<pair<int, pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
#endif //GENERADORLABERINTOS_GENERADORLABERINTOS_H
