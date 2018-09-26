//EA872 - LAB4
// Mariane Tiemi Iguti (RA147279) e Gabriela Akemi Shima (RA135819)
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <fstream> //edit: include from playback.cpp
#include <sstream> //edit: include from playback.cpp
#include <string> //edit: include from playback.cpp
#include <random> //edit: include from playback.cpp
#include <typeinfo>

#include "oo_model.hpp"

#include <ncurses.h>
using namespace std::chrono;

Corpo::Corpo(float posicao_x, float posicao_y, int tipo) {
  this->posicao_x = posicao_x;
  this->posicao_y = posicao_y;
  this->tipo = tipo;

}

void Corpo::update_posicao(float nova_posicao_x, float nova_posicao_y) {
  this->posicao_x = nova_posicao_x;
  this->posicao_y = nova_posicao_y;
}

float Corpo::get_posicao_x() {
  return this->posicao_x;
}

float Corpo::get_posicao_y() {
  return this->posicao_y;
}

int Corpo::get_tipo() {
  return this->tipo;
}

SnakeModel::SnakeModel(float posicao_x, float posicao_y, int tipo, float velocidade, int direcao) :
Corpo(posicao_x, posicao_y, tipo){
  this->posicao_x = posicao_x;
  this->posicao_y = posicao_y;
  this->tipo = tipo;
  this->velocidade = velocidade;
  this->direcao = PARA_DIREITA;
  this->snake_body = new std::vector<Corpo *>(0);
  Corpo *p = new Corpo(posicao_x,posicao_y,SNAKE);
  (this->snake_body)->push_back(p);
  // Corpo *p1 = new Corpo(posicao_x-1,posicao_y,SNAKE_BODY);
  // (this->snake_body)->push_back(p1);
  // Corpo *p2 = new Corpo(posicao_x-2,posicao_y,SNAKE_BODY);
  // (this->snake_body)->push_back(p2);
  // Corpo *p3 = new Corpo(posicao_x-3,posicao_y,SNAKE_BODY);
  // (this->snake_body)->push_back(p3);
}

float SnakeModel::get_posicao_x() {
  return Corpo::get_posicao_x();
}
float SnakeModel::get_posicao_y(){
  return Corpo::get_posicao_y();
}
int SnakeModel::get_tipo(){
  return Corpo::get_tipo();
}

void SnakeModel::add_corpo(Corpo *c) {
  (this->snake_body)->push_back(c);
}

std::vector<Corpo*> *SnakeModel::get_snake_body() {
  return (this->snake_body);
}

int SnakeModel::get_velocidade(){
    return (this->velocidade);
}

int SnakeModel::get_direcao(){
    return (this->direcao);
}
SnakeController::SnakeController(ListaDeCorpos *ldc) {
    this->lista = ldc;
}
void SnakeController::add_corpo(Corpo *c) {

}
void SnakeController::update(float deltaT) { // andar
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *corpos = this->lista->get_corpos();
  for (int i = 0; i < (*corpos).size(); i++) {

    if((*corpos)[i]->get_tipo() == SNAKE) {

      float new_pos_x_cabeca = (*corpos)[i]->get_posicao_x();
      float new_pos_y_cabeca = (*corpos)[i]->get_posicao_y();

      SnakeModel *snake_cast = (SnakeModel*) (*corpos)[i];
      std::vector<Corpo *> *corpos_snake = (snake_cast)->get_snake_body();

      if((snake_cast)->get_direcao() == PARA_DIREITA) {
        if(move(-35, -65 ) != ERR) echochar('&');
        int lala = (snake_cast)->get_posicao_x();
        std::cout<< lala <<std::endl;
        new_pos_x_cabeca = (snake_cast)->get_posicao_x() + (snake_cast)->get_velocidade()*deltaT/1000;
        if(new_pos_x_cabeca > SCREEN_WIDTH ) new_pos_x_cabeca = (int)new_pos_x_cabeca % SCREEN_WIDTH;
      }

      // else if((snake_cast)->get_direcao() == PARA_ESQUERDA) {
      //   new_pos_x_cabeca = (snake_cast)->get_posicao_x() - (snake_cast)->get_velocidade()*deltaT;
      //   if(new_pos_x_cabeca < 0 ) new_pos_x_cabeca = SCREEN_WIDTH + new_pos_x_cabeca;
      // }
      //
      // else if((snake_cast)->get_direcao() == PARA_CIMA) {
      //   new_pos_y_cabeca = (snake_cast)->get_posicao_y() - (snake_cast)->get_velocidade()*deltaT;
      //   if(new_pos_y_cabeca > SCREEN_HEIGHT) new_pos_y_cabeca = (int)new_pos_y_cabeca % SCREEN_HEIGHT;
      // }
      //
      // else if((snake_cast)->get_direcao() == PARA_BAIXO) {
      //   new_pos_y_cabeca = (snake_cast)->get_posicao_y() + (snake_cast)->get_velocidade()*deltaT;
      //   if(new_pos_y_cabeca < 0 ) new_pos_y_cabeca = SCREEN_HEIGHT+ new_pos_y_cabeca;
      // }

      (*corpos)[i]->update_posicao(new_pos_x_cabeca, new_pos_y_cabeca);


      // for(int l=1; l < corpos_snake->size(); l++){
      //   float new_pos_x =
      //   float new_pos_y =
      //
      // }
    }
    // if else ((*corpos)[i]->get_tipo() == SNAKE) {
    // }

  }
}
//void SnakeController::andar_para_direita(float deltaT);

// void SnakeController::andar(float deltaT) {
//   int delta_posicao = (this->velocidade)*deltaT;
//   if(this->direcao == PARA_DIREITA ) {
//     this->posicao_x = this->posicao_x + delta_posicao;
//     // for( l = 0 ; ) {
//     //
//     // }
//
//   }

//}
void SnakeModel::update_velocidade(float nova_velocidade) {
  this->velocidade = nova_velocidade;
}

void SnakeModel::update_direcao(int nova_direcao) {
  this->direcao = nova_direcao;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_posicao_x(),\
                          (*corpos)[k]->get_posicao_y(),
                          (*corpos)[k]->get_tipo()
                        );
    if( (*corpos)[k]->get_tipo() == SNAKE) {
       SnakeModel *snake_cast = (SnakeModel*) (*corpos)[k];
       // if(move(-35, -65 ) != ERR) echochar('&');
       // int lala = (snake_cast)->get_posicao_x();
       // std::cout<< lala <<std::endl;
      SnakeModel *snake_copy = new SnakeModel(  (snake_cast)->get_posicao_x(),\
                                                (snake_cast)->get_posicao_y(),\
                                                (snake_cast)->get_tipo(),\
                                                (snake_cast)->get_velocidade(),\
                                                (snake_cast)->get_direcao()
                                              );
      std::vector<Corpo *> *corpos_snake = (snake_cast)->get_snake_body();

      for(int l=0; l<corpos_snake->size();l++) {
        Corpo *d = new Corpo( (*corpos_snake)[l]->get_posicao_x(),\
                              (*corpos_snake)[l]->get_posicao_y(),\
                              (*corpos_snake)[l]->get_tipo()\
                            );
        snake_copy->add_corpo(d);
      }
      this->add_corpo( (Corpo*) snake_copy );
      c = (Corpo*) snake_copy;
    }

    this->add_corpo(c);
  }

}


void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();

  for (int i = 0; i < (*c).size(); i++) {

    // float k_corpo = (*c)[i]->get_k(); //edit: Add constante da mola N/m
    // float b_corpo = (*c)[i]->get_b(); //edit: Add coeficiente de amortecimento
    //
    // float new_aceleracao = (- b_corpo*(*c)[i]->get_velocidade() - k_corpo*(*c)[i]->get_posicao() ) / (*c)[i]->get_massa();//edit: Add Calcula aceleracao a partir do modelo a=(-b*v-k*x)/m
    // float new_vel = (*c)[i]->get_velocidade() + (float)deltaT * (new_aceleracao)/1000; //edit: Trocamos a gravidade = - 10 por aceleracao calculada
    // float new_pos = (*c)[i]->get_posicao() + (float)deltaT * new_vel/1000;
    // float new_forca = (*c)[i]->get_aceleracao() * (*c)[i]->get_massa(); //edit: Add Calcula a forca
    // (*c)[i]->update(new_vel, new_pos, new_aceleracao, new_forca); //edit: Atualiza os novos parâmetros de aceleracao e forca
  }
}

void Fisica::choque() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    // float new_vel = (*c)[i]->get_velocidade() + 15;
    // float new_pos = (*c)[i]->get_posicao();
    // float new_acel = (*c)[i]->get_aceleracao();
    // float new_forca = (*c)[i]->get_forca();
    // (*c)[i]->update(new_vel, new_pos, new_acel, new_forca);
  }
}

void Fisica::choque_contrario() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    // float new_vel = (*c)[i]->get_velocidade()-15;
    // float new_pos = (*c)[i]->get_posicao();
    // float new_acel = (*c)[i]->get_aceleracao();
    // float new_forca = (*c)[i]->get_forca();
    // (*c)[i]->update(new_vel, new_pos, new_acel, new_forca);
  }
}

Tela::Tela(ListaDeCorpos *ldc, int maxI, int maxJ, float maxX, float maxY) {
  this->lista = ldc;
  this->lista_anterior = new ListaDeCorpos();
  this->lista_anterior->hard_copy(this->lista);
  this->maxI = maxI;
  this->maxJ = maxJ;
  this->maxX = maxX;
  this->maxY = maxY;
}

void Tela::init() {
  initscr();			       /* Start curses mode 		*/
	raw();				         /* Line buffering disabled	*/
  curs_set(0);           /* Do not display cursor */
}

void Tela::update() {
  int i , j;

  std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();

  // Apaga corpos na tela
  for (int k=0; k<corpos_old->size(); k++)
  {
    i = (int) ((*corpos_old)[k]->get_posicao_x()) * (this->maxI / this->maxX);
    j = (int) ((*corpos_old)[k]->get_posicao_y()) * (this->maxJ / this->maxY);
    //if(move(j, i) != ERR) echochar(' ');

    if(move(j, i) != ERR) {
      if((*corpos_old)[k]->get_tipo() == SNAKE) {
        SnakeModel *snake_cast = (SnakeModel*) (*corpos_old)[k];
        std::vector<Corpo *> *corpos_snake = (snake_cast)->get_snake_body();
        //int lala = (snake_cast)->get_direcao();
        //std::cout<< lala <<std::endl;
        for(int l=0; l < corpos_snake->size(); l++){
          i = (int) ((*corpos_snake)[l]->get_posicao_x()) * (this->maxI / this->maxX);
          j = (int) ((*corpos_snake)[l]->get_posicao_y()) * (this->maxJ / this->maxY);
          if(move(j, i) != ERR) echochar(' '); //imprime cobra
        }
      }
      else echochar(' ');  // imprime comida
    }
  }

  // Desenha corpos na tela
  std::vector<Corpo *> *corpos = this->lista->get_corpos();

  for (int k=0; k<corpos->size(); k++)
  {
    i = (int) ((*corpos)[k]->get_posicao_x()) * (this->maxI / this->maxX);
    j = (int) ((*corpos)[k]->get_posicao_y()) * (this->maxJ / this->maxY);
    if(move(j, i) != ERR) {
      if((*corpos)[k]->get_tipo() == SNAKE) {
        SnakeModel *snake_cast = (SnakeModel*) (*corpos)[k];
        std::vector<Corpo *> *corpos_snake = (snake_cast)->get_snake_body();
        //int lala = (snake_cast)->get_direcao();
        //std::cout<< lala <<std::endl;
        for(int l=0; l < corpos_snake->size(); l++){
          i = (int) ((*corpos_snake)[l]->get_posicao_x()) * (this->maxI / this->maxX);
          j = (int) ((*corpos_snake)[l]->get_posicao_y()) * (this->maxJ / this->maxY);
          if(move(j, i) != ERR)
            echochar('@'); //imprime cobra
        }
      }
      else echochar('*');  // imprime comida
    } /* Move cursor to position */


    // Atualiza corpos antigos
    (*corpos_old)[k]->update_posicao( (*corpos)[k]->get_posicao_x(),\
                                      (*corpos)[k]->get_posicao_y()
                                    );
  }

  // Atualiza tela
  refresh();
}

void Tela::stop() {
  endwin();
}

Tela::~Tela() {
  this->stop();;
}


/*
class Teclado {
  private:
    char ultima_captura;
    int rodando;

  public:
    Teclado();
    ~Teclado();
    void stop();
    void init();
    char getchar();
}

*/

void threadfun (char *keybuffer, int *control)
{
  char c;
  while ((*control) == 1) {
    c = getch();
    if (c!=ERR) (*keybuffer) = c;
    else (*keybuffer) = 0;
    std::this_thread::sleep_for (std::chrono::milliseconds(10));
  }
  return;
}

Teclado::Teclado() {
}

Teclado::~Teclado() {
}

void Teclado::init() {
  // Inicializa ncurses
  raw();				         /* Line buffering disabled	*/
	keypad(stdscr, TRUE);	 /* We get F1, F2 etc..		*/
	noecho();			         /* Don't echo() while we do getch */
  curs_set(0);           /* Do not display cursor */

  this->rodando = 1;
  std::thread newthread(threadfun, &(this->ultima_captura), &(this->rodando));
  (this->kb_thread).swap(newthread);
}

void Teclado::stop() {
  this->rodando = 0;
  (this->kb_thread).join();
}

char Teclado::getchar() {
  char c = this->ultima_captura;
  this->ultima_captura = 0;
  return c;
}

using namespace Audio;

Sample::Sample() {

}

Sample::~Sample() {

}

bool Sample::finished() {
  if ( (this->position) >= (this->data.size())) return true;
  else return false;
}

void Sample::load(const char *filename) {
  std::string buffer;
  float fdata;
  std::ifstream input_file;
  unsigned int count = 0;

  input_file.open(filename, std::ios_base::in);
  if (!input_file) {
    std::cerr << "Arquivo " << filename << " nao encontrado" << std::endl;
    return;
  }

  while (std::getline(input_file, buffer) ) {
    std::stringstream(buffer) >> fdata;
    (this->data).push_back(fdata);
    count ++;
  }
  this->position = 0;

  //std::cerr << "Total: " << count << " samples" << std::endl;

}

unsigned int Sample::get_position() {
  return this->position;
}

void Sample::set_position(unsigned int pos) {
  this->position = pos;
}

std::vector<float> Sample::get_data() {
  return this->data;
}



Player::Player() {
  this->playing = false;
  this->audio_sample = NULL;
}

void Player::pause() {
  this->playing = false;
}

Player::~Player() {

}

Sample *Player::get_data() {
  return this->audio_sample;
}

//funcao de callback:
int mix_and_play (const void *inputBuffer, void *outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void *userData )

{
  Player *player = (Player*) userData;
  float *buffer = (float *) outputBuffer;
  Sample *s;
  s = player->get_data();
  if (s != NULL) {
    std::vector<float> data = s->get_data();
    unsigned int pos = s->get_position();

    // Fill the buffer with samples!
    for (int i=0; (i<framesPerBuffer); i++) {
      if (pos < data.size())
        buffer[i] = data[pos];
      else
        buffer[i] = 0;
      //i++;
      pos+=2;
    }
    s->set_position(pos);
  }
  return 0;
}

void Player::play(Sample *audiosample) {
  this->audio_sample = audiosample;
}

void Player::init() {
  PaError err;

  err = Pa_Initialize();
  if( err != paNoError ) {
    std::cerr << "Error on Pa_Initialize()" << std::endl;
    return;
  }

  outputParameters.device = Pa_GetDefaultOutputDevice(); /* Default output device. */
  if (outputParameters.device == paNoDevice) {
    std::cerr << "Error: No default output device on Pa_GetDefaultOutputDevice()" << std::endl;
    return;
  }

  outputParameters.channelCount = 1;                     /* Mono output. */
  outputParameters.sampleFormat = paFloat32;
  outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
  outputParameters.hostApiSpecificStreamInfo = NULL;
  err = Pa_OpenStream( &stream,
                         NULL,      /* No input. */
                         &outputParameters,
                         44100,
                         64,       /* Frames per buffer. */
                         paClipOff, /* We won't output out of range samples so don't bother clipping them. */
                         mix_and_play,
                         this );

  if( err != paNoError ) {
    std::cerr << "Error on Pa_OpenStream()" << std::endl;
    return;
  }

  err = Pa_StartStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error on Pa_StartStream()" << std::endl;
    return;
  }


}

void Player::stop() {
  PaError err;
  err = Pa_StopStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error on Pa_StopStream()" << std::endl;
    return;
  }

  err = Pa_CloseStream( stream );
  if( err != paNoError ) {
    std::cerr << "Error on Pa_StopStream()" << std::endl;
    return;
  }

  Pa_Terminate();

}
