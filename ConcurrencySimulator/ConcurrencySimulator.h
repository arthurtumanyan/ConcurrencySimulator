#ifndef CONCURRENCYSIMULATOR_H
#define CONCURRENCYSIMULATOR_H

#include <queue>
#include <string>
#include <array>
#include<vector>
#include <fstream>
using namespace std;

#define MAXVARS 26
#define MAXN 1024

typedef struct Memory {
    vector<string> statement;
    int counter;
} MEMORY;

class ConcurrencySimulator {
public:
    int nTestCase;

private:
    int nProgramCount;
    int nQuantum;
    array<int, 5> aUnitTime;
    array<int, MAXVARS> nVars;
    deque<int> readyQ, blockQ;
    bool bLocked;
    MEMORY Memory[MAXN];
    string sIFile;
    string sOFile;
    ifstream hInputHandle;


public:
    ConcurrencySimulator(int testcase);
    void RunProgram();
    bool SetInputFile(string iFileName);
 
    virtual ~ConcurrencySimulator();
private:
    void ExecuteStatement(int pid);
    void ReadStatements(int pid);
    bool GetInputParameters();
};

#endif /* CONCURRENCYSIMULATOR_H */

