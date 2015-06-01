
#include "negamax.h"
#include "scout.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <iomanip>

using namespace std;

int main(int argc, const char **argv) {
    
    if (argc < 3 || atoi(argv[1]) > 4 || atoi(argv[1]) < 1) {
        cout << "Usage: ./othello <algorithmNumber> <fileName>" << endl;
        cout << "algorithmNumber: " << endl;
        cout << "\t1: negamax\n\t2: negamax-AB\n\t3: scout\n\t4: negascout\n";
        return 1;
    }

    ofstream file;

    static char fileName[30];

    sprintf(fileName, "../results/%s", argv[2]);

    file.open(fileName);

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
    int player = 1;

    clock_t t;

    for (it_states; it_states != PV_states.rend() && depth < 10; it_states++) {

        file << depth;
        color *= -1;
        player = !player;
        
        switch (algorithm) {
            case 1:

                t = clock();

                file << setw(15) << negamax(*(it_states),depth,color);

                t = clock() - t;

                break;
            case 2:
                
                t = clock();

                file << setw(15) << negamax_ab(*(it_states),depth,INT_MIN,INT_MAX,color);

                t = clock() - t;
                
                break;
            case 3:
                
                t = clock();

                file << setw(15) << scout(*(it_states),depth,player);

                t = clock() - t;
                break;
            case 4:
                file << setw(15) << negascout(*(it_states),depth,INT_MIN,INT_MAX,color);
                break;

        }
        depth++;

        file << setw(15) << ((float)t)/CLOCKS_PER_SEC << std::scientific << endl;
    }

    file.close();
    return 0;
}

