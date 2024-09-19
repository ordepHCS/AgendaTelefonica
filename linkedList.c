#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 40
#define MAX_TELEFONE 15
#define MAX_EMAIL 40

typedef struct {
    int dia;
    int mes;
} Data;

typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char celular[MAX_TELEFONE];
    char email[MAX_EMAIL];
    Data aniversario;
} Contato;

typedef struct {
    Contato informacao;
    struct elemento *proximo;
} Elemento;

typedef Elemento *Lista;

//lista encadeada retornando ponteiro para null 
Lista* cria_agenda() {
    Lista *lista = (Lista*)malloc(sizeof(Lista));
    if(lista == NULL) {
        return NULL;
    }
    return lista;
}

//inserir contato
int insere_contato(Lista **lista, Contato contato) {
    if(lista == NULL) 
    return 0;
    
    Elemento *novo = (Elemento*)malloc(sizeof(Elemento));
    
    if(novo == NULL)
    return 0;

    novo -> informacao = contato;
    novo -> proximo = NULL;

    if(*lista == NULL) {
        *lista = novo;
    }else {
        Elemento *auxiliar = *lista;
        while(auxiliar -> proximo != NULL) {
            auxiliar = auxiliar -> proximo;
        }
        auxiliar -> proximo = novo;
    }
    return 1;
}

int main(void) {
}



