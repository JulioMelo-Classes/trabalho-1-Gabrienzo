# Trabalho-1
Repositório contendo as especificações do Trabalho 1 da disciplina de LP1
especificações dos autores do codigo em [author.md](author.md)

***

## Como compilar o projeto;
	Basta digitar "make all" no console.
## Como executar o projeto;
	Digitando o nome dos arquivos contendo as palavras e os scores nesta ordem respectivamente.

  ```
  ./jogo [nome arquivo com as palavras] [nome arquivo com os scores]
  ```
  Exemplo:
  ```
  ./jogo nomes.txt scores.txt
  ```
## Como executar o conjunto dos testes planejados por você (ou grupo).
	Basta digitar os nomes dos arquivos de teste ao iniciar o programa.
    "nomes.txt" (arquivos de palavras com formatação correta)
    "scores.txt" (arquivos de scores com formatação correta)
    "nomes_erro.txt" (arquivos de palavras com formatação incorreta)
    "scores_erro.txt" (arquivos de scores com formatação incorreta)

## Limitações ou funcionalidades não implementadas no programa.
    + organização em src e include
    + Valgrind e/ou address sanitizer
    + GDB (debbuger)