#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

//¿Veo el colaborador?
bool verColaborador(const stateN0 &st){
	bool visto = false;
	switch(st.jugador.brujula){
		case norte:
			if(st.colaborador.f < st.jugador.f-3){
				return false;
			}else{
				if(st.colaborador.c <= st.jugador.c+3 && st.colaborador.c > st.jugador.c-3){
					return true;
				}
				else{
					return false;
				}
			}
			break;
		case sur:
			if(st.colaborador.f > st.jugador.f+3){
				return false;
			}else{
				if(st.colaborador.c <= st.jugador.c+3 && st.colaborador.c >= st.jugador.c-3){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
		case este:
			if(st.colaborador.c > st.jugador.c-3){
				return false;
			}else{
				if(st.colaborador.f <= st.jugador.f+3 && st.colaborador.f >= st.jugador.f-3){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
		case oeste:
			if(st.colaborador.c > st.jugador.c+3){
				return false;
			}else{
				if(st.colaborador.f <= st.jugador.f + 3 && st.colaborador.f >= st.jugador.f-3){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
		case noreste:
			if(st.colaborador.c > st.jugador.c+3){
				return false;
			}else{
				if(st.colaborador.f >= st.jugador.f-3 && st.colaborador.f <= st.jugador.f){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
		case noroeste:
			if(st.colaborador.c > st.jugador.c+3){
				return false;
			}else{
				if(st.colaborador.f >= st.jugador.f-3 && st.colaborador.f <= st.jugador.f){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
		case sureste:
			if(st.colaborador.f > st.jugador.f+3){
				return false;
			}else{
				if(st.colaborador.c <= st.jugador.c+3 && st.colaborador.c >= st.jugador.c){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
		case suroeste:
			if(st.colaborador.f > st.jugador.f+3){
				return false;
			}else{
				if(st.colaborador.c >= st.jugador.c-3 && st.colaborador.c <= st.jugador.c){
					return true;
				}
				else{
					return false;
				}
			}	
			break;
	}
	//if(visto == true){
	//	cout << "visto\n";
	//}
	return visto;
}
// Pone a cero toos los elementos de una matriz
void AnularMatriz(vector<vector<unsigned char>> &matriz)
{
	for (int i = 0; i < matriz.size(); i++)
	{
		for (int j = 0; j < matriz[0].size(); j++)
		{
			matriz[i][j] = 0;
		}
	}
}

// Devuelve si una ubicación en el mapa es transitable para el agente
bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa)
{
	return (mapa[x.f][x.c] != 'P' && mapa[x.f][x.c] != 'M');
}

// Devuelve la ubicación siguiente según el valor el avance del agente en el sentido de su avance
ubicacion NextCasilla(const ubicacion &pos)
{
	ubicacion next = pos;
	switch (pos.brujula){
	case norte:
		next.f = pos.f - 1;
		break;
	case noreste:
		next.f = pos.f - 1;
		next.c = pos.c + 1;
		break;
	case este:
		next.c = pos.c + 1;
		break;
	case sureste:
		next.f = pos.f + 1;
		next.c = pos.c + 1;
		break;
	case sur:
		next.f = pos.f + 1;
		break;
	case suroeste:
		next.f = pos.f + 1;
		next.c = pos.c - 1;
		break;
	case oeste:
		next.c = pos.c - 1;
		break;
	case noroeste:
		next.f = pos.f - 1;
		next.c = pos.c - 1;
		break;
	}
	return next;
}
// Devuelve el estado que se genera si el agente puede avanzar
// Si no se puede avanzar, devuelve como salida el mismo estado de entrada
stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> mapa,int nivel){
	stateN0 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch (a){
	case actWALK: // Si la proxima casilla es transitable y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			st_result.jugador = sig_ubicacion;
			if(nivel == 1){
				st_result.colaboradorVisto = verColaborador(st_result);
			}
			//cout << "st_result: " << st_result.colaboradorVisto << endl;
		}
		break;
	case actRUN: // Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			sig_ubicacion2 = NextCasilla(sig_ubicacion);
			if (CasillaTransitable(sig_ubicacion2, mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
				st_result.jugador = sig_ubicacion2;
				if(nivel == 1) st_result.colaboradorVisto = verColaborador(st_result);
			}
		}
		break;
	case actTURN_L:
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
		if(nivel == 1) st_result.colaboradorVisto = verColaborador(st_result);
		break;
	case actTURN_SR:
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 1) % 8);
		if(nivel == 1) st_result.colaboradorVisto = verColaborador(st_result);
		break;

	case act_CLB_WALK:
		sig_ubicacion = NextCasilla(st.colaborador);
		if(CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.jugador.f && sig_ubicacion.c == st.jugador.c)){
			st_result.jugador = sig_ubicacion;
		}
		break;
	case act_CLB_TURN_SR:
		st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula + 1) % 8);
		break;
	}
	return st_result;
}
// Encuentra si el elemento item está en la lista
bool Find(const stateN0 &item, const list<stateN0> &lista){
	auto it = lista.begin();
	while (it != lista.end() && !((*it) == item))
		it++;
	return (!(it == lista.end()));
}
// Sobrecarga de la función Find para buscar en lista de nodeN0
bool Find(const stateN0 &item, const list<nodeN0> &lista){
	auto it = lista.begin();
	while (it != lista.end() && !(it->st == item))
		it++;
	return (!(it == lista.end()));
}

// Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st
void ComportamientoJugador::VisualizarPlan(const stateN0 &st, const list<Action> &plan){
	AnularMatriz(mapaConPlan);
	stateN0 cst = st;

	auto it = plan.begin();
	while (it != plan.end()){
		if ((*it != act_CLB_WALK) and (*it != act_CLB_TURN_SR) and (*it != act_CLB_STOP)){
			switch (cst.ultimaOrdenColaborador){
			case act_CLB_WALK:
				cst.colaborador = NextCasilla(cst.colaborador);
				mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
				break;
			case act_CLB_TURN_SR:
				cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula + 1) % 8);
				break;
			}
		}
		
		switch (*it){
		case actRUN:
			cst.jugador = NextCasilla(cst.jugador);
			mapaConPlan[cst.jugador.f][cst.jugador.c] = 3;
			cst.jugador = NextCasilla(cst.jugador);
			mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
			break;
		case actWALK:
			cst.jugador = NextCasilla(cst.jugador);
			mapaConPlan[cst.jugador.f][cst.jugador.c] = 1;
			break;
		case actTURN_SR:
			cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 1) % 8);
			break;
		case actTURN_L:
			cst.jugador.brujula = (Orientacion)((cst.jugador.brujula + 6) % 8);
			break;
		case act_CLB_WALK:
			cst.colaborador = NextCasilla(cst.colaborador);
			cst.ultimaOrdenColaborador = act_CLB_WALK;
			mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
			break;
		case act_CLB_TURN_SR:
			cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula + 1) % 8);
			cst.ultimaOrdenColaborador = act_CLB_TURN_SR;
			break;
		case act_CLB_STOP:
			cst.ultimaOrdenColaborador = act_CLB_STOP;
			break;
		}
		it++;
	}
}

// Pinta plan
void PintaPlan(const list<Action> &plan){
	auto it = plan.begin();
	while (it != plan.end()){
		if (*it == actWALK)
			cout << "W ";
		else if (*it == actRUN)
			cout << "R ";
		else if (*it == actTURN_SR)
			cout << "r ";
		else if (*it == actTURN_L)
			cout << "L ";
		else if (*it == act_CLB_WALK)
			cout << "cW ";
		else if (*it == act_CLB_TURN_SR)
			cout << "cr ";
		else if (*it == act_CLB_STOP)
			cout << "cS ";
		else if (*it == actIDLE)
			cout << "I ";
		else
			cout << "-_ ";
		it++;
	}
	cout << " (" << plan.size() << " acciones)\n";
}
/*ALGORITMOS DE BÚSQUEDA*/

// Tercera version busqueda en anchura, revuelve plan
list<Action> AnchuraSoloJugador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	nodeN0 current_node;
	list<nodeN0> frontier;
	set<nodeN0> explored;
	list<Action> plan;
	current_node.st = inicio;
	
	bool solutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);
	
	frontier.push_back(current_node);
	
	while (!frontier.empty() && !solutionFound){
		frontier.pop_front();
		explored.insert(current_node);

		// Generar hijo actWALK
		nodeN0 child_walk = current_node;
		child_walk.st = apply(actWALK, current_node.st, mapa,0);
		child_walk.secuencia.push_back(actWALK);

		if (child_walk.st.jugador.f == final.f && child_walk.st.jugador.c == final.c){
			current_node = child_walk;
			solutionFound = true;
		}
		else if (explored.find(child_walk) == explored.end()){
			frontier.push_back(child_walk);
		}
	
		if (!solutionFound){
			nodeN0 child_run = current_node;
			child_run.st = apply(actRUN, current_node.st, mapa,0);
			child_run.secuencia.push_back(actRUN);

			if (child_run.st.jugador.f == final.f && child_run.st.jugador.c == final.c){
				current_node = child_run;
				solutionFound = true;
			}
			else if (explored.find(child_run) == explored.end()){
				frontier.push_back(child_run);
			}
		}
		if (!solutionFound){
			// Generar hijo actTURN_L
			nodeN0 child_turnl = current_node;
			child_turnl.st = apply(actTURN_L, current_node.st, mapa,0);
			child_turnl.secuencia.push_back(actTURN_L);
			if (explored.find(child_turnl) == explored.end()){
				frontier.push_back(child_turnl);
			}

			//Genera hijo actTURN_SR
			nodeN0 child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR, current_node.st, mapa,0);
			child_turnsr.secuencia.push_back(actTURN_SR);
			if (explored.find(child_turnsr) == explored.end()){
				frontier.push_back(child_turnsr);
			}
		}
		if (!solutionFound && !frontier.empty()){
			current_node = frontier.front();
			while(!frontier.empty() && explored.find(current_node) != explored.end()){
				frontier.pop_front();
				if(!frontier.empty())
					current_node = frontier.front();
			}
		}
	}
	
	if (solutionFound)
	{
		plan = current_node.secuencia;
		cout << "Encontrado plan: ";
		PintaPlan(current_node.secuencia);
	}
	return plan;
}

void pintaEtadoN1(nodeN1 &st){
	cout << "(" << st.st.jugador.f << ", " << st.st.jugador.c << ", " << st.st.jugador.brujula << ")" << endl;
	cout << "(" << st.st.colaborador.f << ", " << st.st.colaborador.c << ", " << st.st.colaborador.brujula << ", " << st.st.ultimaOrdenColaborador << ")" << endl; 
}

//Busqueda en anchura con colaborador, Nivel 1
list<Action> AnchuraSoloColaborador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	nodeN1 current_node;
	list<nodeN1>frontier;
	set<nodeN1> explored;
	list<Action> plan;
	current_node.st = inicio;
	bool solutionFound = (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c);
	bool veoColaborador = verColaborador(current_node.st);
	frontier.push_back(current_node);
	
	
	while(!frontier.empty() && !solutionFound){
		frontier.pop_front();
		explored.insert(current_node);
		veoColaborador = verColaborador(current_node.st);
		
		cout << "tamaño frontier: " << frontier.size() << "\t tamaño explored: " << explored.size() << endl;
		PintaPlan(current_node.secuencia);
		pintaEtadoN1(current_node);

		if(veoColaborador){
			cout << "entro colaborador\n";
			//hijo act_CLB_walk
			nodeN1 child_clbwalk = current_node;
			child_clbwalk.st = apply(act_CLB_WALK,current_node.st,mapa,1);
			
			if(child_clbwalk.st.colaborador.f == final.f && child_clbwalk.st.colaborador.c == final.c){
				child_clbwalk.secuencia.push_back(act_CLB_WALK);
				current_node = child_clbwalk;
				solutionFound = true;
			}
			else if(explored.find(child_clbwalk) == explored.end()){
				child_clbwalk.secuencia.push_back(act_CLB_WALK);
				child_clbwalk.st.ultimaOrdenColaborador = act_CLB_WALK;
				frontier.push_back(child_clbwalk);
			}
			//el que se pare.
			if(!solutionFound){
				//hijo act_CLB_turn_SR
				nodeN1 child_clbturnsr = current_node;
				child_clbturnsr.st = apply(act_CLB_TURN_SR,current_node.st,mapa,1);
				if(explored.find(child_clbturnsr) == explored.end()){
					child_clbturnsr.secuencia.push_back(act_CLB_TURN_SR);
					child_clbturnsr.st.ultimaOrdenColaborador = act_CLB_TURN_SR;
					frontier.push_back(child_clbturnsr);
				}
				nodeN1 child_clbstop = current_node;
				child_clbstop.st = apply(act_CLB_STOP,current_node.st,mapa,1);
				if(explored.find(child_clbstop) == explored.end()){
					child_clbstop.secuencia.push_back(act_CLB_STOP);
					child_clbstop.st.ultimaOrdenColaborador = act_CLB_STOP;
					frontier.push_back(child_clbstop);
				}
			}
		}
		//genero estado intermedio
		if(current_node.st.ultimaOrdenColaborador == act_CLB_WALK){
			nodeN1 modificacion = current_node;
			modificacion.st = apply(act_CLB_WALK,current_node.st,mapa,1);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		else if(current_node.st.ultimaOrdenColaborador == act_CLB_TURN_SR){
			nodeN1 modificacion = current_node;
			modificacion.st = apply(act_CLB_TURN_SR,current_node.st,mapa,1);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		else if(current_node.st.ultimaOrdenColaborador == act_CLB_STOP){
			nodeN1 modificacion = current_node;
			modificacion.st = apply(act_CLB_STOP,current_node.st,mapa,1);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		
		//hijo actWALK
		nodeN1 child_walk = current_node;
		child_walk.st = apply(actWALK,current_node.st,mapa,1);

		if(explored.find(child_walk) == explored.end()){
			child_walk.secuencia.push_back(actWALK);
			frontier.push_back(child_walk);
		}
		if(!child_walk.st.colaboradorVisto){
			//hijo actRUN
			nodeN1 child_run = current_node;
			child_run.st = apply(actRUN,current_node.st,mapa,1);
			 if(explored.find(child_run) == explored.end()){
				child_run.secuencia.push_back(actRUN);
				frontier.push_back(child_run);
			}
		}
		if(!child_walk.st.colaboradorVisto){
			//hijo actTURN_L
			nodeN1 child_turnl = current_node;
			child_turnl.st = apply(actTURN_L,current_node.st,mapa,1);
			if(explored.find(child_turnl) == explored.end()){
				child_turnl.secuencia.push_back(actTURN_L);
				frontier.push_back(child_turnl);
			}
			//hijo actTURN_SR
			nodeN1 child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR,current_node.st,mapa,1);
			if(explored.find(child_turnsr) == explored.end()){
				child_turnsr.secuencia.push_back(actTURN_SR);
				frontier.push_back(child_turnsr);
			}
			//hijo actIDLE
			nodeN1 child_idle = current_node;
			child_idle.st = apply(actIDLE,current_node.st,mapa,1);
			if(explored.find(child_idle) == explored.end()){
				child_idle.secuencia.push_back(actIDLE);
				frontier.push_back(child_idle);
			}
		}
	
		if(!solutionFound && !frontier.empty()){
			current_node = frontier.front();
			while(!frontier.empty() && explored.find(current_node) != explored.end()){
				frontier.pop_front();
				if(!frontier.empty())
					current_node = frontier.front();
			}
		}
	}
	if (solutionFound){
		plan = current_node.secuencia;
		cout << "Encontrado plan: ";
		PintaPlan(current_node.secuencia);
	}
	return plan;
}

// Este es el método principal que se piden en la practica.
// Tiene como entrada la información de los sensores y devuelve la acción a realizar.
// Para ver los distintos sensores mirar fichero "comportamiento.hpp"
Action ComportamientoJugador::think(Sensores sensores)
{
	Action accion = actIDLE;
	if (sensores.nivel != 4)
	{
		if (!hayPlan)
		{
			cout << "Calculando un nuevo plan\n";
			c_state.jugador.f = sensores.posF;
			c_state.jugador.c = sensores.posC;
			c_state.jugador.brujula = sensores.sentido;

			c_state.colaborador.f = sensores.CLBposF;
			c_state.colaborador.c = sensores.CLBposC;
			c_state.colaborador.brujula = sensores.CLBsentido;
			c_state.colaboradorVisto = false;

			goal.f = sensores.destinoF;
			goal.c = sensores.destinoC;
			switch (sensores.nivel)
			{
			case 0:
				plan = AnchuraSoloJugador(c_state, goal, mapaResultado);
				if (plan.size() > 0){
					hayPlan = true;
					VisualizarPlan(c_state, plan);
				}
				break;
			case 1:
				//c_state.colaboradorVisto = verColaborador(c_state);
				plan = AnchuraSoloColaborador(c_state, goal, mapaResultado);
				if (plan.size() > 0){
					hayPlan = true;
					VisualizarPlan(c_state, plan);
				}
				break;
			case 2:
				cout << "Pendiente de implementacion\n";
				break;
			case 3:
				cout << "Pendiente de implementacion\n";
				break;
			}
		}
		if (hayPlan && plan.size() > 0)
		{
			accion = plan.front();
			plan.pop_front();
			//cout << "acción: " << accion << endl;
		}
		if (plan.size() == 0)
		{
			cout << "Se completo el plan\n";
			hayPlan = false;
		}
	}
	else
	{
		// nivel 4
	}
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}
