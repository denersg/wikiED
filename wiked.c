#include"trab.h"
#include<string.h>
#include <stdio.h>
#include <stdlib.h>
#define TAM 30
/*
As funções listadas aqui sao sómente para deixar a int main mais "limpa",
sao todas funções que só leem e chamam funções da wiked.h implementadas na wiked.c
*/
ListPag* inserePagina(ListPag* lpag, char* nome, char*nomeArq){
    Pag* pag;
    pag = criaPag(nome,nomeArq);
    lpag = inserePag(lpag,pag);
    return lpag;
}
ListEdit* insereEdit(ListEdit* lEditor, char* nome){
    Editor* edit;
    edit=criaEditor(nome);
    lEditor=insereEditor(edit, lEditor);    
    return lEditor;
}
ListCont* insereContribuicao(ListCont* lCont, ListEdit* lEdit, ListPag* lpag , char*pag, char* editor, char* arq){
    Cont* cont;
    Editor* auxE;
    Pag* auxP;
    auxE=achaEditor(editor,lEdit); // acha o editor dono da contribuicao para verificar se ele realmente existe
    auxP=achaPagina(pag, lpag); // acha a pagina para ver se existe para nao inserir uma contribuicao numa pagina inexistente
    if (auxP==NULL||auxE==NULL){ //se a pagina ou editor for null ele(a) nao existe
           FILE* log=fopen("log.txt", "a");
           fprintf (log,"ERRO: Editor %s ou Pagina %s nao exite na WikED!.\n",editor, pag); // imprime o erro no log, sendo que pelo menos um deles nao existe podendo ser os dois
           fclose(log);
           return lCont;       
    }
    cont=criaContrib(arq,editor,pag);
    lCont=insereCont(cont,lCont);
    return lCont;
}
void imprime_pagina(ListPag* lPag, ListCont* lcont, ListLink* links,char* pag){
    Pag* aux=achaPagina(pag,lPag);  //acha pagina para verificar se ela existe
    if (aux==NULL){
        FILE* log=fopen("log.txt","a");
        fprintf (log,"ERRO: Pagina %s nao existe na WikED!.\n",pag); // imprime mensagem de erro no log
        fclose(log);
        return ;
    }
    imprimePagina(aux,lcont, links);
}
void retiraCont(ListCont* list, char*pag, char* editor,char* cont){
    retira_cont(editor, list , cont, pag);
}
ListLink* INSERELINK(ListPag* lista, ListLink* listL, char* origem, char* destino){
    Link* link;
    Pag* pagO=achaPagina(origem, lista);
    Pag* pagD=achaPagina(destino,lista);
    if (pagO==NULL||pagD==NULL){
        FILE* log=fopen("log.txt","a");
        fprintf (log,"ERRO: Pagina de origem %s ou pagina destino %s nao existe na WikED!.\n",origem,destino); // imprime mensagem de erro no log
        fclose(log);
        return listL;
    }
    link= criaLink(pagO,pagD);
    listL=insereLink(listL,link);
    return listL;  
}
ListLink* RETIRALINK(ListLink* list, ListPag* lPag, char* origem, char* destino){
    retiraLink(list, achaPagina(origem,lPag), achaPagina(destino,lPag));   
}
ListEdit* RETIRAEDITOR(ListEdit* list, char* nome, ListCont* lcont){
    list=retiraEditor(nome,list,lcont);
    return list;
}
void CAMINHO (ListLink* list, ListPag* lpag, char* origem, char* destino){
    int i;
    zeraVisitados(list);
    Pag* aux=achaPagina(origem, lpag); // procura e acha as pagina de origem
    Pag* aux2= achaPagina (destino, lpag); // procura e acha a pagina de destino
    if (aux==NULL || aux2==NULL){ //verifica se existem as paginas se nao imprime na WikED!
        FILE* log=fopen ("log.txt", "a");
        fprintf (log, "ERRO: Pagina de origem: %s ou Pagina de destino: %s nao existem na WikED!.\n",origem, destino ); 
        fclose(log);
        return ;
    }
    i=caminho (list, aux ,aux2); //procura caminho e armazena em i
    if (i==1){      // se caminho existe , logo i==1, imprime que existe caminho
        FILE* log=fopen ("log.txt", "a");
        fprintf (log, "Existe caminho de %s para %s.\n",origem, destino );
        fclose(log);
        return;
    }               // se nao imprime que nao existe caminho
    FILE* log=fopen ("log.txt", "a");
    fprintf (log, "Nao existe caminho de %s para %s.\n",origem, destino );
    fclose(log);
    return;
    
}

int main(int cont, char** ent) {
    char comando[TAM];
    char contArq[TAM];
    char pagNome  [TAM];
    char pagNome2 [TAM];
    char pagArq [TAM];
    char nomeEditor[TAM];
    ListLink* lLink= criaListaLinkVazia();   
    ListPag* lpag=crialistaPagVazia(); 
    ListCont* lCont=listaContVazia ();
    ListEdit* lEditor=criaLeditorVazia();
    FILE* entrada=fopen(ent[1],"r");
    fscanf(entrada,"%s",comando);
    while (strcmp (comando,"FIM")){ //Verifica se comando é igual FIM para finalizar ou nao o programa
        if(!strcmp(comando,"INSEREPAGINA")){ 
            fscanf(entrada,"%s %s", pagNome, pagArq);
            lpag=inserePagina(lpag, pagNome, pagArq);                
        }
        if (!strcmp(comando,"INSEREEDITOR")){
            fscanf(entrada,"%s",nomeEditor);
            lEditor=insereEdit(lEditor, nomeEditor);                      
        }
        if(!strcmp(comando,"INSERECONTRIBUICAO")){
            fscanf(entrada, "%s %s %s", pagNome, nomeEditor, contArq);
            lCont=insereContribuicao(lCont, lEditor,lpag, pagNome,nomeEditor, contArq);
        }
        if (!strcmp(comando,"IMPRIMEPAGINA")){
            fscanf(entrada,"%s", pagNome);
            imprime_pagina(lpag, lCont,lLink,pagNome);
        }
        if (!strcmp(comando,"RETIRACONTRIBUICAO")){
            fscanf(entrada, "%s %s %s", pagNome, nomeEditor, contArq);
            retiraCont (lCont,pagNome,nomeEditor,contArq);
        }
        if (!strcmp(comando,"INSERELINK")){
            fscanf(entrada,"%s %s", pagNome,pagNome2);
            lLink=INSERELINK(lpag,lLink,pagNome, pagNome2);
        }
        if (!strcmp(comando,"RETIRALINK")){  
             fscanf(entrada,"%s %s", pagNome,pagNome2);
            lLink=RETIRALINK(lLink, lpag, pagNome, pagNome2);
        }
        if (!strcmp(comando,"CAMINHO")){ 
            fscanf(entrada,"%s %s", pagNome,pagNome2);
            CAMINHO(lLink,lpag,pagNome, pagNome2);
        }
        if (!strcmp(comando,"RETIRAEDITOR")){   
            fscanf(entrada,"%s", nomeEditor);
            lEditor=RETIRAEDITOR(lEditor,nomeEditor,lCont);
        }
        if (!strcmp(comando,"RETIRAPAGINA")){  // a funcao do retira pagina por mecher com tanta coisa (lista de pagina, lista de contribuicoes e lista de links)                                              
            Pag* pag;                               // preferi deixala na propria int main, consciente de que a int main nao esta tao poluida
            fscanf(entrada,"%s", pagNome);
            pag=achaPagina(pagNome, lpag);                  // tenta achar a pagina na lista
            if (pag==NULL){                 // caso nao exista imprime a mensagem de erro no log;
            FILE* log=fopen("log.txt","a");
            fprintf (log,"Erro: Pagina %s nao existe na Wiked!.\n",pagNome);
            fclose(log);
            }else{  //caso exista chama as funções para retirada da pagina por conpleto
                lLink= retiraLinkPagina (pag,lLink);    //retira os links
                lCont = retiraContPag(pag, lCont);      // retira as contribuições 
                lpag = retiraPagina(pag,lpag);          //retira a pagina. obs a pagina só é liberada (free) nesta função por isso a ordem 
                                                        //dela SÓMENTE  depois delas é essencial 
            }
        }
        if (!strcmp(comando,"IMPRIMEWIKED")){
                imprimeWiked(lpag,lLink,lCont);     // chamada da função da wiked.h direto ja que ela na otem a nescessidade de ler nada junto a ela
        }
        fscanf(entrada,"%s",comando);   // sempre le o comando e verifica se é = a FIM
    }
    fclose(entrada);

    return (0);
}

  
  
  
  
  
 
 
  
  
