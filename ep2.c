#include <stdio.h>
#include <stdlib.h>

void insertion_sort(int tam, float* vetor);
void quick_sort(int tam, float* vetor);

float to_float(){

}

char* to_string(){
	
}

/* INSERE VALORES DESORDENADOS NO VETOR */
void bagunca_vetor(float* vetor){
	float* valores = (float []){
		11.0f, 16.0f, 18.0f, 19.0f, 15.0f, 2.0f, 5.0f, 7.0f, 10.0f, 17.0f,
		9.0f, 4.0f, 13.0f, 12.0f, 3.0f, 1.0f, 14.0f, 8.0f, 6.0f, 20.0f
	};
	for(int i = 0; i < 20; i++) {
		vetor[i] = valores[i];
	}
}

/* FUNÇÃO QUE IMPRIME O VALOR */
void print_list(int tam, float* vetor){
	int i = 0;
	_print_loop:
		printf("%f\n", vetor[i]); // Imprime o elemento atual do vetor.
		i++;
		// Continua o loop até mostrar todos os elementos.
		if(i < tam)	goto _print_loop;
}

/* FUNÇÃO "ORDENA" */

float* ordena(int tam, int tipo, float* vetor){
	if (tipo == 0) return insertion_sort(tam, vetor);
	else return quick_sort(tam, vetor);
}

/* INSERTION SORT */
float* insertion_sort(int tam, float* vetor) {
	int i = 1; // Começa do segundo elemento, pois o primeiro já está "ordenado".
	
	_insertion_loopi: // Inicia o loop para percorrer o vetor.
		float selecionado = vetor[i]; // O elemento a ser inserido.
		int j = i-1; // Índice do último elemento ordenado.
		
		_insertion_loopj:
			// Pula o deslocamento se 'selecionado' já é maior ou igual.
			if(selecionado >= vetor[j]) goto _lugar_certo;

			vetor[j+1] = vetor[j]; // Desloca elemento maior para a direita.
			vetor[j] = selecionado; // Move 'selecionado' para a esquerda junto com o deslocamento.
			
			_lugar_certo:
				j--;
				// Verifica se ainda há elementos a comparar.
				if(j>=0) goto _insertion_loopj; // Continua o loop interno.

		i++;

		// Próximo elemento a ser inserido.
		if(i<tam) goto _insertion_loopi;
	return vetor;
}

/* QUICK SORT */
// Função auxiliar para trocar dois elementos
void swap(float* a, float* b){
	float t = *a;
	*a = *b;
	*b = t;
}

// Função para particionar o vetor
// Retorna o índice do pivô após a partição
int partition(float* vetor, int l, int h){
	float x = vetor[h]; // Pivô é o último elemento
	int i = l - 1; // Índice do menor elemento
	int j = l; // Índice do menor elemento

	// Percorre o vetor do índice l até h-1
	// e coloca os elementos menores ou iguais ao pivô à esquerda
	_partition_loop:
		if (j > h - 1) goto _final;

		if (vetor[j] > x) goto _partition_ignora;
			i++;
			swap(&(vetor[i]), &(vetor[j]));
		
		_partition_ignora:
			j++;
			goto _partition_loop;

	_final:
	// Coloca o pivô na posição correta
	swap(&vetor[i + 1], &vetor[h]);
	return (i + 1);
}

// Função para realizar o Quick Sort iterativo
float* quick_sort_iterative(float* vetor, int l, int h){

	int stack[h - l + 1];
	int top = -1; // Índice do topo da pilha

	stack[++top] = l; // Empilha o índice inicial
	stack[++top] = h; // Empilha o índice final

	_quick_loop: // Enquanto houver elementos na pilha

		// Desempilha os índices
		h = stack[top--];
		l = stack[top--];

		// Realiza a partição e obtém o índice do pivô
		int p = partition(vetor, l, h);

		// Se houver elementos à esquerda do pivô, 
		// empilha o índice do próximo elemento à esquerda
		int t = p - 1;
		if (t <= l) goto _quick_continue1;
			stack[++top] = l;
			stack[++top] = p - 1;

		_quick_continue1:
		// Se houver elementos à direita do pivô,
		// empilha o índice do próximo elemento à direita
		t = p + 1;
		if (t >= h) goto _quick_continue2;
			stack[++top] = p + 1;
			stack[++top] = h;
		
		_quick_continue2:
		// Continua o loop enquanto houver elementos na pilha
		if (top >= 0) goto _quick_loop;

	return vetor;
}

// Função para chamar o Quick Sort
float* quick_sort(int tam, float* vetor){
	// Tudo que é necessário é chamar a função iterativa
	// com os índices iniciais e finais do vetor.
	return quick_sort_iterative(vetor, 0, tam - 1);
}

void main() {
	float* vetor = (float*) malloc (20 * sizeof(float));
	bagunca_vetor(vetor);
	ordena(20, 0, vetor);
	printf("Vetor ordenado por Insertion Sort:\n");
	print_list(20, vetor);
	printf("\n");
	bagunca_vetor(vetor);
	ordena(20, 1, vetor);
	printf("Vetor ordenado por Quick Sort:\n");
	print_list(20, vetor);
	free(vetor); // Libera a memória alocada para o vetor
}