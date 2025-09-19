# Projeto: Simulação de Decisão e Consumo com Algoritmos de Ordenação

## Integrantes do Grupo
*   **Pedro Mendes** - RM: 562242
*   **Leonardo** - RM: 565564
*   **Alexandre** - RM: 563346
*   **Guilherme Peres** - RM: 563981
*   **Gabriel de Matos** - RM: 565218

## Descrição da Evolução do Sistema

Este projeto simula um sistema de gerenciamento de consumo de energia, que decide quais dispositivos eletrônicos devem ser ativados com base em sua prioridade e na energia total disponível.

*   **Sprint 1 (Conceitual):** Definição da estrutura de dados `Dispositivo` e implementação das funcionalidades básicas em memória, como cadastro e listagem de dispositivos. A lógica de decisão era simples, sem persistência de dados.

*   **Sprint 2 (Funcional):** Introdução do algoritmo **Bubble Sort** para ordenar os dispositivos por prioridade. Foi implementada a persistência de dados, permitindo salvar e carregar a lista de dispositivos em um arquivo binário (`dispositivos.dat`). O sistema tornou-se mais robusto, com um menu interativo completo.

*   **Sprint 3 (Análise de Desempenho):** O sistema foi aprimorado com a adição de um segundo algoritmo de ordenação, o **Selection Sort**. Foi implementada uma funcionalidade para comparar o desempenho do Bubble Sort e do Selection Sort, medindo o **tempo de execução** (usando `clock()` da biblioteca `time.h`) e o **número de operações** (comparações e trocas) de cada um. O usuário agora pode escolher qual algoritmo usar para a simulação e visualizar os resultados comparativos.

## Instruções de Compilação e Execução

### Pré-requisitos
*   Um compilador C (como GCC).

### Compilação
Abra um terminal no diretório onde o arquivo `simulacao_consumo_sprint3.c` está localizado e execute o seguinte comando:

```bash
gcc simulacao_consumo_sprint3.c -o simulacao_consumo
```

### Execução
Após a compilação bem-sucedida, execute o programa com o comando:

```bash
./simulacao_consumo
```

## Resultados Comparativos da Sprint 3

Os testes foram realizados com uma lista de 10 dispositivos com prioridades desordenadas. Os resultados abaixo mostram o desempenho de cada algoritmo para ordenar essa lista.

| Métrica de Desempenho | Bubble Sort | Selection Sort |
| :-------------------- | :---------- | :------------- |
| **Tempo de Execução** | ~0.000025 s | ~0.000005 s    |
| **Nº de Comparações** | 45          | 45             |
| **Nº de Trocas**      | 22          | 7              |

*Observação: O tempo de execução pode variar ligeiramente dependendo do hardware e da carga do sistema no momento da execução.*

---
