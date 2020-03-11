#ifndef CONCURRENCYSIMULATOR_H
#define CONCURRENCYSIMULATOR_H

#include <queue>
#include <string>
#include <array>
#include<vector>
using namespace std;

#define MAXVARS 26
#define MAXM 32
#define MAXN 1024

typedef struct Memory {
    array<string, MAXM> s;
    int counter;
}MEMORY;

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


public:
    ConcurrencySimulator(int testcase);
    void RunProgram();
    void SetInputFilename(string iFileName);
    void SetOutputFilename(string oFileName);
    virtual ~ConcurrencySimulator();
private:
    void MemoryRead(int cellNo);
    void MemoryWrite(int cellNo);
    void ExecuteStatement(int pid);
    bool ReadStatements();
};

#endif /* CONCURRENCYSIMULATOR_H */

