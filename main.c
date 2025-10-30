/*

  NOTA IMPORTANTE - Confira o README para obter os passos da preparação do ambiente para rodar o programa

  Integrantes do Grupo: 

  Lucas Alves Antunes Almeida / RM: 566362 
  Lucas Werpp Franco / RM: 556044 
  Lucca Rosseto Rezende / RM: 564180 
  Massayoshi Bando Fogaça e Silva / RM: 561779 
  Miguel Lima da Silva / RM: 565141

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define WIDTH 50
#define ARQUIVO "dispositivos.txt"

typedef struct {
    char nome[50];
    float consumo;
    int prioridade;
    int status;
} Dispositivo;

// Declarações
int visual_width(const char *s);
void print_border_top();
void print_border_bottom();
void print_line(const char *text);
void limparBufferEntrada();
int capturaTecla();
void esperarPressionarQ();

void exibirDispositivos(Dispositivo* dispositivos, int quantidade);
void alterarStatusDispositivo(Dispositivo* dispositivos, int quantidade);
void cadastrarDispositivos(Dispositivo** dispositivos, int* quantidade);
void salvarDispositivos(Dispositivo* dispositivos, int quantidade);
int carregarDispositivos(Dispositivo** dispositivos);

// Novas funções de ordenação
void bubbleSort(Dispositivo* arr, int n, long *comparacoes);
void insertionSort(Dispositivo* arr, int n, long *comparacoes);
void compararAlgoritmos(Dispositivo* dispositivos, int quantidade);

// Main
int main() {
    Dispositivo* dispositivos = NULL;
    int quantidade = 0;
    quantidade = carregarDispositivos(&dispositivos);

    const char* opcoes[] = {
        "Cadastrar dispositivo",
        "Listar dispositivos",
        "Alterar status de dispositivos",
        "Comparar algoritmos",
        "Sair"
    };
    int total_opcoes = 5;
    int selected = 0;
    int running = 1;

    while (running) {
        system("clear");
        print_border_top();
        print_line("            <=== MENU PRINCIPAL ===>");
        print_line("");
        for (int i = 0; i < total_opcoes; i++) {
            char buffer[100];
            if (i == selected)
                snprintf(buffer, sizeof(buffer), " < %s >", opcoes[i]);
            else
                snprintf(buffer, sizeof(buffer), "    %s   ", opcoes[i]);
            print_line(buffer);
        }
        print_line("");
        print_line("Use as setas ou W/S para navegar.");
        print_border_bottom();

        int tecla = capturaTecla();

        if (tecla == 'w') {
            selected = (selected - 1 + total_opcoes) % total_opcoes;
        } else if (tecla == 's') {
            selected = (selected + 1) % total_opcoes;
        } else if (tecla == '\n') {
            switch (selected) {
                case 0:
                    cadastrarDispositivos(&dispositivos, &quantidade);
                    break;
                case 1:
                    exibirDispositivos(dispositivos, quantidade);
                    break;
                case 2:
                    alterarStatusDispositivo(dispositivos, quantidade); // Chamada correta
                    break;
                case 3:
                    compararAlgoritmos(dispositivos, quantidade);
                    break;
                case 4:
                    salvarDispositivos(dispositivos, quantidade);
                    system("clear");
                    print_border_top();
                    print_line("Dispositivos salvos. Saindo...");
                    print_border_bottom();
                    running = 0;
                    break;
            }
        }
    }

    free(dispositivos);
    return 0;
}

// Funções auxiliares de layout
int visual_width(const char *s) {
    int width = 0;
    wchar_t wc;
    mbstate_t state;
    memset(&state, 0, sizeof state);
    const char *p = s;

    while (*p) {
        size_t len = mbrtowc(&wc, p, MB_CUR_MAX, &state);
        if (len == (size_t)-1 || len == (size_t)-2) break;
        int w = wcwidth(wc);
        if (w > 0) width += w;
        p += len;
    }
    return width;
}

void print_border_top() {
    printf("╔");
    for (int i = 0; i < WIDTH - 2; i++) printf("═");
    printf("╗\n");
}

void print_border_bottom() {
    printf("╚");
    for (int i = 0; i < WIDTH - 2; i++) printf("═");
    printf("╝\n");
}

void print_line(const char *text) {
    printf("║");
    int content_width = visual_width(text);
    int padding = WIDTH - 2 - content_width;
    printf("%s", text);
    for (int j = 0; j < padding; j++) printf(" ");
    printf("║\n");
}

// Entrada de teclado
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int capturaTecla() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    if (ch == 27) {
        getchar();
        ch = getchar();
        if (ch == 'A') ch = 'w';
        else if (ch == 'B') ch = 's';
        else ch = 0;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void esperarPressionarQ() {
    char input[10];
    print_border_top();
    print_line("Pressione 'q' para voltar ao menu...");
    print_border_bottom();
    do {
        printf("> ");
        if (fgets(input, sizeof(input), stdin)) {
            if (input[0] == 'q' || input[0] == 'Q') break;
        }
    } while (1);
}

// Funções do sistema
void exibirDispositivos(Dispositivo* dispositivos, int quantidade) {
    if (quantidade == 0) {
        print_border_top();
        print_line("Nenhum dispositivo cadastrado!");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }

    for (int i = 0; i < quantidade - 1; i++) {
        for (int j = i + 1; j < quantidade; j++) {
            if (dispositivos[i].prioridade < dispositivos[j].prioridade ||
                (dispositivos[i].prioridade == dispositivos[j].prioridade &&
                 dispositivos[i].consumo < dispositivos[j].consumo)) {

                Dispositivo temp = dispositivos[i];
                dispositivos[i] = dispositivos[j];
                dispositivos[j] = temp;
            }
        }
    }

    system("clear");
    print_border_top();
    print_line("          <=== LISTA DE DISPOSITIVOS ===>");
    print_border_bottom();
    printf("\n");

    char buffer[300];
    for (int i = 0; i < quantidade; i++) {
        char prioridadeTexto[10];
        switch (dispositivos[i].prioridade) {
            case 3: strcpy(prioridadeTexto, "Alta"); break;
            case 2: strcpy(prioridadeTexto, "Media"); break;
            case 1: strcpy(prioridadeTexto, "Baixa"); break;
            default: strcpy(prioridadeTexto, "N/D"); break;
        }

        char statusTexto[10];
        if (dispositivos[i].status == 0) strcpy(statusTexto, "Desligado");
        else strcpy(statusTexto, "Ligado");

        snprintf(buffer, sizeof(buffer),
                 " %-20s | Consumo (kWh): %-8.2f | Prioridade: %-5s | Status: %-8s",
                 dispositivos[i].nome,
                 dispositivos[i].consumo,
                 prioridadeTexto,
                 statusTexto);

        printf("%s\n", buffer);
    }
    printf("\n");

    esperarPressionarQ();
}

void alterarStatusDispositivo(Dispositivo* dispositivos, int quantidade) {
    if (quantidade == 0) {
        system("clear");
        print_border_top();
        print_line("Nenhum dispositivo cadastrado!");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }

    int selected = 0;
    int running = 1;

    while (running) {
        system("clear");
        print_border_top();
        print_line("=== ALTERAR STATUS DE DISPOSITIVOS ===");
        print_border_bottom();
        printf("\n");

        // Exibe os dispositivos com destaque no selecionado
        for (int i = 0; i < quantidade; i++) {
            char prioridadeTexto[10];
            switch (dispositivos[i].prioridade) {
                case 3: strcpy(prioridadeTexto, "Alta"); break;
                case 2: strcpy(prioridadeTexto, "Media"); break;
                case 1: strcpy(prioridadeTexto, "Baixa"); break;
                default: strcpy(prioridadeTexto, "N/D"); break;
            }

            char statusTexto[10];
            if (dispositivos[i].status == 0) strcpy(statusTexto, "Desligado");
            else strcpy(statusTexto, "Ligado");

            char buffer[300];
            snprintf(buffer, sizeof(buffer),
                     " %-20s | Consumo: %-8.2f | Prioridade: %-5s | Status: %-8s",
                     dispositivos[i].nome,
                     dispositivos[i].consumo,
                     prioridadeTexto,
                     statusTexto);

            if (i == selected) {
                printf("> %s <\n", buffer);
            } else {
                printf("   %s\n", buffer);
            }
        }

        print_border_top();
        print_line("Use W/S para navegar e Q para sair.");
        print_border_bottom();

        int tecla = capturaTecla();
        switch (tecla) {
            case 'w':
                selected = (selected - 1 + quantidade) % quantidade;
                break;
            case 's':
                selected = (selected + 1) % quantidade;
                break;
            case '\n':
                dispositivos[selected].status = !dispositivos[selected].status;
                break;
            case 'q':
            case 'Q':
                running = 0;
                break;
        }
    }

    salvarDispositivos(dispositivos, quantidade);
}

void cadastrarDispositivos(Dispositivo** dispositivos, int* quantidade) {
    int n;

    system("clear");
    print_border_top();
    print_line("Quantos dispositivos deseja cadastrar?");
    print_border_bottom();
    printf("> ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        limparBufferEntrada();
        system("clear");
        print_border_top();
        print_line("Entrada inválida!");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }
    limparBufferEntrada();

    size_t novo_tamanho = (size_t)(*quantidade + n) * sizeof(Dispositivo);
    Dispositivo* temp = realloc(*dispositivos, novo_tamanho);
    if (!temp) {
        system("clear");
        print_border_top();
        print_line("Erro ao alocar memória.");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }
    *dispositivos = temp;

    for (int i = 0; i < n; i++) {
        Dispositivo novo;
        memset(&novo, 0, sizeof(novo));

        system("clear");
        print_border_top();
        char bufferTitle[100];
        snprintf(bufferTitle, sizeof(bufferTitle), "Cadastro do dispositivo %d de %d", i + 1, n);
        print_line(bufferTitle);
        print_line("Digite o nome do dispositivo:");
        print_border_bottom();
        printf("> ");
        if (fgets(novo.nome, sizeof(novo.nome), stdin) == NULL) {
            strncpy(novo.nome, "Desconhecido", sizeof(novo.nome)-1);
            novo.nome[sizeof(novo.nome)-1] = '\0';
        } else {
            novo.nome[strcspn(novo.nome, "\n")] = 0;
        }

        system("clear");
        print_border_top();
        print_line("Digite o consumo (kWh):");
        print_border_bottom();
        printf("> ");
        while (scanf("%f", &novo.consumo) != 1) {
            limparBufferEntrada();
            printf("Entrada inválida! Digite um número:\n> ");
        }
        limparBufferEntrada();

        system("clear");
        print_border_top();
        print_line("Digite a prioridade:");
        print_line("(1-Alta, 2-Media, 3-Baixa)");
        print_border_bottom();
        printf("> ");
        while (scanf("%d", &novo.prioridade) != 1 || novo.prioridade < 1 || novo.prioridade > 3) {
            limparBufferEntrada();
            printf("Entrada inválida! Digite 1, 2 ou 3:\n> ");
        }
        limparBufferEntrada();

        novo.status = 0;

        (*dispositivos)[*quantidade] = novo;
        (*quantidade)++;
    }

    salvarDispositivos(*dispositivos, *quantidade);

    system("clear");
    print_border_top();
    print_line("Dispositivos cadastrados com sucesso!");
    print_border_bottom();
    esperarPressionarQ();
}

void salvarDispositivos(Dispositivo* dispositivos, int quantidade) {
    FILE* f = fopen(ARQUIVO, "w");
    if (!f) {
        system("clear");
        print_border_top();
        print_line("Erro ao abrir arquivo para escrita.");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }

    if (fprintf(f, "%d\n", quantidade) < 0) {
        fclose(f);
        system("clear");
        print_border_top();
        print_line("Erro ao escrever no arquivo.");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        if (fprintf(f, "%s\n", dispositivos[i].nome) < 0) {
            fclose(f);
            system("clear");
            print_border_top();
            print_line("Erro ao escrever no arquivo.");
            print_border_bottom();
            esperarPressionarQ();
            return;
        }
        if (fprintf(f, "%.2f %d %d\n", dispositivos[i].consumo,
                                      dispositivos[i].prioridade,
                                      dispositivos[i].status) < 0) {
            fclose(f);
            system("clear");
            print_border_top();
            print_line("Erro ao escrever no arquivo.");
            print_border_bottom();
            esperarPressionarQ();
            return;
        }
    }

    fclose(f);
}

int carregarDispositivos(Dispositivo** dispositivos) {
    FILE* f = fopen(ARQUIVO, "r");
    if (!f) {
        *dispositivos = NULL;
        return 0;
    }

    int quantidade = 0;
    if (fscanf(f, "%d\n", &quantidade) != 1) {
        fclose(f);
        *dispositivos = NULL;
        return 0;
    }

    if (quantidade <= 0) {
        *dispositivos = NULL;
        fclose(f);
        return 0;
    }

    Dispositivo* arr = malloc(quantidade * sizeof(Dispositivo));
    if (!arr) {
        fclose(f);
        *dispositivos = NULL;
        return 0;
    }

    for (int i = 0; i < quantidade; i++) {
        if (!fgets(arr[i].nome, sizeof(arr[i].nome), f)) {
            free(arr);
            *dispositivos = NULL;
            fclose(f);
            return 0;
        }
        arr[i].nome[strcspn(arr[i].nome, "\n")] = 0;

        if (fscanf(f, "%f %d %d\n",
                   &arr[i].consumo,
                   &arr[i].prioridade,
                   &arr[i].status) != 3) {
            free(arr);
            *dispositivos = NULL;
            fclose(f);
            return 0;
        }
    }

    fclose(f);
    *dispositivos = arr;
    return quantidade;
}

void bubbleSort(Dispositivo* arr, int n, long *comparacoes) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (arr[j].consumo > arr[j + 1].consumo) {
                Dispositivo temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void insertionSort(Dispositivo* arr, int n, long *comparacoes) {
    for (int i = 1; i < n; i++) {
        Dispositivo chave = arr[i];
        int j = i - 1;
        while (j >= 0) {
            (*comparacoes)++;
            if (arr[j].consumo > chave.consumo) {
                arr[j + 1] = arr[j];
                j--;
            } else break;
        }
        arr[j + 1] = chave;
    }
}

// Comparação entre algoritmos
void compararAlgoritmos(Dispositivo* dispositivos, int quantidade) {
    if (quantidade == 0) {
        system("clear");
        print_border_top();
        print_line("Nenhum dispositivo cadastrado.");
        print_border_bottom();
        esperarPressionarQ();
        return;
    }

    Dispositivo* copia1 = malloc(quantidade * sizeof(Dispositivo));
    Dispositivo* copia2 = malloc(quantidade * sizeof(Dispositivo));
    memcpy(copia1, dispositivos, quantidade * sizeof(Dispositivo));
    memcpy(copia2, dispositivos, quantidade * sizeof(Dispositivo));

    long compBubble = 0, compInsertion = 0;

    clock_t startB = clock();
    bubbleSort(copia1, quantidade, &compBubble);
    clock_t endB = clock();
    double tempoBubble = (double)(endB - startB) / CLOCKS_PER_SEC;

    clock_t startI = clock();
    insertionSort(copia2, quantidade, &compInsertion);
    clock_t endI = clock();
    double tempoInsertion = (double)(endI - startI) / CLOCKS_PER_SEC;

    system("clear");
    print_border_top();
    print_line("  === Comparacao de Algoritmos ===");
    print_border_bottom();
    printf("\n%-15s | %-10s | %-12s\n", "Algoritmo", "Tempo (s)", "Comparacoes");
    printf("---------------------------------------------\n");
    printf("%-15s | %-10f | %-12ld\n", "Bubble Sort", tempoBubble, compBubble);
    printf("%-15s | %-10f | %-12ld\n", "Insertion Sort", tempoInsertion, compInsertion);

    free(copia1);
    free(copia2);

    esperarPressionarQ();
}

