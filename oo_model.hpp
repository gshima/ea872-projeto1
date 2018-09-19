//EA872 - LAB4
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#ifndef OO_MODEL_HPP
#define OO_MODEL_HPP

#include "portaudio.h"  //edit: From MP4 playback.hpp
#include <vector>       //edit: From MP4 playback.hpp
#include <thread>

class Corpo {
  private:
  float massa;
  float velocidade;
  float posicao;
  float aceleracao; //edit: Add novo atributo
  float forca;      //edit: Add novo atributo
  float k;          //edit: Add novo atributo
  float b;          //edit: Add novo atributo

  public:
  Corpo(float massa, float velocidade, float aceleracao, float forca,float posicao, float k, float b);
  void update(float nova_velocidade, float nova_posicao, float nova_aceleracao, float nova_forca);
  float get_massa();
  float get_velocidade();
  float get_posicao();
  float get_aceleracao(); //edit: Add metodo get para novo atributo
  float get_forca();      //edit: Add metodo get para novo atributo
  float get_k();          //edit: Add metodo get para novo atributo
  float get_b();          //edit: Add metodo get para novo atributo

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
