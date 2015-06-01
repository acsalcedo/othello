#ifndef HEADER_SCOUT_H
#define HEADER_SCOUT_H

#include "othello_cut.h"
#include <climits>

using namespace std;

//TODO agregar jugador?
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

// TODO - Revisar bien si es asi 
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