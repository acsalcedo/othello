
#include "negamax.h"
#include "scout.h"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int main(int argc, const char **argv) {
    
    if (argc < 3 || atoi(argv[1]) > 4 || atoi(argv[1]) < 1) {
        cout << "Usage: ./othello <algorithmNumber> <fileName>" << endl;
        cout << "algorithmNumber: " << endl;
        cout << "\t1: negamax\n\t2: negamax-AB\n\t3: scout\n\t4: negascout\n";
        return 1;
    }

    ofstream file;
    file.open(argv[2]);

    if (!file.is_open()) {
        cout << "Error opening file.\n";
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

    //ITERACION DE NIVELES
    // COLOR: black = 1 (max), white = -1 (min)

    std::vector<state_t>::reverse_iterator it_states = PV_states.rbegin();

    int color = -1;
    int depth = 0;

    clock_t t;

    for (it_states; it_states != PV_states.rend() && depth < 15; it_states++) {

        file << depth << "\t";
        color *= -1;
        
        switch (algorithm) {
            case 1:

                t = clock();

                file << negamax(*(it_states),depth,color) << "\t";

                t = clock() - t;

                break;
            case 2:
                
                t = clock();

                file << negamax_ab(*(it_states),depth,INT_MIN,INT_MAX,color) << "\t";

                t = clock() - t;
                
                break;
            case 3:
                //scout
                break;
            case 4:
                //negascout
                break;

        }
        depth++;

        file << ((float)t)/CLOCKS_PER_SEC << endl;
    }

    file.close();
    return 0;
}

