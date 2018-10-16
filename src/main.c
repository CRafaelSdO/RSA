#include <stdio.h>
#include <stdlib.h>
#include "libs/prime_numbers.h"
#include "libs/linked_list.h"
#include "../DEBUG/debug.h"

S64_t char_to_int(char);

S64_t int_pow(S64_t, S64_t);

int main(int argc, char *argv[]) {
	int state = 0;

	S64_t p, q, e, n, phi;
	bool next;
	FILE *text_file = NULL;

	char tmp;
	S64_t *tmpPtr = NULL;
	linked_list_t *string = NULL;
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
				phi = 0;
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
				phi = (p - 1) * (q - 1);

				while(!next){
					printf("Digite e (deve ser co-primo de %lld e maior que 1): ", phi);
					scanf("%lld", &e);
					next = are_they_co_primes(phi, e);
					if(!next) {
						printf("\n\t%lld Não é co-primo de %lld!\n\tTente novamente...\n\n", e, phi);
					} else if(e == 1) {
						printf("\n\te == 1!\n\tTente novamente...\n\n");
						next = false;
					}
				}

				getchar();
				
				printf("\n\tSalvando Chave Pública...\n");
				text_file = fopen("public_key.txt", "w");
				fprintf(text_file, "Chave Pública = (%lld, %lld)", n, e);
				fclose(text_file);
				printf("\tPronto!\n");

				printf("\nPressione qualquer tecla para continuar...");
				getchar();

				state = 0;
				break;
			case 2:
				string = new_list();
				printf("Digite a mensagem que será criptografada: ");
				scanf("%c", &tmp);
				while(tmp != '\n') {
					tmpPtr = calloc(1, sizeof(S64_t));
					(*tmpPtr) = char_to_int(tmp);
					insert((void *) tmpPtr, length(string), string);
					scanf("%c", &tmp);
				}

				printf("Digite a Chave pública: ");
				scanf("%lld%lld", &n, &e);
				getchar();

				printf("\n\tSalvando Mensagem Criptografada...\n");
				text_file = fopen("encrypted_messege.txt", "w");
				for(S64_t i = 0; i < length(string); i++) {
					tmpPtr = get_item_of_index(i, string);
					fprintf(text_file, "%lld ", int_pow((*tmpPtr), e) % n);
				}
				fclose(text_file);
				printf("\tPronto!\n");

				printf("\nPressione qualquer tecla para continuar...");
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

S64_t char_to_int(char m) {
	if(m >= 'A' && m <= 'Z') {
		return (S64_t) m - 65;
	} else if(m >= 'a' && m <= 'z') {
		return (S64_t) m - 97;
	} else if(m == ' ') {
		return 26;
	} else {
		return -1;
	}
}

S64_t int_pow(S64_t b, S64_t e) {
	S64_t r = b;
	for(S64_t i = 2; i <= e; i++) {
		r *= b;
	}
	return r;
}