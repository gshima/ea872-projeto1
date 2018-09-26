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

#include "oo_model.hpp"

#include <ncurses.h>
using namespace std::chrono;

Corpo::Corpo( float velocidade_x,
              float velocidade_y,
              float posicao_x,
              float posicao_y,
              int tipo
            ) {

  this->velocidade_x = velocidade_x;
  this->velocidade_y = velocidade_y;
  this->posicao_x = posicao_x;
  this->posicao_y = posicao_y;
  this->tipo = tipo;

}

void Corpo::update( float nova_velocidade_x,
                    float nova_velocidade_y,
                    float nova_posicao_x ,
                    float nova_posicao_y
                  ) {
  this->velocidade_x = nova_velocidade_x;
  this->velocidade_y = nova_velocidade_y;
  this->posicao_x = nova_posicao_x;
  this->posicao_y = nova_posicao_y;

}


float Corpo::get_velocidade_x() {
  return this->velocidade_x;
}

float Corpo::get_velocidade_y() {
  return this->velocidade_y;
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


ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_velocidade_x(),\
                          (*corpos)[k]->get_velocidade_y(),\
                          (*corpos)[k]->get_posicao_x(),\
                          (*corpos)[k]->get_posicao_y(),
                          (*corpos)[k]->get_tipo()
                        );
    this->add_corpo(c);
  }

}


void ListaDeCorpos::add_corpo(Corpo *c) {
  (this->corpos)->push_back(c);
}

std::vector<Corpo*> *ListaDeCorpos::get_corpos() {
  return (this->corpos);
}

SnakeController::SnakeController(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void SnakeController::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  float new_vel_x, new_vel_y, new_pos_x, new_pos_y;
  for (int i = 0; i < (*c).size(); i++) {
    if((*c)[i]->get_tipo() == SNAKE_HEAD) {
      new_vel_x = (*c)[i]->get_velocidade_x();
      new_vel_y = (*c)[i]->get_velocidade_y();
      new_pos_x = (*c)[i]->get_posicao_x() + (float)deltaT * new_vel_x/5000;
      new_pos_y = (*c)[i]->get_posicao_y() + (float)deltaT * new_vel_y/5000;
    }
    (*c)[i]->update(new_vel_x, new_vel_y, new_pos_x, new_pos_y); //edit: Atualiza os novos parâmetros de aceleracao e forca
  }
}

void SnakeController::andar_para_cima() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  float new_vel_x, new_vel_y, new_pos_x, new_pos_y;
  for (int i = 0; i < (*c).size(); i++) {
    if((*c)[i]->get_tipo() == SNAKE_HEAD) {
      new_vel_x = 0;
      new_vel_y = - 20;
      new_pos_x = (*c)[i]->get_posicao_x();
      new_pos_y = (*c)[i]->get_posicao_y();
    }
    (*c)[i]->update(new_vel_x, new_vel_y, new_pos_x, new_pos_y);
  }
}

void SnakeController::andar_para_baixo() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  float new_vel_x, new_vel_y, new_pos_x, new_pos_y;
  for (int i = 0; i < (*c).size(); i++) {
    if((*c)[i]->get_tipo() == SNAKE_HEAD) {
      new_vel_x = 0;
      new_vel_y = 20;
      new_pos_x = (*c)[i]->get_posicao_x();
      new_pos_y = (*c)[i]->get_posicao_y();
    }
    (*c)[i]->update(new_vel_x, new_vel_y, new_pos_x, new_pos_y);
  }
}

void SnakeController::andar_para_direita() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  float new_vel_x, new_vel_y, new_pos_x, new_pos_y;
  for (int i = 0; i < (*c).size(); i++) {
    if((*c)[i]->get_tipo() == SNAKE_HEAD) {
      new_vel_x = 20;
      new_vel_y = 0;
      new_pos_x = (*c)[i]->get_posicao_x();
      new_pos_y = (*c)[i]->get_posicao_y();
    }
    (*c)[i]->update(new_vel_x, new_vel_y, new_pos_x, new_pos_y);
  }
}

void SnakeController::andar_para_esquerda() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    float new_vel_x, new_vel_y, new_pos_x, new_pos_y;
    if((*c)[i]->get_tipo() == SNAKE_HEAD) {
      new_vel_x = - 20;
      new_vel_y = 0;
      new_pos_x = (*c)[i]->get_posicao_x();
      new_pos_y = (*c)[i]->get_posicao_y();
    }
    (*c)[i]->update(new_vel_x, new_vel_y, new_pos_x, new_pos_y);
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
  int i, j;

  std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();

  // Apaga corpos na tela
  for (int k=0; k<corpos_old->size(); k++)
  {
    i = (int) ((*corpos_old)[k]->get_posicao_x()) * (this->maxI / this->maxX);
    j = (int) ((*corpos_old)[k]->get_posicao_y()) * (this->maxI / this->maxX);
    if(move(j, i) != ERR)   /* Move cursor to position */
      echochar(' ');  /* Prints character, advances a position */
  }

  // Desenha corpos na tela
  std::vector<Corpo *> *corpos = this->lista->get_corpos();

  for (int k=0; k<corpos->size(); k++)
  {
    i = (int) ((*corpos)[k]->get_posicao_x()) * (this->maxI / this->maxX);
    j = (int) ((*corpos)[k]->get_posicao_y()) * (this->maxI / this->maxX);
    if(move(j, i) != ERR) /* Move cursor to position */
      echochar('*');  /* Prints character, advances a position */

    // Atualiza corpos antigos
    (*corpos_old)[k]->update(   (*corpos)[k]->get_velocidade_x(),\
                                (*corpos)[k]->get_velocidade_y(),\
                                (*corpos)[k]->get_posicao_x(),\
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
