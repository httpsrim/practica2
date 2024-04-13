#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

//Devuelve si una ubicación en el mapa es transitable para el agente
bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa){
	return(mapa[x.f][x.c] != 'P' && mapa[x.f][x.c] != 'M');
}
//Devuelve la ubicación siguiente según el valor el avance del agente en el sentido de su avance
ubicacion NextCasilla(const ubicacion &pos){
	ubicacion next = pos;
	switch(pos.brujula){
		case norte:
			next.f = pos.f-1;
			break;
		case noreste:
			next.f = pos.f-1;
			next.c = pos.c+1;
			break;
		case este:
			next.f = pos.c+1;
			break;
		case sureste:
			next.f = pos.f+1;
			next.c = pos.c+1;
			break;
		case sur:
			next.c = pos.c+1;
			break;
		case suroeste:
			next.f = pos.f+1;
			next.c = pos.c-1;
			break;
		case oeste:
			next.f = pos.c-1;
			break;
		case noroeste:
		next.f = pos.f-1;
		next.c = pos.c-1;
			break;
	}
	return next;
}
//Devuelve el estado que se genera si el agente puede avanzar
//Si no se puede avanzar, devuelve como salida el mismo estado de entrada
stateN0 apply(const Action &a,const stateN0 &st, const vector<vector<unsigned char>> mapa){
	stateN0 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch(a){
		case actWALK: //Si la proxima casilla es transitable y NO está ocupada por el colaborador
			sig_ubicacion = NextCasilla(st.jugador);
			if(CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.colaborador.f &&  sig_ubicacion.c == st.colaborador.c)){
				st_result.jugador = sig_ubicacion;
			}
			break;
		case actRUN: //Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
			sig_ubicacion = NextCasilla(st.jugador);
			if(CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
				sig_ubicacion2 = NextCasilla(sig_ubicacion);
				if(CasillaTransitable(sig_ubicacion2,mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
					st_result.jugador = sig_ubicacion2;
				}
			}
			break;
		case actTURN_L:
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+6)%8);
			break;
		case actTURN_SR:
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula+1)%8);
			break;
	}
	return st_result;
}
//Encuentra si el elemento item está en la lista
bool Find(const stateN0 &item, const list<stateN0> &lista){
	auto it = lista.begin();
	while(it != lista.end() && !((*it) == item))
		it++;
	return(!(it == lista.end()));
}

/*ALGORITMOS DE BÚSQUEDA*/

//Primera aproximación a la implementación de la búsqueda en anchura
bool AnchuraSoloJugador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	stateN0 current_state = inicio;
	list<stateN0> frontier;
	list<stateN0> explored;
	frontier.push_back(current_state);
	bool solutionFound = (current_state.jugador.f == final.f && current_state.jugador.c == final.c);
	while(!frontier.empty() && !solutionFound){
		frontier.pop_front();
		explored.push_back(current_state);

		//Generar hijo actWALK
		stateN0 child_walk = apply(actWALK,current_state,mapa);
		if(child_walk.jugador.f == final.f && child_walk.jugador.c == final.c){
			current_state = child_walk;
			solutionFound = true;
		}else if(!Find(child_walk,frontier) && !Find(child_walk,explored)){
			frontier.push_back(child_walk);
		}
		if(!solutionFound){
			//Generar hijo actRUN
			stateN0 child_run = apply(actRUN, current_state,mapa);
			if(child_run.jugador.f == final.f && child_run.jugador.c == final.c){
				current_state = child_run;
				solutionFound = true;
			}else if(!Find(child_run,frontier) && !Find(child_run, explored)){
				frontier.push_back(child_run);
			}
		}
		if(!solutionFound){
			//Generar hijo actTURN_R
			stateN0 child_turnr = apply(actTURN_SR, current_state,mapa);
			if(child_turnr.jugador.f == final.f && child_turnr.jugador.c == final.c){
				current_state = child_turnr;
				solutionFound = true;
			}else if(!Find(child_turnr,frontier) && !Find(child_turnr, explored)){
				frontier.push_back(child_turnr);
			}
		}
		if(!solutionFound){
			//Generar hijo actTURN_R
			stateN0 child_turnr = apply(actTURN_SR, current_state,mapa);
			if(child_turnr.jugador.f == final.f && child_turnr.jugador.c == final.c){
				current_state = child_turnr;
				solutionFound = true;
			}else if(!Find(child_turnr,frontier) && !Find(child_turnr, explored)){
				frontier.push_back(child_turnr);
			}
		}
		if(!solutionFound){
			stateN0 child_turnl = apply(actTURN_L, current_state,mapa);
			if(child_turnl.jugador.f == final.f && child_turnl.jugador.c == final.c){
				current_state = child_turnl;
				solutionFound = true;
			}else if(!Find(child_turnl,frontier) && !Find(child_turnl, explored)){
				frontier.push_back(child_turnl);
			}
		}
		if(!solutionFound && !frontier.empty())
			current_state = frontier.front();
	}
	return solutionFound;
}

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores){
	Action accion = actIDLE;

	if(!hayPlan){
		//invocar método de búsqueda
		cout << "Calculando un nuevo plan\n";
	//	plan = AvanzaASaltosDeCaballo();
		hayPlan = true;
	}
	if(hayPlan && plan.size()>0){
		accion = plan.front();
		plan.pop_front();
	}
	if(plan.size() == 0){
		hayPlan = false;
	}
	return accion;
}


int ComportamientoJugador::interact(Action accion, int valor){
	return false;
}
