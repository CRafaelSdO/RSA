#include "libs/decrypt_message.h"

char int_to_char(S64_t);

int decrypt_message() {
	S64_t p = 0;
	S64_t q = 0;
	S64_t e = 0;
	S64_t d = 0;
	S64_t n = 0;
	S64_t phi = 0;
	S64_t *tmpPtr = NULL;
	FILE *text_file = NULL;
	bool next = false;
	linked_list_t *lst = NULL;

	while (!next) {
		printf("Digite p (deve ser primo): ");
		scanf("%lld", &p);
		next = is_it_prime(p);
		if (!next) {
			printf("\n\t%lld Não é primo!\n\tTente novamente...\n\n", p);
		}
	}

	next = false;

	while (!next) {
		printf("Digite q (deve ser primo): ");
		scanf("%lld", &q);
		next = is_it_prime(q);
		if (!next) {
			printf("\n\t%lld Não é primo!\n\tTente novamente...\n\n", q);
		}
	}

	next = false;
	n = p * q;
	phi = (p - 1) * (q - 1);

	while (!next) {
		printf("Digite e (deve ser co-primo de %lld e maior que 1): ", phi);
		scanf("%lld", &e);
		next = are_they_co_primes(phi, e);
		if (!next) {
			printf("\n\t%lld Não é co-primo de %lld!\n\tTente novamente...\n\n", e, phi);
		} else if (e == 1) {
			printf("\n\te == 1!\n\tTente novamente...\n\n");
			next = false;
		}
	}

	getchar();

	d = modular_inverse(e, phi);

	lst = new_list();
	text_file = fopen("encrypted_message.txt", "r");
	while (!feof(text_file)) {
		tmpPtr = calloc(1, sizeof(S64_t));
		fscanf(text_file, "%lld", tmpPtr);
		if (!feof(text_file)) {
			insert((void *)tmpPtr, length(lst), lst);
		}
	}
	fclose(text_file);

	printf("\n\tSalvando Mensagem Descriptografada...\n");
	text_file = fopen("decrypted_message.txt", "w");
	for (S64_t i = 0; i < length(lst); i++) {
		tmpPtr = get_item_of_index(i, lst);
		fprintf(text_file, "%c", int_to_char(modular_pow((*tmpPtr), d, n)));
	}
	fclose(text_file);
	printf("\tPronto!\n");
	destroy_list(&lst, (*free));

	printf("\nPressione qualquer tecla para continuar...");
	getchar();

	return 0;
}

char int_to_char(S64_t c) {
	if(c >= 0 && c <= 25) {
		return (char) c + 97;
	} else if(c == 26) {
		return ' ';
	} else {
		return -1;
	}
}