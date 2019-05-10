#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trabED1.h"
#define TAM 41

//FORMA CORRETA DE EXECUTAR:
// 2015105530@labgrad:~$ cd Desktop/
// 2015105530@labgrad:~/Desktop$ gcc -c trabED1.c
// 2015105530@labgrad:~/Desktop$ gcc -c progtrabED1.c
// 2015105530@labgrad:~/Desktop$ gcc -o nada trabED1.o progtrabED1.o
// 2015105530@labgrad:~/Desktop$ ./nada
// 2015105530@labgrad:~/Desktop$

int main(void){
	FILE* arq;
	int i;
	char texto[TAM];
	char texto_formatado[TAM];
	char nome_pagina[TAM];
	char nome_arquivo[TAM];
	char editor[TAM];
	char contribuicao[TAM];
	char insere1[TAM];
	char insere2[TAM];

	Lista* lst = inilistapagina();//Inicializa pagina vazia.
	LstEditor* lst_editor = inicializaeditor();//Inicializa vazio.
	LstContrib* lst_contrib = inicializacontrobuicao();//Inicializa lista vazia de contribuicoes.
	LstLink* lst_link = inicializalink();

	arq = fopen("entrada.txt", "r");
	if(arq == NULL){
		printf("Erro na leitura do arquivo.\n");
		exit(1);
	}
	do{
		fscanf(arq, "%s", texto);
		if( strcmp(texto, "INSEREPAGINA") == 0){
			fscanf(arq, "%s %s", nome_pagina, nome_arquivo);
			inserepag(nome_pagina, nome_arquivo, lst);
		}
		else if(strcmp(texto, "INSEREEDITOR") == 0){
			fscanf(arq, "%s", editor);
			lst_editor = insereedit(lst_editor, editor);
		}
		else if(strcmp(texto, "INSERECONTRIBUICAO") == 0){
			fscanf(arq, "%s %s %s", nome_pagina, editor, contribuicao);
			inserecontrib(lst_contrib, lst_editor, lst, nome_pagina, editor, contribuicao);
		}
		else if(strcmp(texto, "INSERELINK") == 0){
			fscanf(arq, "%s %s", insere1, insere2);
			inserelink(lst, lst_link, insere1, insere2);
		}
		else if(strcmp(texto, "RETIRAEDITOR") == 0){
			fscanf(arq, "%s", editor);
			lst_editor = retiraeditor(editor, lst_editor, lst_contrib);
		}
		else if(strcmp(texto, "RETIRACONTRIBUICAO") == 0){
			fscanf(arq, "%s %s %s", nome_pagina, editor, nome_arquivo);
		}
		else if(strcmp(texto, "IMPRIMEPAGINA") == 0){
			fscanf(arq, "%s", nome_pagina);
			ImprimePagina(nome_pagina, lst, lst_contrib, lst_link);
		}
		else if(strcmp(texto, "CAMINHO") == 0){
			fscanf(arq, "%s %s", insere1, insere2);
		}
		else if(strcmp(texto, "RETIRAPAGINA") == 0){
			fscanf(arq, "%s", nome_pagina);
		}
		else if(strcmp(texto, "IMPRIMEWIKED") == 0){
		}
	}while( strcmp(texto, "FIM") != 0);

	fclose(arq);

	return 0;
}
