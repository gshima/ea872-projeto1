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

Corpo::Corpo(float massa, float velocidade, float posicao, float aceleracao, float forca, float k, float b) {
  this->massa = massa;
  this->velocidade = velocidade;
  this->posicao = posicao;
  this->aceleracao = aceleracao; //edit: novo atributo aceleracao
  this->forca = forca;//edit: novo atributo forca
  this->k = k; //edit: novo atributo k: constante da mola
  this->b = b; //edit: novo atributo b: constante de amortecimento

}

void Corpo::update(float nova_velocidade, float nova_posicao, float nova_aceleracao, float nova_forca) { //edit: Add novos parametros de aceleracao e forca
  this->velocidade = nova_velocidade;
  this->posicao = nova_posicao;
  this->aceleracao = nova_aceleracao; //edit: novo atributo aceleracao
  this->forca = nova_forca; //edit: novo atributo forca
}

float Corpo::get_massa() {
  return this->massa;
}

float Corpo::get_velocidade() {
  return this->velocidade;
}

float Corpo::get_posicao() {
  return this->posicao;
}

float Corpo::get_aceleracao() { //edit: Add método de get para novo parametro aceleracao
  return this->aceleracao;
}

float Corpo::get_forca() { //edit: Add método de get para novo parametro forca
  return this->forca;
}
float Corpo::get_k() { //edit: Add método de get para novo parametro k: constante da mola
  return this->k;
}

float Corpo::get_b() { //edit: Add método de get para novo parametro b: constante de amortecimento
  return this->b;
}

ListaDeCorpos::ListaDeCorpos() {
  this->corpos = new std::vector<Corpo *>(0);
}

void ListaDeCorpos::hard_copy(ListaDeCorpos *ldc) {
  std::vector<Corpo *> *corpos = ldc->get_corpos();

  for (int k=0; k<corpos->size(); k++) {
    Corpo *c = new Corpo( (*corpos)[k]->get_massa(),\
                          (*corpos)[k]->get_posicao(),\
                          (*corpos)[k]->get_velocidade(),\
                          (*corpos)[k]->get_aceleracao(),\
                          (*corpos)[k]->get_forca(),\
                          (*corpos)[k]->get_k(),\
                          (*corpos)[k]->get_b()
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

Fisica::Fisica(ListaDeCorpos *ldc) {
  this->lista = ldc;
}

void Fisica::update(float deltaT) {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();

  for (int i = 0; i < (*c).size(); i++) {

    float k_corpo = (*c)[i]->get_k(); //edit: Add constante da mola N/m
    float b_corpo = (*c)[i]->get_b(); //edit: Add coeficiente de amortecimento

    float new_aceleracao = (- b_corpo*(*c)[i]->get_velocidade() - k_corpo*(*c)[i]->get_posicao() ) / (*c)[i]->get_massa();//edit: Add Calcula aceleracao a partir do modelo a=(-b*v-k*x)/m
    float new_vel = (*c)[i]->get_velocidade() + (float)deltaT * (new_aceleracao)/1000; //edit: Trocamos a gravidade = - 10 por aceleracao calculada
    float new_pos = (*c)[i]->get_posicao() + (float)deltaT * new_vel/1000;
    float new_forca = (*c)[i]->get_aceleracao() * (*c)[i]->get_massa(); //edit: Add Calcula a forca
    (*c)[i]->update(new_vel, new_pos, new_aceleracao, new_forca); //edit: Atualiza os novos parâmetros de aceleracao e forca
  }
}

void Fisica::choque() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    float new_vel = (*c)[i]->get_velocidade() + 15;
    float new_pos = (*c)[i]->get_posicao();
    float new_acel = (*c)[i]->get_aceleracao();
    float new_forca = (*c)[i]->get_forca();
    (*c)[i]->update(new_vel, new_pos, new_acel, new_forca);
  }
}

void Fisica::choque_contrario() {
  // Atualiza parametros dos corpos!
  std::vector<Corpo *> *c = this->lista->get_corpos();
  for (int i = 0; i < (*c).size(); i++) {
    float new_vel = (*c)[i]->get_velocidade()-15;
    float new_pos = (*c)[i]->get_posicao();
    float new_acel = (*c)[i]->get_aceleracao();
    float new_forca = (*c)[i]->get_forca();
    (*c)[i]->update(new_vel, new_pos, new_acel, new_forca);
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
  int i;

  std::vector<Corpo *> *corpos_old = this->lista_anterior->get_corpos();

  // Apaga corpos na tela
  for (int k=0; k<corpos_old->size(); k++)
  {
    i = (int) ((*corpos_old)[k]->get_posicao()) * \
        (this->maxI / this->maxX);
    if(move(i+10, k) != ERR)   /* Move cursor to position */
      echochar(' ');  /* Prints character, advances a position */
  }

  // Desenha corpos na tela
  std::vector<Corpo *> *corpos = this->lista->get_corpos();

  for (int k=0; k<corpos->size(); k++)
  {
    i = (int) ((*corpos)[k]->get_posicao()) * \
        (this->maxI / this->maxX);
    if(move(i+10,k) != ERR) /* Move cursor to position */
      echochar('*');  /* Prints character, advances a position */

    // Atualiza corpos antigos
    (*corpos_old)[k]->update(  (*corpos)[k]->get_velocidade(),\
                               (*corpos)[k]->get_posicao(),\
                               (*corpos)[k]->get_aceleracao(),\
                               (*corpos)[k]->get_forca()
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
