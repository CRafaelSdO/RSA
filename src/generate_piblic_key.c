#include "libs/generate_public_key.h"

int generate_public_key() {
	S64_t p = 0;
	S64_t q = 0;
	S64_t e = 0;
	S64_t n = 0;
	S64_t phi = 0;
	bool next = false;
	FILE *text_file = NULL;

	while (!next) {
		printf("Digite p (deve ser primo): ");
		scanf("%lld", &p);
		next = is_it_prime(p);
		if (!next)
		{
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

	printf("\n\tSalvando Chave Pública...\n");
	text_file = fopen("public_key.txt", "w");
	fprintf(text_file, "Chave Pública = (%lld, %lld)", n, e);
	fclose(text_file);
	printf("\tPronto!\n");

	printf("\nPressione qualquer tecla para continuar...");
	getchar();

	return 0;
}