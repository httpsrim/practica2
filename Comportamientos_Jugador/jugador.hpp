#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

/*
Para nivel 4 se puede usar el algoritmo del nv 2.
*/

struct stateN0{
  ubicacion jugador;
  ubicacion colaborador;
  Action ultimaOrdenColaborador;  //almacena la ultima orden que el jugador le dio al colaborador.
  bool operator == (const stateN0 &x) const{
    if(jugador == x.jugador && colaborador.f == x.colaborador.f && colaborador.c == x.colaborador.c){
      return true;
    }else{
      return false;
    }
  }
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado de nivel 4
    }
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado resto de niveles
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);


  private:
    // Declarar Variables de Estado
    list<Action> plan; //Almacena el plan ejecucción
    bool hayPlan;      // Si verdad indica que se está siguiendo un plan





};

#endif
