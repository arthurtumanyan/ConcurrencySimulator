#include <iostream>
#include "ConcurrencySimulator.h"

int main() {
    ConcurrencySimulator CS(1);
    if (CS.SetInputFile("input.txt")) {
        CS.RunProgram();
    }
    return 0;
}