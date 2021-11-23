#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>

#include "Forca.hpp"
#include "interface.hpp"

int main(int argc, char *argv[]){
  int vidas,n,menu=0,back,pontos=0,g_loop=0,partida;
  std::string palavra, pontilhado,letra,nome;
  Forca::Dificuldade dif;
  std::vector<std::string> palavras_acertadas;
  std::pair<bool,std::string> verifica;
  //verificação e carregamento dos arquivos
  ClearScreen();
  std::cout << "====================================" << std::endl;
  Forca f(argv[1],argv[2]);
  std::cout << "Verificando arquivos..." << std::endl;
  verifica = f.eh_valido();
  if(verifica.first == false){
    std::cout << verifica.second << std::endl;
    std::cout << "====================================" << std::endl;
    return 0;
  }else{
    std::cout << verifica.second << std::endl;
    std::cout << "====================================" << std::endl;
  }
  f.carrega_arquivos();


  while(menu == 0){
    imp_inicio();
    std::cin >> n;
    std::cout << std::endl;
    if(n == 0){
      //IMPRIMIR SCORES
      ClearScreen();
      imp_scores("scores.txt");
      std::cout << std::endl;
      std::cout << "Digite qualquer numero para voltar ao menu" << std::endl << ">";
      std::cin >> back;
      ClearScreen();
    }else if(n == 1){
      //INICIAR JOGO
      ClearScreen();
      //Selecionando dificuldade inicio
      imp_dificuldade();
      std::cin >> n;
      switch(n){
      case 0: dif = Forca::Dificuldade::FACIL; break;
      case 1: dif = Forca::Dificuldade::MEDIO; break;
      case 2: dif = Forca::Dificuldade::DIFICIL; break;
      default: dif = Forca::Dificuldade::FACIL; break;
      }
      f.set_dificuldade(dif);
      g_loop = 0;
      partida = 0;
      //iniciando jogo
      while(g_loop == 0){
        int next = 0;
        f.set_tentativas_restantes(6);
        std::string letras_usadas;
        
        ClearScreen();
        std::cout << "Sorteando palavra para a dificuldade selecionada..." << std::endl;
        pontilhado = f.proxima_palavra();
        palavra = f.get_palavra_atual();
        partida = 0;
        
        std::cout << "Tente acertar essa palavra:" << std::endl;
        while(partida == 0){
          vidas = f.get_tentativas_restantes();
          imp_boneco(vidas);
          std::cout << pontilhado << std::endl;
          std::cout << "Pontos: " << pontos << std::endl;
          std::cout << "Palpite: ";
          //pegar letra do usuario
          std::cin >> letra;
          converte_palavra(letra);

          //testa o palpite
          if(letras_usadas.find(letra) == std::string::npos){
            //testa se o palpite é repetido
            if(f.palpite(letra) == true){
              std::string letra_aux;
              int acerto=0;
              //muda o pontilhado
              for(int i=0;i<palavra.size();i++){
                letra_aux = tolower(palavra[i]);
                if(letra_aux == letra){
                  pontilhado[i*2] = palavra[i];
                  acerto++;
                }//letra_aux
              }//for
              if(acerto > 0){
                if(vidas == 6){
                  pontos+=2;
                }else{
                  pontos+=1;
                }
              }
            }else if(letras_usadas.find(tolower(letra[0])) == std::string::npos){
            std::cout << std::endl << "ERROU!" << std::endl;
            pontos-=1;
            }
          }//find

          letras_usadas+=letra;

          //verificação se o jogo acabou
          if(f.game_over()==true){
            partida = 1;
            vidas = f.get_tentativas_restantes();
            imp_boneco(vidas);
            std::cout << "A palavra era: " << palavra << std::endl;
            imp_gameover();
            break;
          }

          if(pontilhado.find('_') == std::string::npos){
            std::cout << std::endl;
            std::cout << pontilhado << std::endl;
            std::cout << std::endl;
            pontos+=2;
            std::cout << "Pontos: " << pontos << std::endl;
            std::cout << std::endl;
            std::cout << "Parabéns! Você acertou a palavra! Caso deseja seguir para a proxima palavra digite 1, se não, digite 0." << std::endl;
            std::cin >> next;
            partida = 1;
          }
          
        }//partida

        if(f.palavras_restantes() == false){
          std::cout << "Não existem mais palavras para essa dificuldade" << std::endl;
          g_loop = 1;
          next = 0;
        }

        switch(next){
          case 0: g_loop = 1; std::cout << "Digite seu nome: "; std::cin >> nome;
          case 1: continue;
          default: g_loop = 1; std::cout << "Digite seu nome: "; std::cin >> nome;
        }
        

      }//g_loop

      
      f.change_score(dif, nome, pontos);
      

      //fim
    }else if(n==2){
        std::cout<<"Até mais!"<<std::endl;
        return 0;
    }else{
      ClearScreen();
      std::cout << "OPÇÃO INVALIDA - Digite qualquer numero para retornar ao menu" << std::endl << ">";
      std::cin >> back;
      ClearScreen();
    }
  }

} 