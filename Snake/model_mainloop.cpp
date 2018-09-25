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
  Corpo *comida1 = new Corpo(0,0);
  Corpo *comida2 = new Corpo(SCREEN_WIDTH,0);
  Corpo *comida3 = new Corpo(0,SCREEN_HEIGHT);
  Corpo *comida4 = new Corpo(SCREEN_WIDTH,SCREEN_HEIGHT);
  Corpo *comida = new Corpo(centro_x,centro_y); //Corpo(float posicao_x, float posicao_y)
  //Snake *snake = new Snake(5, 5, 3, 2); //Snake(float posicao_x, float posicao_y, int tam, float velocidade );

  //inicializa lista de corpos
  //Corpo *c1 = new Corpo(10, 0, 20, 0, 0, 100, 5);
  // Corpo *c2 = new Corpo(10, 0, 20, 0, 0, 100, 5);
  // Corpo *c3 = new Corpo(10, 0, 20, 0, 0, 100, 5);
  // Corpo *c4 = new Corpo(10, 0, 20, 0, 0, 100, 5);

  ListaDeCorpos *l = new ListaDeCorpos();
  l->add_corpo(comida);
  l->add_corpo(comida1);
  l->add_corpo(comida2);
  l->add_corpo(comida3);
  l->add_corpo(comida4);
  // l->add_corpo(c1);
  // l->add_corpo(c2);
  // l->add_corpo(c3);
  // l->add_corpo(c4);

  //inicializa SnakeController()
  Fisica *f = new Fisica(l);

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
