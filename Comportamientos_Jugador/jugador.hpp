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

//estado para nivel 2
struct stateN2{
  ubicacion jugador;
  ubicacion colaborador;
  int coste = 0;    //coste de llegar a este nodo
  int costeTotal;
  bool bikini = false;
  bool zapas = false;
  Action ultimaOrdenColaborador;  //almacena la ultima orden que el jugador le dio al colaborador.
  bool operator == (const stateN2 &x) const{
    return(jugador.f == x.jugador.f && jugador.c == x.jugador.c && jugador.brujula == x.jugador.brujula);
  }
};

//Tipo de nodo para nivel 2
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

//estado para nivel 2
struct stateN3{
  ubicacion jugador;
  ubicacion colaborador;
  int heuristica = 0;
  int coste = 0;
  bool colaboradorVisto = false;
  bool bikiniJ = false;
  bool zapasJ = false;
  bool bikiniC = false;
  bool zapasC = false;
  Action ultimaOrdenColaborador;  //almacena la ultima orden que el jugador le dio al colaborador.
  bool operator == (const stateN3 &x) const{
    return(jugador.f == x.jugador.f && jugador.c == x.jugador.c && jugador.brujula == x.jugador.brujula && colaborador.f == x.colaborador.f && colaborador.c == x.colaborador.c && colaborador.brujula == x.colaborador.brujula);
  }
};

//Tipo de nodo para nivel 2
struct nodeN3{
  stateN3 st;
  list<Action> secuencia;
  bool operator==(const nodeN3 &n) const{
    return (st == n.st);
  }
  bool operator <(const nodeN3 &n) const{
    return(st.heuristica > n.st.heuristica);
  }
};

struct nodeN3comparar{
  bool operator()(const nodeN3 &a,const nodeN3 &b)const{
    if(a.st.jugador.f < b.st.jugador.f)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c < b.st.jugador.c)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula <  b.st.jugador.brujula)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ < b.st.zapasJ)
      return true;
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ == b.st.zapasJ && a.st.bikiniJ < b.st.bikiniJ)
      return true; 
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ == b.st.zapasJ && a.st.bikiniJ == b.st.bikiniJ && a.st.colaborador.f < b.st.colaborador.f)
      return true; 
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ == b.st.zapasJ && a.st.bikiniJ == b.st.bikiniJ && a.st.colaborador.f == b.st.colaborador.f &&  a.st.colaborador.c < b.st.colaborador.c)
      return true; 
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ == b.st.zapasJ && a.st.bikiniJ == b.st.bikiniJ && a.st.colaborador.f == b.st.colaborador.f &&  a.st.colaborador.c == b.st.colaborador.c && a.st.colaborador.brujula < b.st.colaborador.brujula)
      return true;   
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ == b.st.zapasJ && a.st.bikiniJ == b.st.bikiniJ && a.st.colaborador.f == b.st.colaborador.f &&  a.st.colaborador.c == b.st.colaborador.c && a.st.colaborador.brujula == b.st.colaborador.brujula && a.st.bikiniC < b.st.bikiniC)
      return true;   
    else if(a.st.jugador.f == b.st.jugador.f && a.st.jugador.c == b.st.jugador.c && a.st.jugador.brujula == b.st.jugador.brujula && a.st.zapasJ == b.st.zapasJ && a.st.bikiniJ == b.st.bikiniJ && a.st.colaborador.f == b.st.colaborador.f &&  a.st.colaborador.c == b.st.colaborador.c && a.st.colaborador.brujula == b.st.colaborador.brujula && a.st.bikiniC == b.st.bikiniC && a.st.zapasC < b.st.zapasC)
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
    void VisualizarPlanN3(const stateN3 &st, const list<Action> &plan);
    Action think(Sensores sensores);
    int interact(Action accion, int valor);


  private:
    // Declarar Variables de Estado
    list<Action> plan; //Almacena el plan ejecucción
    bool hayPlan;      // Si verdad indica que se está siguiendo un plan
    stateN0 c_stateN0;
    stateN1 c_stateN1;
    stateN2 c_stateN2;
    stateN3 c_stateN3;
    ubicacion goal;

};

#endif
