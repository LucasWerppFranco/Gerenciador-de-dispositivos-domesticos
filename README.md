# Gerenciador de dispositivos domesticos

> ⚠️ **Nota Importante:** - O programa foi criado no contexto de uma maquina Linux 

Eexistem alguns fatores que impedem a sua compilação em uma maquina Windows. Para contornar isso, Eu desenvolvi uma Dockerfile que compila e roda o código no contexto de uma maquina windos para quem for usar este programa.

---

Na **Sprint 3**, o sistema foi evoluído com:
- Implementação de dois algoritmos de ordenação:
  - **Bubble Sort**
  - **Insertion Sort**
- Comparação entre os algoritmos, registrando:
  - Tempo de execução (via `clock()`).
  - Número de comparações realizadas.
- Exibição de resultados comparativos em tabela.

## 📊 Resultados Comparativos (exemplo com 6 dispositivos)
Algoritmo	Tempo (s)	Comparações

Bubble Sort	0.000002	15

Insertion Sort	0.000001	9

<img width="453" height="241" alt="20250923_19h07m21s_grim" src="https://github.com/user-attachments/assets/06f7ea29-20d7-4e42-87a5-acd66c11256d" />

Os valores variam conforme o número de dispositivos cadastrados e a máquina de execução.

## 📈 Análise de Complexidade
Bubble Sort

- Melhor caso (já ordenado): Θ(n²) → ainda percorre todos os pares.
- Caso médio: Θ(n²).
- Pior caso (inversamente ordenado): Θ(n²).

Insertion Sort
-Melhor caso (já ordenado): Θ(n).
- Caso médio: Θ(n²).
- Pior caso (inversamente ordenado): Θ(n²).

## 📌 Conclusão
embora ambos tenham complexidade quadrática no pior caso, o Insertion Sort é mais eficiente em listas pequenas ou parcialmente ordenadas.

---

## Comando Para Compilar o Programa No Linux

```
gcc -std=c99 -D_XOPEN_SOURCE=700 main.c -o main
```

## Instalando Imagem e Rodando o Programa No Docker

```
docker build -t meu_programa .
docker run -it --rm meu_programa
```

# Colaboradores do Projeto

  Lucas Alves Antunes Almeida / RM: 566362 

  Lucas Werpp Franco / RM: 556044 

  Lucca Rosseto Rezende / RM: 564180 

  Massayoshi Bando Fogaça e Silva / RM: 561779 

  Miguel Lima da Silva / RM: 565141
