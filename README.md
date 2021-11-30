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

# Avaliação

## Código | Funcionalidades
1. Classe forca 10/10

2. Interface textual 10/10

3. Execução completa do jogo 15/15
- Mesmo com um bug ou outro acho que a execução ficou muito boa, assim vou considerar 100%

4. Validação dos arquivos de texto 5/5

5. Arquivos de teste de validação dos casos de erro 5/5

6. Arquivos de teste de validação dos níveis de dificuldade 1/5
- A ideia aqui era vc ter arquivos de palavras para validar os game overs quando o usuário acerta todas, validando
assim os níveis de dificuldade e sorteios.

7. Observações gerais
- Acho que caberia  mais uma classe para o score, mas ficou muito boa a divisão do código.
- Você poderia ter criado uma classe "interface"

## Código | Boas práticas

1. Documentação do código e readme 8/10
- Vc não documentou as funções de interface.hpp no formato doxygen, mas vou considerar parte

2. Organização e indentação 5/10
- Não foi feita a divisão em diretórios como especificado

3. Compilação automatizada 5/5
- Sugiro que tente o cmake da próxima vez

