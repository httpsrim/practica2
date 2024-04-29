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
    return(jugador.f == x.jugador.f && jugador.c == x.jugador.c && jugador.brujula == x.jugador.brujula);
  }
};
//Redefinición del tipo nodo del nivel 0
struct nodeN0{
  stateN0 st;
  list<Action> secuencia;
  bool operator == (const nodeN0 &n) const{
    return (st == n.st);
  }
  bool operator<(const nodeN0 &b)const{
    if(st.jugador.f < b.st.jugador.f) return true;
    else if(st.jugador.f == b.st.jugador.f && st.jugador.c < b.st.jugador.c)
      return true;
    else if(st.jugador.f == b.st.jugador.f && st.jugador.c == b.st.jugador.c && st.jugador.brujula <  b.st.jugador.brujula)
      return true;
    else 
      return false;
  }
};

//Struct para nivel 1
struct stateN1{
  ubicacion jugador;
  ubicacion colaborador;
  bool colaboradorVisto;
  Action ultimaOrdenColaborador;  //almacena la ultima orden que el jugador le dio al colaborador.
  bool operator == (const stateN1 &x) const{
    return(jugador.f == x.jugador.f && jugador.c == x.jugador.c && jugador.brujula == x.jugador.brujula && colaborador.f == x.colaborador.f && colaborador.c == x.colaborador.c && colaborador.brujula == x.colaborador.brujula);
  }
};

//Tipo de nodo para nivel 1
struct nodeN1{
  stateN1 st;
  list<Action> secuencia;
  bool operator==(const nodeN1 &n) const{
    return (st == n.st);
  }
  bool operator <(const nodeN1 &n) const{
    if(st.jugador.f < n.st.jugador.f)
      return true;
    else if(st.jugador.f == n.st.jugador.f && st.jugador.c < n.st.jugador.c)
      return true;
    else if(st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula <  n.st.jugador.brujula)
      return true;
    else if(st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f < n.st.colaborador.f)
      return true;
    else if(st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f == n.st.colaborador.f && st.colaborador.c < n.st.colaborador.c)
      return true;
    else if(st.jugador.f == n.st.jugador.f && st.jugador.c == n.st.jugador.c && st.jugador.brujula == n.st.jugador.brujula && st.colaborador.f == n.st.colaborador.f && st.colaborador.c == n.st.colaborador.c && st.colaborador.brujula < n.st.colaborador.brujula)
      return true;
    else
      return false;
  }
};

//Struct para nivel 2
struct stateN2{
  ubicacion jugador;
  ubicacion colaborador;
  int coste;    //coste de llegar a este nodo
  bool bikini;
  bool zapas;
  Action ultimaOrdenColaborador;  //almacena la ultima orden que el jugador le dio al colaborador.
  bool operator == (const stateN2 &x) const{
    return(jugador.f == x.jugador.f && jugador.c == x.jugador.c && jugador.brujula == x.jugador.brujula && colaborador.f == x.colaborador.f && colaborador.c == x.colaborador.c && colaborador.brujula == x.colaborador.brujula);
  }
};

//Tipo de nodo para nivel 1
struct nodeN2{
  stateN2 st;
  list<Action> secuencia;
  bool operator==(const nodeN2 &n) const{
    return (st == n.st);
  }
  bool operator <(const nodeN2 &n) const{
    return(st.coste > n.st.coste);
  }
};

struct nodeN2comparar{
  bool operator()(const nodeN2 &a,const nodeN2 &b)const{
    if(a.st.jugador.f < b.st.jugador.f)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c < b.st.jugador.c)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula <  b.st.jugador.brujula)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapas < b.st.zapas)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapas == b.st.zapas && a.st.bikini < b.st.bikini)
      return true; 
    else
      return false;
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

    void VisualizarPlanN0(const stateN0 &st, const list<Action> &plan);
    void VisualizarPlanN1(const stateN1 &st, const list<Action> &plan);
    void VisualizarPlanN2(const stateN2 &st, const list<Action> &plan);

    Action think(Sensores sensores);
    int interact(Action accion, int valor);


  private:
    // Declarar Variables de Estado
    list<Action> plan; //Almacena el plan ejecucción
    bool hayPlan;      // Si verdad indica que se está siguiendo un plan
    stateN0 c_stateN0;
    stateN1 c_stateN1;
    stateN2 c_stateN2;
    ubicacion goal;

};

#endif
