#include <iostream>
#include "ConcurrencySimulator.h"

int main() {
    ConcurrencySimulator CS(1); // remove testcase
    if (CS.SetInputFile("input.txt")) {
        CS.RunProgram();
    }
    return 0;
}