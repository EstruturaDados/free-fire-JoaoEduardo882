#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Função para inserir um item no inventário
void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(mochila[*totalItens].nome, 30, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Digite o tipo do item (arma, munição, cura, etc): ");
    fgets(mochila[*totalItens].tipo, 20, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    getchar(); // Limpa o buffer

    (*totalItens)++;
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            mochila[i] = mochila[*totalItens - 1]; // Substitui pelo último item
            (*totalItens)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }

    printf("Item não encontrado.\n");
}

// Função para listar todos os itens
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n--- Inventário Atual ---\n");
    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("---------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-30s %-20s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// Função para buscar um item pelo nome
void buscarItemPorNome(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = 0;

    printf("Digite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeBusca);
    }
}

// Função principal com menu
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    printf("=========================================\n");
    printf("SISTEMA DE INVENTARIO - NIVEL AVENTUREIRO\n");
    printf("=========================================\n");

    do {
        printf("\nItens na mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("=== MENU ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item por nome\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o \n do buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItemPorNome(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do sistema.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
