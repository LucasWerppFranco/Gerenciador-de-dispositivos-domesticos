# Gerenciador de dispositivos domesticos

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

# Colaboradores do Projeto

  Lucas Alves Antunes Almeida / RM: 566362 

  Lucas Werpp Franco / RM: 556044 

  Lucca Rosseto Rezende / RM: 564180 

  Massayoshi Bando Fogaça e Silva / RM: 561779 

  Miguel Lima da Silva / RM: 565141
