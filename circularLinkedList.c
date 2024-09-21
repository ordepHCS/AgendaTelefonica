// codigo não tem saida e o arquivo.exe fecha sozinho e eu n sei mais o que fazer.

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // algumas funcoes garantem que N seja diferente a cada vez que rodar o programa

#define NUM_SOBREVIVENTES 5
#define MIN_RANDOM 2
#define MAX_RANDOM 6

typedef struct No {
    char nome;
    struct No* anterior;
    struct No* proximo;
} No;

No* criarNo(char nome) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo -> nome = nome;
    novoNo -> anterior = novoNo -> proximo = NULL;
    return novoNo;
}

void adicionarNo(No** head, char nome) {
    No* novoNo = criarNo(nome);
    if(head == NULL) {
        *head = novoNo;
    }else {
        No* tail = (*head) -> proximo;
        tail -> proximo = novoNo;
        novoNo -> anterior = tail;
        novoNo -> proximo = *head;
        (*head) -> anterior = novoNo;
    }
}

void imprimirLista(No* head) {
    No* temporario = head;
    if(head == NULL)
    return;
    do {
        printf("%c\n", temporario -> nome);
        temporario = temporario -> proximo;
    } while (temporario -> proximo);
}

void removerNo(No** head, No* paraRemover) {
    if(*head == paraRemover) {
        *head = paraRemover -> proximo;
    }
    paraRemover -> anterior -> proximo = paraRemover -> proximo;
    paraRemover -> proximo -> anterior = paraRemover -> anterior;
    free(paraRemover);
}

char encontrarSobrevivente(No* head, int N, No* start) {
    No* atual = start;
    while(head -> proximo != head) {
        for(int i = 0; i < N; i++) {
            atual = atual -> anterior;
        }
        No* paraRemover = atual;
        atual = paraRemover -> anterior;
        printf("%c morreu... :O\n", paraRemover -> nome);
        removerNo(&head, paraRemover);
    }
    return head -> nome;
}

int main(void) {
    No* head = NULL;
    char sobreviventesId[NUM_SOBREVIVENTES] = {'A', 'B', 'C', 'D', 'E'}; // tive que me render a metodos arcaicos professor desculpe, mas eu poderia usar alocação dinamica com malloc eu acho :)

    for(int i = 0; i < NUM_SOBREVIVENTES; i++) {
        adicionarNo(&head, sobreviventesId[i]);
    }

    printf("Iniciais: ");
    imprimirLista(head);

    // gerando N aleatoriamente
    srand(time(0));
    int N = rand() % (MAX_RANDOM - MIN_RANDOM + 1) + MIN_RANDOM;
    printf("E o sorteado (N) e: %d\n", N);

    // define o sobrevivente inicial
    No* start = head -> proximo;

    // ultimo sobrevivente
    char sobrevivente = encontrarSobrevivente(head, N, start);
    printf("O sobrevivente sortudo e: %c\n", sobrevivente);
    getchar();

    return 0;
}