
#include "othello_cut.h"
#include "negamax.h"
#include "scout.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, const char **argv) {
    
    if (argc < 2 || atoi(argv[1]) > 4 || atoi(argv[1]) < 1) {
        cout << "Usage: ./othello <algorithmNumber>" << endl;
        cout << "algorithmNumber: " << endl;
        cout << "\t1: negamax\n\t2: negamax-AB\n\t3: scout\n\t4: negascout\n";
        return 1;
    }

    state_t state;
    std::vector<state_t> PV_states;
    
    // Black moves first and is equal to 0
    for(int i = 0; PV[i] != -1; ++i) {

        bool player = i % 2 == 0;
        int pos = PV[i];

        PV_states.push_back(state);
        state = state.move(player, pos);
    }    

    PV_states.push_back(state);

    int algorithm = atoi(argv[1]);

    switch (algorithm) {
        case 1:
            //negamax
            break;
        case 2:
            //negamax-AB
            break;
        case 3:
            //scout
            break;
        case 4:
            //negascout
            break;

    }

   // std::vector<state_t>::reverse_iterator it = PV_states.rbegin();

    // black ends game
    // int i = 0;

    // for (it; it != PV_states.rend(); it++) {
        
    //     bool player = i % 2 == 0;

    //     myfile << *it;
    //     myfile << (player ? "Black" : "White") << endl;             
    //     myfile << "---------------------------------------------" << endl;
    //     myfile << "Valid states: " << endl;

    //     std::vector<int> moves = (*it).get_valid_moves(player);

    //     std::vector<int>::iterator it_children = moves.begin();

    //     for (it_children; it_children != moves.end(); it_children++) {
    //         myfile << ' ' << *it_children << endl;
    //     }
    //     myfile << "---------------------------------------------" << endl;
    //     i++;
    // }

    //myfile.close();
    // if(argc > 1) {

    //     int n = atoi(argv[1]);
    //     cout << endl << "Apply " << n << " random movements at empty board:";
    //     state = state_t();

    //     for(int i = 0; i < n; ++i) {
    //         bool player = i % 2 == 0; // black moves first
    //         int pos = state.get_random_move(player);
    //         state = state.move(player, pos);
    //         cout << " " << pos;
    //     }

    //     cout << endl << state;
    // }

    return 0;
}

