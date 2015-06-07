#ifndef HEADER_NEGAMAX_H
#define HEADER_NEGAMAX_H

#include "othello_cut.h"
#include <climits>

using namespace std;

/**
 * negamax
 * @brief Combina el minimax y maximax para recorrer arbol de juego desde jugador min y max.
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la busqueda.
 * @param color 1 o -1 para obtener el valor correspondiente a max o min.
 * @return score El score del camino optimo.
 **/
static int negamax(state_t node, int depth, int color, int& expandidos, int& generados) {

    if (depth == 0 || node.terminal()) {
        expandidos++;
        return color * node.value();
    }
    int score = INT_MIN;
    bool player = color == 1;
    int value;

    vector<int> moves = node.get_valid_moves(player);
    vector<int>::iterator children = moves.begin();
    
    //Pass
    if (moves.size() == 0) {
        generados++;
        score = -negamax(node,depth,-color,expandidos,generados);
    }
    
    for (children; children != moves.end(); children++) {
        generados++;
        value = -negamax(node.move(player,*children),depth-1,-color, expandidos, generados);
        
        score = max(score,value);
    }
    return score;
}

/**
 * negamax_ab
 * @brief Similar al negamax, a diferencia de que hace uso de alpha/beta prunning.
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la busqueda.
 * @param alpha Primer valor de comparacion para prunning.
 * @param beta Segundo valor de comparacion para prunning.
 * @param color 1 o -1 para obtener el valor correspondiente a max o min.
 * @return score El score del camino optimo.
 **/
static int negamax_ab(state_t node, int depth, int alpha, int beta, int color,int& expandidos, int& generados) {

    if (depth == 0 || node.terminal()) {
        expandidos++;
        return color * node.value();
    }

    int score = INT_MIN;
    bool player = color == 1;
    int value;

    vector<int> moves = node.get_valid_moves(player);
    vector<int>::iterator children = moves.begin();

    //generados = generados + moves.size();
    //Pass
    if (moves.size() == 0)
        score = -negamax_ab(node,depth,-beta,-alpha,-color,expandidos,generados);

    for (children; children != moves.end(); children++) {
        generados++;
        value = -negamax_ab(node.move(player,*children),depth-1,-beta,-alpha,-color,expandidos,generados);
        score = max(score,value);
        alpha = max(alpha,value);
        
        if (alpha >= beta)
            break;
    }
    return score;
}

#endif