#ifndef HEADER_SCOUT_H
#define HEADER_SCOUT_H

#include "othello_cut.h"
#include <climits>

using namespace std;

/**
 * testGreater
 * @brief Verifica si vale la pena revisar una rama para hacer prunning. Verifica mayor que
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la búsqueda.
 * @param value Valor h del nodo 
 * @param player Jugador actual.
 * @return bool Si vale la pena revisar la rama o no.
 **/
static bool testGreater(state_t node, int depth, int value, bool player) {

    if (depth == 0 || node.terminal())
        return node.value() > value;

    vector<int> moves = node.get_valid_moves(player);
    
    vector<int>::iterator children = moves.begin();

    for(children;children != moves.end(); children++) {

        if (!player && testGreater(node.move(player,*children),depth-1,value,!player))
            return true;
        if (player && !testGreater(node.move(player,*children),depth-1,value,!player))
            return false;
    }   
    return !player ? false : true;
}

/**
 * testLesser
 * @brief Verifica si vale la pena revisar una rama para hacer prunning. Verifica menor que
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la búsqueda.
 * @param value Valor h del nodo 
 * @param player Jugador actual.
 * @return bool Si vale la pena revisar la rama o no.
 **/
static bool testLesser(state_t node, int depth, int value, bool player) {

    if (depth == 0 || node.terminal())
        return node.value() < value;

    vector<int> moves = node.get_valid_moves(player);
    
    vector<int>::iterator children = moves.begin();

    for(children;children != moves.end(); children++) {

        if (!player && !testLesser(node.move(player,*children),depth-1,value,!player))
            return false;
        if (player && testLesser(node.move(player,*children),depth-1,value,!player))
            return true;
    }   
    return player ? false : true;
}

/**
 * scout
 * @brief Algoritmo que hace uso de los tests para podar el árbol de juego. 
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la búsqueda.
 * @param player Jugador actual.
 * @return score del camino óptimo.
 **/
static int scout(state_t node, int depth, bool player) {

    if (depth == 0 || node.terminal())  
        return node.value();

    int score = 0;

    vector<int> moves = node.get_valid_moves(player);
    
    vector<int>::iterator children = moves.begin();

    for(children; children != moves.end(); children++) {    

        state_t child = node.move(player,*children);
        
        if (children == moves.begin())
            score = scout(child,depth-1,!player);
        
        else {
            
            if (!player && testGreater(child,depth-1,score,!player))
                score = scout(child,depth-1,!player);

            if (player && testLesser(child,depth-1,score,!player))
                score = scout(child,depth-1,!player);
        }
    }
    return score;
}

/**
 * negascout
 * @brief Verifica usando únicamente el menor igual <.
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la búsqueda.
 * @param alpha Valor de la ventana a revisar
 * @param beta  Valor de la ventana a revisar
 * @param player Jugador actual.
 * @return bool Si vale la pena revisar la rama o no.
 **/
static int negascout(state_t node, int depth, int alpha, int beta, int color) {

    if (depth == 0 || node.terminal()) 
        return color * node.value();

    int score = 0;

    bool player = color == -1 ? 1 : 0;

    vector<int> moves = node.get_valid_moves(player);
    
    vector<int>::iterator children = moves.begin();

    for(children; children != moves.end(); children++) {    
    
        state_t child = node.move(player,*children);
        
        if (children == moves.begin())
            score = -negascout(child,depth-1,-beta,-alpha,-color);  
        
        else {
            score = -negascout(child,depth-1,-alpha-1,-alpha,-color);

            if (alpha < score && score < beta)
                score = -negascout(child,depth-1,-beta,-score,-color);  
        }

        alpha = max(alpha,score);
        
        if (alpha >= beta)
            break;
    }
    return alpha;
}

#endif 