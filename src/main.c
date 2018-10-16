#include <stdio.h>
#include "libs/generate_public_key.h"
#include "libs/encrypt_message.h"
#include "libs/decrypt_message.h"
#include "../DEBUG/debug.h"

int main(int argc, char *argv[]) {
	int state = 0;

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
				state = generate_public_key();
				break;
			case 2:
				state = encrypt_message();
				break;
			case 3:
				state = decrypt_message();
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