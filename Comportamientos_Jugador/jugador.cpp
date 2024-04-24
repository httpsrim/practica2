#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>

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
	switch (pos.brujula)
	{
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
		next.f = pos.c - 1;
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
stateN0 apply(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> mapa)
{
	stateN0 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch (a)
	{
	case actWALK: // Si la proxima casilla es transitable y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c))
		{
			st_result.jugador = sig_ubicacion;
		}
		break;
	case actRUN: // Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c))
		{
			sig_ubicacion2 = NextCasilla(sig_ubicacion);
			if (CasillaTransitable(sig_ubicacion2, mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c))
			{
				st_result.jugador = sig_ubicacion2;
			}
		}
		break;
	case actTURN_L:
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
		break;
	case actTURN_SR:
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 1) % 8);
		break;
	}
	return st_result;
}
// Encuentra si el elemento item está en la lista
bool Find(const stateN0 &item, const list<stateN0> &lista)
{
	auto it = lista.begin();
	while (it != lista.end() && !((*it) == item))
		it++;
	return (!(it == lista.end()));
}
// Sobrecarga de la función Find para buscar en lista de nodeN0
bool Find(const stateN0 &item, const list<nodeN0> &lista)
{
	auto it = lista.begin();
	while (it != lista.end() && !(it->st == item))
		it++;
	return (!(it == lista.end()));
}







// Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st
void ComportamientoJugador::VisualizarPlan(const stateN0 &st, const list<Action> &plan)
{
	AnularMatriz(mapaConPlan);
	stateN0 cst = st;

	auto it = plan.begin();
	while (it != plan.end())
	{
		if ((*it != act_CLB_WALK) and (*it != act_CLB_TURN_SR) and (*it != act_CLB_STOP))
		{
			switch (cst.ultimaOrdenColaborador)
			{
			case act_CLB_WALK:
				cst.colaborador = NextCasilla(cst.colaborador);
				mapaConPlan[cst.colaborador.f][cst.colaborador.c] = 2;
				break;
			case act_CLB_TURN_SR:
				cst.colaborador.brujula = (Orientacion)((cst.colaborador.brujula + 1) % 8);
				break;
			}
		}
		
		switch (*it)
		{
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
void PintaPlan(const list<Action> &plan)
{
	auto it = plan.begin();
	while (it != plan.end())
	{
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

// Primera aproximación a la implementación de la búsqueda en anchura
bool AnchuraSoloJugador(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
	stateN0 current_state = inicio;
	list<stateN0> frontier;
	list<stateN0> explored;
	frontier.push_back(current_state);
	bool solutionFound = (current_state.jugador.f == final.f && current_state.jugador.c == final.c);
	while (!frontier.empty() && !solutionFound)
	{
		frontier.pop_front();
		explored.push_back(current_state);

		// Generar hijo actWALK
		stateN0 child_walk = apply(actWALK, current_state, mapa);
		if (child_walk.jugador.f == final.f && child_walk.jugador.c == final.c)
		{
			current_state = child_walk;
			solutionFound = true;
		}
		else if (!Find(child_walk, frontier) && !Find(child_walk, explored))
		{
			frontier.push_back(child_walk);
		}
		if (!solutionFound)
		{
			// Generar hijo actRUN
			stateN0 child_run = apply(actRUN, current_state, mapa);
			if (child_run.jugador.f == final.f && child_run.jugador.c == final.c)
			{
				current_state = child_run;
				solutionFound = true;
			}
			else if (!Find(child_run, frontier) && !Find(child_run, explored))
			{
				frontier.push_back(child_run);
			}
		}
		if (!solutionFound)
		{
			// Generar hijo actTURN_R
			stateN0 child_turnr = apply(actTURN_SR, current_state, mapa);
			if (child_turnr.jugador.f == final.f && child_turnr.jugador.c == final.c)
			{
				current_state = child_turnr;
				solutionFound = true;
			}
			else if (!Find(child_turnr, frontier) && !Find(child_turnr, explored))
			{
				frontier.push_back(child_turnr);
			}
		}
		if (!solutionFound)
		{
			// Generar hijo actTURN_R
			stateN0 child_turnr = apply(actTURN_SR, current_state, mapa);
			if (child_turnr.jugador.f == final.f && child_turnr.jugador.c == final.c)
			{
				current_state = child_turnr;
				solutionFound = true;
			}
			else if (!Find(child_turnr, frontier) && !Find(child_turnr, explored))
			{
				frontier.push_back(child_turnr);
			}
		}
		if (!solutionFound)
		{
			stateN0 child_turnl = apply(actTURN_L, current_state, mapa);
			if (child_turnl.jugador.f == final.f && child_turnl.jugador.c == final.c)
			{
				current_state = child_turnl;
				solutionFound = true;
			}
			else if (!Find(child_turnl, frontier) && !Find(child_turnl, explored))
			{
				frontier.push_back(child_turnl);
			}
		}
		if (!solutionFound && !frontier.empty())
			current_state = frontier.front();
	}
	return solutionFound;
}

void PintaEstado(const ubicacion &p){
	cout << "(" << p.f << "," << p.c << "," << p.brujula <<")\n";
}


// Segunda version busqueda en anchura, revuelve plan
list<Action> AnchuraSoloJugador_V2(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
	nodeN0 current_node;
	list<nodeN0> frontier;
	list<nodeN0> explored;
	list<Action> plan;
	current_node.st = inicio;
	frontier.push_back(current_node);

	bool solutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);

	while (!frontier.empty() && !solutionFound)
	{
		frontier.pop_front();
		explored.push_back(current_node);
		PintaEstado(current_node.st.jugador);
		PintaPlan(current_node.secuencia);

		// Generar hijo actWALK
		nodeN0 child_walk = current_node;
		child_walk.st = apply(actWALK, current_node.st, mapa);
		child_walk.secuencia.push_back(actWALK);

		cout << "\t";
		PintaPlan(child_walk.secuencia);


		if (child_walk.st.jugador.f == final.f && child_walk.st.jugador.c == final.c)
		{
			current_node = child_walk;
			solutionFound = true;
		}
		else if (!Find(child_walk.st, frontier) && !Find(child_walk.st, explored))
		{
			frontier.push_back(child_walk);
		}
		else if (Find(child_walk.st, frontier)){
			cout << "está en frontier ";
			PintaEstado(child_walk.st.jugador);

			cout << endl;
			for (auto it= frontier.begin();it != frontier.end(); ++it){
				PintaPlan(it->secuencia);
				PintaEstado(it->st.jugador);
				cout << endl;
			}
			cout << "===========================\n";
		}
		if (!solutionFound)
		{
			nodeN0 child_run = current_node;
			child_run.st = apply(actRUN, current_node.st, mapa);
			child_run.secuencia.push_back(actRUN);

			if (child_run.st.jugador.f == final.f && child_run.st.jugador.c == final.c)
			{
				current_node = child_run;
				solutionFound = true;
			}
			else if (!Find(child_run.st, frontier) && !Find(child_run.st, explored))
			{
				frontier.push_back(child_run);
			}
		}
		if (!solutionFound)
		{
			// Generar hijo actTURN_R
			nodeN0 child_turnl = current_node;
			child_turnl.st = apply(actTURN_L, current_node.st, mapa);
			child_turnl.secuencia.push_back(actTURN_L);
			if (!(Find(child_turnl.st, frontier)) && !(Find(child_turnl.st, explored)))
			{
				frontier.push_back(child_turnl);
			}

			nodeN0 child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR, current_node.st, mapa);
			child_turnsr.secuencia.push_back(actTURN_SR);
			if (!(Find(child_turnsr.st, frontier)) && !(Find(child_turnsr.st, explored)))
			{
				frontier.push_back(child_turnsr);
			}
		}
		if (!solutionFound && !frontier.empty())
			current_node = frontier.front();
	}
	if (solutionFound)
	{
		plan = current_node.secuencia;
		cout << "Encontrado plan: ";
		PintaPlan(current_node.secuencia);
	}
	return plan;
}
// Tercera version busqueda en anchura, revuelve plan
list<Action> AnchuraSoloJugador_V3(const stateN0 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa)
{
	nodeN0 current_node;
	list<nodeN0> frontier;
	set<nodeN0> explored;
	list<Action> plan;
	current_node.st = inicio;
	frontier.push_back(current_node);

	bool solutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);

	while (!frontier.empty() && !solutionFound)
	{
		frontier.pop_front();
		explored.insert(current_node);

		// Generar hijo actWALK
		nodeN0 child_walk = current_node;
		child_walk.st = apply(actWALK, current_node.st, mapa);
		child_walk.secuencia.push_back(actWALK);

		if (child_walk.st.jugador.f == final.f && child_walk.st.jugador.c == final.c)
		{
			current_node = child_walk;
			solutionFound = true;
		}
		else if (explored.find(child_walk) == explored.end())
		{
			frontier.push_back(child_walk);
		}

		if (!solutionFound)
		{
			nodeN0 child_run = current_node;
			child_run.st = apply(actRUN, current_node.st, mapa);
			child_run.secuencia.push_back(actRUN);

			if (child_run.st.jugador.f == final.f && child_run.st.jugador.c == final.c)
			{
				current_node = child_run;
				solutionFound = true;
			}
			else if (explored.find(child_run) == explored.end())
			{
				frontier.push_back(child_run);
			}
		}

		if (!solutionFound)
		{
			// Generar hijo actTURN_R
			nodeN0 child_turnl = current_node;
			child_turnl.st = apply(actTURN_L, current_node.st, mapa);
			child_turnl.secuencia.push_back(actTURN_L);
			if (explored.find(child_turnl) == explored.end())
			{
				frontier.push_back(child_turnl);
			}

			nodeN0 child_turnsr = current_node;
			child_turnsr.st = apply(actTURN_SR, current_node.st, mapa);
			child_turnsr.secuencia.push_back(actTURN_SR);
			if (explored.find(child_turnsr) == explored.end())
			{
				frontier.push_back(child_turnsr);
			}
		}
		if (!solutionFound && !frontier.empty())
		{
			current_node = frontier.front();
			while (!frontier.empty() && explored.find(current_node) != explored.end())
			{
				frontier.pop_front();
				if (!frontier.empty())
				{
					current_node = frontier.front();
				}
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
			goal.f = sensores.destinoF;
			goal.c = sensores.destinoC;
			switch (sensores.nivel)
			{
			case 0:
				plan = AnchuraSoloJugador_V2(c_state, goal, mapaResultado);
				if (plan.size() > 0)
				{
					hayPlan = true;
					VisualizarPlan(c_state, plan);
				}
				break;
			case 1:
				cout << "Pendiente de implementacion\n";
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
			cout << "acción: " << accion << endl;
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
