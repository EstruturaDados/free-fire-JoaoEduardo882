#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Enum para critérios de ordenação
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Estrutura que representa um item do inventário
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // 1 (baixa) a 5 (alta)
} Item;

// Função para inserir um item no inventário
void inserirItem(Item mochila[], int *totalItens, bool *ordenadoPorNome) {
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

    printf("Digite a prioridade (1 a 5): ");
    scanf("%d", &mochila[*totalItens].prioridade);
    getchar(); // Limpa o buffer

    (*totalItens)++;
    *ordenadoPorNome = false; // A lista perdeu a ordenação
    printf("Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *totalItens, bool *ordenadoPorNome) {
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
            *ordenadoPorNome = false;
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
    printf("%-30s %-20s %-10s %-10s\n", "Nome", "Tipo", "Quantidade", "Prioridade");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < totalItens; i++) {
        printf("%-30s %-20s %-10d %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
}

// Função para buscar item por nome (sequencial)
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
            printf("Prioridade: %d\n", mochila[i].prioridade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Item \"%s\" não encontrado na mochila.\n", nomeBusca);
    }
}

// Função de ordenação (Insertion Sort)
void ordenarMochila(Item mochila[], int totalItens, CriterioOrdenacao criterio, int *comparacoes) {
    *comparacoes = 0;

    for (int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            (*comparacoes)++;
            int cmp = 0;

            if (criterio == ORDENAR_NOME)
                cmp = strcmp(mochila[j].nome, chave.nome);
            else if (criterio == ORDENAR_TIPO)
                cmp = strcmp(mochila[j].tipo, chave.tipo);
            else if (criterio == ORDENAR_PRIORIDADE)
                cmp = mochila[j].prioridade - chave.prioridade;

            if (cmp > 0) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }

    printf("Mochila ordenada com sucesso! Comparações realizadas: %d\n", *comparacoes);
}

// Função de busca binária por nome
void buscarItemBinario(Item mochila[], int totalItens, bool ordenadoPorNome) {
    if (!ordenadoPorNome) {
        printf("A lista precisa estar ordenada por NOME para fazer busca binária.\n");
        return;
    }

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item que deseja buscar (binário): ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    int inicio = 0, fim = totalItens - 1;
    int comparacoes = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoes++;

        int cmp = strcmp(mochila[meio].nome, nomeBusca);
        if (cmp == 0) {
            printf("\nItem encontrado (Busca Binária)!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            printf("Comparações realizadas: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("Item não encontrado. Comparações realizadas: %d\n", comparacoes);
}

// Função principal com menu
int main() {
    Item mochila[MAX_ITENS];
    int totalItens = 0;
    int opcao, comparacoes = 0;
    bool ordenadoPorNome = false;

    printf("=============================================\n");
    printf("PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
    printf("=============================================\n");

    do {
        printf("\nItens na mochila: %d/%d\n", totalItens, MAX_ITENS);
        printf("=== MENU ===\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descatar Componente\n");
        printf("3. Listar Componentes (Inventario)\n");
        printf("4. Buscar Sequencial por Componente-Chaves(por nome)\n");
        printf("5. Organizar Mochila(Ordenar Componetes)\n");
        printf("6. Buscar Binaria por Componetes-Chaves(por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens, &ordenadoPorNome);
                listarItens(mochila, totalItens);
                break;
            case 2:
                removerItem(mochila, &totalItens, &ordenadoPorNome);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItemPorNome(mochila, totalItens);
                break;
            case 5:
                printf("Escolha o critério de ordenação:\n");
                printf("1. Nome\n");
                printf("2. Tipo\n");
                printf("3. Prioridade\n");
                int criterio;
                scanf("%d", &criterio);
                getchar();

                ordenarMochila(mochila, totalItens, criterio, &comparacoes);

                if (criterio == ORDENAR_NOME)
                    ordenadoPorNome = true;
                else
                    ordenadoPorNome = false;

                listarItens(mochila, totalItens);
                break;
            case 6:
                buscarItemBinario(mochila, totalItens, ordenadoPorNome);
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
