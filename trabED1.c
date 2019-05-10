#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trabED1.h"

//*************** DEFINICOES DOS TADS ***************

struct editor{
	char* nome;
	struct editor* prox;
};

struct lsteditor{
	Edit* prim;
	Edit* ult;
};

struct contribuicao{
	char* arq_contr;
	char* editor;
	char* pag;
};

struct celcontribuicao{
	Contrib info_contrib;
	struct celcontribuicao* prox;
};

struct lstcontrib{
	CelContrib* prim;
	CelContrib* ult;
};

struct link{
 	char* origem;
    char* arq_origem;
 	char* destino;
    char* arq_destino;
};

struct cellink{
	Link info_link;
	struct cellink* prox;
};

struct listalink{
	CelLink* prim;
	CelLink* ult;
};

struct pagina{
	char* nome_pag;//Variavel que vai guardar o nome de cada pagina.
	char* nome_arquivo;//Variavel que vai guardar o nome arquivo (Ex: fisica.txt). Depois, na funcao 'imprime' eu abro um arquivo com este nome e imprimo nele.
	LstContrib info;//Recebe o ponteiro que vai conter a contribuicao (trecho de texto) de determinado editor e o ponteiro para o nome deste editor junto com o ponteiro para o proximo editor.
	LstLink link;
};

struct celpagina{
	Pag info_pag;
	struct celpagina* prox;
};

struct lista{
	CelPagina* prim;
	CelPagina* ult;
};



//*************** FUNCOES DE INICIALIZACAO ***************



Lista* inilistapagina(){
	Lista* l = (Lista*)malloc(sizeof(Lista));
	l->prim = NULL;
	l->ult = NULL;
	return l;
}

LstEditor* inicializaeditor(){
	LstEditor* novo_editor = (LstEditor*)malloc(sizeof(LstEditor));
	novo_editor->prim = NULL;
	novo_editor->ult = NULL;
	return (novo_editor);
}

LstContrib* inicializacontrobuicao(){
	LstContrib* nova_contribuicao = (LstContrib*)malloc(sizeof(LstContrib));
	nova_contribuicao->prim = NULL;
	nova_contribuicao->ult = NULL;
	return (nova_contribuicao);
}

LstLink* inicializalink(){
	LstLink* novo_lk = (LstLink*)malloc(sizeof(LstLink));
	novo_lk->prim = NULL;
	novo_lk->ult = NULL;
	return (novo_lk);
}


//*************** FUNCOES DE MANIPULACAO DAS LISTAS ***************


LstEditor* insereedit(LstEditor* lst_editor, char* nome){
	Edit* edit = (Edit*)malloc(sizeof(Edit));
	edit->nome = malloc(strlen(nome + 1)*sizeof(char));
	strcpy(edit->nome, nome);//Copia o nome do editor.
	edit->prox = NULL;
	//Se lista for vazia.
	if(lst_editor->ult == NULL){
		lst_editor->prim = edit;
		lst_editor->ult = edit;
	}
	//Se nao for vazia.
	lst_editor->ult->prox = edit;
	lst_editor->ult = edit;
	return (lst_editor);
}

Pag* inictipopagina(char* nome, char* nomedoarq){
	Pag* new_pag = (Pag*)malloc(sizeof(Pag*));
	new_pag->nome_pag = malloc(strlen(nome + 1)*sizeof(char));
	strcpy(new_pag->nome_pag, nome);
	new_pag->nome_arquivo = malloc(strlen(nomedoarq + 1)*sizeof(char));
	strcpy(new_pag->nome_arquivo, nomedoarq);

	return (new_pag);
}

void insercaodepag(Pag* nova_pagina, Lista* lista){
	CelPagina* novo = (CelPagina*)malloc(sizeof(CelPagina));
	if(lista->ult == NULL){
		lista->prim = novo;
		lista->ult = novo;
	}

	lista->ult->prox = novo;
	lista->ult = novo;
	lista->ult->info_pag = *nova_pagina;
	lista->ult->prox = NULL;
}

void inserepag(char* nome, char* nomedoarq, Lista* lista){
	Pag* nova_pagina = inictipopagina(nome, nomedoarq);
	insercaodepag(nova_pagina, lista);
}

Edit* buscaeditor(char* editor, LstEditor* lst_editor){
	Edit* aux;
	for(aux = lst_editor->prim; aux != NULL; aux = aux->prox){
		if( strcmp(aux->nome, editor) == 0){
			return (aux);
		}
	}
	return (NULL);

}

CelPagina* buscapagina(char* pag, Lista* lista){
	CelPagina* aux = lista->prim;
	while(aux != NULL){
		if( strcmp(aux->info_pag.nome_pag, pag) == 0){
			return (aux);
		}
		aux = aux->prox;
	}
	return (NULL);
}

Contrib* inictipocontrib(char* nome_pagina, char* editor, char* contribuicao){
	Contrib* novo = (Contrib*)malloc(sizeof(Contrib));
	novo->pag = malloc( strlen(nome_pagina + 1)*sizeof(char) );
	strcpy(novo->pag, nome_pagina);
	novo->editor = malloc( strlen(editor + 1)*sizeof(char) );
	strcpy(novo->editor, editor);
	novo->arq_contr = malloc( strlen(contribuicao + 1)*sizeof(char) );
	strcpy(novo->arq_contr, contribuicao);
	return (novo);//Retorna o ponteiro para estrutura.
}

void criacelcontr(Contrib* contr, LstContrib* lst_contrib, CelPagina* pag_procur){
	CelContrib* nova = (CelContrib*)malloc(sizeof(CelContrib));
	if(lst_contrib->ult == NULL){
		lst_contrib->prim = nova;
		lst_contrib->ult = nova;
	}
	lst_contrib->ult->prox = nova;
	lst_contrib->ult = nova;
	lst_contrib->ult->info_contrib = *contr;
	lst_contrib->ult->prox = NULL;
}

void inserecontrib(LstContrib* lst_contrib, LstEditor* lst_editor, Lista* lista, char* nome_pagina, char* editor, char* contribuicao){
	Edit* edit_procur = buscaeditor(editor, lst_editor);
	CelPagina* pag_procur = buscapagina(nome_pagina, lista);

	if(edit_procur == NULL || pag_procur == NULL){
		FILE* arq = fopen("log.txt", "a");
		if(arq == NULL){
			printf("Erro ao abrir arquivo log.txt\n");
			exit(1);
		}
		fprintf(arq, "Erro - Pagina %s ou editor %s nao existem\n", nome_pagina, editor);
		fclose(arq);
		//return (lst_contrib);
	}
	Contrib* contr = inictipocontrib(nome_pagina, editor, contribuicao);
	criacelcontr(contr, lst_contrib, pag_procur);
}


Link* inictipolink(CelPagina* origem, CelPagina* destino){
	Link* novo = (Link*)malloc(sizeof(Link));

    novo->origem = malloc( strlen(origem->info_pag.nome_pag + 1)*sizeof(char) );//Aloca espaco para o nome da pagina de origem.
	strcpy(novo->origem, origem->info_pag.nome_pag);//Copia o nome da pagina de origem para a estrutura "Link".
    novo->arq_origem = malloc( strlen(origem->info_pag.nome_arquivo + 1)*sizeof(char) );//Aloca espaco para o nome do arquivo de origem.
    strcpy(novo->arq_origem, origem->info_pag.nome_arquivo);//Copia o nome do arquivo de origem para a estrutura "Link".

    novo->destino = malloc( strlen(destino->info_pag.nome_pag + 1)*sizeof(char) );//Aloca espaco para o nome da pagina de destino.
    strcpy(novo->destino, destino->info_pag.nome_pag);//Copia o nome da pagina de destino para a estrutura "Link".
    novo->arq_destino = malloc( strlen(destino->info_pag.nome_arquivo + 1)*sizeof(char) );//Aloca espaco para o nome do arquivo de destino.
    strcpy(novo->arq_destino, destino->info_pag.nome_arquivo);//Copia o nome do arquivo de destino para a estrutura "Link".

	return (novo);
}

void criacellink(Link* link, LstLink* lst_link){
	CelLink* novo = (CelLink*)malloc(sizeof(CelLink));
	if(lst_link->ult == NULL){
		lst_link->prim = novo;
		lst_link->ult = novo;
	}
	lst_link->ult->prox = novo;
	lst_link->ult = novo;
	lst_link->ult->info_link = *link;
	lst_link->ult->prox = NULL;
}

void inserelink(Lista* lista, LstLink* lst_link, char* origem, char* destino){
	CelPagina* pag_origem = buscapagina(origem, lista);//Faz a busca na lista de paginas e armazena a pagina de origem.
	CelPagina* pag_destino = buscapagina(destino, lista);//Faz a busca na lista de paginas e armazena a pagina de destino.
	if(pag_origem == NULL || pag_destino == NULL){
		FILE* arq = fopen("log.txt", "a");
		if(arq == NULL){
			printf("Erro ao abrir arquivo log.txt\n");
			exit(1);
		}
		//Se nao achou pagina de origem ou de destino, imprime uma mensagem de erro.
		fprintf(arq, "Erro - Pagina de origem %s ou pagina de destino %s nao existem na lista!\n", origem, destino);
		fclose(arq);
	}
	Link* link = inictipolink(pag_origem, pag_destino);
	criacellink(link, lst_link);
}

LstEditor* retiraeditor(char* editor, LstEditor* lst_editor, LstContrib* lst_contrib){
    Edit* p = lst_editor->prim;
    Edit* ant = NULL;
    //printf("Retira editor: %s\n", p->nome);

    while(p != NULL && p->nome != editor){
    	ant = p;
    	p = p->prox;
    }
    if(p == NULL){
    	return(lst_editor);
    }
    if(p == lst_editor->prim && p == lst_editor->ult){
    	lst_editor->prim = NULL;
    	lst_editor->ult = NULL;
    	free(p);
    	return(lst_editor);
    }
    if(p == lst_editor->prim){
    	lst_editor->prim = p->prox;
    	free(p);
    	return(lst_editor);
    }
    if(p == lst_editor->ult){
    	lst_editor->ult = ant;
    	ant->prox = NULL;
    	free(p);
    }
    else{
    	ant->prox = p->prox;
    }
    free(p);
    return(lst_editor);
}


//*************** FUNCAO DE IMPRESSAO ***************


void ImprimePagina(char* pagina, Lista* lista, LstContrib* lst_contrib, LstLink* lst_link){
	FILE* arqC;//Recebe o ponteiro para o arquivo de contribuicao.
	FILE* saida;
	//Primeiro, precisamos buscar a pagina na lista para poder escrever nela.
	CelPagina* pag_buscada = buscapagina(pagina, lista);

	if(pag_buscada == NULL){//Se o retorno da funcao seja NULL, escreve uma mensagem de erro no arquivo de log.
		FILE* arq = fopen("log.txt", "a");
		fprintf(arq, "Erro: a pagina %s nao existe ou nao pode ser encontrada!\n", pagina);
		fclose(arq);
		return;
	}

    /*Impressao do historico de contribuicoes no arquivo da pagina*/
	CelContrib* hist_contrib = lst_contrib->prim;
	saida = fopen(pag_buscada->info_pag.nome_arquivo, "a");
	fprintf(saida, "%s\n\n--> Historico de contribuicoes\n", pagina);
	while( hist_contrib != NULL){
		if( strcmp(hist_contrib->info_contrib.pag, pagina) == 0){
			fprintf(saida, "%s\n", hist_contrib->info_contrib.arq_contr);

		}
		hist_contrib = hist_contrib->prox;
	}
	fprintf(saida, "\n");
	fclose(saida);

    /*Impressao da lista de links no arquivo da pagina*/
    CelLink* link_list = lst_link->prim;
    saida = fopen(pag_buscada->info_pag.nome_arquivo, "a");
	while(link_list != NULL){
		if( strcmp(link_list->info_link.origem, pagina) == 0){
			fprintf(saida, "--> Links\n%s %s\n", link_list->info_link.destino, link_list->info_link.arq_destino);
		}
		link_list = link_list->prox;
	}
	fprintf(saida, "\n--> Textos\n");
    fclose(saida);

	CelContrib* pagcomcontrib = lst_contrib->prim;
	while( pagcomcontrib != NULL){
	 	if( strcmp(pagcomcontrib->info_contrib.pag, pagina) == 0){/*Abre apenas os arquivos que contribuem com a pagina.
	 																Para isso, compara a pagina da lista de contribuicoes
	 																com o nome da pagina fornecida.
	 															  */
	 		char text_contr;
	 		arqC = fopen(pagcomcontrib->info_contrib.arq_contr, "r");//Abre o arquivo de contribuicao para leitura.
	 		saida = fopen(pag_buscada->info_pag.nome_arquivo, "a");
	 		if(arqC == NULL){//Caso erro na leitura.
	 			printf("Erro ao abrir o arquivo %s\n", pagcomcontrib->info_contrib.arq_contr);
	 			exit(1);
	 		}
	 		if(saida == NULL){
	 			printf("Erro ao abrir o arquivo saida.txt\n");
	 			exit(1);
	 		}
	 		fprintf(saida, "\n-------- %s (%s) --------\n\n", pagcomcontrib->info_contrib.arq_contr, pagcomcontrib->info_contrib.editor);
	 		while( fscanf(arqC, "%c", &text_contr) != EOF ){//Le enquanto nao for o fim do arquivo.
	 			putc(text_contr, saida);//Imprime caracter por caracter no arquivo de saida.
	 		}
	 		fprintf(saida, "\n");

	 		fclose(arqC);
	 		fclose(saida);

	 	}
	 	pagcomcontrib = pagcomcontrib->prox;//Atualiza o valor da lista.
	}
}
