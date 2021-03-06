//EA872 - LAB4
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#define SCREEN_HEIGHT 20
#define SCREEN_WIDTH SCREEN_HEIGHT*2

#define PARA_CIMA 13
#define PARA_BAIXO 14
#define PARA_DIREITA 15
#define PARA_ESQUERDA 16

#define COMIDA 21
#define SNAKE 22
#define SNAKE_BODY 23

//#define SPACE_WIDTH 50
//#define SPACE_HEIGHT 50

#include "portaudio.h"  //edit: From MP4 playback.hpp
#include <vector>       //edit: From MP4 playback.hpp
#include <thread>

class Corpo {
  protected:
    float posicao_x;
    float posicao_y;
    int tipo;

  public:
    Corpo(float posicao_x, float posicao_y, int tipo);
    void update_posicao(float nova_posicao_x, float nova_posicao_y);
    float get_posicao_x();
    float get_posicao_y();
    int get_tipo();
};

class SnakeModel : Corpo {
  private:
    float velocidade;
    int direcao;
    std::vector<Corpo*> *snake_body;

  public:
    SnakeModel( float posicao_x,
                float posicao_y,
                int get_tipo,
                float velocidade,
                int direcao
              ) ;
    float get_posicao_x();
    float get_posicao_y();
    int get_tipo();
    void add_corpo(Corpo *c);
    int get_velocidade();
    int get_direcao();
    void update_velocidade(float nova_velocidade);
    void update_direcao(int nova_direcao);
    std::vector<Corpo*> *get_snake_body();
};

class ListaDeCorpos {
 private:
    std::vector<Corpo*> *corpos;

  public:
    ListaDeCorpos();
    void hard_copy(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    std::vector<Corpo*> *get_corpos();
};

class SnakeController {
  private:
    ListaDeCorpos *lista;

  public:
    SnakeController(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    void update(float deltaT);
    void andar_para_direita();
    //TODO void virar(char comando);
    //TODO void comer();
    //TODO void morrer();

};

class Fisica {
  private:
    ListaDeCorpos *lista;

  public:
    Fisica(ListaDeCorpos *ldc);
    void add_corpo(Corpo *c);
    void choque();
    void choque_contrario(); //edit: Adicionad
    void update(float deltaT);

};

class Tela {
  private:
    ListaDeCorpos *lista, *lista_anterior;
    int maxI, maxJ;
    float maxX, maxY;

  public:
    Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY);
    ~Tela();
    void stop();
    void init();
    void update();
};

void threadfun (char *keybuffer, int *control);

class Teclado {
  private:
    char ultima_captura;
    int rodando;

    std::thread kb_thread;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
};

namespace Audio { //edit: Class from MP4 playback.hpp

class Sample {
  private:
    std::vector<float> data;
    unsigned int position;

  public:
    Sample();
    ~Sample();
    void load(const char *filename);
    std::vector<float> get_data();
    unsigned int get_position();
    void set_position(unsigned int pos);
    bool finished();

};


class Player {
  private:
    Sample *audio_sample;
    bool playing;

    PaStreamParameters  outputParameters;
    PaStream*           stream;
    PaError             err;
    PaTime              streamOpened;


  public:
    Player();
    ~Player();

    void init();
    void pause();
    void stop();
    void play(Sample *audiosample);
    Sample *get_data();
};

}

#endif
