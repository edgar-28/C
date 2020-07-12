//
// Created by yerguerrero on 11/7/20.
//

#include "generadorLaberintos.h"

void creacionGrafo(int filas, int columnas) {
    n = filas * columnas;
    for (int i = 0; i < n; i++) {
        if (i >= columnas) {
            int vnorte = i - columnas;
            if (i < vnorte) {
                int num = experimental::randint(1,30);
                Grafo[i].push_back(make_pair(num, vnorte));
                Grafo[vnorte].push_back(make_pair(num, i));
            }
        }
        if (i / columnas < filas - 1) {
            int vsur = i + columnas;
            if (i < vsur) {
                int num = experimental::randint(1,30);
                Grafo[i].push_back(make_pair(num, vsur));
                Grafo[vsur].push_back(make_pair(num, i));
            }
        }
        if (i % columnas != columnas - 1) {
            int veste = i + 1;
            if (i < veste) {
                int num = experimental::randint(1,30);
                Grafo[i].push_back(make_pair(num, veste));
                Grafo[veste].push_back(make_pair(num, i));
            }
        }
        if (i % columnas != 0) {
            int voeste = i - 1;
            if (i < voeste) {
                int num = experimental::randint(1,30);
                Grafo[i].push_back(make_pair(num, voeste));
                Grafo[voeste].push_back(make_pair(num, i));
            }
        }
    }
}

void process(int v) {
    visitados[v] = true;
    forall(e, Grafo[v]) {
        if (!visitados[e->second]) {
            pq.push(make_pair(e->first, make_pair(v, e->second)));
        }
    }
}

vector<par> prim() {
    zero(visitados);
    process(0);
    while (sz(pq)) {
        pair<int, pair<int, int>> e = pq.top();
        pq.pop();
        if (!visitados[e.second.second]) {
            resultado.push_back(make_pair(e.second.first, e.second.second));
            process(e.second.second);
        }
    }
    return resultado;
}

void grafoKruskal() {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < sz(Grafo[i]); ++j) {
            grafoK.push_back({i, Grafo[i][j].second, Grafo[i][j].first});
        }
    }
}

struct UnionFind {
    vector<int> f;
    void init(int n) {f.clear();f.insert(f.begin(), n, -1);}
    int comp(int x) {return (f[x] == -1 ? x : f[x] = comp(f[x]));}
    bool join(int i, int j) { bool con = comp(i) == comp(j); if (!con) { f[comp(i)] = comp(j);}return con;}
} uf;

bool operator<(const A &o, const A &d) { return o.c < d.c; }

vector<par> kruskal() {
    sort(grafoK.begin(), grafoK.end());
    uf.init(n);
    forall(it, grafoK) {
        if (uf.comp(it->o) != uf.comp(it->d)) {
            uf.join(it->o, it->d);
            resultado.push_back(make_pair(it->o, it->d));
        }
    }
    return resultado;
}


void aristas_laberinto(int columnas) {
    for (int i = 0; i < n; i++) {
        arista.oeste=false;
        arista.norte=false;
        if (i >= columnas) {
            int vnorte = i - columnas;
            std::vector<par>::iterator c1 = std::find(resultado.begin(), resultado.end(), make_pair(i, vnorte));
            if (c1 != resultado.end()) {
                arista.norte = true;
            }
            else{
                std::vector<par>::iterator c2 = std::find(resultado.begin(), resultado.end(), make_pair(vnorte, i));
                if(c2 != resultado.end() ){
                    arista.norte = true;
                }
            }
        }
        if (i % columnas != 0) {
            int voeste = i - 1;
            std::vector<par>::iterator c1 = std::find(resultado.begin(), resultado.end(), make_pair(i, voeste));
            if (c1 != resultado.end()) {
                arista.oeste = true;
            } else {
                std::vector<par>::iterator c2 = std::find(resultado.begin(), resultado.end(), make_pair(voeste, i));
                if (c2 != resultado.end()) {
                    arista.oeste = true;
                }
            }
        }
        aristas.push_back(arista);
    }
}


void generar_laberinto(){
    for (int i = 0; i <sz(aristas); ++i) {
        if (!aristas[i].norte and !aristas[i].oeste){
            laberinto.push_back(0);
        }
        else if(!aristas[i].norte and aristas[i].oeste){
            laberinto.push_back(1);
        }
        else if(aristas[i].norte and !aristas[i].oeste){
            laberinto.push_back(2);;
        }
        else if(aristas[i].norte and aristas[i].oeste){
            laberinto.push_back(3);;
        }
    }
}

void imprimir_laberinto(int filas, int columnas){
    int ind=0;
    for (int i = 0; i <filas ; ++i) {
        for (int j = 0; j <columnas ; ++j) {
            printf("%d",laberinto[ind]);
            ind+=1;
        }
        printf("\n");
    }
}


int main(int args, char *argsv[]) {
    int filas = atoi(argsv[1]);
    int columnas = atoi(argsv[2]);
    char *algoritmo = argsv[3];
    creacionGrafo(filas, columnas);

    if (strcmp(algoritmo, "p") == 0 or strcmp(algoritmo, "P") == 0) {
        prim();
    } else if (strcmp(algoritmo, "k") == 0 or strcmp(algoritmo, "K") == 0) {
        grafoKruskal();
        kruskal();
    }
    aristas_laberinto(columnas);
    generar_laberinto();
    imprimir_laberinto(filas, columnas);
    return 0;
}