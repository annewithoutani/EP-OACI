#───────────────────────────────────────────╖╓──────────────────────────────#
# 				Requisito 1					║║			Requisito 2			#
#───────────────────────────────────────────╢╟──────────────────────────────#
#	*float ordena(int tam, int tipo,		║║	Os dados devem ser			#
# 	float *vetor), onde:					║║	lidos de um arquivo,		#
# 											║║	o qual será passado			#
# 	· ordena: Nome da função;				║║	como entrada para			#
# 	· int tam: Tamanho do vetor a ser		║║	o programa.					#
#	ordenado;								║║								#
#	· int tipo: Especifica qual método		║║	O vetor ordenado			#
# 	será utilizado;							║║	de forma crescente			#
#	· float *vetor: Vetor com os valores	║║	deve ser escrito			#
#	a serem ordenados;						║║	no final do arquivo.		#
#	· retorno (*float): Retorna um			║║								#
#	ponteiro para o vetor ordenado.			║║								#
#───────────────────────────────────────────╜╙──────────────────────────────#

# FUNÇÕES
# main
# descobre_tamanho
# le_linhas
# escreve_no_final
# para_float
# inverter_substring
# para_string
# preenche_vetor
# print_list
# ordena
# insertion_sort
# swap
# partition
# quick_sort_recursivo
# quick_sort

.data
	ARQ: .asciiz "teste.txt"

.text
	.globl main
	main:

	descobre_tamanho:

	le_linhas:

	escreve_no_final:

	para_float:

	#-------------------------------------------------------#
	# inverter_substring(char* string, int inicio, int fim)	#
	# string -> $a0, inicio -> $a1, fim -> $a2				#
	#-------------------------------------------------------#
	inverter_substring:
		_loop_inverter:
			slt $t4, $a1, $a2 	# inicio >= fim ? 1 : 0
			beq $t4, $zero, _loop_inverter_fim
						
			add $t0, $a0, $a1	# Calcula o endereço de string[inicio]
			add $t1, $a0, $a2	# Calcula o endereço de string[fim]

			lb $t2, 0($t0)		# Salva string[inicio] no $t2
			lb $t3, 0($t1)		# Salva string[fim] no $t3
			sb $t3, 0($t0)		# Salva $t3 no endereço de inicio
			sb $t2, 0($t1)		# Salva $t3 no endereço de fim

			
			addi $a1, $a1, 1	# inicio++;
			addi $a2, $a2, -1	# fim--;
			
			b _loop_inverter

		_loop_inverter_fim:
			# Retorna para quem chamou
			jr $ra

	para_string:

	#-------------------------------------------------------#
	# preenche_vetor(int tam, char** linhas, float* vetor)	#
	# tam -> $a0, linhas -> $a1, vetor -> $a2				#
	#-------------------------------------------------------#												
	preenche_vetor:
		addi $sp, $sp, -16
		sw $ra, 12($sp)		# Salva $ra
		sw $a0, 8($sp)		# Armazena o tamanho 
		sw $a1, 4($sp)		# Armazena o array de strings
		sw $a2, 0($sp)		# Armazena o vetor

		move $s0, $a0		# $s0 = tam
		move $s1, $a1		# $s1 = endereço base do array
		move $s2, $a2		# $s2 = endereço base do vetor
		
		li $t0, 0			# int i = $t0

		_preenche_loop:
			slt $t3, $t0, $s0 	# i >= tam ? 1 : 0
			beq $t3, $zero, _preenche_loop_fim

			#vetor[i] = para_float(linhas[i]);
			# 1. Obtem o argumento para para_float: linhas[i]
			sll $t1, $t0, 2		# Offset = i * 4
			add $t2, $s1, $t1	# Endereço de linhas[i]: endereço_base + offset
			lw $a0, 0($t2)		# Carrega em $a0 para a chamada da função

			# 2. Chama a função para_float
			jal para_float		# Pula para a função para_float e salva o endereço de retorno em $ra
								# Após o retorno, o resultado (float) estará em $f0

			# 3. Armazena o resultado na posição vetor[i]
			sll $t1, $t0, 2		# Offset = i * 4
			add $t2, $s2, $t1	# Endereço de vetor[i]: endereço_base + offset
			s.s $f0, 0($t2)		# Armazena o float de $f0 em vetor[i]

			# i++;
			addi $t0, $t0, 1

			# Volta pra _preenche_loop;
			b _preenche_loop

		_preenche_loop_fim:
			# Restaura os registradores que salvamos no início
			lw $s2, 0($sp)
			lw $s1, 4($sp)
			lw $s0, 8($sp)
			lw $ra, 12($sp)
			addi $sp, $sp, 16
			
			# Retorna para quem chamou a função
			jr $ra

	print_list:

	#-------------------------------------------#
	# ordena(int tam, int tipo, float* vetor)	#
	# tam -> $a0, tipo -> $a1, vetor -> $a2		#
	#-------------------------------------------#
	ordena:
		# Como ambas as funções esperam tam em $a0 e vetor em $a1
		# e $a0 já contém 'tam'
		move $t0, $a1	# Copia $a1 para $t0
		move $a1, $a2	# Copia 'vetor' para $a1

		beq $t0, $zero, _usa_insertion	# Se tipo == 0, usa insertion

		# Se não, chama quick_sort
		j quick_sort

		_usa_insertion:
			# Chama insertion_sort
			j insertion_sort

	#-----------------------------------------------------------------------
	# insertion_sort(int tam -> $a0, float* vetor -> $a1)
	# Ordena o vetor usando o algoritmo de Insertion Sort.
	#-----------------------------------------------------------------------
	insertion_sort:
		# --- Prólogo ---
		# Salva 5 registradores $s na pilha -> 5 * 4 = 20 bytes
		addi $sp, $sp, -20
		sw $s0, 16($sp)		# Salva $s0 (tam)
		sw $s1, 12($sp)		# Salva $s1 (vetor)
		sw $s2, 8($sp)		# Salva $s2 (i)
		sw $s3, 4($sp)		# Salva $s3 (selecionado)
		sw $s4, 0($sp)		# Salva $s4 (j)

		# Copia argumentos para registradores salvos
		move $s0, $a0
		move $s1, $a1

		# --- Início do Algoritmo ---
		# int i = 1;
		li $s2, 1

		_insertion_loopi:
			# if (i >= tam) goto _insertion_fim;
			slt $t0, $s2, $s0	# $t0 = (i < tam) ? 1 : 0
			beq $t0, $zero, _insertion_fim

				# float selecionado = vetor[i];
				sll $t0, $s2, 2		# offset = i * 4
				add $t1, $s1, $t0	# endereço de vetor[i]
				lw $s3, 0($t1)		# $s3 = padrão de bits do float 'selecionado'

				# int j = i - 1;
				addi $s4, $s2, -1	# $s4 = j

			_insertion_loopj:
				# if (j < 0) goto _fim_loopj;
				slt $t1, $zero, $s4	# selecionado < vetor[j] ? 1 : 0
				beq $t1, $zero, _fim_loopj

				sll $t0, $s4, 2				# offset = j * 4
				add $t1, $s1, $t0			# endereço de vetor[j]
				lw $t2, 0($t1)				# $t2 = padrão de bits de vetor[j]
				slt $t0, $s3, $t2			# $t0 = (selecionado < vetor[j]) ? 1 : 0
				beq $t0, $zero, _fim_loopj 	# Se for falso (selecionado >= vetor[j]), pula.

					# vetor[j+1] = vetor[j];
					addi $t3, $s4, 1	# $t3 = j + 1
					sll $t3, $t3, 2		# offset = (j + 1) * 4
					add $t3, $s1, $t3	# endereço de vetor[j+1]
					sw $t2, 0($t3)		# Salva o valor no novo local.

					# j--;
					addi $s4, $s4, -1
					b _insertion_loopj

			_fim_loopj:
				# vetor[j+1] = selecionado;
				addi $t0, $s4, 1	# $t0 = j + 1
				sll $t0, $t0, 2		# offset = (j + 1) * 4
				add $t1, $s1, $t0	# endereço de vetor[j+1]
				sw $s3, 0($t1)		# Salva selecionado na posição final.

			addi $s2, $s2, 1 	# i++
			b _insertion_loopi

		_insertion_fim:
			move $v0, $s1	# Retorna o ponteiro do vetor

			# Restaura os registradores salvos
			lw $s0, 16($sp)
			lw $s1, 12($sp)
			lw $s2, 8($sp)
			lw $s3, 4($sp)
			lw $s4, 0($sp)
			addi $sp, $sp, 20

			# Retorna para quem chamou a função
			jr $ra

	#---------------------------#
	# swap(float* a, float* b)	#
	# 	a -> $a0, b -> $a1		#
	#---------------------------#
	swap:
		l.s $f0, 0($a0) # Carrega o float 'a' em $t0
		l.s $f1, 0($a1) # Carrega o float 'b' em $t1
		s.s $f1, 0($a0) # Salva 'b' no endereço de 'a'
		s.s $f0, 0($a1)	# Salva 'a' no endereço de 'b'

		# Retorna para quem chamou
		jr $ra

	#---------------------------------------#
	# partition(float* vetor, int l, int h)	#
	# vetor -> $a0, l -> $a1, h -> $a2		#
	#---------------------------------------#
	partition:
		addi $sp, $sp, -24
		sw $ra, 20($sp)
		sw $s0, 16($sp)		# $s0 = vetor
		sw $s1, 12($sp)		# $s1 = l
		sw $s2, 8($sp)		# $s2 = h
		sw $s3, 4($sp)		# $s3 = i
		sw $s4, 0($sp)		# $s4 = j

		move $s0, $a0
		move $s1, $a1
		move $s2, $a2
		
		# float x = vetor[h];
		sll $t0, $s2, 2		# offset = h * 4
		add $t1, $s0, $t0	# endereço de vetor[h]
		lw $t5, 0($t1)		# $t5 = x (pivô)
		addi $s3, $s1, -1	# int i = l - 1;
		move $s4, $s1		# int j = l;

		_partition_loop:
			slt $t0, $s4, $s2		# j < h ? 1 : 0
			beq $t0, $zero, _final 	# Se j >= h, pula para o final

			sll $t0, $s4, 2		# offset = j * 4
			add $t1, $s0, $t0	# endereço de vetor[j]
			lw $t6, 0($t1)		# $t6 = valor de vetor[j]
			
			slt $t0, $t5, $t6	# x < vetor[j] ? 1 : 0
			bne $t0, $zero, _partition_ignora
			
			addi $s3, $s3, 1 	# i++;
			
			# Swap(&(vetor[i]), &(vetor[j]))
			sll $t0, $s3, 2		# offset = i * 4
			add $a0, $s0, $t0	# $a0 = endereço de vetor[i]
			
			sll $t1, $s4, 2		# offset = j * 4
			add $a1, $s0, $t1	# $a1 = endereço de vetor[j]
			
			jal swap

		_partition_ignora:
			addi $s4, $s4, 1 	# j++;
			j _partition_loop

		_final:
			# Swap(&vetor[i + 1], &vetor[h]);
			addi $t0, $s3, 1	# t0 = i + 1
			sll $t0, $t0, 2		# offset = (i + 1) * 4
			add $a0, $s0, $t0	# $a0 = endereço de vetor[i+1]
			
			sll $t1, $s2, 2		# offset = h * 4
			add $a1, $s0, $t1	# $a1 = endereço de vetor[h]
			
			jal swap
			
			addi $v0, $s3, 1	# Coloca o valor de retorno em $v0

			# Restaura os registradores que salvamos no início
			lw $ra, 20($sp)
			lw $s0, 16($sp)
			lw $s1, 12($sp)
			lw $s2, 8($sp)
			lw $s3, 4($sp)
			lw $s4, 0($sp)
			addi $sp, $sp, 24

			# Retorna para quem chamou a função
			jr $ra

	#---------------------------------------------------#
	# quickSort_recursivo(float* vetor, int l, int h)	#
	# vetor -> $a0, l -> $a1, h -> $a2					#
	#---------------------------------------------------#
	quickSort_recursivo:
		addi $sp, $sp, -20
		sw $ra, 16($sp)
		sw $s0, 12($sp)		# Salva ponteiro vetor
		sw $s1, 8($sp)		# Salva l
		sw $s2, 4($sp)		# Salva h
		sw $s3, 0($sp)		# Espaço para salvar p

		move $s0, $a0
		move $s1, $a1
		move $s2, $a2

		# Base da recursão: se l >= h, apenas retorna
		slt $t0, $s1, $s2	# (l < h) ? 1 : 0
		beq $t0, $zero, _quick_recursivo_fim

		# Faz partition(vetor, l, h), com argumentos $a0, $a1, $a2
		jal partition
		move $s3, $v0		# Salva o resultado em $s3

		# Chamada recursiva para a esquerda
					addi $a2, $s3, -1	# $a2 = p - 1
		jal quickSort_recursivo

		# Chamada recursiva para a direita
		addi $a1, $s3, 1	# $a1 = p + 1
		jal quickSort_recursivo
		
		_quick_recursivo_fim:
			# Restaura os registradores que salvamos no início
			lw $ra, 16($sp)
			lw $s0, 12($sp)
			lw $s1, 8($sp)
			lw $s2, 4($sp)
			lw $s3, 0($sp)
			addi $sp, $sp, 20
			
			# Retorna para quem chamou a função
			jr $ra

	#-----------------------------------#
	# quick_sort(int tam, float* vetor)	#
	# tam -> $a0, vetor -> $a1			#
	#-----------------------------------#
	quick_sort:
		# quick_sort_recursivo espera: vetor em $a0, l em $a1, h em $a2		
		move $t0, $a0      # Salva 'tam' temporariamente em $t0
		move $a0, $a1      # Move 'vetor' para $a0 (posição correta)
		li $a1, 0          # Argumento 'l' = 0
		addi $a2, $t0, -1  # Argumento 'h' = tam - 1
		
		# O valor de retorno de quickSort_recursivo já está em $v0,
		# então 'jr $ra' nele retornará para onde chamou 'quick_sort'.
		b quickSort_recursivo