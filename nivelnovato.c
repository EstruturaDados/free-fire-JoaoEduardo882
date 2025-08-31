#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

//Estrutura para representar um item do inventario
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

//Função para inserir um item no inventario
void inserirItem(Item mochila[], int *totalItens) {
    if (*totalItens >= MAX_ITENS) {
        printf("Mochila cheia! Não é possivel adicionar mais itens.\n");
        return;
    }

    printf("Digite o nome do item: ");
    fgets(mochila[*totalItens].nome, 30, stdin);
    mochila[*totalItens].nome[strcspn(mochila[*totalItens].nome, "\n")] = '\0';

    printf("Digite o tipo de item (arma, municao, cura etc..): ");
    fgets(mochila[*totalItens].tipo, 20, stdin);
    mochila[*totalItens].tipo[strcspn(mochila[*totalItens].tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &mochila[*totalItens].quantidade);
    getchar(); //Limpar buffer

    (*totalItens)++;
    printf("Item adicionado com sucesso!\n");
}

//Função para remover um item pelo nome
void removerItem(Item mochila[], int *totalItens) {
    if (*totalItens == 0) {
        printf("Mochila vazia! Nenhum item para remover");
        return;
    }

    char nomeRemover[30];
    printf("Digite o nome do item a ser removido: ");
    fgets(nomeRemover, 30, stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    for (int i = 0; i < *totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            mochila[i] = mochila[*totalItens - 1]; //Substitui pelo último item
            (*totalItens)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }

    printf("Item não encontrado.\n");
}

//Função para listar todos os itens
void listarItens(Item mochila[], int totalItens) {
    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("\n--- Inventario Atual ---\n");
    printf("%-30s %-20s %-10s\n", "Nome", "Tipo", "Quantidade");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-30s %-20s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade );
    }
}

//Função pricipal do menu
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao;

    printf("====================================\n");
    printf("SISTEMA DE INVENTARIO - NIVEL NOVATO\n");
    printf("====================================\n");

    do {
        printf("\nItens na mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("=== MENU ===\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção:");
        scanf("%d", &opcao);
        getchar(); //Limpa o \n do buffer

        switch(opcao) {
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
            case 0:
            printf("Saindo do Sistema.\n");
            break;
            default:
            printf("Opção inválida. Tente novamente.\n");

        }

    } while (opcao != 0);

    return 0;

}