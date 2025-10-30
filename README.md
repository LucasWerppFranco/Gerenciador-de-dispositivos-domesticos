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

# Sprint 1 – Cadastro Dinâmico

## 💡 Descrição

Nesta sprint foi implementada a **estrutura de dados dinâmica** para o cadastro de dispositivos elétricos.
Cada dispositivo possui três atributos principais:

* `nome` → identificação textual do aparelho;
* `consumo` → valor em watts (ou outra unidade definida);
* `prioridade` → grau de importância do dispositivo.

O programa armazena esses dados em um vetor dinâmico de estruturas (`Dispositivo`), permitindo **crescimento em tempo de execução** conforme o usuário adiciona novos registros.
Também foram criadas funções de **leitura e gravação em arquivo** (`dispositivos.txt`) para persistir as informações entre execuções.

## 🔍 Resultados

Durante os testes, o sistema permitiu cadastrar, listar e salvar os dispositivos com sucesso.
As operações de entrada e saída se mostraram estáveis, com os seguintes destaques:

* Cadastro dinâmico e sem limite fixo de dispositivos;
* Leitura correta de dados armazenados no arquivo;
* Estrutura simples e extensível para futuras funcionalidades (como ordenação ou filtragem).

# Sprint 2 – Simulação de Decisão

## 💡 Descrição

Na Sprint 2 foi desenvolvida a **simulação de decisão**, que utiliza as informações cadastradas para **avaliar prioridades** e simular o comportamento dos dispositivos em situações específicas (por exemplo, desligamento por sobrecarga ou consumo máximo).
O foco foi testar a interação entre o cadastro e as futuras operações de ordenação, servindo como uma “prévia” da lógica de comparação entre dispositivos.

A interface textual foi aprimorada com um **menu interativo**, que permite navegar entre as opções:

1. Cadastrar dispositivo
2. Listar dispositivos
3. Comparar algoritmos
4. Sair

Esse menu utiliza captura direta de teclado (sem necessidade de pressionar Enter) e fornece uma experiência fluida dentro do terminal.

## 🔍 Resultados

* Simulação executada corretamente, com feedback visual no terminal;
* Integração funcional entre cadastro, listagem e simulação;
* Preparação do ambiente para a introdução de **algoritmos de decisão e ordenação** na sprint seguinte.

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
