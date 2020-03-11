#include "ConcurrencySimulator.h"

ConcurrencySimulator::ConcurrencySimulator(int testcase) {
    nTestCase = testcase;
    nProgramCount = 0;
    nQuantum = 0;
    bLocked = false;
    aUnitTime.fill(0);
    nVars.fill(0);
    //sMemory.clear();
    sIFile.clear();
    sOFile.clear();
}

void ConcurrencySimulator::RunProgram() {
    int i = 0;
    int nPid = 0;
    while (nTestCase--) {
        /* Read statements and other info from input file */
        if (ReadStatements()) {
            for (i = 0; i < nProgramCount; i++) {
                MemoryRead(i);
            }
            for (i = 0; i < nProgramCount; i++) {
                readyQ.push_back(i);
                Memory[i].counter = 0;
            }
            bLocked = false;
            while (!readyQ.empty()) {
                nPid = readyQ.front();
                readyQ.pop_front();
                ExecuteStatement(nPid);
            }
        } else {
            /* Generate error message */
        }

    }
}

bool ConcurrencySimulator::ReadStatements() {
    return true;
}

void ConcurrencySimulator::ExecuteStatement(int pid) {
}

void ConcurrencySimulator::SetInputFilename(string iFileName) {
    sIFile = iFileName;
}

void ConcurrencySimulator::SetOutputFilename(string oFileName) {
    sOFile = oFileName;
}

void ConcurrencySimulator::MemoryRead(int cellNo) {
}

void ConcurrencySimulator::MemoryWrite(int cellNo) {

}

ConcurrencySimulator::~ConcurrencySimulator() {

}

