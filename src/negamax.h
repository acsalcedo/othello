#include "othello_cut.h"
#include <climits>

using namespace std;

static int negamax(state_t node, int depth, int color) {

    if (depth == 0 || node.terminal()) 
        return color * node.value();
    
    int score = INT_MIN;

    vector<int> moves = node.get_valid_moves(color);
    
    vector<int>::iterator children = moves.begin();

    int value;

    bool player = color == -1 ? 1 : 0;

    for (children; children != moves.end(); children++) {
        
        value = negamax(node.move(player,*children),depth-1,-color);
        
        score = max(score,-value);
    }
    return score;
}


static int negamax_ab(state_t node, int depth, int alpha, int beta, int color) {

    if (depth == 0 || node.terminal())
        return color * node.value();

    int score = INT_MIN;

    vector<int> moves = node.get_valid_moves(color);
    
    vector<int>::iterator children = moves.begin();

    int value;

    bool player = color == -1 ? 1 : 0;

    for (children; children != moves.end(); children++) {
    
        value = negamax_ab(node.move(player,*children),depth-1,-beta,-alpha,-color);
        score = max(score,-value);

        alpha = max(alpha,-value);

        if (alpha >= beta)
            break;
    }
    return score;
}