#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Para medir o tempo de execução

#define MAX_NOME 50
#define MAX_DISPOSITIVOS 100

// Estrutura para representar um dispositivo
typedef struct {
    char nome[MAX_NOME];
    float consumo;     // Consumo em kWh
    int prioridade;    // Quanto menor o número, maior a prioridade (1 = máxima prioridade)
    int status;        // 1 = ligado, 0 = desligado
} Dispositivo;

// Variáveis globais para análise de desempenho
long long comparacoes = 0;
long long trocas = 0;

// Protótipos das funções
void cadastrarDispositivo(Dispositivo dispositivos[], int *numDispositivos);
void listarDispositivos(Dispositivo dispositivos[], int numDispositivos);
void simularConsumoInteligente(Dispositivo dispositivos[], int numDispositivos);
void bubbleSort(Dispositivo dispositivos[], int numDispositivos);
void selectionSort(Dispositivo dispositivos[], int numDispositivos);
float calcularConsumoTotal(Dispositivo dispositivos[], int numDispositivos);
void salvarDispositivos(Dispositivo dispositivos[], int numDispositivos);
int carregarDispositivos(Dispositivo dispositivos[]);
void exibirMenu();
void resetarContadores();
void copiarDispositivos(Dispositivo origem[], Dispositivo destino[], int numDispositivos);


int main() {
    Dispositivo dispositivos[MAX_DISPOSITIVOS];
    int numDispositivos = 0;
    int opcao;
    
    // Tenta carregar dispositivos salvos anteriormente
    numDispositivos = carregarDispositivos(dispositivos);
    
    do {
        exibirMenu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarDispositivo(dispositivos, &numDispositivos);
                break;
            case 2:
                listarDispositivos(dispositivos, numDispositivos);
                break;
            case 3:
                simularConsumoInteligente(dispositivos, numDispositivos);
                break;
            case 4:
                salvarDispositivos(dispositivos, numDispositivos);
                printf("\nDispositivos salvos com sucesso!\n");
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            printf("\nPressione Enter para continuar...");
            getchar(); // Consome o '\n' deixado pelo scanf
            getchar(); // Aguarda o Enter
        }
        
    } while(opcao != 0);
    
    return 0;
}

// Exibe o menu principal
void exibirMenu() {
    system("clear || cls"); // Limpa a tela (funciona em Linux/macOS e Windows)
    printf("\n===== SISTEMA DE SIMULAÇÃO DE CONSUMO INTELIGENTE =====\n");
    printf("1. Cadastrar Dispositivo\n");
    printf("2. Listar Dispositivos\n");
    printf("3. Simular Consumo Inteligente\n");
    printf("4. Salvar Dispositivos\n");
    printf("0. Sair\n");
    printf("====================================================\n");
}

// Reseta os contadores de desempenho
void resetarContadores() {
    comparacoes = 0;
    trocas = 0;
}

// Copia um array de dispositivos para outro
void copiarDispositivos(Dispositivo origem[], Dispositivo destino[], int numDispositivos) {
    for (int i = 0; i < numDispositivos; i++) {
        destino[i] = origem[i];
    }
}

// Cadastra um novo dispositivo
void cadastrarDispositivo(Dispositivo dispositivos[], int *numDispositivos) {
    if (*numDispositivos >= MAX_DISPOSITIVOS) {
        printf("\nLimite máximo de dispositivos atingido!\n");
        return;
    }
    
    Dispositivo novoDispositivo;
    
    printf("\n--- Cadastro de Dispositivo ---\n");
    
    printf("Nome do dispositivo: ");
    scanf(" %[^\n]", novoDispositivo.nome);
    
    printf("Consumo em kWh: ");
    scanf("%f", &novoDispositivo.consumo);
    
    printf("Prioridade (1 = máxima prioridade, números maiores = menor prioridade): ");
    scanf("%d", &novoDispositivo.prioridade);
    
    novoDispositivo.status = 0; // Por padrão, o dispositivo começa desligado
    
    dispositivos[*numDispositivos] = novoDispositivo;
    (*numDispositivos)++;
    
    printf("\nDispositivo cadastrado com sucesso!\n");
}

// Lista todos os dispositivos cadastrados
void listarDispositivos(Dispositivo dispositivos[], int numDispositivos) {
    if (numDispositivos == 0) {
        printf("\nNenhum dispositivo cadastrado!\n");
        return;
    }
    
    printf("\n--- Lista de Dispositivos ---\n");
    printf("%-30s %-15s %-15s %-10s\n", "Nome", "Consumo (kWh)", "Prioridade", "Status");
    printf("-------------------------------------------------------------------------\n");
    
    for (int i = 0; i < numDispositivos; i++) {
        printf("%-30s %-15.2f %-15d %-10s\n", 
               dispositivos[i].nome, 
               dispositivos[i].consumo, 
               dispositivos[i].prioridade, 
               dispositivos[i].status ? "Ligado" : "Desligado");
    }
    
    float consumoTotal = calcularConsumoTotal(dispositivos, numDispositivos);
    printf("-------------------------------------------------------------------------\n");
    printf("Consumo total dos dispositivos ligados: %.2f kWh\n", consumoTotal);
}

// Calcula o consumo total dos dispositivos ligados
float calcularConsumoTotal(Dispositivo dispositivos[], int numDispositivos) {
    float total = 0.0;
    for (int i = 0; i < numDispositivos; i++) {
        if (dispositivos[i].status == 1) {
            total += dispositivos[i].consumo;
        }
    }
    return total;
}

// Implementação do Bubble Sort com contadores
void bubbleSort(Dispositivo dispositivos[], int numDispositivos) {
    int i, j;
    Dispositivo temp;
    
    for (i = 0; i < numDispositivos - 1; i++) {
        for (j = 0; j < numDispositivos - i - 1; j++) {
            comparacoes++; // Incrementa o contador de comparações
            if (dispositivos[j].prioridade > dispositivos[j + 1].prioridade) {
                trocas++; // Incrementa o contador de trocas
                temp = dispositivos[j];
                dispositivos[j] = dispositivos[j + 1];
                dispositivos[j + 1] = temp;
            }
        }
    }
}

// Implementação do Selection Sort com contadores
void selectionSort(Dispositivo dispositivos[], int numDispositivos) {
    int i, j, min_idx;
    Dispositivo temp;

    for (i = 0; i < numDispositivos - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < numDispositivos; j++) {
            comparacoes++; // Incrementa o contador de comparações
            if (dispositivos[j].prioridade < dispositivos[min_idx].prioridade) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            trocas++; // Incrementa o contador de trocas
            temp = dispositivos[i];
            dispositivos[i] = dispositivos[min_idx];
            dispositivos[min_idx] = temp;
        }
    }
}

// Executa a lógica de simulação para um conjunto de dispositivos já ordenado
void executarLogicaSimulacao(Dispositivo dispositivos[], int numDispositivos, float energiaDisponivel) {
    // Primeiro, desliga todos os dispositivos
    for (int i = 0; i < numDispositivos; i++) {
        dispositivos[i].status = 0;
    }

    float consumoAcumulado = 0.0;
    int dispositivosLigados = 0;

    // Liga os dispositivos por ordem de prioridade até atingir o limite de energia
    for (int i = 0; i < numDispositivos; i++) {
        if (consumoAcumulado + dispositivos[i].consumo <= energiaDisponivel) {
            dispositivos[i].status = 1; // Liga o dispositivo
            consumoAcumulado += dispositivos[i].consumo;
            dispositivosLigados++;
        }
    }

    // Exibe o resultado da simulação
    printf("\n--- Resultado da Simulação ---\n");
    printf("Energia disponível: %.2f kWh\n", energiaDisponivel);
    printf("Dispositivos ativados (%d):\n", dispositivosLigados);
    if (dispositivosLigados > 0) {
        printf("%-30s %-15s %-15s\n", "Nome", "Consumo (kWh)", "Prioridade");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < numDispositivos; i++) {
            if (dispositivos[i].status == 1) {
                printf("%-30s %-15.2f %-15d\n", dispositivos[i].nome, dispositivos[i].consumo, dispositivos[i].prioridade);
            }
        }
    }

    printf("\nDispositivos desativados (%d):\n", numDispositivos - dispositivosLigados);
    if (numDispositivos - dispositivosLigados > 0) {
        printf("%-30s %-15s %-15s\n", "Nome", "Consumo (kWh)", "Prioridade");
        printf("----------------------------------------------------------\n");
        for (int i = 0; i < numDispositivos; i++) {
            if (dispositivos[i].status == 0) {
                printf("%-30s %-15.2f %-15d\n", dispositivos[i].nome, dispositivos[i].consumo, dispositivos[i].prioridade);
            }
        }
    }
    
    printf("\nConsumo total após simulação: %.2f kWh\n", consumoAcumulado);
    printf("Energia restante: %.2f kWh\n", energiaDisponivel - consumoAcumulado);
}


// Simula o consumo inteligente, permitindo escolher o algoritmo
void simularConsumoInteligente(Dispositivo dispositivos[], int numDispositivos) {
    if (numDispositivos == 0) {
        printf("\nNenhum dispositivo cadastrado para simular!\n");
        return;
    }

    float energiaDisponivel;
    int escolhaAlgoritmo;
    
    printf("\nInforme a quantidade de energia disponível (kWh): ");
    scanf("%f", &energiaDisponivel);

    printf("\nEscolha o algoritmo de ordenação:\n");
    printf("1. Bubble Sort\n");
    printf("2. Selection Sort\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolhaAlgoritmo);

    Dispositivo copiaDispositivos[MAX_DISPOSITIVOS];
    copiarDispositivos(dispositivos, copiaDispositivos, numDispositivos);

    clock_t inicio, fim;
    double tempoGasto;

    resetarContadores();

    switch (escolhaAlgoritmo) {
        case 1:
            printf("\nOrdenando com Bubble Sort...\n");
            inicio = clock();
            bubbleSort(copiaDispositivos, numDispositivos);
            fim = clock();
            break;
        case 2:
            printf("\nOrdenando com Selection Sort...\n");
            inicio = clock();
            selectionSort(copiaDispositivos, numDispositivos);
            fim = clock();
            break;
        default:
            printf("Opção de algoritmo inválida!\n");
            return;
    }

    tempoGasto = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Executa a lógica de decisão com os dispositivos ordenados
    executarLogicaSimulacao(copiaDispositivos, numDispositivos, energiaDisponivel);

    // Exibe as métricas de desempenho
    printf("\n--- Análise de Desempenho do Algoritmo ---\n");
    printf("Tempo de execução: %f segundos\n", tempoGasto);
    printf("Número de comparações: %lld\n", comparacoes);
    printf("Número de trocas: %lld\n", trocas);
    printf("------------------------------------------\n");
}


// Salva os dispositivos em um arquivo binário
void salvarDispositivos(Dispositivo dispositivos[], int numDispositivos) {
    FILE *arquivo = fopen("dispositivos.dat", "wb");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo para salvar!\n");
        return;
    }
    fwrite(&numDispositivos, sizeof(int), 1, arquivo);
    fwrite(dispositivos, sizeof(Dispositivo), numDispositivos, arquivo);
    fclose(arquivo);
}

// Carrega os dispositivos de um arquivo binário
int carregarDispositivos(Dispositivo dispositivos[]) {
    FILE *arquivo = fopen("dispositivos.dat", "rb");
    int numDispositivos = 0;
    if (arquivo == NULL) {
        // Arquivo não existe, o que é normal na primeira execução
        return 0;
    }
    
    // Lê o número de dispositivos, se o arquivo não estiver vazio
    if (fread(&numDispositivos, sizeof(int), 1, arquivo) != 1) {
        fclose(arquivo);
        return 0;
    }
    
    // Lê o array de dispositivos
    fread(dispositivos, sizeof(Dispositivo), numDispositivos, arquivo);
    
    fclose(arquivo);
    
    printf("Carregados %d dispositivos do arquivo.\n", numDispositivos);
    return numDispositivos;
}
