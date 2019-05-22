/**
 * Programa que verifica a existencia de um ciclo negativo
 * utlizando o algoritmo de Floyd Warshall
 * @author Guilherme Reis Barbosa de Oliveira
 * @author Ian Rodrigues dos Reis Paixao
 * @author Jorge Allan de Castro Oliveira
 * @version 2 05/2019
 */

#include <iostream> 
using namespace std; 

// Numero de vertices do grafo
#define V 4 

// Define INF como o maior valor possivel
//Este valor sera usado para vertices nao conectados a nenhum outro
#define INF 99999 

// Imprime solucao da matriz 
void printSolucao(int dist[][V]); 

// Retorna se existe ciclo negativo ou nao
bool cicloNegfloydWarshall(int grafo[][V]) { 
    // dist[][] eh o vetor que armazena a menor distancia entre um par de vertices
    int dist[V][V], i, j, k; 

    // Inicializa a matriz dist com os mesmos valores do grafo
    // Podemos dizer que o menor caminho inicial eh a distancia entre os vertices sem nenhum no entre eles.
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            dist[i][j] = grafo[i][j];
        }
    }
	
    /* Adiciona todos os vetices no conjunto de vertices intermediarios. 
    -> Antes de inicializar, temos as menores distancias entre todos os pares de vertices de tal modo que as menores distancias considerem apenas um conjunto de vertices intermediarios {0, 1, 2, .. k}
    -> Apos o final da iteracao, vertice de numero k eh adicionado ao conjunto de vertices intermediarios {0, 1, 2, .. k} */
    for (k = 0; k < V; k++) { 
        // Pega todos os vertices pela origem um por um
        for (i = 0; i < V; i++) { 
            // Pega todos os vertices destinos acima do origem selecionado
            for (j = 0; j < V; j++) { 
                // Se o vertice k esta no menor caminho de i para j, entao o valor eh atualizado em dist[]i[j]
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j]; 
                }
            } 
        } 
    } 

    // Se a distancia de qualquer vertice para ele mesmo se torna negativa, entao existe um ciclo negativo
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            return true;
        }
    }
    return false; 
} 

int main() { 
    //Valores de entrada do grafo
    int grafo[V][V] = { {0 , -1 , INF , INF},
                        {INF , 0 , -1 , INF},
                        {INF , INF , 0 , -1},
                        {-1 , INF , INF , 0} }; 
                        
    //Imprime se existe ciclo negativo ou nao
    if (cicloNegfloydWarshall(grafo)) { 
        cout << "Sim"; 
    } else {
        cout << "Nao"; 
    }
    return 0; 
} 