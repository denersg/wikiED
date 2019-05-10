#ifndef TRABED1_H
#define TRABED1_H

/*Edit (tipo opaco)
  Estrutura interna do tipo a ser definida na implementação do TAD. Definido com o campos:
  - nome (string)
  */
typedef struct editor Edit;

/*Tipo que define a lista de editores (tipo opaco)
  Estrutura interna do tipo a ser definida na implementada do TAD.
*/
typedef struct lsteditor LstEditor;

/*Contrib (tipo opaco)
  - arquivo (string)
  - editor (string)
  - pagina (string)
  */
typedef struct contribuicao Contrib;

/*Tipo que define o tipo celula de contribuicao (tipo opaco)*/
typedef struct celcontribuicao CelContrib;

/*Tipo que define a lista de contribuicoes (tipo opaco)
  Estrutura interna do tipo a ser definida na implementada do TAD.
*/
typedef struct lstcontrib LstContrib;

/*Link (tipo opaco)
  Estrutura interna do tipo a ser definida na implementação do TAD. Definido com os campos:
  - origem (string)
  - arquivo de origem (string)
  - destino (string)
  - arquivo de destino (string)
  */
typedef struct link Link;

/*Tipo que define o tipo celula de link (tipo opaco)*/
typedef struct cellink CelLink;

/*Tipo que define a lista de links (tipo opaco)
  Estrutura interna do tipo a ser definida na implementada do TAD.
*/
typedef struct listalink LstLink;

/*Pag (tipo opaco)
  Estrutura interna do tipo a ser definida na implementação do TAD. Definido com os campos:
  - nome da pagina (string)
  - nome do arquivo (string)
  - Lista de contribuicoes (string)
  - Lista de links (string)
  */
typedef struct pagina Pag;

/*Tipo que define o tipo celula de pagina (tipo opaco)*/
typedef struct celpagina CelPagina;

/*Tipo que define a lista de paginas (tipo opaco)
  Estrutura interna do tipo a ser definida na implementada do TAD.
*/
typedef struct lista Lista;

/*Inicializa o sentinela de uma lista de paginas
* inputs: nenhum
* output: Sentinela inicializado
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
Lista* inilistapagina();

/*Inicializa o sentinela de uma lista de editores
* inputs: nenhum
* output: Sentinela inicializado
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
LstEditor* inicializaeditor();

/*Inicializa o sentinela de uma lista de contribuicoes
* inputs: nenhum
* output: Sentinela inicializado
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
LstContrib* inicializacontrobuicao();

/*Inicializa o sentinela de uma lista de links
* inputs: nenhum
* output: Sentinela inicializado
* pre-condicao: nenhuma
* pos-condicao: sentinela da lista de retorno existe e os campos primeiro e ultimo apontam para NULL
*/
LstLink* inicializalink();

/*Insere um editor na ultima posicao da lista de editores
* inputs: editor a ser inserido na lista (do tipo Edit) e a lista
* output: lista de editores atualizada
* pre-condicao: editor e lista nao sao nulos
* pos-condicao: lista contem o editor inserido na ultima posicao
*/
LstEditor* insereedit(LstEditor* lst_editor, char* nome);

/*Inicializa um Pag pagina
* inputs: o nome da pagina e o nome do arquivo
* output: um ponteiro para o tipo pagina criado
* pre-condicao: nome da pagina e nome do arquivo validos
* pos-condicao: tipo pagina criado, com os campos nome da pagina e nome do arquivo copiados
*/
Pag* inictipopagina(char* nome, char* nomedoarq);

/*Insere uma pagina na ultima posicao da lista de paginas
* inputs: pagina a ser inserido na lista (do tipo Lista) e a lista
* output: nenhuma
* pre-condicao: pagina e lista nao sao nulos
* pos-condicao: lista contem a pagina inserido na ultima posicao
*/
void insercaodepag(Pag* nova_pagina, Lista* lista);

/*Insere uma pagina na ultima posicao da lista de paginas
* inputs: nome da pagina e nome do arquivo a serem inseridos na lista (do tipo Lista) e a lista
* output: nenhuma
* pre-condicao: pagina e lista nao sao nulos
* pos-condicao: lista contem a pagina inserido na ultima posicao
*/
void inserepag(char* nome, char* nomedoarq, Lista* lista);

/*Procura um dado editor na lista de editores
* inputs: nome do editor a ser buscado na lista (do tipo LstEditor)
* output: ponteiro para editor achado
* pre-condicao: editor nao pode ser nulo
* pos-condicao: editor tem seu endereco de memoria retornado
*/
Edit* buscaeditor(char* editor, LstEditor* lst_editor);

/*Procura uma dada pagina na lista de paginas
* inputs: nome da pagina a ser buscada na lista (do tipo Lista)
* output: ponteiro para pagina achado
* pre-condicao: nenhuma
* pos-condicao: pagina tem seu endereco de memoria retornado
*/
CelPagina* buscapagina(char* pag, Lista* lista);

/*Inicializa um Contrib
* inputs: o nome da pagina, editor e a contribuicao
* output: um ponteiro para o tipo contribuicao criado
* pre-condicao: nome da pagina, nome do editor e a contribuicao validos
* pos-condicao: tipo contribuicao criado, com os campos nome da pagina, nome do editor e a contribuicao copiados
*/
Contrib* inictipocontrib(char* nome_pagina, char* editor, char* contribuicao);

/*Insere uma contribuicao na ultima posicao da lista de contribuicoes
* inputs: ponteiro para estrutura e ponteiro para celula da pagina serem inseridos na lista (do tipo LstContrib) e a lista
* output: nenhuma
* pre-condicao: contribuicao e lista nao sao nulos
* pos-condicao: lista contem a contribuicao inserida na ultima posicao
*/
void criacelcontr(Contrib* contr, LstContrib* lst_contrib, CelPagina* pag_procur);

/*Insere uma contribuicao na ultima posicao da lista de contribuicoes
* inputs: nomes da pagina, editor e contribuicao serem inseridos na lista (do tipo LstContrib) e
		  listas de contribuicao, editores e paginas
* output: nenhuma
* pre-condicao: contribuicao e lista nao sao nulos
* pos-condicao: lista contem a contribuicao inserida na ultima posicao
*/
void inserecontrib(LstContrib* lst_contrib, LstEditor* lst_editor, Lista* lista, char* nome_pagina, char* editor, char* contribuicao);

/*Inicializa um Link
* inputs: celula da pagina de origem e celula da pagina de destino
* output: um ponteiro para o tipo link criado
* pre-condicao: pagina e arquivo de origem e pagina e arquivo de destino validos
* pos-condicao: tipo link criado, com os campos pagina e arquivo de origem e pagina e arquivo de destino copiados
*/
Link* inictipolink(CelPagina* origem, CelPagina* destino);

/*Insere um link na ultima posicao da lista de links
* inputs: ponteiro para estrutura ser inserido na lista (do tipo LstLink)
* output: nenhuma
* pre-condicao: link e lista nao sao nulos
* pos-condicao: lista contem o link inserido na ultima posicao
*/
void criacellink(Link* link, LstLink* lst_link);

/*Verifica se as paginas de origem e destino existem
* inputs: pagina de origem e pagina de destino a serem inseridos na lista (do tipo LstLink) e lista de pagina e de link
* output: nenhuma
* pre-condicao: link e lista nao sao nulos
* pos-condicao: lista contem o link inserido na ultima posicao
*/
void inserelink(Lista* lista, LstLink* lst_link, char* origem, char* destino);

/*Retira um dado editor da lista de editores
* inputs: editor ser retirado da lista (do tipo LstEditor) e lista de editores e de contribuicoes
* output: lista de editores
* pre-condicao: editor tem que existir na lista
* pos-condicao: lista de editores tem seu valor atualizado
*/
LstEditor* retiraeditor(char* editor, LstEditor* lst_editor, LstContrib* lst_contrib);

/*Imprime os dados determinada pagina da lista
* inputs: nome da pagina, lista de pagina, de contribuicao e de links
* output: nenhum
* pre-condicao: lista de pagina nao nula
* pos-condicao: dados da pagina impressos na saida padrao
*/
void ImprimePagina(char* pagina, Lista* lista, LstContrib* lst_contrib, LstLink* lst_link);

//#endif

#endif /* TRABED1_H */
