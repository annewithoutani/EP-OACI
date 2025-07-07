#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void insertion_sort(int tam, float* vetor);
void quick_sort(int tam, float* vetor);

int descobre_tamanho(char* nomeDoArquivo){
	FILE *arq;
	char c;
	int tam = 0;
	char string[20];

	if(!(arq = fopen(nomeDoArquivo, "r"))){
		printf("Nao foi possivel ler");
		exit(1);
	}

	while(fgets(string, 20, arq) != NULL){
		tam++;
	}

	fclose(arq);
	return tam;
}

char** le_linhas(int tam, char* nomeDoArquivo){
	FILE *arq;
	char c;
	char** linhas = (char**) malloc (tam * sizeof (char*));
	
	if(!(arq = fopen(nomeDoArquivo, "r"))){
		printf("Nao foi possivel ler");
		exit(1);
	}

	for(int i = 0; i < tam; i++){
		linhas[i] = (char*) malloc (20 * sizeof (char));
		fgets(linhas[i], 20, arq);
	}

	fclose(arq);
	return linhas;
}

void escreve_no_final(char* nomeDoArquivo, char* texto){
	FILE *arq;

	if(!(arq = fopen(nomeDoArquivo, "a"))){
		printf("Nao foi possivel adicionar");
		exit(1);
	}
	
	fprintf(arq, "%s", texto);
	fclose(arq);
}

float para_float(char* string){
    bool negativo = false;
    bool fracionario = false;
    float valor = 0.0f;
    float fator_fracionario = 1.0f;

	if(string == NULL) {
        return 0.0f;
    }

    if(*string == '-') {
        negativo = true;
        *string++;
    }

    while(*string != '\0') {
    	if(*string == '.' && !fracionario) {
            fracionario = true;
        }

        if(*string >= '0' && *string <= '9') {
            int digito = *string - '0';
            if(fracionario) {
                fator_fracionario /= 10.0f;
                valor += digito * fator_fracionario;
            } else {
                valor = valor * 10.0f + digito;
            }
        }

        *string++;
    }

    if(negativo) {
        valor = -valor;
    }

    return valor;
}

void inverter_substring(char* string, int inicio, int fim) {
    while (inicio < fim) {
        char temp = string[inicio];

        string[inicio] = string[fim];
        string[fim] = temp;
        
        inicio++;
        fim--;
    }
}

char* para_string(float num) {
    char* string = (char*)malloc(20 * sizeof(char));
    int i = 0; // Índice para a posição na string

    if (num < 0) {
        string[i++] = '-';
        num = -num;
    }

    int inteiro = (int)num;
    int inicio = i; // Marca onde os dígitos do inteiro começam

    if (inteiro == 0) {
        string[i++] = '0';
    } else {
        // Extrai os dígitos de trás para frente
        while (inteiro > 0) {
            string[i++] = (inteiro % 10) + '0';
            inteiro /= 10;
        }
        // Inverte a parte que acabamos de escrever
        inverter_substring(string, inicio, i - 1);
    }

    string[i++] = '.';

    float decimal = num - (int)num;
    // Precisão de 5 casas decimais
    for (int p = 0; p < 5; p++) {
        decimal *= 10;
        int digito = (int)decimal;
        string[i++] = digito + '0';
        decimal -= digito;
    }
    
    string[i] = '\0';

    return string;
}

/* INSERE VALORES DESORDENADOS NO VETOR */
void preenche_vetor(int tam, char** linhas, float* vetor){
	for(int i = 0; i < tam; i++){
		vetor[i] = para_float(linhas[i]);
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
		if(j > h - 1) goto _final;

		if(vetor[j] > x) goto _partition_ignora;
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
		if(t <= l) goto _quick_continua1;
			stack[++top] = l;
			stack[++top] = p - 1;

		_quick_continua1:
		// Se houver elementos à direita do pivô,
		// empilha o índice do próximo elemento à direita
		t = p + 1;
		if(t >= h) goto _quick_continua2;
			stack[++top] = p + 1;
			stack[++top] = h;
		
		_quick_continua2:
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
	char* arq = "teste.txt";
	int tam = descobre_tamanho(arq);
	char** linhas = le_linhas(tam, arq);

	float* vetor = (float*) malloc (tam * sizeof (float));
	preenche_vetor(tam, linhas, vetor);
	ordena(tam, 0, vetor);
	printf("Vetor ordenado por Insertion Sort:\n");
	print_list(tam, vetor);
	printf("\n");

	for(int i = 0; i < tam; i++){
		escreve_no_final(arq, "\n");
		escreve_no_final(arq, para_string(vetor[i]));
	}

	preenche_vetor(tam, linhas, vetor);
	ordena(tam, 1, vetor);
	printf("Vetor ordenado por Quick Sort:\n");
	print_list(tam, vetor);

	free(vetor); // Libera a memória alocada para o vetor
}