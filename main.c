#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#define WIDTH 50
#define ARQUIVO "dispositivos.txt"

typedef struct {
    char nome[50];
    float consumo;
    int prioridade;
} Dispositivo;

// Funções de borda
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

// Função auxiliar para limpar buffer
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funções principais
void esperarPressionarQ() {
    char c;
    print_border_top();
    print_line("Pressione 'q' para voltar ao menu...");
    print_border_bottom();
    do {
        c = getchar();
    } while (c != 'q' && c != 'Q');
}

void exibirDispositivos(Dispositivo* dispositivos, int quantidade) {
    system("clear");
    print_border_top();
    if (quantidade == 0) {
        print_line("Nenhum dispositivo cadastrado.");
        print_border_bottom();
    } else {
        print_line("=== Lista de Dispositivos Cadastrados ===");
        print_border_bottom();
        print_border_top();
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

void cadastrarDispositivo(Dispositivo* dispositivos, int* quantidade) {
    Dispositivo novo;

    system("clear");
    print_border_top();
    print_line("=== Cadastro de Novo Dispositivo ===");
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

    dispositivos[*quantidade] = novo;
    (*quantidade)++;

    system("clear");
    print_border_top();
    print_line("Dispositivo cadastrado com sucesso!");
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

int carregarDispositivos(Dispositivo* dispositivos) {
    FILE* f = fopen(ARQUIVO, "r");
    if (!f) {
        return 0;
    }
    int quantidade;
    fscanf(f, "%d\n", &quantidade);
    for (int i = 0; i < quantidade; i++) {
        fgets(dispositivos[i].nome, sizeof(dispositivos[i].nome), f);
        dispositivos[i].nome[strcspn(dispositivos[i].nome, "\n")] = 0;
        fscanf(f, "%f %d\n", &dispositivos[i].consumo, &dispositivos[i].prioridade);
    }
    fclose(f);
    return quantidade;
}

int main() {
    Dispositivo dispositivos[100];
    int quantidade = 0;

    quantidade = carregarDispositivos(dispositivos);

    int opcao;
    do {
        system("clear");
        print_border_top();
        print_line("            <=== MENU PRINCIPAL ===>");
        print_line("");
        print_line("  1. Cadastrar dispositivo");
        print_line("  2. Listar dispositivos");
        print_line("  3. Sair");
        print_line("");
        print_line("  Escolha uma opcao:");
        print_border_bottom();

        printf("> ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                cadastrarDispositivo(dispositivos, &quantidade);
                break;
            case 2:
                exibirDispositivos(dispositivos, quantidade);
                break;
            case 3:
                salvarDispositivos(dispositivos, quantidade);
                system("clear");
                print_border_top();
                print_line("Dispositivos salvos. Saindo...");
                print_border_bottom();
                break;
            default:
                system("clear");
                print_border_top();
                print_line("Opcao invalida! Tente novamente.");
                print_border_bottom();
                esperarPressionarQ();
        }
    } while (opcao != 3);

    return 0;
}

