#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

float* insertion_sort(int tam, float* vetor);
float* quick_sort(int tam, float* vetor);

// VERSÃO CORRIGIDA PARA CONTAR TODAS AS LINHAS
int descobre_tamanho(char* nomeDoArquivo){
	FILE *arq;
	int tam = 0;
	char string_buffer[100]; // Buffer para ler cada linha

	if(!(arq = fopen(nomeDoArquivo, "r"))) goto nao_leu;

	// Inicia o laço para contar as linhas
	_loop_conta_linhas:
		// Se fgets retornar NULL, o arquivo acabou.
		if(fgets(string_buffer, 100, arq) == NULL) goto _fim_contagem;
		
		// Se leu uma linha com sucesso, incrementa o tamanho.
		tam++;
		goto _loop_conta_linhas;

	_fim_contagem:
		fclose(arq);
		return tam;

	nao_leu:
		printf("Nao foi possivel ler o arquivo para descobrir o tamanho.\n");
		exit(1);
}

char** le_linhas(int tam, char* nomeDoArquivo){
	FILE *arq;
	char** linhas = (char**) malloc (tam * sizeof (char*));
	
	if ((arq = fopen(nomeDoArquivo, "r"))) goto _arquivo_aberto_ok;
		printf("Nao foi possivel ler");
		exit(1);

	_arquivo_aberto_ok:
	int i = 0;
	_loop_le_linhas:
		if (i >= tam) goto _loop_le_linhas_fim;

		linhas[i] = (char*) malloc (20 * sizeof (char));
		fgets(linhas[i], 20, arq);
	
		i++;
		goto _loop_le_linhas;
	_loop_le_linhas_fim:

	fclose(arq);
	return linhas;
}

void escreve_no_final(char* nomeDoArquivo, char* texto){
	FILE *arq;

	if((arq = fopen(nomeDoArquivo, "a"))) goto _escreve_aberto_ok;
		printf("Nao foi possivel adicionar");
		exit(1);
	
	_escreve_aberto_ok:
	fprintf(arq, "%s", texto);
	fclose(arq);
}

float para_float(char* string){
    bool negativo = false;
    bool fracionario = false;
    float valor = 0.0f;
    float fator_fracionario = 1.0f;

	if(string != NULL) goto _string_nao_nula;
        return 0.0f;
    _string_nao_nula:

    if(*string != '-') goto _nao_negativo;
        negativo = true;
        string++;
    _nao_negativo:

    _loop_para_float:
    	if(*string == '\0' || *string == '\n' || *string == '\r') goto _loop_para_float_fim;
    
    	if(!(*string == '.' && !fracionario)) goto _nao_eh_ponto_decimal;
            fracionario = true;
            goto _pular_logica_digito; 
        _nao_eh_ponto_decimal:

        if(!(*string >= '0' && *string <= '9')) goto _pular_logica_digito;
            int digito = *string - '0';
            
			if(fracionario) goto _parte_fracionaria;
                valor = valor * 10.0f + digito;
				goto _fim_logica_digito;
			_parte_fracionaria:
                fator_fracionario /= 10.0f;
                valor += digito * fator_fracionario;
			_fim_logica_digito:

		_pular_logica_digito:
        string++;
		goto _loop_para_float;
	_loop_para_float_fim:

    if(!negativo) goto _fim_para_float;
        valor = -valor;
    _fim_para_float:

    return valor;
}

void inverter_substring(char* string, int inicio, int fim) {
    _loop_inverter:
		if(inicio >= fim) goto _loop_inverter_fim;

        char temp = string[inicio];
        string[inicio] = string[fim];
        string[fim] = temp;
        
        inicio++;
        fim--;
		goto _loop_inverter;
	_loop_inverter_fim:;
}

char* para_string(float num) {
    char* string = (char*)malloc(20 * sizeof(char));
    int i = 0; 
    
    if (num >= 0) goto _num_nao_negativo;
        string[i++] = '-';
        num = -num;
	_num_nao_negativo:

    long int inteiro = (long int)num;
    int inicio_inteiro = i;

    if (inteiro != 0) goto _inteiro_nao_zero;
        string[i++] = '0';
		goto _fim_logica_inteiro;
	_inteiro_nao_zero:
		_loop_extrai_inteiro:
			if(inteiro <= 0) goto _loop_extrai_inteiro_fim;
            string[i++] = (inteiro % 10) + '0';
            inteiro /= 10;
			goto _loop_extrai_inteiro;
		_loop_extrai_inteiro_fim:
        inverter_substring(string, inicio_inteiro, i - 1);
	_fim_logica_inteiro:

    string[i++] = '.';

    float decimal = num - (long int)num;
    
	int p = 0;
	_loop_decimal:
		if(p >= 5) goto _loop_decimal_fim;
        decimal *= 10;
        int digito = (int)decimal;
        string[i++] = digito + '0';
        decimal -= digito;
		p++;
		goto _loop_decimal;
	_loop_decimal_fim:
    
    string[i] = '\0';

    return string;
}

/* INSERE VALORES DESORDENADOS NO VETOR */
void preenche_vetor(int tam, char** linhas, float* vetor){
	int i = 0;
	_preenche_loop:
		if (i >= tam) goto _preenche_loop_fim;
		vetor[i] = para_float(linhas[i]);
		i++;
		goto _preenche_loop;
	_preenche_loop_fim:;
}

/* FUNÇÃO QUE IMPRIME O VALOR */
void print_list(int tam, float* vetor){
	int i = 0;
	_print_loop:
        if (i >= tam) return;
		printf("%f\n", vetor[i]); // Imprime o elemento atual do vetor.
		i++;
		// Continua o loop até mostrar todos os elementos.
		goto _print_loop;
}

/* FUNÇÃO "ORDENA" */
float* ordena(int tam, int tipo, float* vetor){
	if (tam <= 1) return vetor; // Não precisa ordenar vetores de 0 ou 1 elemento
	// Verifica o tipo de ordenação.
	if (tipo == 0) goto _use_insertion;
	return quick_sort(tam, vetor); // Se não for 0, usa Quick Sort.
	_use_insertion:
	return insertion_sort(tam, vetor); // Se for 0, usa Insertion Sort.
}

/* INSERTION SORT */
float* insertion_sort(int tam, float* vetor) {
	int i = 1; // Começa do segundo elemento, pois o primeiro já está "ordenado".
	
	_insertion_loopi:
		if (i >= tam) goto _insertion_fim;
		float selecionado = vetor[i]; // O elemento a ser inserido.
		int j = i - 1; // Índice do último elemento ordenado.
		
		_insertion_loopj:
			if (j < 0) goto _fim_loopj;
			if(selecionado >= vetor[j]) goto _fim_loopj;

			vetor[j+1] = vetor[j]; // Desloca elemento maior para a direita.
			j--;
			goto _insertion_loopj;

		_fim_loopj:
			vetor[j+1] = selecionado;

		i++;
		goto _insertion_loopi;
	_insertion_fim:
	return vetor;
}

/* QUICK SORT */
void swap(float* a, float* b){
	float t = *a;
	*a = *b;
	*b = t;
}

int partition(float* vetor, int l, int h){
	float x = vetor[h]; // Pivô é o último elemento
	int i = l - 1; 
	int j = l; 

	_partition_loop:
		if(j >= h) goto _final;

		if(vetor[j] > x) goto _partition_ignora;
			i++;
			swap(&(vetor[i]), &(vetor[j]));
		
		_partition_ignora:
			j++;
			goto _partition_loop;

	_final:
	swap(&vetor[i + 1], &vetor[h]);
	return (i + 1);
}

float* quick_sort_iterative(float* vetor, int l, int h){
	if (l >= h) return vetor;
	int stack[h - l + 1];
	int top = -1; 

	stack[++top] = l;
	stack[++top] = h;

	_quick_loop: 
		if (top < 0) goto _quick_fim;

		h = stack[top--];
		l = stack[top--];

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
		
		goto _quick_loop;

	_quick_fim:
	return vetor;
}

float* quick_sort(int tam, float* vetor){
	return quick_sort_iterative(vetor, 0, tam - 1);
}

void main() {
	goto main;
	_arquivo_vazio:
        printf("Arquivo vazio ou nao encontrado.\n");
        return;

	main:
		char* arq = "teste.txt";
		int tam = descobre_tamanho(arq);

	    if (tam == 0) goto _arquivo_vazio;

		char** linhas = le_linhas(tam, arq);
		float* vetor = (float*) malloc (tam * sizeof (float));

		preenche_vetor(tam, linhas, vetor);
		ordena(tam, 0, vetor);
		printf("Vetor ordenado por Insertion Sort:\n");
		print_list(tam, vetor);
		printf("\n");

		int i = 0;
		_loop_main_escreve:
			if(i >= tam) goto _loop_main_escreve_fim;
			escreve_no_final(arq, "\n");
			char* str_num = para_string(vetor[i]);
			escreve_no_final(arq, str_num); // CORREÇÃO APLICADA AQUI
			free(str_num); 
			i++;
			goto _loop_main_escreve;
		_loop_main_escreve_fim:
		
		preenche_vetor(tam, linhas, vetor);
		ordena(tam, 1, vetor);
		printf("Vetor ordenado por Quick Sort:\n");
		print_list(tam, vetor);

	    i = 0;
	    _loop_free_linhas:
	        if (i >= tam) goto _loop_free_linhas_fim;
	        free(linhas[i]);
	        i++;
	        goto _loop_free_linhas;
	    _loop_free_linhas_fim:
		free(linhas);

		free(vetor);
}