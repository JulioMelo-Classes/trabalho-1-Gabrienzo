#include <string>
#include <fstream>
#include "Forca.hpp"

void imp_inicio(){
  std::cout << "Bem-vindo ao jogo da Forca, digite a opção desejada:" << std::endl << "0 - Scores" << std::endl << "1 - Iniciar jogo" << std::endl << "2 - Sair" << std::endl << "Digite a opção: ";
}

void imp_scores(std::string score){
  std::ifstream arq1;
  std::string linha;
  std::cout << "::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
  arq1.open(score, std::ios::in);
  while (! arq1.eof()){
    getline(arq1, linha);

    std::cout << linha << std::endl;
  }
  arq1.close();
  std::cout << "::::::::::::::::::::::::::::::::::::::::::::::" << std::endl;
}

void imp_dificuldade(){
  std::cout << "Digite a dificuldade do jogo desejada:" << std::endl << "0 - Fácil" << std::endl << "1 - Médio" << std::endl << "2 - Difícil" << std::endl << std::endl << "Digite a opção: ";
}

int imp_boneco(int erros){
  switch(erros){
    case 5: std::cout << "○" << std::string(7,'\n'); break;
    case 4: std::cout << "○" << std::endl << "|" << std::endl << "|" << std::endl << std::string(6,'\n'); break;
    case 3: std::cout << " ○" << std::endl << "/" << "|" << std::endl << " |" << std::endl << "" << std::string(5,'\n'); break;
    case 2: std::cout << " ○" << std::endl << "/" << "|" << "\\" << std::endl << " |" << std::endl << "" << std::string(4,'\n'); break;
    case 1: std::cout << " ○" << std::endl << "/" << "|" << "\\" << std::endl << " |" << std::endl << "/" << "" << std::string(3,'\n'); break;
    case 0: std::cout << " ○" << std::endl << "/" << "|" << "\\" << std::endl << " |" << std::endl << "/" << " " << "\\" << std::string(2,'\n'); break;
    default: std::cout << std::string(8,'\n');
  }
  return erros;
}

void imp_gameover(){
  std::cout << "  _____                         ____                 " << std::endl << " / ____|                       / __ \\                " << std::endl << "| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ " << std::endl << "| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|" << std::endl << "| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   " << std::endl << " \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   " << std::endl<< std::endl;
}

void ClearScreen(){
    std::cout << std::string(100, '\n');
}