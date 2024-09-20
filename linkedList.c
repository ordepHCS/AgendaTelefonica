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
    char email[MAX_EMAIL];
    Data aniversario;
} Contato;

typedef struct elemento {
    Contato informacao;
    struct elemento *proximo;
} Elemento;

typedef Elemento *Lista;

// cria uma agenda vazia
Lista cria_agenda() {
    return NULL;
}

// inserir contato
int insere_contato(Lista *lista, Contato contato) {
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
// listar os contatos
void lista_contatos(Lista lista) {
    if(lista == NULL) {
        printf("Agenda vazia.\n");
        return;
    }
    Elemento *auxiliar = lista;
    while(auxiliar != NULL) {
        printf("Nome: %s\n", auxiliar -> informacao.nome);
        printf("Telefone: %s\n", auxiliar -> informacao.telefone);
        printf("Email: %s\n", auxiliar -> informacao.email);
        printf("Data de Aniversario: %d/%d\n", auxiliar -> informacao.aniversario.dia, auxiliar -> informacao.aniversario.mes);
        auxiliar = auxiliar -> proximo;
    }
}

// buscar contato pelo "nome"
Elemento* busca_contato(Lista lista, char *nome) {
    if(lista == NULL)
    return NULL;
    Elemento *auxiliar = lista;
    while(auxiliar != NULL) {
        if(strcmp(auxiliar -> informacao.nome, nome) == 0) {
            return auxiliar;
        }
        auxiliar = auxiliar -> proximo;
    }
    return NULL;
}

// remover contato
int remove_contato(Lista *lista, char *nome) {
    if(lista == NULL || *lista == NULL)
    return 0;
    Elemento *antigo = NULL;
    Elemento *atual = *lista;

    while(atual != NULL && strcmp(atual -> informacao.nome, nome) != 0) {
        antigo = atual;
        atual = atual -> proximo;
    }
    if(atual == NULL) {
        printf("Contato nao encontrado.\n");
        return 0;
    }

    if(antigo == NULL) {
        *lista = atual -> proximo;
    }else {
        antigo -> proximo = atual -> proximo;
    }
    free(atual);
    return 1;
}

// att contato
int atualiza_contato(Lista *lista, char *nome) {
    Elemento *contato = busca_contato(*lista, nome);
    if(contato == NULL){
        printf("Contato nao encontrado.\n");
        return 0;
    }
    printf("Atualizando contato %s:\n", nome);

    printf("Novo telefone: ");
    scanf("%s", contato -> informacao.telefone);

    printf("Novo Email:\n");
    scanf("%s", contato -> informacao.email);
      
    printf("Seu contato foi atualizado com sucesso!.\n");
    return 1;
}

// main
int main(void) {
    Lista agenda = cria_agenda();
    int opcao;
    char nome[MAX_NOME];
    Contato contato;

    do {
        printf("1 - Inserir Contato\n");
        printf("2 - Listar Contato\n");
        printf("3 - Buscar Contato\n");
        printf("4 - Editar Contato\n");
        printf("5 - Remover Contato\n");
        printf("6 - Sair\n");

        printf("Escolha uma opcao: \n");
        scanf("%d",&opcao);
        
        switch(opcao) {
            // inserir
            case 1:            
            printf("Nome: ");
            scanf("%s", contato.nome);

            printf("Telefone: ");
            scanf("%s", contato.telefone);
            
            printf("Email: ");
            scanf("%s", contato.email);

            printf("Data de Aniversario (dia/mes):\n");
            scanf("%d %d", &contato.aniversario.dia, &contato.aniversario.mes);
            insere_contato(&agenda, contato);
            break;

            // listar
            case 2:
            lista_contatos(agenda);
            break;

            // buscar
            case 3:
            printf("Digite o nome do contato:\n");
            scanf("%s", nome);
            
            Elemento *busca = busca_contato(agenda, nome);
            if(busca != NULL) {
                printf("Nome: %s\n", busca -> informacao.nome);
                printf("Telefone: %s\n", busca -> informacao.telefone);
                printf("Email: %s\n", busca -> informacao.email);
                printf("Data de Aniversario: %d/%d\n", busca -> informacao.aniversario.dia, busca -> informacao.aniversario.mes);
            }else {
                printf("Contato nao encontrado.\n");
            }
            break;

            // editar
            case 4:
            printf("Digite o nome do contato:\n");
            scanf("%s", nome);
            atualiza_contato(&agenda, nome);
            break;

            // remover
            case 5:
            printf("Digite o nome do contato.\n");
            scanf("%s", nome);
            if(remove_contato(&agenda, nome)) {
                printf("Removido com sucesso\n");
            }else {
                printf("Falha ao remover o contato.");
            }
            break;

            // sair
            case 6:
            printf("Bye ;-;...");
            break;

            default:
            printf("Error.\n");
        }
    } while(opcao != 6);

    return 0;
}
