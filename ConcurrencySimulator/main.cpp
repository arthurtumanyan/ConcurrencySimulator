#include "ConcurrencySimulator.h"

int main(){
    ConcurrencySimulator CS(1);
    CS.SetInputFilename("input.txt");
    CS.SetOutputFilename("output.txt");
    CS.RunProgram();
    return 0;
}