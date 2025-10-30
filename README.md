# Gerenciador de dispositivos domesticos

Este é um programa simples em C de cadastro dinâmico, simulação de decisão e comparação de algoritmos desenvolvido no meu primeiro ano da faculdade de ciências da computação. Esta aplicação foi desenvolvida com o intuito de reforçar e colocar em pratica as habilidades competências técnicas desenvolvidas durante todo o ano na diciplina de **Data Structures and Algorithms**.

```
             ________________________________________________
            /                                                \
           |    _________________________________________     |
           |   | ╔════════════════════════════════╗      |    |
           |   | ║    <=== MENU PRINCIPAL ===>    ║      |    |
           |   | ║                                ║      |    |
           |   | ║ < Cadastrar dispositivo >      ║      |    |
           |   | ║    Listar dispositivos         ║      |    |
           |   | ║    Comparar algoritmos         ║      |    |
           |   | ║    Sair                        ║      |    |
           |   | ║                                ║      |    |
           |   | ║Use as setas ou W/S             ║      |    |
           |   | ╚════════════════════════════════╝      |    |
           |   | _                                       |    |
           |   |                                         |    |
           |   |                                         |    |
           |   |_________________________________________|    |
           |                                                  |
            \_________________________________________________/
                   \___________________________________/
                ___________________________________________
             _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_
          _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_
       _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_
    _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_
 _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_
:-------------------------------------------------------------------------:
`---._.-------------------------------------------------------------._.---'
```

> ⚠️ **Nota Importante:** - O programa foi criado no contexto de uma maquina Linux 

Eexistem alguns fatores que impedem a sua compilação em uma maquina Windows. Para contornar isso, Eu desenvolvi uma Dockerfile que compila e roda o código no contexto de uma maquina windos para quem for usar este programa.

## Comando Para Compilar o Programa No Linux

```
gcc -std=c99 -D_XOPEN_SOURCE=700 main.c -o main
```

## Instalando Imagem e Rodando o Programa No Docker

```
docker build -t meu_programa .
docker run -it --rm meu_programa
```

---

# Funcionamento Do Projeto



---
# Sprint 1 - Cadastro dinâmico

# Sprint 2 - Simulação de decisão

# Sprint 3 - Comparação de algoritmos

## 📊 Resultados Comparativos (exemplo com 6 dispositivos)
Algoritmo	Tempo (s)	Comparações:

- **Bubble Sort**	- 0.000003	15

- **Insertion Sort** -	0.000001	12

<img width="453" height="241" alt="20250923_19h07m21s_grim" src="https://github.com/user-attachments/assets/06f7ea29-20d7-4e42-87a5-acd66c11256d" />

> ⚠️ **Nota Importante:** - Os valores variam conforme o número de dispositivos cadastrados e a máquina de execução.

## 📈 Análise de Complexidade
Bubble Sort

- Melhor caso (já ordenado): Θ(n²) → ainda percorre todos os pares.
- Caso médio: Θ(n²).
- Pior caso (inversamente ordenado): Θ(n²).

Insertion Sort
-Melhor caso (já ordenado): Θ(n).
- Caso médio: Θ(n²).
- Pior caso (inversamente ordenado): Θ(n²).

---

# Colaboradores do Projeto

  Lucas Alves Antunes Almeida / RM: 566362 

  Lucas Werpp Franco / RM: 556044 

  Lucca Rosseto Rezende / RM: 564180 

  Massayoshi Bando Fogaça e Silva / RM: 561779 

  Miguel Lima da Silva / RM: 565141
