/*
#include <stdio.h>
#include <string.h>
#include <time.h>

// Struct dos componentes
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Contadores pra comparacao
int comp_bubble = 0, comp_insertion = 0, comp_selection = 0;

// Cadastra os componentes
void cadastrarComponentes(Componente comps[], int *total) {
    if (*total >= 20) {
        printf("Ja tem 20 componentes! Chega!\n");
        return;
    }
    
    printf("\n--- Novo Componente %d ---\n", *total + 1);
    printf("Nome: ");
    scanf("%29s", comps[*total].nome);
    
    printf("Tipo: ");
    scanf("%19s", comps[*total].tipo);
    
    printf("Prioridade (1-10): ");
    scanf("%d", &comps[*total].prioridade);
    
    // Ajusta se passar do limite
    if (comps[*total].prioridade < 1) comps[*total].prioridade = 1;
    if (comps[*total].prioridade > 10) comps[*total].prioridade = 10;
    
    (*total)++;
    printf("Deu certo!\n");
}

// Bubble Sort pro nome
void bubbleSortNome(Componente comp[], int n) {
    comp_bubble = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comp_bubble++;
            if (strcmp(comp[j].nome, comp[j + 1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j + 1];
                comp[j + 1] = temp;
            }
        }
    }
}

// Insertion Sort pro tipo
void insertionSortTipo(Componente comp[], int n) {
    comp_insertion = 0;
    for (int i = 1; i < n; i++) {
        Componente key = comp[i];
        int j = i - 1;
        
        while (j >= 0) {
            comp_insertion++;
            if (strcmp(comp[j].tipo, key.tipo) > 0) {
                comp[j + 1] = comp[j];
                j--;
            } else {
                break;
            }
        }
        comp[j + 1] = key;
    }
}

// Selection Sort pra prioridade
void selectionSortPrioridade(Componente comp[], int n) {
    comp_selection = 0;
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comp_selection++;
            if (comp[j].prioridade < comp[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            Componente temp = comp[i];
            comp[i] = comp[min_idx];
            comp[min_idx] = temp;
        }
    }
}

// Busca binaria soh funciona se tiver ordenado por nome
int buscaBinariaPorNome(Componente comp[], int n, char nome[]) {
    int left = 0, right = n - 1;
    int comparacoes = 0;
    
    while (left <= right) {
        comparacoes++;
        int mid = left + (right - left) / 2;
        int cmp = strcmp(comp[mid].nome, nome);
        
        if (cmp == 0) {
            printf("Comparacoes na busca: %d\n", comparacoes);
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    printf("Comparacoes na busca: %d\n", comparacoes);
    return -1;
}

// Mede quanto tempo leva cada algoritmo
void medirTempo(void (*algoritmo)(Componente[], int), Componente comp[], int n, char* nomeAlgo) {
    Componente* copia = malloc(n * sizeof(Componente));
    memcpy(copia, comp, n * sizeof(Componente));
    
    clock_t inicio = clock();
    algoritmo(copia, n);
    clock_t fim = clock();
    
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    
    printf("%s: %.6f segundos\n", nomeAlgo, tempo);
    free(copia);
}

// Mostra todos os componentes
void mostrarComponentes(Componente comp[], int n) {
    printf("\n=== COMPONENTES ===\n");
    if (n == 0) {
        printf("Nada aqui ainda...\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        printf("%2d. %-20s %-15s Prio: %2d\n", 
               i + 1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
    printf("Total: %d\n", n);
}

// Monta tudo e verifica o componente principal
void montagemFinal(Componente comp[], int n, char componenteChave[]) {
    printf("\n=== MONTAGEM FINAL ===\n");
    
    // Ordena por nome pra poder buscar
    bubbleSortNome(comp, n);
    mostrarComponentes(comp, n);
    
    // Procura o componente importante
    printf("\n--- PROCURANDO COMPONENTE-CHAVE ---\n");
    int pos = buscaBinariaPorNome(comp, n, componenteChave);
    
    if (pos != -1) {
        printf("✅ ACHAMOS O COMPONENTE-CHAVE!\n");
        printf("   Nome: %s\n", comp[pos].nome);
        printf("   Tipo: %s\n", comp[pos].tipo);
        printf("   Prioridade: %d\n", comp[pos].prioridade);
        printf("   Posicao: %d\n", pos + 1);
    } else {
        printf("❌ NAO ACHAMOS O COMPONENTE-CHAVE!\n");
        printf("   Procuramos por: '%s'\n", componenteChave);
    }
}

int main() {
    Componente componentes[20];
    int totalComponentes = 0;
    int opcao;
    char componenteChave[30] = "chip central";
    
    printf("=== SISTEMA DE MONTAGEM ===\n");
    printf("Componente mais importante: %s\n", componenteChave);
    
    do {
        printf("\n=== MENU ===\n");
        printf("1. Add componente\n");
        printf("2. Listar tudo\n");
        printf("3. Ordenar por Nome (Bubble)\n");
        printf("4. Ordenar por Tipo (Insertion)\n");
        printf("5. Ordenar por Prioridade (Selection)\n");
        printf("6. Buscar por nome\n");
        printf("7. Testar velocidade\n");
        printf("8. Montar tudo\n");
        printf("9. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:
                cadastrarComponentes(componentes, &totalComponentes);
                break;
                
            case 2:
                mostrarComponentes(componentes, totalComponentes);
                break;
                
            case 3:
                if (totalComponentes > 0) {
                    bubbleSortNome(componentes, totalComponentes);
                    printf("Ordenado por nome!\n");
                    printf("Comparacoes: %d\n", comp_bubble);
                    mostrarComponentes(componentes, totalComponentes);
                } else {
                    printf("Cadastra algo primeiro!\n");
                }
                break;
                
            case 4:
                if (totalComponentes > 0) {
                    insertionSortTipo(componentes, totalComponentes);
                    printf("Ordenado por tipo!\n");
                    printf("Comparacoes: %d\n", comp_insertion);
                    mostrarComponentes(componentes, totalComponentes);
                } else {
                    printf("Cadastra algo primeiro!\n");
                }
                break;
                
            case 5:
                if (totalComponentes > 0) {
                    selectionSortPrioridade(componentes, totalComponentes);
                    printf("Ordenado por prioridade!\n");
                    printf("Comparacoes: %d\n", comp_selection);
                    mostrarComponentes(componentes, totalComponentes);
                } else {
                    printf("Cadastra algo primeiro!\n");
                }
                break;
                
            case 6:
                if (totalComponentes > 0) {
                    char nomeBusca[30];
                    printf("Nome pra buscar: ");
                    scanf("%29s", nomeBusca);
                    
                    // Ordena antes de buscar
                    bubbleSortNome(componentes, totalComponentes);
                    int pos = buscaBinariaPorNome(componentes, totalComponentes, nomeBusca);
                    
                    if (pos != -1) {
                        printf("Achei na posicao %d!\n", pos + 1);
                        printf("  Nome: %s\n", componentes[pos].nome);
                        printf("  Tipo: %s\n", componentes[pos].tipo);
                        printf("  Prioridade: %d\n", componentes[pos].prioridade);
                    } else {
                        printf("Nao achei isso nao...\n");
                    }
                } else {
                    printf("Cadastra algo primeiro!\n");
                }
                break;
                
            case 7:
                if (totalComponentes > 0) {
                    printf("\n=== TESTE DE VELOCIDADE ===\n");
                    medirTempo(bubbleSortNome, componentes, totalComponentes, "Bubble");
                    printf("Comparacoes: %d\n", comp_bubble);
                    
                    medirTempo(insertionSortTipo, componentes, totalComponentes, "Insertion");
                    printf("Comparacoes: %d\n", comp_insertion);
                    
                    medirTempo(selectionSortPrioridade, componentes, totalComponentes, "Selection");
                    printf("Comparacoes: %d\n", comp_selection);
                } else {
                    printf("Cadastra algo primeiro!\n");
                }
                break;
                
            case 8:
                if (totalComponentes > 0) {
                    montagemFinal(componentes, totalComponentes, componenteChave);
                } else {
                    printf("Cadastra algo primeiro!\n");
                }
                break;
                
            case 9:
                printf("Valeu! Tchau!\n");
                break;
                
            default:
                printf("Essa opcao nao existe!\n");
        }
        
    } while (opcao != 9);
    
    return 0;
}*/