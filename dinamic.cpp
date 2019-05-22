/**
 * Algoritmo de programação dinamica para encontrar o caminho mais curto
 * sem ciclo negativo
 * @author Guilherme Reis Barbosa de Oliveira
 * @author Ian Rodrigues dos Reis Paixao
 * @author Jorge Allan de Castro Oliveira
 * @version 3 05/2019
 */

#include <iostream> 
#include <climits> 
using namespace std; 

// Define o numero de vertices do grafo e valor infinito
#define V 4 
#define INF INT_MAX 

// Funcao baseada em programacao dinamica para definir o menor caminho de u ate v com exatamente k arestas 
int menorCaminho(int grafo[][V], int u, int v, int k) { 
    // Tabela para ser preenchida usando programacao dinamica. A variavel sp[i][j][e] vai armazenar o peso do caminho mais curto de i ate j com exatamente k arestas
	int sp[V][V][k+1]; 

	// Loop para o numero de arestas de 0 ate k 
	for (int e = 0; e <= k; e++) { 
		for (int i = 0; i < V; i++) { // Origem 
			for (int j = 0; j < V; j++) { // Destino 
				// Inicializa variavel com valor INF 
				sp[i][j][e] = INF; 

				// Casos base 
				if (e == 0 && i == j) 
					sp[i][j][e] = 0; 
				if (e == 1 && grafo[i][j] != INF) 
					sp[i][j][e] = grafo[i][j]; 

                // Vai para o adjacente somente quando o numero de arestas é maior do que 1 
				if (e > 1) { 
					for (int a = 0; a < V; a++) { 
						// Deve haver uma aresta de i ate a e a não deve ser igual i ou j 
						if (grafo[i][a] != INF && i != a && 
							j!= a && sp[a][j][e-1] != INF) 
						sp[i][j][e] = min(sp[i][j][e], grafo[i][a] + 
													sp[a][j][e-1]); 
					} 
				} 
		    } 
		} 
	} 
	return sp[u][v][k]; 
}

// Retorna se existe ciclo negativo ou nao
bool cicloNegfloydWarshall(int grafo[][V]) { 
    // dist[][] eh o vetor que armazena a menor distancia entre um par de vertices
    int dist[V][V], i, j, k; 

    // Inicializa a matriz dist com os mesmos valores do grafo
    // Podemos dizer que o menor caminho inicial eh a distancia entre os vertices sem nenhum no entre eles
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

// Funcao principal para testar o programa
int main() { 
	// Criacao do grafo
	int grafo[V][V] = { { 0, 1, 100, 1000}, 
                        { 1, 0, 6, 5}, 
                        { 100, 6, 0, 10}, 
                        { 1000, 5, 10, 0 } }; 
                    
    int u = 0, v = 3, k = 2; 
    if(cicloNegfloydWarshall(grafo) == false) {
        cout << menorCaminho(grafo, u, v, k);
    }

	return 0; 
} 
