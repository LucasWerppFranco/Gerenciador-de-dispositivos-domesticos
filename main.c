/*

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

#define WIDTH 50
#define ARQUIVO "dispositivos.txt"

typedef struct {
    char nome[50];
    float consumo;
    int prioridade;
} Dispositivo;

// Functions
int visual_width(const char *s);
void print_border_top();
void print_border_bottom();
void print_line(const char *text);
void limparBufferEntrada();
int capturaTecla();
void esperarPressionarQ();

void exibirDispositivos(Dispositivo* dispositivos, int quantidade);
void cadastrarDispositivos(Dispositivo** dispositivos, int* quantidade);
void salvarDispositivos(Dispositivo* dispositivos, int quantidade);
int carregarDispositivos(Dispositivo** dispositivos);

// Main Function

int main() {
    Dispositivo* dispositivos = NULL;
    int quantidade = 0;
    quantidade = carregarDispositivos(&dispositivos);

    const char* opcoes[] = {"Cadastrar dispositivo", "Listar dispositivos", "Sair"};
    int total_opcoes = 3;
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
        print_line("Use as setas para navegar entre a pagina.");
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

    // Libera a memória alocada
    free(dispositivos);

    return 0;
}

// Struct Functions

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

// Keybord Structs

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

// System Functions

void exibirDispositivos(Dispositivo* dispositivos, int quantidade) {
    system("clear");
    print_border_top();
    if (quantidade == 0) {
        print_line("Nenhum dispositivo cadastrado.");
    } else {
        print_line("   === Lista de Dispositivos Cadastrados ===");
        print_border_bottom();
        print_border_top();
        print_line("");
        for (int i = 0; i < quantidade; i++) {
            char buffer[100];
            snprintf(buffer, sizeof(buffer), "Dispositivo %d: %s", i + 1, dispositivos[i].nome);
            print_line(buffer);
            snprintf(buffer, sizeof(buffer), "Consumo: %.2f kWh", dispositivos[i].consumo);
            print_line(buffer);
            if (dispositivos[i].prioridade == 1)
                print_line("Prioridade: Alta - Essencial");
            else if (dispositivos[i].prioridade == 2)
                print_line("Prioridade: Media - Importante");
            else
                print_line("Prioridade: Baixa - Nao essencial");
            print_line("");
        }
    }
    print_border_bottom();
    esperarPressionarQ();
}

void cadastrarDispositivos(Dispositivo** dispositivos, int* quantidade) {
    int n;
    system("clear");
    print_border_top();
    print_line("Quantos dispositivos deseja cadastrar?");
    print_border_bottom();
    printf("> ");
    scanf("%d", &n);
    limparBufferEntrada();

    // Realoca o vetor para armazenar os novos dispositivos
    *dispositivos = realloc(*dispositivos, (*quantidade + n) * sizeof(Dispositivo));

    for (int i = 0; i < n; i++) {
        Dispositivo novo;

        system("clear");
        print_border_top();
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Cadastro do dispositivo %d de %d", i + 1, n);
        print_line(buffer);
        print_line("Digite o nome do dispositivo:");
        print_border_bottom();
        printf("> ");
        fgets(novo.nome, sizeof(novo.nome), stdin);
        novo.nome[strcspn(novo.nome, "\n")] = 0;

        system("clear");
        print_border_top();
        print_line("Digite o consumo (kWh):");
        print_border_bottom();
        printf("> ");
        scanf("%f", &novo.consumo);
        limparBufferEntrada();

        system("clear");
        print_border_top();
        print_line("Digite a prioridade:");
        print_line("(1-Alta, 2-Media, 3-Baixa)");
        print_border_bottom();
        printf("> ");
        scanf("%d", &novo.prioridade);
        limparBufferEntrada();

        (*dispositivos)[*quantidade] = novo;
        (*quantidade)++;
    }

    system("clear");
    print_border_top();
    print_line("Dispositivos cadastrados com sucesso!");
    print_border_bottom();
    esperarPressionarQ();
}

void salvarDispositivos(Dispositivo* dispositivos, int quantidade) {
    FILE* f = fopen(ARQUIVO, "w");
    if (!f) {
        print_line("Erro ao abrir arquivo para escrita.");
        return;
    }
    fprintf(f, "%d\n", quantidade);
    for (int i = 0; i < quantidade; i++) {
        fprintf(f, "%s\n%.2f %d\n", dispositivos[i].nome, dispositivos[i].consumo, dispositivos[i].prioridade);
    }
    fclose(f);
}

int carregarDispositivos(Dispositivo** dispositivos) {
    FILE* f = fopen(ARQUIVO, "r");
    if (!f) {
        return 0;
    }
    int quantidade;
    fscanf(f, "%d\n", &quantidade);

    *dispositivos = malloc(quantidade * sizeof(Dispositivo));

    for (int i = 0; i < quantidade; i++) {
        fgets((*dispositivos)[i].nome, sizeof((*dispositivos)[i].nome), f);
        (*dispositivos)[i].nome[strcspn((*dispositivos)[i].nome, "\n")] = 0;
        fscanf(f, "%f %d\n", &(*dispositivos)[i].consumo, &(*dispositivos)[i].prioridade);
    }
    fclose(f);
    return quantidade;
}

