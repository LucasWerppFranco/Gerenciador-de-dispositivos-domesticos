#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define OPTIONS 3
#define WIDTH 50

// Configuração do terminal para entrada sem buffering
void setBufferedInput(int enable) {
    static struct termios oldt, newt;

    if (!enable) {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO); // Desliga canonical mode e echo
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    } else {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    }
}

// Função para limpar tela
void clearScreen() {
    printf("\033[H\033[J");
}

// Desenha borda superior
void print_border_top() {
    printf("╔");
    for (int i = 0; i < WIDTH - 2; i++) printf("═");
    printf("╗\n");
}

// Desenha borda inferior
void print_border_bottom() {
    printf("╚");
    for (int i = 0; i < WIDTH - 2; i++) printf("═");
    printf("╝\n");
}

// Desenha linha de texto centralizada com borda
void print_line(const char *text) {
    printf("║");
    int len = strlen(text);
    int padding = (WIDTH - 2 - len) / 2;

    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s", text);
    for (int i = 0; i < WIDTH - 2 - padding - len; i++) printf(" ");
    printf("║\n");
}

// Exibe menu e destaca a opção atual
void showMenu(int selected, char *options[]) {
    clearScreen();
    print_border_top();
    print_line("   MENU PRINCIPAL   ");
    print_line("");

    for (int i = 0; i < OPTIONS; i++) {
        char buffer[100];
        if (i == selected) {
            snprintf(buffer, sizeof(buffer), "< %s >", options[i]);
        } else {
            snprintf(buffer, sizeof(buffer), "  %s  ", options[i]);
        }
        print_line(buffer);
    }
    print_line("");
    print_line("Use ↑ ↓ para navegar e ENTER para selecionar    ");
    print_border_bottom();
}

int main() {
    char *options[OPTIONS] = {"Cadastrar dispositivo", "Listar dispositivos", "Sair"};
    int selected = 0;
    char c;

    setBufferedInput(0);  // Modo não bufferizado

    while (1) {
        showMenu(selected, options);

        c = getchar();
        if (c == '\033') { // sequência de escape
            getchar(); // '['
            c = getchar();
            if (c == 'A') { // seta para cima
                selected = (selected - 1 + OPTIONS) % OPTIONS;
            } else if (c == 'B') { // seta para baixo
                selected = (selected + 1) % OPTIONS;
            }
        } else if (c == '\n' || c == '\r') { // ENTER
            break;
        }
    }

    setBufferedInput(1);  // Restaura configuração padrão

    clearScreen();
    print_border_top();
    print_line("");
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Você selecionou: %s", options[selected]);
    print_line(buffer);
    print_line("");
    print_border_bottom();


    return selected;
}

