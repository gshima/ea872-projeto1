//EA872 - Projeto 1
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <stdlib.h>
#include <time.h>

#include "oo_model.hpp"

using namespace std::chrono;
uint64_t get_now_ms() {
  return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

int main ()
{
  //edit: inicializa o Player
  uint64_t t0_player, t1_player;

  Audio::Sample *asample;
  asample = new Audio::Sample();
  asample->load("assets/blip.dat");

  Audio::Player *player;
  player = new Audio::Player();
  player->init();


  Corpo *c1 = new Corpo(0, 0, (int)SCREEN_WIDTH/2, (int)SCREEN_HEIGHT/2 , COMIDA);
  Corpo *c2 = new Corpo(10, 0, (int)SCREEN_WIDTH/2 + 10, (int)SCREEN_HEIGHT/2 , SNAKE_HEAD);
  Corpo *c3 = new Corpo(10, 0, (int)SCREEN_WIDTH/2, (int)SCREEN_HEIGHT/2 , SNAKE_BODY);
  Corpo *c4 = new Corpo(10, 0, (int)SCREEN_WIDTH/2, (int)SCREEN_HEIGHT/2 , SNAKE_BODY);

  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(c1);
  l->add_corpo(c2);
  l->add_corpo(c3);
  l->add_corpo(c4);


  SnakeController *f = new SnakeController(l);
  //f->surgir_comida();

  Tela *tela = new Tela(l, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
  tela->init();

  Teclado *teclado = new Teclado();
  teclado->init();

  uint64_t t0;
  uint64_t t1;
  uint64_t deltaT;
  uint64_t T;

  int i = 0;

  T = get_now_ms();
  t1 = T;
  while (1) {
    // Atualiza timers
    t0 = t1;
    t1 = get_now_ms();
    deltaT = t1-t0;

    // Atualiza modelo
    f->update(deltaT);
    // if(flag_morreu) {
    //   break;
    // }
    // if(!flag_cresceu) {
    //   Corpo *c5 = new Corpo(  posicao_x_cresce,
    //                           posicao_y_cresce,
    //                           velocidade_x_cresce,
    //                           velocidade_y_cresce,
    //                           SNAKE_BODY
    //                         );
    //   l->add_corpo(c5);
    //   flag_cresceu = TRUE;
    // }


    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='w') {
      f->andar_para_cima();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='s') {
      f->andar_para_baixo();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='d') {
      f->andar_para_direita();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='a') {
      f->andar_para_esquerda();
      player->play(asample);
      asample->set_position(0);
    }

    if (c=='q') {
      break;
    }

    // Condicao de parada
    //if ( (t1-T) > 10000 ) break;

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  tela->stop();
  teclado->stop();
  return 0;
}
