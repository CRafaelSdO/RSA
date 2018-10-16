#include <stdio.h>
#include <stdlib.h>
#include "libs/prime_numbers.h"
#include "../DEBUG/debug.h"

int main(int argc, char *argv[]) {
	int state = 0;
	bool next;
	FILE *public_key;
	s64_t p, q, e, n, fi;
	while(state != -1) {
		system("clear");
		switch (state) {
			case 0:
				printf("O que deseja fazer?\n\n");
				printf("\t1. Gerar chave pública.\n");
				printf("\t2. Criptografar mensagem.\n");
				printf("\t3. Descriptografar mensagem.\n");
				printf("\nDigite o número da opção desejada (use -1 para sair): ");
				scanf("%d", &state);
				getchar();
				break;
			case 1:
				p = 0;
				q = 0;
				e = 0;
				n = 0;
				fi = 0;
				next = false;
				while(!next){
					printf("Digite p (deve ser primo): ");
					scanf("%lld", &p);
					next = is_it_prime(p);
					if(!next) {
						printf("\n\t%lld Não é primo!\n\tTente novamente...\n\n", p);
					}
				}

				next = false;

				while(!next){
					printf("Digite q (deve ser primo): ");
					scanf("%lld", &q);
					next = is_it_prime(q);
					if(!next) {
						printf("\n\t%lld Não é primo!\n\tTente novamente...\n\n", q);
					}
				}

				next = false;
				n = p * q;
				fi = (p - 1) * (q - 1);

				while(!next){
					printf("Digite e (deve ser co-primo de %lld e maior que 1): ", fi);
					scanf("%lld", &e);
					next = are_they_co_primes(fi, e);
					if(!next) {
						printf("\n\t%lld Não é co-primo de %lld!\n\tTente novamente...\n\n", e, fi);
					} else if(e == 1) {
						printf("\n\te == 1!\n\tTente novamente...\n\n");
						next = false;
					}
				}

				getchar();
				
				printf("\n\tSalvando Chave Pública...\n");

				public_key = fopen("public_key.txt", "w");
				fprintf(public_key, "Chave Pública = (%lld, %lld)", n, e);
				fclose(public_key);

				printf("\tPronto!\n");
				printf("\nPressione qualquer tecla para continuar...");
				getchar();

				state = 0;
				break;
			case 2:
				printf("Opção 2");
				getchar();
				state = 0;
				break;
			case 3:
				printf("Opção 3");
				getchar();
				state = 0;
				break;
			default:
				printf("Opão inválida!\n");
				printf("Pressione qualquer tecla para continuar...");
				getchar();
				state = 0;
				break;
		}
	}
	
	return 0;
}