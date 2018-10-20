#include "libs/encrypt_message.h"

int encrypt_message() {
	S64_t e = 0;
	S64_t n = 0;
	U8_t byte = 0;
	S64_t lInt = 0;
	S8_t *tmp = (S8_t *) calloc(1, sizeof(S8_t));
	FILE *inputFile = NULL;
	FILE *outputFile = NULL;
	linked_list_t *string = new_list();

	printf("Digite o caminho para o arquivo que será criptografado:\n");
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
	S8_t outputFileName[strlen(inputFileName) + 4];
	strcpy(outputFileName, inputFileName);
	strcat(outputFileName, ".rsa\0");

	printf("Digite o caminho para o arquivo que contem a Chave pública:\n");
	scanf("%c", tmp);
	while ((*tmp) != '\n') {
		insert((void *) tmp, length(string), string);
		tmp = calloc(1, sizeof(U8_t));
		scanf("%c", tmp);
	}

	S8_t publicKeyFileName[length(string) + 1];
	i = 0;
	while(!is_empty(string)) {
		tmp = (S8_t *) remove_by_index(0, string);
		publicKeyFileName[i] = (*tmp);
		i++;
	}
	publicKeyFileName[i] = '\0';
	destroy_list(&string, (*free));

	printf("\n\tPegando Chave Pública...\n");
	inputFile = fopen(publicKeyFileName, "rb");
	if(inputFile == NULL) {
		printf("\n\tErro: Arquivo \"%s\" não encontrado.\n", publicKeyFileName);
	} else {
		fread(&n, sizeof(S64_t), 1, inputFile);
		fread(&e, sizeof(S64_t), 1, inputFile);
		fclose(inputFile);

		printf("\tSalvando arquivo criptografado...\n");
		inputFile = fopen(inputFileName, "rb");
		if(inputFile == NULL) {
			printf("\n\tErro: Arquivo \"%s\" não encontrado.\n", inputFileName);
		} else {
			outputFile = fopen(outputFileName, "wb");
			fread(&byte, sizeof(U8_t), 1, inputFile);
			while(!feof(inputFile)) {
				lInt = modular_pow(byte, e, n);
				fwrite(&lInt, sizeof(S64_t), 1, outputFile);
				fread(&byte, sizeof(U8_t), 1, inputFile);
			}
			fclose(inputFile);
			fclose(outputFile);
			printf("\tPronto!\n");
		}
	}
	
	printf("\nPressione qualquer tecla para continuar...");
	getchar();

	return 0;
}