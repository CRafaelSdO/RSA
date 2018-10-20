#include "libs/decrypt_message.h"

int decrypt_message() {
	S64_t p = 0;
	S64_t q = 0;
	S64_t e = 0;
	S64_t n = 0;
	S64_t phi = 0;
	S64_t d = 0;
	U8_t byte = 0;
	S64_t lInt = 0;
	S8_t *tmp = (S8_t *) calloc(1, sizeof(S8_t));
	bool next = false;
	FILE *inputFile = NULL;
	FILE *outputFile = NULL;
	linked_list_t *string = NULL;

	while (!next) {
		printf("Digite p (deve ser primo):\n");
		scanf("%lld", &p);
		next = is_it_prime(p);
		if (!next) {
			printf("\n\t%lld Não é primo!\n\tTente novamente...\n\n", p);
		}
	}

	next = false;

	while (!next) {
		printf("Digite q (deve ser primo):\n");
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
		printf("Digite e (deve ser co-primo de %lld e maior que 1):\n", phi);
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

	string = new_list();
	printf("Digite o caminho para o arquivo que será descriptografado:\n");
	scanf("%c", tmp);
	while ((*tmp) != '\n') {
		insert((void *) tmp, length(string), string);
		tmp = (S8_t *) calloc(1, sizeof(S8_t));
		scanf("%c", tmp);
	}

	S8_t inputFileName[length(string) + 1];
	int i = 0;
	while(!is_empty(string)) {
		tmp = (S8_t *) remove_by_index(0, string);
		inputFileName[i] = (*tmp);
		i++;
	}
	inputFileName[i] = '\0';
	S8_t outputFileName[strlen(inputFileName) - 4];
	strcpy(outputFileName, inputFileName);
	outputFileName[strlen(inputFileName) - 4] = '\0';

	printf("\n\tSalvando arquivo descriptografado...\n");
	inputFile = fopen(inputFileName, "rb");
	if(inputFile == NULL) {
		printf("\n\tErro: Arquivo \"%s\" não encontrado.\n", inputFileName);
	} else {
		outputFile = fopen(outputFileName, "wb");
		fread(&lInt, sizeof(S64_t), 1, inputFile);
		while(!feof(inputFile)) {
			byte = modular_pow(lInt, d, n);
			fwrite(&byte, sizeof(U8_t), 1, outputFile);
			fread(&lInt, sizeof(S64_t), 1, inputFile);
		}
		fclose(inputFile);
		fclose(outputFile);
		printf("\tPronto!\n");
	}

	printf("\nPressione qualquer tecla para continuar...");
	getchar();

	return 0;
}