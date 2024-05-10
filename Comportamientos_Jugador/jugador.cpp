#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <stack>
#include <queue>

//coste
void getCoste(const Action &a, stateN2 &st, const vector<vector<unsigned char>> &mapa){
	char terreno = mapa[st.jugador.f][st.jugador.c];

	switch (a){
		case actWALK:
			switch(terreno){
				case 'A':
					if(st.bikini) st.coste += 10;
					else st.coste += 100;
					break;
				case 'B':
					if(st.zapas) st.coste += 15;
					else st.coste += 50;
					break;
				case 'T':
					st.coste += 2;
					break;
				default:
					st.coste += 1;
					break;
				}
			break;
		case actRUN:
			switch(terreno){
				case 'A':
					if(st.bikini) st.coste += 15;
					else st.coste += 150;
					break;
				case 'B':
					if(st.zapas) st.coste += 25;
					else st.coste += 75;
					break;
				case 'T':
					st.coste += 3;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
		case actTURN_L:
			switch(terreno){
				case 'A':
					if(st.bikini) st.coste += 5;
					else st.coste += 30;
					break;
				case 'B':
					if(st.zapas)st.coste += 1;
					else st.coste += 7;
					break;
				case 'T':
					st.coste += 2;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
		case actTURN_SR:
			switch(terreno){
				case 'A':
					if(st.bikini) st.coste += 2;
					else st.coste += 10;
					break;
				case 'B':
					if(st.zapas) st.coste += 1;
					else st.coste += 5;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
	}
}

void costeCasillaJ(const Action &a, stateN3 &st, const vector<vector<unsigned char>> &mapa){
	char terreno = mapa[st.jugador.f][st.jugador.c];
	
	switch (a){
		case actWALK:
			switch(terreno){
				case 'A':
					if(st.bikiniJ) st.coste += 10;
					else st.coste += 100;
					break;
				case 'B':
					if(st.zapasJ) st.coste += 15;
					else st.coste += 50;
					break;
				case 'T':
					st.coste += 2;
					break;
				default:
					st.coste += 1;
					break;
				}
			break;
		case actRUN:
			switch(terreno){
				case 'A':
					if(st.bikiniJ) st.coste += 15;
					else st.coste += 150;
					break;
				case 'B':
					if(st.zapasJ) st.coste += 25;
					else st.coste += 75;
					break;
				case 'T':
					st.coste += 3;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
		case actTURN_L:
			switch(terreno){
				case 'A':
					if(st.bikiniJ) st.coste += 5;
					else st.coste += 30;
					break;
				case 'B':
					if(st.zapasJ)st.coste += 1;
					else st.coste += 7;
					break;
				case 'T':
					st.coste += 2;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
		case actTURN_SR:
			switch(terreno){
				case 'A':
					if(st.bikiniJ) st.coste += 2;
					else st.coste += 10;
					break;
				case 'B':
					if(st.zapasJ) st.coste += 1;
					else st.coste += 5;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
	}
}

void costeCasillaC(const Action &a, stateN3 &st, const vector<vector<unsigned char>> &mapa){
	char terreno = mapa[st.colaborador.f][st.colaborador.c];

	switch (a){
		case act_CLB_WALK:
			switch(terreno){
				case 'A':
					if(st.bikiniC) st.coste += 10;
					else st.coste += 100;
					break;
				case 'B':
					if(st.zapasC) st.coste += 15;
					else st.coste += 50;
					break;
				case 'T':
					st.coste += 2;
					break;
				default:
					st.coste += 1;
					break;
				}
		case actTURN_SR:
			switch(terreno){
				case 'A':
					if(st.bikiniC) st.coste += 2;
					else st.coste += 10;
					break;
				case 'B':
					if(st.zapasC) st.coste += 1;
					else st.coste += 5;
					break;
				default:
					st.coste += 1;
					break;
			}
			break;
	}
}
int getHeuristica(const stateN3 &st, const ubicacion &final){
	int heuristica = 0;
	int fila = abs(final.f - st.colaborador.f);
	int columna = abs(final.c - st.colaborador.c);
	heuristica = max(fila, columna);
	heuristica += st.coste;
	return heuristica;
}
//¿Veo el colaborador?
bool verColaborador(const ubicacion &j, const ubicacion &c){
	switch(j.brujula){
		case norte:
			if((j.f-1) == c.f && (j.c-1) == c.c) return true;
			if((j.f-1) == c.f && (j.c) == c.c) return true;
			if((j.f-1) == c.f && (j.c+1) == c.c) return true;			
			if((j.f-2) == c.f && (j.c-2) == c.c) return true;			
			if((j.f-2) == c.f && (j.c-1) == c.c) return true;
			if((j.f-2) == c.f && (j.c) == c.c) return true;			
			if((j.f-2) == c.f && (j.c+1) == c.c) return true;
			if((j.f-2) == c.f && (j.c+2) == c.c) return true;
			if((j.f-3) == c.f && (j.c-3) == c.c) return true;
			if((j.f-3) == c.f && (j.c-2) == c.c) return true;
			if((j.f-3) == c.f && (j.c-1) == c.c) return true;
			if((j.f-3) == c.f && (j.c) == c.c) return true;
			if((j.f-3) == c.f && (j.c+1) == c.c) return true;
			if((j.f-3) == c.f && (j.c+2) == c.c) return true;
			if((j.f-3) == c.f && (j.c+3) == c.c) return true;			
			break;
		case sur: 
			if((j.f+1) == c.f && (j.c+1) == c.c) return true;
			if((j.f+1) == c.f && (j.c) == c.c) return true;
			if((j.f+1) == c.f && (j.c-1) == c.c) return true;
			if((j.f+2) == c.f && (j.c+2) == c.c) return true;
			if((j.f+2) == c.f && (j.c+1) == c.c) return true;
			if((j.f+2) == c.f && (j.c) == c.c) return true;
			if((j.f+2) == c.f && (j.c-1) == c.c) return true;
			if((j.f+2) == c.f && (j.c-2) == c.c) return true;
			if((j.f+3) == c.f && (j.c+3) == c.c) return true;
			if((j.f+3) == c.f && (j.c+2) == c.c) return true;
			if((j.f+3) == c.f && (j.c+1) == c.c) return true;
			if((j.f+3) == c.f && (j.c) == c.c) return true;
			if((j.f+3) == c.f && (j.c-1) == c.c) return true;
			if((j.f+3) == c.f && (j.c-2) == c.c) return true;
			if((j.f+3) == c.f && (j.c-3) == c.c) return true;
			break;
		case este:
			if((j.f-1) == c.f && (j.c+1) == c.c) return true;
			if((j.f) == c.f && (j.c+1) == c.c) return true;
			if((j.f+1) == c.f && (j.c+1) == c.c) return true;
			if((j.f-2) == c.f && (j.c+2) == c.c) return true;
			if((j.f-1) == c.f && (j.c+2) == c.c) return true;
			if((j.f) == c.f && (j.c+2) == c.c) return true;
			if((j.f+1) == c.f && (j.c+2) == c.c) return true;
			if((j.f+2) == c.f && (j.c+2) == c.c) return true;
			if((j.f-3) == c.f && (j.c+3) == c.c) return true;
			if((j.f-2) == c.f && (j.c+3) == c.c) return true;
			if((j.f-1) == c.f && (j.c+3) == c.c) return true;
			if((j.f) == c.f && (j.c+3) == c.c) return true;
			if((j.f+1) == c.f && (j.c+3) == c.c) return true;
			if((j.f+2) == c.f && (j.c+3) == c.c) return true;
			if((j.f+3) == c.f && (j.c+3) == c.c) return true;
			break;
		case oeste:
			if((j.f+1) == c.f && (j.c-1) == c.c) return true;
			if((j.f) == c.f && (j.c-1) == c.c) return true;
			if((j.f-1) == c.f && (j.c-1) == c.c) return true;
			if((j.f+2) == c.f && (j.c-2) == c.c) return true;
			if((j.f+1) == c.f && (j.c-2) == c.c) return true;
			if((j.f) == c.f && (j.c-2) == c.c) return true;
			if((j.f-1) == c.f && (j.c-2) == c.c) return true;
			if((j.f-2) == c.f && (j.c-2) == c.c) return true;
			if((j.f+3) == c.f && (j.c-3) == c.c) return true;
			if((j.f+2) == c.f && (j.c-3) == c.c) return true;
			if((j.f+1) == c.f && (j.c-3) == c.c) return true;
			if((j.f) == c.f && (j.c-3) == c.c) return true;
			if((j.f-1) == c.f && (j.c-3) == c.c) return true;
			if((j.f-2) == c.f && (j.c-3) == c.c) return true;
			if((j.f-3) == c.f && (j.c-3) == c.c) return true;
			break;
		case noreste:
			if((j.f-1) == c.f && (j.c) == c.c) return true;
			if((j.f-1) == c.f && (j.c+1) == c.c) return true;
			if((j.f) == c.f && (j.c+1) == c.c) return true;
			if((j.f-2) == c.f && (j.c) == c.c) return true;
			if((j.f-2) == c.f && (j.c+1) == c.c) return true;
			if((j.f-2) == c.f && (j.c+2) == c.c) return true;
			if((j.f-1) == c.f && (j.c+2) == c.c) return true;
			if((j.f) == c.f && (j.c+2) == c.c) return true;
			if((j.f-3) == c.f && (j.c) == c.c) return true;
			if((j.f-3) == c.f && (j.c+1) == c.c) return true;
			if((j.f-3) == c.f && (j.c+2) == c.c) return true;
			if((j.f-3) == c.f && (j.c+3) == c.c) return true;
			if((j.f-2) == c.f && (j.c+3) == c.c) return true;
			if((j.f-1) == c.f && (j.c+3) == c.c) return true;
			if((j.f) == c.f && (j.c+3) == c.c) return true;
			break;
		case noroeste:
			if((j.f) == c.f && (j.c-1) == c.c) return true;
			if((j.f-1) == c.f && (j.c-1) == c.c) return true;
			if((j.f-1) == c.f && (j.c) == c.c) return true;
			if((j.f) == c.f && (j.c-2) == c.c) return true;
			if((j.f-1) == c.f && (j.c-2) == c.c) return true;
			if((j.f-2) == c.f && (j.c-2) == c.c) return true;
			if((j.f-2) == c.f && (j.c-1) == c.c) return true;
			if((j.f-2) == c.f && (j.c) == c.c) return true;
			if((j.f) == c.f && (j.c-3) == c.c) return true;
			if((j.f-1) == c.f && (j.c-3) == c.c) return true;
			if((j.f-2) == c.f && (j.c-3) == c.c) return true;
			if((j.f-3) == c.f && (j.c-3) == c.c) return true;
			if((j.f-3) == c.f && (j.c-2) == c.c) return true;
			if((j.f-3) == c.f && (j.c-1) == c.c) return true;
			if((j.f-3) == c.f && (j.c) == c.c) return true;
			break;
		case sureste:
			if((j.f) == c.f && (j.c+1) == c.c) return true;
			if((j.f+1) == c.f && (j.c+1) == c.c) return true;
			if((j.f+1) == c.f && (j.c) == c.c) return true;
			if((j.f) == c.f && (j.c+2) == c.c) return true;
			if((j.f+1) == c.f && (j.c+2) == c.c) return true;
			if((j.f+2) == c.f && (j.c+2) == c.c) return true;
			if((j.f+2) == c.f && (j.c+1) == c.c) return true;
			if((j.f+2) == c.f && (j.c) == c.c) return true;
			if((j.f) == c.f && (j.c+3) == c.c) return true;
			if((j.f+1) == c.f && (j.c+3) == c.c) return true;
			if((j.f+2) == c.f && (j.c+3) == c.c) return true;
			if((j.f+3) == c.f && (j.c+3) == c.c) return true;
			if((j.f+3) == c.f && (j.c+2) == c.c) return true;
			if((j.f+3) == c.f && (j.c+1) == c.c) return true;
			if((j.f+3) == c.f && (j.c) == c.c) return true;
			break;
		case suroeste:
			if((j.f+1) == c.f && (j.c) == c.c) return true;
			if((j.f+1) == c.f && (j.c-1) == c.c) return true;
			if((j.f) == c.f && (j.c-1) == c.c) return true;
			if((j.f+2) == c.f && (j.c) == c.c) return true;
			if((j.f+2) == c.f && (j.c-1) == c.c) return true;
			if((j.f+2) == c.f && (j.c-2) == c.c) return true;
			if((j.f+1) == c.f && (j.c-2) == c.c) return true;
			if((j.f) == c.f && (j.c-2) == c.c) return true;
			if((j.f+3) == c.f && (j.c) == c.c) return true;
			if((j.f+3) == c.f && (j.c-1) == c.c) return true;
			if((j.f+3) == c.f && (j.c-2) == c.c) return true;
			if((j.f+3) == c.f && (j.c-3) == c.c) return true;
			if((j.f+2) == c.f && (j.c-3) == c.c) return true;
			if((j.f+1) == c.f && (j.c-3) == c.c) return true;
			if((j.f) == c.f && (j.c-3) == c.c) return true;
			break;		
	}
	return false;
}

// Pone a cero toos los elementos de una matriz
void AnularMatriz(vector<vector<unsigned char>> &matriz){
	for (int i = 0; i < matriz.size(); i++){
		for (int j = 0; j < matriz[0].size(); j++){
			matriz[i][j] = 0;
		}
	}
}

// Devuelve si una ubicación en el mapa es transitable para el agente
bool CasillaTransitable(const ubicacion &x, const vector<vector<unsigned char>> &mapa)
{
	return (mapa[x.f][x.c] != 'P' && mapa[x.f][x.c] != 'M');
}

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

/*Apply para nivel 0*/
stateN0 applyN0(const Action &a, const stateN0 &st, const vector<vector<unsigned char>> &mapa){
	stateN0 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch (a){
	case actWALK: // Si la proxima casilla es transitable y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			st_result.jugador = sig_ubicacion;
		}
		break;
	case actRUN: // Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			sig_ubicacion2 = NextCasilla(sig_ubicacion);
			if (CasillaTransitable(sig_ubicacion2, mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
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

/*Apply para nivel 1*/
stateN1 applyN1(const Action &a, const stateN1 &st, const vector<vector<unsigned char>> &mapa){
	stateN1 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch (a){
		case actWALK: // Si la proxima casilla es transitable y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			st_result.jugador = sig_ubicacion;
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
		}
		break;
	case actRUN: // Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			sig_ubicacion2 = NextCasilla(sig_ubicacion);
			if (CasillaTransitable(sig_ubicacion2, mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
				st_result.jugador = sig_ubicacion2;
				st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
			}
		}
		break;
	case actTURN_L:
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
		break;
	case actTURN_SR:
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 1) % 8);
				st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
		break;

	case act_CLB_WALK:
		sig_ubicacion = NextCasilla(st.colaborador);
		if(CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.jugador.f && sig_ubicacion.c == st.jugador.c)){
			st_result.colaborador = sig_ubicacion;
			st_result.ultimaOrdenColaborador = act_CLB_WALK;
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
		}
		break;
	case act_CLB_TURN_SR:
		st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula + 1) % 8);
		st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
		st_result.ultimaOrdenColaborador = act_CLB_TURN_SR;	
		break;
	}
	return st_result;
}

/*Apply para nivel 2*/
stateN2 applyN2(const Action &a, const stateN2 &st, const vector<vector<unsigned char>> &mapa){
	stateN2 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch (a){
	case actWALK: // Si la proxima casilla es transitable y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			getCoste(actWALK,st_result,mapa);
			st_result.jugador = sig_ubicacion;
			//st_result = item(st_result,st_result.jugador,mapa);
		}
		break;
	case actRUN: // Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			sig_ubicacion2 = NextCasilla(sig_ubicacion);
			if (CasillaTransitable(sig_ubicacion2, mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
				getCoste(actRUN,st_result,mapa);
				st_result.jugador = sig_ubicacion2;
			}
		}
		break;
	case actTURN_L:
		getCoste(actTURN_L,st_result,mapa);
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
		break;
	case actTURN_SR:
		getCoste(actTURN_SR,st_result,mapa);
		st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 1) % 8);
		break;
	}
	return st_result;
}

/*Nivel 3*/
stateN3 applyN3(const Action &a, const stateN3 &st, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	stateN3 st_result = st;
	ubicacion sig_ubicacion, sig_ubicacion2;
	switch (a){
		case actWALK: // Si la proxima casilla es transitable y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			costeCasillaJ(actWALK,st_result,mapa);
			st_result.heuristica = getHeuristica(st_result,final);
			st_result.jugador = sig_ubicacion;
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
		}
		break;
	case actRUN: // Si las proximas 2 casillas son transitables y NO está ocupada por el colaborador
		sig_ubicacion = NextCasilla(st.jugador);
		if (CasillaTransitable(sig_ubicacion, mapa) && !(sig_ubicacion.f == st.colaborador.f && sig_ubicacion.c == st.colaborador.c)){
			sig_ubicacion2 = NextCasilla(sig_ubicacion);
			if (CasillaTransitable(sig_ubicacion2, mapa) && !(sig_ubicacion2.f == st.colaborador.f && sig_ubicacion2.c == st.colaborador.c)){
				costeCasillaJ(actRUN,st_result,mapa);
				st_result.heuristica = getHeuristica(st_result,final);
				st_result.jugador = sig_ubicacion2;
				st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
			}
		}
		break;
		case actTURN_L:
			costeCasillaJ(actTURN_L,st_result,mapa);
			st_result.heuristica = getHeuristica(st_result,final);
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 6) % 8);
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
			break;
		case actTURN_SR:
			costeCasillaJ(actTURN_SR,st_result,mapa);
			st_result.heuristica = getHeuristica(st_result,final);
			st_result.jugador.brujula = static_cast<Orientacion>((st_result.jugador.brujula + 1) % 8);
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
			break;
		case act_CLB_WALK:
			sig_ubicacion = NextCasilla(st.colaborador);
			if(CasillaTransitable(sig_ubicacion,mapa) && !(sig_ubicacion.f == st.jugador.f && sig_ubicacion.c == st.jugador.c)){
				costeCasillaC(act_CLB_WALK,st_result,mapa);
				st_result.heuristica = getHeuristica(st_result,final);
				st_result.colaborador = sig_ubicacion;
				st_result.ultimaOrdenColaborador = act_CLB_WALK;
				st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
			}
			break;
		case act_CLB_TURN_SR:
			costeCasillaC(act_CLB_TURN_SR,st_result,mapa);
			st_result.heuristica = getHeuristica(st_result,final);
			st_result.colaborador.brujula = static_cast<Orientacion>((st_result.colaborador.brujula + 1) % 8);
			st_result.colaboradorVisto = verColaborador(st_result.jugador,st_result.colaborador);
			st_result.ultimaOrdenColaborador = act_CLB_TURN_SR;	
			break;
	}
	return st_result;
}
// Permite pintar sobre el mapa del simulador el plan partiendo desde el estado st
/*Para nivel 0*/
void ComportamientoJugador::VisualizarPlanN0(const stateN0 &st, const list<Action> &plan){
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
/*Para nivel 1*/
void ComportamientoJugador::VisualizarPlanN1(const stateN1 &st, const list<Action> &plan){
	AnularMatriz(mapaConPlan);
	stateN1 cst = st;

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
/*Para nivel 2*/
void ComportamientoJugador::VisualizarPlanN2(const stateN2 &st, const list<Action> &plan){
	AnularMatriz(mapaConPlan);
	stateN2 cst = st;

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

/*Para nivel 3*/
void ComportamientoJugador::VisualizarPlanN3(const stateN3 &st, const list<Action> &plan){
	AnularMatriz(mapaConPlan);
	stateN3 cst = st;

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
		child_walk.st = applyN0(actWALK, current_node.st, mapa);
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
			child_run.st = applyN0(actRUN, current_node.st, mapa);
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
			child_turnl.st = applyN0(actTURN_L, current_node.st, mapa);
			child_turnl.secuencia.push_back(actTURN_L);
			if (explored.find(child_turnl) == explored.end()){
				frontier.push_back(child_turnl);
			}

			//Genera hijo actTURN_SR
			nodeN0 child_turnsr = current_node;
			child_turnsr.st = applyN0(actTURN_SR, current_node.st, mapa);
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
	
	if (solutionFound){
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

list<Action> AnchuraSoloColaborador(const stateN1 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	nodeN1 current_node;
	list<nodeN1>frontier;
	set<nodeN1> explored;
	list<Action> plan;
	current_node.st = inicio;
	bool solutionFound = (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c);
	bool veoColaborador = current_node.st.colaboradorVisto;
	frontier.push_back(current_node);
	
	
	while(!frontier.empty() && !solutionFound){
		frontier.pop_front();
		explored.insert(current_node);
		//veoColaborador = verColaborador(current_node.st.jugador,current_node.st.colaborador);
		veoColaborador = verColaborador(current_node.st.jugador,current_node.st.colaborador);
		/* cout << "tamaño frontier: " << frontier.size() << "\t tamaño explored: " << explored.size() << endl;
		PintaPlan(current_node.secuencia);
		pintaEtadoN1(current_node);*/

		if(veoColaborador){
			//cout << "entro colaborador\n";
			//hijo act_CLB_walk
			nodeN1 child_clbwalk = current_node;
			child_clbwalk.st = applyN1(act_CLB_WALK,current_node.st,mapa);
			
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
				child_clbturnsr.st = applyN1(act_CLB_TURN_SR,current_node.st,mapa);
				if(explored.find(child_clbturnsr) == explored.end()){
					child_clbturnsr.secuencia.push_back(act_CLB_TURN_SR);
					child_clbturnsr.st.ultimaOrdenColaborador = act_CLB_TURN_SR;
					frontier.push_back(child_clbturnsr);
				}
				nodeN1 child_clbstop = current_node;
				child_clbstop.st = applyN1(act_CLB_STOP,current_node.st,mapa);
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
			modificacion.st = applyN1(act_CLB_WALK,current_node.st,mapa);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		else if(current_node.st.ultimaOrdenColaborador == act_CLB_TURN_SR){
			nodeN1 modificacion = current_node;
			modificacion.st = applyN1(act_CLB_TURN_SR,current_node.st,mapa);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		else if(current_node.st.ultimaOrdenColaborador == act_CLB_STOP){
			nodeN1 modificacion = current_node;
			modificacion.st = applyN1(act_CLB_STOP,current_node.st,mapa);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
					//hijo actIDLE
			nodeN1 child_idle = current_node;
			child_idle.st = applyN1(actIDLE,current_node.st,mapa);
			if(child_idle.st.colaborador.f == final.f && child_idle.st.colaborador.c == final.c){
				current_node = child_idle;
				solutionFound = true;
			}

			else if(explored.find(child_idle) == explored.end()){
				child_idle.secuencia.push_back(actIDLE);
				frontier.push_back(child_idle);
			}
		//hijo actWALK
		nodeN1 child_walk = current_node;
		child_walk.st = applyN1(actWALK,current_node.st,mapa);
		if(explored.find(child_walk) == explored.end()){
			child_walk.secuencia.push_back(actWALK);
			frontier.push_back(child_walk);
		}
		//hijo actRUN
		nodeN1 child_run = current_node;
		child_run.st = applyN1(actRUN,current_node.st,mapa);
		 if(explored.find(child_run) == explored.end()){
			child_run.secuencia.push_back(actRUN);
			frontier.push_back(child_run);
		}
		//hijo actTURN_L
		nodeN1 child_turnl = current_node;
		child_turnl.st = applyN1(actTURN_L,current_node.st,mapa);
		if(explored.find(child_turnl) == explored.end()){
			child_turnl.secuencia.push_back(actTURN_L);
			frontier.push_back(child_turnl);
		}
		//hijo actTURN_SR
		nodeN1 child_turnsr = current_node;
		child_turnsr.st = applyN1(actTURN_SR,current_node.st,mapa);
		if(explored.find(child_turnsr) == explored.end()){
			child_turnsr.secuencia.push_back(actTURN_SR);
			frontier.push_back(child_turnsr);
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

list<Action> DijkstraSoloJugador(const stateN2 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
    nodeN2 current_node;
    priority_queue<nodeN2> frontier;
    set<nodeN2, nodeN2comparar> explored;
    list<Action> plan;
    current_node.st = inicio;
    current_node.st.coste = 0;
    bool solutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);
    
    char terreno = mapa[current_node.st.jugador.f][current_node.st.jugador.c];
    if(terreno == 'K'){
        current_node.st.bikini = true;
		current_node.st.zapas = false;
    }else if(terreno == 'D'){
        current_node.st.zapas = true;
		current_node.st.bikini = false;
    }
    frontier.push(current_node);
    while (!frontier.empty() && !solutionFound){
		frontier.pop();
        
		explored.insert(current_node);

	terreno = mapa[current_node.st.jugador.f][current_node.st.jugador.c];
    if(terreno == 'K'){
        current_node.st.bikini = true;
		current_node.st.zapas = false;
    }else if(terreno == 'D'){
        current_node.st.zapas = true;
		current_node.st.bikini = false;
    }
        //cout << "bikini: " << current_node.st.bikini << endl;
        //cout << "zapas: " << current_node.st.zapas << endl;

        // Generar hijo actWALK
        nodeN2 child_walk = current_node;
        child_walk.st = applyN2(actWALK, current_node.st, mapa);
        child_walk.secuencia.push_back(actWALK);
		if(!(child_walk.st == current_node.st))
        if (explored.find(child_walk) == explored.end()){
            frontier.push(child_walk);
        }
    
       // if (!solutionFound){
            nodeN2 child_run = current_node;
            child_run.st = applyN2(actRUN, current_node.st, mapa);
            if(!(child_run.st == current_node.st))
            	if (explored.find(child_run) == explored.end()){
					child_run.secuencia.push_back(actRUN);
            	    frontier.push(child_run);
            	}
       // }
      // 	if (!solutionFound){
            // Generar hijo actTURN_L
            nodeN2 child_turnl = current_node;
            child_turnl.st = applyN2(actTURN_L, current_node.st, mapa);
            child_turnl.secuencia.push_back(actTURN_L);
           // if(!(child_turnl.st == current_node.st))
		    if (explored.find(child_turnl) == explored.end()){
                frontier.push(child_turnl);
            }

            //Genera hijo actTURN_SR
            nodeN2 child_turnsr = current_node;
            child_turnsr.st = applyN2(actTURN_SR, current_node.st, mapa);
            child_turnsr.secuencia.push_back(actTURN_SR);
          // if(!(child_turnsr.st == current_node.st))
		    if (explored.find(child_turnsr) == explored.end()){
                frontier.push(child_turnsr);
            }
    	//}
        if (!solutionFound && !frontier.empty()){
            current_node = frontier.top();
            while(!frontier.empty() && explored.find(current_node) != explored.end()){
                frontier.pop();
                if(!frontier.empty())
                    current_node = frontier.top();
            }
        }
		solutionFound = (current_node.st.jugador.f == final.f && current_node.st.jugador.c == final.c);
    }
    
    if (solutionFound){
        plan = current_node.secuencia;
        cout << "Encontrado plan: ";
        PintaPlan(current_node.secuencia);
    }
    return plan;
}

list<Action> AEstrellaSoloColaborador(const stateN3 &inicio, const ubicacion &final, const vector<vector<unsigned char>> &mapa){
	nodeN3 current_node;
	priority_queue<nodeN3> frontier;
    set<nodeN3, nodeN3comparar> explored;
	list<Action> plan;
	
	current_node.st = inicio;
	current_node.st.coste = 0;
	current_node.st.heuristica = getHeuristica(current_node.st,final);
	
	bool solutionFound = (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c);
	bool veoColaborador = current_node.st.colaboradorVisto;
	
	char terrenoJ = mapa[current_node.st.jugador.f][current_node.st.jugador.c];
    if(terrenoJ == 'K'){
        current_node.st.bikiniJ = true;
		current_node.st.zapasJ = false;
    }else if(terrenoJ == 'D'){
        current_node.st.zapasJ = true;
		current_node.st.bikiniJ = false;
    }
		
	char terrenoC = mapa[current_node.st.colaborador.f][current_node.st.colaborador.c];
    if(terrenoC == 'K'){
        current_node.st.bikiniC = true;
		current_node.st.zapasC = false;
    }else if(terrenoC == 'D'){
        current_node.st.zapasC = true;
		current_node.st.bikiniC = false;
    }
	frontier.push(current_node);
	
	
	while(!frontier.empty() && !solutionFound){
		frontier.pop();
		explored.insert(current_node);
		//veoColaborador = verColaborador(current_node.st.jugador,current_node.st.colaborador);
		veoColaborador = verColaborador(current_node.st.jugador,current_node.st.colaborador);
		
		terrenoJ = mapa[current_node.st.jugador.f][current_node.st.jugador.c];
		if(terrenoJ == 'K'){
			current_node.st.bikiniJ = true;
			current_node.st.zapasJ = false;
		}else if(terrenoJ == 'D'){
			current_node.st.zapasJ = true;
			current_node.st.bikiniJ = false;
		}

		terrenoC = mapa[current_node.st.colaborador.f][current_node.st.colaborador.c];
		if(terrenoC == 'K'){
			current_node.st.bikiniC = true;
			current_node.st.zapasC = false;
		}else if(terrenoC == 'D'){
			current_node.st.zapasC = true;
			current_node.st.bikiniC = false;
		}
		if(veoColaborador){
			//cout << "entro colborador\n";
			//hijo act_CLB_walk
			nodeN3 child_clbwalk = current_node;
			child_clbwalk.st = applyN3(act_CLB_WALK,current_node.st, final, mapa);
		/*	if(child_clbwalk.st.colaborador.f == final.f && child_clbwalk.st.colaborador.c == final.c){
				child_clbwalk.secuencia.push_back(act_CLB_WALK);
				current_node = child_clbwalk;
				solutionFound = true;
			}
			else*/ 
			if(explored.find(child_clbwalk) == explored.end()){
				child_clbwalk.secuencia.push_back(act_CLB_WALK);
				child_clbwalk.st.ultimaOrdenColaborador = act_CLB_WALK;
				frontier.push(child_clbwalk);
			}
			//el que se pare.
			if(!solutionFound){
				//hijo act_CLB_turn_SR
				nodeN3 child_clbturnsr = current_node;
				child_clbturnsr.st = applyN3(act_CLB_TURN_SR,current_node.st, final, mapa);
				if(explored.find(child_clbturnsr) == explored.end()){
					child_clbturnsr.secuencia.push_back(act_CLB_TURN_SR);
					child_clbturnsr.st.ultimaOrdenColaborador = act_CLB_TURN_SR;
					frontier.push(child_clbturnsr);
				}
				nodeN3 child_clbstop = current_node;
				child_clbstop.st = applyN3(act_CLB_STOP,current_node.st, final, mapa);
				if(explored.find(child_clbstop) == explored.end()){
					child_clbstop.secuencia.push_back(act_CLB_STOP);
					child_clbstop.st.ultimaOrdenColaborador = act_CLB_STOP;
					frontier.push(child_clbstop);
				}
			}

		}
		//genero estado intermedio
		if(current_node.st.ultimaOrdenColaborador == act_CLB_WALK){
			nodeN3 modificacion = current_node;
			modificacion.st = applyN3(act_CLB_WALK,current_node.st, final, mapa);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		else if(current_node.st.ultimaOrdenColaborador == act_CLB_TURN_SR){
			nodeN3 modificacion = current_node;
			modificacion.st = applyN3(act_CLB_TURN_SR,current_node.st,final, mapa);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
		else if(current_node.st.ultimaOrdenColaborador == act_CLB_STOP){
			nodeN3 modificacion = current_node;
			modificacion.st = applyN3(act_CLB_STOP,current_node.st, final, mapa);
			if(!(modificacion == current_node)){
				current_node = modificacion;
			}
		}
					//hijo actIDLE
			nodeN3 child_idle = current_node;
			child_idle.st = applyN3(actIDLE,current_node.st, final, mapa);
		
			if(explored.find(child_idle) == explored.end()){
				child_idle.secuencia.push_back(actIDLE);
				frontier.push(child_idle);
			}
			if(child_idle.st.colaborador.f == final.f && child_idle.st.colaborador.c == final.c){
				current_node = child_idle;
				solutionFound = true;
			}
		//hijo actWALK
		nodeN3 child_walk = current_node;
		child_walk.st = applyN3(actWALK,current_node.st,final,mapa);
		if(explored.find(child_walk) == explored.end()){
			child_walk.secuencia.push_back(actWALK);
			frontier.push(child_walk);
		}
		//hijo actRUN
		nodeN3 child_run = current_node;
		child_run.st = applyN3(actRUN,current_node.st,final,mapa);
		 if(explored.find(child_run) == explored.end()){
			child_run.secuencia.push_back(actRUN);
			frontier.push(child_run);
		}
		//hijo actTURN_L
		nodeN3 child_turnl = current_node;
		child_turnl.st = applyN3(actTURN_L,current_node.st,final,mapa);
		if(explored.find(child_turnl) == explored.end()){
			child_turnl.secuencia.push_back(actTURN_L);
			frontier.push(child_turnl);
		}
		//hijo actTURN_SR
		
		nodeN3 child_turnsr = current_node;
		child_turnsr.st = applyN3(actTURN_SR,current_node.st,final,mapa);
		if(explored.find(child_turnsr) == explored.end()){
			child_turnsr.secuencia.push_back(actTURN_SR);
			frontier.push(child_turnsr);
		}
	
		if(!solutionFound && !frontier.empty()){
			current_node = frontier.top();
			while(!frontier.empty() && explored.find(current_node) != explored.end()){
				frontier.pop();
				if(!frontier.empty())
					current_node = frontier.top();
			}
		}
		//else{
					solutionFound = (current_node.st.colaborador.f == final.f && current_node.st.colaborador.c == final.c);
		//}

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
	if (sensores.nivel != 4){
		if (!hayPlan){
			cout << "Calculando un nuevo plan\n";
			goal.f = sensores.destinoF;
			goal.c = sensores.destinoC;
			switch (sensores.nivel){
				case 0:
					c_stateN0.jugador.f = sensores.posF;
					c_stateN0.jugador.c = sensores.posC;
					c_stateN0.jugador.brujula = sensores.sentido;

					c_stateN0.colaborador.f = sensores.CLBposF;
					c_stateN0.colaborador.c = sensores.CLBposC;
					c_stateN0.colaborador.brujula = sensores.CLBsentido;
					plan = AnchuraSoloJugador(c_stateN0, goal, mapaResultado);
					if (plan.size() > 0){
						hayPlan = true;
						VisualizarPlanN0(c_stateN0, plan);
					}
					break;
				case 1:
					c_stateN1.jugador.f = sensores.posF;
					c_stateN1.jugador.c = sensores.posC;
					c_stateN1.jugador.brujula = sensores.sentido;

					c_stateN1.colaborador.f = sensores.CLBposF;
					c_stateN1.colaborador.c = sensores.CLBposC;
					c_stateN1.colaborador.brujula = sensores.CLBsentido;
					c_stateN1.colaboradorVisto = verColaborador(c_stateN1.jugador,c_stateN1.colaborador);

					plan = AnchuraSoloColaborador(c_stateN1, goal, mapaResultado);
					if (plan.size() > 0){
						hayPlan = true;
						VisualizarPlanN1(c_stateN1, plan);
					}
					break;
				case 2:
					c_stateN2.jugador.f = sensores.posF;
					c_stateN2.jugador.c = sensores.posC;
					c_stateN2.jugador.brujula = sensores.sentido;

					c_stateN2.colaborador.f = sensores.CLBposF;
					c_stateN2.colaborador.c = sensores.CLBposC;
					c_stateN2.colaborador.brujula = sensores.CLBsentido;
					plan = DijkstraSoloJugador(c_stateN2,goal,mapaResultado);
					if (plan.size() > 0){
						hayPlan = true;
						VisualizarPlanN2(c_stateN2, plan);
					}
					break;
				case 3:
					c_stateN3.jugador.f = sensores.posF;
					c_stateN3.jugador.c = sensores.posC;
					c_stateN3.jugador.brujula = sensores.sentido;

					c_stateN3.colaborador.f = sensores.CLBposF;
					c_stateN3.colaborador.c = sensores.CLBposC;
					c_stateN3.colaborador.brujula = sensores.CLBsentido;
					plan = AEstrellaSoloColaborador(c_stateN3,goal,mapaResultado);
					if (plan.size() > 0){
						hayPlan = true;
						VisualizarPlanN3(c_stateN3, plan);
					}
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
