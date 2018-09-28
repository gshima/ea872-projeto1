//EA872 - Projeto 1
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "oo_model.hpp"


using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  //inicializa o Player
  uint64_t t0_player, t1_player;

  Audio::Sample *asample;
  asample = new Audio::Sample();
  asample->load("assets/blip.dat");

  Audio::Player *player;
  player = new Audio::Player();
  player->init();

  // Adicionando a comida, head do snake e corpo do snake inicialmente.
  Corpo *c1 = new Corpo(0, 0, (int)SCREEN_WIDTH/2, (int)SCREEN_HEIGHT/2 , COMIDA); // criando a comida
  Corpo *c2 = new Corpo(10, 0, (int)SCREEN_WIDTH/2, (int)SCREEN_HEIGHT/2 , SNAKE_HEAD); // criando a cabeca do snake
  Corpo *c3 = new Corpo(10, 0, ((int)SCREEN_WIDTH/2)-2, (int)SCREEN_HEIGHT/2 , SNAKE_BODY); // criando parte do corpo do snake
  Corpo *c4 = new Corpo(10, 0, ((int)SCREEN_WIDTH/2)-4, (int)SCREEN_HEIGHT/2 , SNAKE_BODY);
  Corpo *c5 = new Corpo(10, 0, ((int)SCREEN_WIDTH/2)-6, (int)SCREEN_HEIGHT/2 , SNAKE_BODY);

  // Adicionando na lista de corpos
  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(c1);
  l->add_corpo(c2);
  l->add_corpo(c3);
  l->add_corpo(c4);
  l->add_corpo(c5);

  // Criando o Snake Controller
  SnakeController *f = new SnakeController(l);

  // Inicializando a Tela
  Tela *tela = new Tela(l, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
  tela->init();

  // Inicializando o Teclado
  Teclado *teclado = new Teclado();
  teclado->init();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  T = get_now_ms();
  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo
    f->update(deltaT);
    
    // TENTAMOS USAR FLAG GLOBAL PARA TENTAR ADICIONAR UM CORPO NA LISTA DE CORPOS QUANDO O SNAKE COME A COMIDA MAS SEM SUCESSO
//     if(flag_cresceu == TRUE){
//       std::vector<Corpo *> *c = l->get_corpos();
//       Corpo *cp = new Corpo ( (*c)[(c)->size() - 1]->get_velocidade_x(),\
//                               (*c)[(c)->size() - 1]->get_velocidade_y(),\
//                               (*c)[(c)->size() - 1]->get_posicao_x(),\
//                               (*c)[(c)->size() - 1]->get_posicao_y(),\
//                               SNAKE_BODY
//                             );
    
//      l->add_corpo(cp); // SEGMENTATION FAULT QUANDO TENTA ADICIONAR NA LISTA
//       flag_cresceu = FALSE;
//     }
    

    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='w') { // Comando para andar pra cima
      f->andar_para_cima();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='s') { // Comando para andar para baixo
      f->andar_para_baixo();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='d') { // Comando para andar para direita
      f->andar_para_direita();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='a') { // Comando para andar para esquerda
      f->andar_para_esquerda();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='q') { // Comando para terminar o jogo
      break;
    }

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
  }
  tela->stop();
  teclado->stop();
  return 0;
}
