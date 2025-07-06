/*──────────────────────────────────────────╖╓──────────────────────────────*/
/* 				Requisito 1					║║			Requisito 2			*/
/*──────────────────────────────────────────╢╟──────────────────────────────*/
/*	*float ordena(int tam, int tipo,		║║	Os dados devem ser			*/
/* 	float *vetor), onde:					║║	lidos de um arquivo,		*/
/* 											║║	o qual será passado			*/
/* 	· ordena: Nome da função;				║║	como entrada para			*/
/* 	· int tam: Tamanho do vetor a ser		║║	o programa.					*/
/*	ordenado;								║║								*/
/*	· int tipo: Especifica qual método		║║	O vetor ordenado			*/
/* 	será utilizado;							║║	de forma crescente			*/
/*	· float *vetor: Vetor com os valores	║║	deve ser escrito			*/
/*	a serem ordenados;						║║	no final do arquivo.		*/
/*	· retorno (*float): Retorna um			║║								*/
/*	ponteiro para o vetor ordenado.			║║								*/
/*──────────────────────────────────────────╜╙──────────────────────────────*/

#include <stdio.h>
#include <stdlib.h>

float* insertionSort(int tam, float* vetor) {
	for(int i=1; i<tam; i++) {			 //Começa em 1 porque se considerar só o primeiro número, já está ordenado
		float selecionado = vetor[i];
		for(int j=i-1; j>=0; j--) {		 //Passa de trás pra frente até o começo do vetor 
			if(selecionado < vetor[j]) {
				vetor[j+1] = vetor[j];
				vetor[j] = selecionado;
			}
		}
/*
	Prints que coloquei pra testar se cada iteração está certa
		printf("\nIteracao %i:\n", i);
		for(int j=0; j<tam; j++) {
			printf("%.2f  ", vetor[j]);
		}
*/
	}
}
float* quickSort(int tam, float* vetor) {
	//TODO
	//Precisei mexer rapidinho no ep de coo
}
/* float* ordena(int tam, int tipo, float* vetor) {
	if(tipo == 0)
		return insertionSort(tam, vetor);
	else if(tipo == 1)
		return quickSort(tam, vetor);
	else
		return NULL;
} */

int main(){
	float vetor[20] = {11.0, 16.0, 18.0, 19.0, 15.0, 2.0, 5.0, 7.0, 10.0, 17.0, 9.0, 4.0, 13.0, 12.0, 3.0, 1.0, 14.0, 8.0, 6.0, 20.0};
	selectionSortComLabel(20, vetor);
	return 0;
}

/* -------------------- CÓDIGOS COM LABEL (LEMBRANDO QUE NÃO RODOU) --------------------

float* insertionSortComLabel(int tam, float* vetor) {
	int j, i = 1;
	loopi:
		float selecionado = vetor[i];
		loopj:
			j = i-1;
			if(selecionado >= vetor[j]) {
				goto lugar_certo;
			}
			vetor[j+1] = vetor[j];
			vetor[j] = selecionado;
			lugar_certo:
				j--;
				if(j>=0) {
					goto loopj;
				}
		printf("\nIteração %i:\n", i);
		for(int k=0; k<tam; k++) {
			printf("%.2f  ", vetor[k]);
		}
		i++;
		if(i<tam) {
			goto loopi;
		}
}

*/