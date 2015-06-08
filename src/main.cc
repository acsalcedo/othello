
#include "negamax.h"
#include "scout.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <iomanip>

#define MAX_DEPTH 12

using namespace std;

int main(int argc, const char **argv) {
    
    ofstream file;

    // Verificamos los parametros de entrada
    if (argc < 2 || atoi(argv[1]) > 4 || atoi(argv[1]) < 1) {
        cout << "Usage: ./othello <algorithmNumber> <fileName>" << endl;
        cout << "algorithmNumber: " << endl;
        cout << "\t1: negamax\n\t2: negamax-AB\n\t3: scout\n\t4: negascout\n";
        cout << "fileName is optional" << endl;
        return 1;

    // Si no se ingreso un nombre de archivo
    } else if (argc < 3) {
        if (atoi(argv[1]) > 4)
        cout << "File name not given" << endl;
        cout << "Default name will be result.txt" <<endl;
        file.open("../results/result.txt");

    // Si se ingreso correctamente un nombre de archivo
    } else {
        static char fileName[30];
        sprintf(fileName, "../results/%s", argv[2]);
        file.open(fileName);
    }
   
    // Se verifica si hubo un error abriendo el archivo
    if (!file.is_open()) {
        cout << "Error opening file.\n";
        return 1;
    }

    state_t state;
    std::vector<state_t> PV_states;
    
    // Almacenamos los estados de la variacion principal
    for(int i = 0; PV[i] != -1; ++i) {

        bool player = i % 2 == 0;
        int pos = PV[i];

        PV_states.push_back(state);
        state = state.move(player, pos);
    }    

    PV_states.push_back(state);

    int algorithm = atoi(argv[1]);

    std::vector<state_t>::reverse_iterator it_states = PV_states.rbegin();

    int color = 1; // black = 1 (max), white = -1 (min)
    int depth = 0;
    bool player = 1; // black = 0, white = 1

    clock_t t;
    int expandidos;
    int generados;

    file << "depth\t   value\t  time\t\tgenerated\texpanded(leaf)" << endl;

    // Para cada estado de la variacion principal, usamos el algoritmo escogido
    for (it_states; it_states != PV_states.rend() && depth < MAX_DEPTH; it_states++) {

        file << depth;
        color *= -1;
        player = !player;
        expandidos = 0;
        generados = 0;
        switch (algorithm) {
            // Caso 1: Algoritmo negamax
            case 1:

                t = clock();
                file << setw(15) << -negamax(*(it_states),depth,color,expandidos,generados);
                t = clock() - t;
                break;

            // Caso 2: Algoritmo negamax alpha beta
            case 2:
                
                t = clock();
                file << setw(15) << -negamax_ab(*(it_states),depth,INT_MIN+1,INT_MAX,color,expandidos,generados);
                t = clock() - t;
                break;

            // Caso 3: Algoritmo scout
            case 3:
                
                t = clock();
                file << setw(15) << scout(*(it_states),depth,player,expandidos,generados);
                t = clock() - t;
                break;

            // Caso 4: Algoritmo negascout
            case 4:

                t = clock();
                file << setw(15) << -negascout(*(it_states),depth,INT_MIN+1,INT_MAX,color,expandidos,generados);
                t = clock() - t;
                break;
        }

        depth++;
        file << setw(20) << ((float)t)/CLOCKS_PER_SEC << std::scientific << "\t" << generados << "\t\t" << expandidos << endl;
    }

    file.close();
    return 0;
}
