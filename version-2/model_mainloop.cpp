//EA872 - LAB4
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
  //edit: inicializa o Player
  uint64_t t0_player, t1_player;

  Audio::Sample *asample;
  asample = new Audio::Sample();
  asample->load("assets/blip.dat");

  Audio::Player *player;
  player = new Audio::Player();
  player->init();

  //inicializa comida no centro da tela
  int centro_x = (int) SCREEN_WIDTH/2;
  int centro_y = (int) SCREEN_HEIGHT/2;
  Corpo *comida = new Corpo(centro_x,centro_y - 2, COMIDA); //Corpo(float posicao_x, float posicao_y)
  SnakeModel *snake = new SnakeModel(centro_x - 10,centro_y, SNAKE,100, PARA_DIREITA);

  //Medição de tela
  Corpo *comida1 = new Corpo(0,0, COMIDA);
  Corpo *comida2 = new Corpo(SCREEN_WIDTH,0,COMIDA);
  Corpo *comida3 = new Corpo(0,SCREEN_HEIGHT,COMIDA);
  Corpo *comida4 = new Corpo(SCREEN_WIDTH,SCREEN_HEIGHT,COMIDA);


  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(comida);
  l->add_corpo(comida1);
  l->add_corpo(comida2);
  l->add_corpo(comida3);
  l->add_corpo(comida4);
  l->add_corpo((Corpo*)snake);


  //inicializa SnakeController()
  Fisica *f = new Fisica(l);
  SnakeController *s = new SnakeController(l);

  //inicializa tela
  // Tela::Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY)
  Tela *tela = new Tela(l, SCREEN_WIDTH , SCREEN_HEIGHT , SCREEN_WIDTH, SCREEN_HEIGHT);
  tela->init();

  //incializa teclado
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
    s->update(deltaT);

    // Atualiza tela
    tela->update();

    // Lê o teclado
    char c = teclado->getchar();
    if (c=='s') {
      f->choque();

      player->play(asample);
      asample->set_position(0);
      //player->stop();
    }
    if (c=='w') { //edit: adicionado outro comando
      f->choque_contrario();

      player->play(asample);
      asample->set_position(0);
      //player->stop();
    }
    if (c=='q') {
      break;
    }

    std::this_thread::sleep_for (std::chrono::milliseconds(100));
    i++;
  }
  tela->stop();
  teclado->stop();
  return 0;
}
