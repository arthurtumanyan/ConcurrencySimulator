#include <iostream>
#include <cstdio>
#include <getopt.h>
#include "ConcurrencySimulator.h"

void usage(char *name) {
    cout << "Usage: " << name << " [-d] -c|--count <simulations number> -f|--file <input filename>" << endl;
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {

    int c;
    int nSimulationsCount = -1;
    bool bDebug;
    string sFilename = "";

    if(argc <= 1){
        usage(argv[0]);
    }
    
    while (1) {
        int option_index = 0;
        static struct option long_options[] = {
            {"debug", optional_argument, 0, 'd'},
            {"count", required_argument, 0, 'c'},
            {"file", required_argument, 0, 'f'},
            {0, 0, 0, 0}
        };

        c = getopt_long(argc, argv, "dc:f:", long_options, &option_index);
        if (c == -1) {
            break;
        }
        switch (c) {
            case 'd':
                bDebug = true;
                break;
            case 'c':
                nSimulationsCount = atoi(optarg);
                break;
            case 'f':
                sFilename.assign(optarg);
                break;
            default:
                usage(argv[0]);
        }
    }
    if(0 > nSimulationsCount || sFilename.empty()){
        usage(argv[0]);
    }
    
    ConcurrencySimulator CS(nSimulationsCount, bDebug, sFilename); /* Initialize object */
    CS.RunSimulation(); /* Run simulation */

    return 0;
}