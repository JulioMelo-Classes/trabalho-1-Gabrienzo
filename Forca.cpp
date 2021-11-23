#include "Forca.hpp"

int medio_chance=0;
std::string palavras_sorteadas;

/*TODO implementação da classe*/

///////////////////////////////////////////////////////
Forca::Forca( std::string palavras, std::string scores ){
  m_arquivo_palavras = palavras;
  m_arquivo_scores = scores;
}

void converte_palavra(std::string& word){
  for(int i=0;i<word.length();i++){
    word[i]= tolower(word[i]);
  }
}
///////////////////////////////////////////////////////
std::pair<bool, std::string> Forca::eh_valido(){
  std::ifstream arq1;
  std::string linescore;
  std::string palavra;
  std::string::size_type sz;

  arq1.open(m_arquivo_palavras, std::ios::in);
  while (! arq1.eof()){
    getline(arq1, linescore);
    int numero =  std::stoi (linescore,&sz);
    palavra=linescore.substr(sz+1);
    if(numero<0){
      return{false, "Nomes.txt: Frequência menor que zero!"};
    }
    if (palavra.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ-")!= std::string::npos){
      return{false,"Nomes.txt: Caractéres não permitidos!"};
    }
    if(palavra.length()<4){
      return{false,"Nomes.txt: Tamanho da palavra menor do que 4!"};
    }
  }
  arq1.close();

  arq1.open(m_arquivo_scores, std::ios::in);
  while (! arq1.eof()){
    getline(arq1, linescore);

    if(linescore[0] != 'F' && linescore[0] != 'M' && linescore[0] !='D'){
      return{false,"Scores.txt: Campo Dificuldade incorreto!"};
    }

    int aux=0,verif_nome=0;
    int tam = linescore.length();
    for(int i=0;i<linescore.length();i++){
      if(linescore[i]==';'){
        aux++;
      }
      if(aux==2 && verif_nome ==0){
        verif_nome = 1;
        if(linescore[i-1]==' '){
          std::cout << linescore[i-1] << std::endl;
          return{false,"Scores.txt: Campo Nome incorreto!"};
          }
      }
      if(aux>3){
      return{false,"Scores.txt: Mais de 3 ';' no arquivo!"};
      }
    }
    
    tam = linescore.length();
    if(linescore[tam-1] != '0' && linescore[tam-1] != '1' && linescore[tam-1] !='2' && linescore[tam-1] != '3' && linescore[tam-1] != '4' && linescore[tam-1] != '5' && linescore[tam-1] != '6' && linescore[tam-1] != '7' && linescore[tam-1] != '8' && linescore[tam-1] != '9'){
      return{false,"Scores.txt: Campo Pontuação incorreto!"};
    }
  
  }   
  arq1.close();
  return{true,"Arquivos validos!"};
}
/////////////////////////////////////////////////////// 
void Forca::carrega_arquivos(){
  std::ifstream arq1;
  std::string linha;
  std::string::size_type sz;
  int media=0,soma=0,qtd=0,fm=0;

  arq1.open(m_arquivo_palavras, std::ios::in);

  while (! arq1.eof()){
    getline(arq1, linha);
    int numero =  std::stoi(linha,&sz);

    std::pair<std::string, int> palavra;
    palavra.second = numero;
    palavra.first = linha.substr(sz+1);

    m_palavras.push_back(palavra);
  
  }

  arq1.close();

  //frequencia media:
  for(int i=0; i<m_palavras.size();i++){
    soma += m_palavras[i].second;
    qtd++;
  }
  media = soma/qtd;
  frequencia_media = media;
  //quantidade de palavras faceis e medias;
  for(int i=0;i<m_palavras.size();i++){
    if(m_palavras[i].second <= frequencia_media){
      fm++;
    }
  }
  m_palavras_FM = fm;

}
///////////////////////////////////////////////////////
void Forca::set_dificuldade(Dificuldade dif){
  d = dif;
}
///////////////////////////////////////////////////////
std::string Forca::proxima_palavra(){
  std::string segredo="_",plvr;
  int pos,w=0,qtd=1,i,j,l_rep=0;
  srand (time(NULL));

  if(m_palavras_usadas.size() == m_palavras.size()){
    std::cout << "Não existe mais palavras" << std::endl;
    segredo = "acabo";
  }else{
    //sorteia uma palavra FACIL:
  if(d == Dificuldade::FACIL){
    int sort=0,tam=m_palavras.size();
    std::string letras_rep;
    //pegar palavra
    while(w==0){
      pos = rand() % m_palavras.size();
      if(m_palavras[pos].second >= frequencia_media && palavras_sorteadas.find(m_palavras[pos].first) == std::string::npos){
        plvr = m_palavras[pos].first;
        w=1;
      }else{
        palavras_sorteadas+=m_palavras[pos].first;
        sort++;
      }
      
    }

    //definindo a palavra atual como a palavra sorteada
    m_palavra_atual = plvr;
    m_palavras_usadas.push_back(plvr);
    converte_palavra(plvr);
    m_palavra_atual = plvr;


    //criar a base de segredo:
    for(i=0;i<plvr.size()-1;i++){
      segredo += " _";
    }

    //sortear consoantes
    qtd = rand() % (tam/5) + 1;
    while(qtd != 0){
      //sortenado posição da letra
      j = rand() % plvr.size();
      //verificação se é consoante
      if(plvr[j] != 'a' && plvr[j] != 'e' && plvr[j] != 'i' && plvr[j] != 'o' && plvr[j] != 'u' && plvr[j] != 'A' && plvr[j] != 'E' && plvr[j] != 'I' && plvr[j] != 'O' && plvr[j] != 'U'){
        //verificação se ela ja foi sorteada
        if(letras_rep.find(plvr[j]) == std::string::npos){
          //colocando em segredo
          segredo[j*2] = plvr[j];
          qtd--;
          letras_rep+=plvr[j];
        }
      //caso seja uma vogal ela vai para letras repetidas
      }else{
        letras_rep+=plvr[j];
      }
      //caso todas as letras ja tenham sido sorteadas ele sai do while
      if(letras_rep.size() == plvr.size()){
        qtd = 0;
      }

    }
  }
  //sorteia uma palavra MEDIO:
  if(d == Dificuldade::MEDIO){
    std::string palavras_sorteadas;
    int sort=0,tam=m_palavras.size();
    std::string letras_rep;

    //pegar palavra
    pos = rand() % m_palavras.size();

    if(medio_chance == 2){
      if(m_palavras[pos].second < frequencia_media && palavras_sorteadas.find(m_palavras[pos].first) == std::string::npos){
        plvr = m_palavras[pos].first;
        medio_chance = 0;
        sort++;
      }
    }else if(palavras_sorteadas.find(m_palavras[pos].first) == std::string::npos){
      plvr = m_palavras[pos].first;
      medio_chance++;
      sort++;
      
    }

    //definindo a palavra atual como a palavra sorteada
    m_palavra_atual = plvr;
    m_palavras_usadas.push_back(plvr);
    converte_palavra(plvr);
    m_palavra_atual = plvr;
    
    //criar a base de segredo:
    for(i=0;i<plvr.size()-1;i++){
      segredo += " _";
    }
    
    //verificação se é vogal
    while(qtd != 0){
      j = rand() % plvr.size();
      if(plvr[j] == 'a' || plvr[j] == 'e' || plvr[j] == 'i' || plvr[j] == 'o' || plvr[j] == 'u' || plvr[j] == 'A' || plvr[j] == 'E' || plvr[j] == 'I' || plvr[j] == 'O' || plvr[j] == 'U'){
        //verificação se ela ja foi sorteada
        if(letras_rep.find(plvr[j]) == std::string::npos){
          //colocando em segredo
          segredo[j*2] = plvr[j];
          qtd--;
          letras_rep+=plvr[j];
          qtd = 0;
        }
      //caso seja uma vogal ela vai para letras repetidas
      }else{
        letras_rep+=plvr[j];
      }
      //caso todas as letras ja tenham sido sorteadas ele sai do while
      if(letras_rep.size() == plvr.size()){
        qtd = 0;
      }
    }
    
  }
  //sorteia uma palavra DIFICIL
  if(d == Dificuldade::DIFICIL){
    std::string palavras_sorteadas;
    int sort=0,tam=m_palavras.size();

    while(w==0){
      pos = rand() % m_palavras.size();
      if(m_palavras[pos].second < frequencia_media && palavras_sorteadas.find(m_palavras[pos].first) == std::string::npos){
        plvr = m_palavras[pos].first;
        w=1;
      }else{
        palavras_sorteadas+=m_palavras[pos].first;
        sort++;
      }
      
    }
    //definindo a palavra atual como a palavra sorteada
    m_palavras_usadas.push_back(plvr);
    converte_palavra(plvr);
    m_palavra_atual = plvr;

    //criar a base de segredo:
    for(i=0;i<plvr.size()-1;i++){
      segredo += " _";
    }

  }
  
  }

  return segredo;
}

///////////////////////////////////////////////////////
bool Forca::palpite(std::string palpite){
  int j,erro=1;

  if(m_palavra_atual.find(palpite) != std::string::npos){
    for(j=0;j<m_palavra_atual.size();j++){
      std::string letra;
      letra = tolower(m_palavra_atual[j]);
      if(letra == palpite){
        return true;
      }
    }
  }else{
    m_tentativas_restantes -= 1;
    return false;
  }
  
  return 0;
}

///////////////////////////////////////////////////////
bool Forca::game_over(){
  if(m_tentativas_restantes==0){
    return true;
  }
  return false;
}
///////////////////////////////////////////////////////
void Forca::set_tentativas_restantes(int tentativas){
  m_tentativas_restantes = tentativas;
}
///////////////////////////////////////////////////////
int Forca::get_tentativas_restantes(){
  return m_tentativas_restantes; 
}
///////////////////////////////////////////////////////
std::string Forca::get_palavra_atual(){
  return m_palavra_atual;
}
///////////////////////////////////////////////////////

void Forca::change_score(Dificuldade dif, std::string name, int pontuacao){
    
    std::ofstream arq1;
    std::string aux;
    arq1.open(m_arquivo_scores, std::ios::app);
    
    switch(dif){
    case 0: aux = "Fácil"; break;
    case 1: aux = "Médio"; break;
    case 2: aux = "Difícil"; break;
    }
    int tam = m_palavras_usadas.size(); 
    arq1<< "\n"<< aux<< "; "<< name<< "; "; 
    for(int i=0;i<tam;i++){
      arq1<<m_palavras_usadas[i];
      if(i<tam-1){
        arq1<<", ";
        }
    }
    arq1<<"; "<< pontuacao;

    arq1.close();
}

///////////////////////////////////////////////////////
bool Forca::palavras_restantes(){
  int nomes=0;
  if(d == Dificuldade::DIFICIL){
    if(m_palavras_usadas.size() == m_palavras.size()){
      return false;
    }
  }else if(m_palavras_FM == m_palavras_usadas.size()){
    return false;
  }

  return true;
}