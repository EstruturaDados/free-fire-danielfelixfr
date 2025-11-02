#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10
#define MAX_NOME 50
#define MAX_TIPO 30

// Enumeração para critérios de ordenação
typedef enum {
    ORDENAR_POR_NOME = 1,
    ORDENAR_POR_TIPO = 2,
    ORDENAR_POR_PRIORIDADE = 3
} CriterioOrdenacao;

// Estrutura para representar um item da mochila
typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// Variáveis globais
Item mochila[MAX_ITENS];
int totalItens = 0;
bool ordenadoPorNome = false;
int contadorComparacoes = 0;

// Protótipos das funções
void adicionarItem();
void removerItem();
void listarItens();
void buscarItemSequencial();
void buscarItemBinaria();
void ordenarMochila();
void exibirMenu();
void insertionSort(CriterioOrdenacao criterio);

int main() {
    int opcao;
    
    printf("===========================================\n");
    printf("  DESAFIO CODIGO DA ILHA - NIVEL MESTRE\n");
    printf("===========================================\n\n");
    
    do {
        exibirMenu();
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpar buffer
        
        printf("\n");
        
        switch(opcao) {
            case 1:
                adicionarItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItemSequencial();
                break;
            case 5:
                buscarItemBinaria();
                break;
            case 6:
                ordenarMochila();
                break;
            case 7:
                printf("Saindo do sistema... Boa sorte na ilha!\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
        
        printf("\n");
        
    } while(opcao != 7);
    
    return 0;
}

void exibirMenu() {
    printf("=========== MENU ===========\n");
    printf("1. Adicionar item\n");
    printf("2. Remover item\n");
    printf("3. Listar itens\n");
    printf("4. Buscar item (sequencial)\n");
    printf("5. Buscar item (binaria)\n");
    printf("6. Ordenar mochila\n");
    printf("7. Sair\n");
    printf("============================\n");
}

void adicionarItem() {
    if(totalItens >= MAX_ITENS) {
        printf("ERRO: Mochila cheia! Nao e possivel adicionar mais itens.\n");
        return;
    }
    
    printf("=== ADICIONAR ITEM ===\n");
    
    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, MAX_NOME, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';
    
    printf("Tipo do item: ");
    fgets(mochila[totalItens].tipo, MAX_TIPO, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    
    do {
        printf("Prioridade (1-5): ");
        scanf("%d", &mochila[totalItens].prioridade);
        
        if(mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5) {
            printf("ERRO: Prioridade deve ser entre 1 e 5!\n");
        }
    } while(mochila[totalItens].prioridade < 1 || mochila[totalItens].prioridade > 5);
    
    getchar(); // Limpar buffer
    
    totalItens++;
    ordenadoPorNome = false; // Invalidar ordenação
    printf("\nItem adicionado com sucesso!\n");
}

void removerItem() {
    if(totalItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para remover.\n");
        return;
    }
    
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    
    printf("=== REMOVER ITEM ===\n");
    printf("Nome do item a remover: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Deslocar itens para preencher o espaço
            for(int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            totalItens--;
            ordenadoPorNome = false; // Invalidar ordenação
            printf("\nItem '%s' removido com sucesso!\n", nomeBusca);
            break;
        }
    }
    
    if(!encontrado) {
        printf("\nERRO: Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

void listarItens() {
    if(totalItens == 0) {
        printf("Mochila vazia! Nenhum item cadastrado.\n");
        return;
    }
    
    printf("=== ITENS NA MOCHILA ===\n");
    printf("%-25s %-20s %-10s %s\n", "NOME", "TIPO", "QUANT.", "PRIOR.");
    printf("------------------------------------------------------------------------\n");
    
    for(int i = 0; i < totalItens; i++) {
        printf("%-25s %-20s %-10d %d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Total de itens: %d/%d\n", totalItens, MAX_ITENS);
    printf("Ordenado por nome: %s\n", ordenadoPorNome ? "SIM" : "NAO");
}

void buscarItemSequencial() {
    if(totalItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }
    
    char nomeBusca[MAX_NOME];
    int encontrado = 0;
    
    printf("=== BUSCA SEQUENCIAL ===\n");
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial
    for(int i = 0; i < totalItens; i++) {
        if(strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome.......: %s\n", mochila[i].nome);
            printf("Tipo.......: %s\n", mochila[i].tipo);
            printf("Quantidade.: %d\n", mochila[i].quantidade);
            printf("Prioridade.: %d\n", mochila[i].prioridade);
            printf("Posicao....: %d\n", i + 1);
            break;
        }
    }
    
    if(!encontrado) {
        printf("\nERRO: Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

void buscarItemBinaria() {
    if(totalItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para buscar.\n");
        return;
    }
    
    if(!ordenadoPorNome) {
        printf("ERRO: A mochila deve estar ordenada por NOME para usar busca binaria!\n");
        printf("Use a opcao 6 para ordenar primeiro.\n");
        return;
    }
    
    char nomeBusca[MAX_NOME];
    
    printf("=== BUSCA BINARIA ===\n");
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, MAX_NOME, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca binária
    int esquerda = 0;
    int direita = totalItens - 1;
    int encontrado = 0;
    
    while(esquerda <= direita) {
        int meio = (esquerda + direita) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);
        
        if(comparacao == 0) {
            encontrado = 1;
            
            printf("\n=== ITEM ENCONTRADO ===\n");
            printf("Nome.......: %s\n", mochila[meio].nome);
            printf("Tipo.......: %s\n", mochila[meio].tipo);
            printf("Quantidade.: %d\n", mochila[meio].quantidade);
            printf("Prioridade.: %d\n", mochila[meio].prioridade);
            printf("Posicao....: %d\n", meio + 1);
            break;
        }
        else if(comparacao < 0) {
            esquerda = meio + 1;
        }
        else {
            direita = meio - 1;
        }
    }
    
    if(!encontrado) {
        printf("\nERRO: Item '%s' nao encontrado na mochila.\n", nomeBusca);
    }
}

void ordenarMochila() {
    if(totalItens == 0) {
        printf("ERRO: Mochila vazia! Nao ha itens para ordenar.\n");
        return;
    }
    
    int criterio;
    
    printf("=== ORDENAR MOCHILA ===\n");
    printf("1. Ordenar por Nome\n");
    printf("2. Ordenar por Tipo\n");
    printf("3. Ordenar por Prioridade\n");
    printf("Escolha o criterio: ");
    scanf("%d", &criterio);
    getchar(); // Limpar buffer
    
    if(criterio < 1 || criterio > 3) {
        printf("ERRO: Criterio invalido!\n");
        return;
    }
    
    contadorComparacoes = 0;
    insertionSort((CriterioOrdenacao)criterio);
    
    ordenadoPorNome = (criterio == ORDENAR_POR_NOME);
    
    printf("\nMochila ordenada com sucesso!\n");
    printf("Comparacoes realizadas: %d\n", contadorComparacoes);
}

void insertionSort(CriterioOrdenacao criterio) {
    for(int i = 1; i < totalItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        
        while(j >= 0) {
            int comparacao = 0;
            contadorComparacoes++;
            
            switch(criterio) {
                case ORDENAR_POR_NOME:
                    comparacao = strcmp(mochila[j].nome, chave.nome) > 0;
                    break;
                case ORDENAR_POR_TIPO:
                    comparacao = strcmp(mochila[j].tipo, chave.tipo) > 0;
                    break;
                case ORDENAR_POR_PRIORIDADE:
                    comparacao = mochila[j].prioridade > chave.prioridade;
                    break;
            }
            
            if(comparacao) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        
        mochila[j + 1] = chave;
    }
}