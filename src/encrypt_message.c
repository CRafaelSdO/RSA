#include "libs/encrypt_message.h"

S64_t char_to_int(char);

int encrypt_message() {
	char tmp;
	S64_t e = 0;
	S64_t n = 0;
	S64_t *tmpPtr = NULL;
	FILE *text_file = NULL;
	linked_list_t *lst = new_list();

	printf("Digite a mensagem que será criptografada: ");
	scanf("%c", &tmp);
	while (tmp != '\n') {
		tmpPtr = calloc(1, sizeof(S64_t));
		(*tmpPtr) = char_to_int(tmp);
		insert((void *) tmpPtr, length(lst), lst);
		scanf("%c", &tmp);
	}

	printf("Digite a Chave pública: ");
	scanf("%lld%lld", &n, &e);
	getchar();

	printf("\n\tSalvando Mensagem Criptografada...\n");
	text_file = fopen("encrypted_message.txt", "w");
	for (S64_t i = 0; i < length(lst); i++) {
		tmpPtr = get_item_of_index(i, lst);
		fprintf(text_file, "%lld ", modular_pow((*tmpPtr), e, n));
	}
	fclose(text_file);
	printf("\tPronto!\n");
	destroy_list(&lst, (*free));

	printf("\nPressione qualquer tecla para continuar...");
	getchar();

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