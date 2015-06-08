#ifndef HEADER_SCOUT_H
#define HEADER_SCOUT_H

#include "othello_cut.h"
#include <climits>

using namespace std;

/**
 * testGreater
 * @brief Verifica si vale la pena revisar una rama para hacer prunning. Verifica mayor que
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la busqueda.
 * @param value Valor h del nodo 
 * @param player Jugador actual.
 * @return bool Si vale la pena revisar la rama o no.
 **/
static bool testGreater(state_t node, int depth, int value, bool player) {

    if (depth == 0 || node.terminal())
        return node.value() > value;

    vector<int> moves = node.get_valid_moves(player);
    vector<int>::iterator children = moves.begin();

    //Pass
    if (moves.size() == 0)
        return testGreater(node,depth,value,!player);

    for(children;children != moves.end(); children++) {

        state_t  child = node.move(player,*children);

        if (player && testGreater(child,depth-1,value,!player))
            return true;
        if (!player && !testGreater(child,depth-1,value,!player))
            return false;
    }   
    return !player;
}

/**
 * testLesser
 * @brief Verifica si vale la pena revisar una rama para hacer prunning. Verifica menor que
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la busqueda.
 * @param value Valor h del nodo 
 * @param player Jugador actual.
 * @return bool Si vale la pena revisar la rama o no.
 **/
static bool testLesser(state_t node, int depth, int value, bool player) {

    if (depth == 0 || node.terminal())
        return node.value() < value;

    vector<int> moves = node.get_valid_moves(player);
    vector<int>::iterator children = moves.begin();

    //Pass
    if (moves.size() == 0) 
        return testLesser(node,depth,value,!player);
    
    for(children;children != moves.end(); children++) {

        state_t  child = node.move(player,*children);

        if (player && !testLesser(child,depth-1,value,!player))
            return false;
        if (!player && testLesser(child,depth-1,value,!player))
            return true;
    }   
    return player;
}

/**
 * scout
 * @brief Algoritmo que hace uso de los tests para podar el arbol de juego. 
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la busqueda.
 * @param player Jugador actual.
 * @param expandidos Numero de nodos expandidos (hojas).
 * @param generados Numero de nodos generados.
 * @return score del camino óptimo.
 **/
static int scout(state_t node, int depth, bool player, int& expandidos, int& generados) {

    if (depth == 0 || node.terminal()) {  
        expandidos++;
        return node.value();
    }

    int score = INT_MIN;
    vector<int> moves = node.get_valid_moves(player);
    vector<int>::iterator children = moves.begin();

    //Pass
    if (moves.size() == 0) {
        generados++;
        return scout(node,depth,!player,expandidos,generados);
    }

    for(int i = 0; i < moves.size(); i++) {    

        state_t child = node.move(player,moves[i]);
        generados++;
        
        if (i == 0)
            score = scout(child,depth-1,!player,expandidos,generados);
        
        else {
            
            if (player && testGreater(child,depth-1,score,!player))
                score = scout(child,depth-1,!player,expandidos,generados);

            if (!player && testLesser(child,depth-1,score,!player))
                score = scout(child,depth-1,!player,expandidos,generados);
        }
    }
    return score;
}

/**
 * negascout
 * @brief Algoritmo que devuelve el valor optimo de un arbol de juego.
 * @param node Nodo con el estado actual.
 * @param depth Profundidad que falta para llegar al final de la busqueda.
 * @param alpha Lower bound de la ventana.
 * @param beta  Upper bound de la ventana. 
 * @param color Jugador actual.
 * @param expandidos Numero de nodos expandidos (hojas).
 * @param generados Numero de nodos generados.
 * @return Valor del camino optimo.
 **/
static int negascout(state_t node, int depth, int alpha, int beta, int color,int& expandidos, int& generados) {
   
    if (depth == 0 || node.terminal()) {
        expandidos++;
        return color * node.value();
    }

    bool player = color == 1;

    vector<int> moves = node.get_valid_moves(player);
    vector<int>::iterator children = moves.begin();

    int a, b, t;
   
    a = alpha;
    b = beta;
    
    //Pass
    if (moves.size() == 0) {
        generados++;
        return -negascout(node,depth,-b,-a,-color,expandidos,generados);
    }

    state_t child;
   
    for(int i = 0; i < moves.size(); i++) { 
        
        generados++;   
        child = node.move(player,moves[i]);
        
        t = -negascout(child,depth-1,-b,-a,-color,expandidos,generados);
      
        if ((t > a) && (t < beta) && (i > 0) && (depth > 1)) {
            generados++;
            a = -negascout(child,depth-1,-beta,-t,-color,expandidos,generados);
        }
        a = max(a,t);
        
        if (a >= beta)
            return a;

        b = a + 1;
   }
   return a;
}


#endif 