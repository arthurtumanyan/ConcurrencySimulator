#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <regex>
#include "ConcurrencySimulator.h"

vector<string> decode(string s) {
    vector<string> ret;
    stringstream sin(s);
    while (sin >> s){
        ret.push_back(s);
    }
    return ret;
}

ConcurrencySimulator::ConcurrencySimulator(int testcase) {
    nTestCase = testcase;
    nProgramCount = 0;
    nQuantum = 0;
    bLocked = false;
    aUnitTime.fill(0);
    nVars.fill(0);
    sIFile.clear();
}

bool ConcurrencySimulator::GetInputParameters() {
    string sParams;
    vector<string> tokens;
    getline(hInputHandle, sParams);

    /* Replacing multiple white spaces with one */
    regex re("\\s{2,}");
    string fmt = " ";
    sParams = regex_replace(sParams, re, fmt);

    /* Splitting the line which contains input parameters separated by space */
    istringstream iss(sParams);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    if (7 != tokens.size()) {
        cout << "Huston, we have a problem! Input parameters count should be 7" << endl;
        return false;
    }
    nProgramCount = atoi(tokens.at(0).c_str());
    aUnitTime[0] = atoi(tokens.at(1).c_str());
    aUnitTime[1] = atoi(tokens.at(2).c_str());
    aUnitTime[2] = atoi(tokens.at(3).c_str());
    aUnitTime[3] = atoi(tokens.at(4).c_str());
    aUnitTime[4] = atoi(tokens.at(5).c_str());
    nQuantum = atoi(tokens.at(6).c_str());
#ifdef DEBUG 
    cout << "*** DEBUG ***" << endl;
    cout << "Program count: " << nProgramCount << endl;
    for (int i = 0; i < aUnitTime.size(); i++) {
        cout << "UnitTime[" << i << "]: " << aUnitTime[i] << endl;
    }
    cout << "Quantum: " << nQuantum << endl;
    cout << "*** END OF DEBUG ***" << endl << endl;
#endif   
    return true;
}

void ConcurrencySimulator::RunProgram() {
    int i = 0;
    int nPid = 0;

    if (GetInputParameters()) {
        while (nTestCase--) {
            for (i = 0; i < nProgramCount; i++) {
                ReadStatements(i);
                readyQ.push_back(i);
                Memory[i].counter = 0;
            }
#ifdef DEBUG 
            cout << "*** DEBUG ***" << endl;
            for (i = 0; i < nProgramCount; i++) {
                for (int j = 0; j < Memory[i].statement.size(); j++) {
                    cout << Memory[i].statement.at(j) << endl;
                }
            }
            cout << "*** END OF DEBUG ***" << endl;
#endif
            nVars.fill(0);
            bLocked = false;
            while (!readyQ.empty()) {
                nPid = readyQ.front();
                readyQ.pop_front();
                ExecuteStatement(nPid);
            }
        }
    }
#ifdef DEBUG 
    cout << endl << "Simulation completed young padawan." << endl << "May the force be with you..." << endl;
#endif
}

void ConcurrencySimulator::ReadStatements(int pid) {
    string line;

    while (getline(hInputHandle, line)) {
        if (line.size() > 0) {
            Memory[pid].statement.push_back(line);
            if (0 == line.compare("end")) {
                break;
            }
        }
    }
}

void ConcurrencySimulator::ExecuteStatement(int pid) {
    int q = nQuantum;
    while (q > 0) {
        vector<string> args = decode(Memory[pid].statement[Memory[pid].counter]);
        if (args[0].length() == 1) {
            nVars[args[0][0] - 'a'] = atoi((args[2]).c_str());
            q -= aUnitTime[0];
        } else if (0 == args[0].compare("print")) {
            cout << (pid + 1) << ": " << nVars[args[1][0] - 'a'] << endl;
            q -= aUnitTime[1];
        } else if (0 == args[0].compare("lock")) {
            if (bLocked) {
                blockQ.push_back(pid);
                return;
            }
            bLocked = true;
            q -= aUnitTime[2];
        } else if (0 == args[0].compare("unlock")) {
            bLocked = false;
            if (!blockQ.empty()) {
                readyQ.push_front(blockQ.front());
                blockQ.pop_front();
            }
            q -= aUnitTime[3];
        } else if (0 == args[0].compare("end")) {
            return;
        }
        Memory[pid].counter++;
    }
    readyQ.push_back(pid);
}

bool ConcurrencySimulator::SetInputFile(string iFileName) {
    sIFile = iFileName;
    hInputHandle.open(sIFile.c_str());
    if (!hInputHandle) {
        std::cerr << "Cannot open the input file : " << sIFile << endl;
        return false;
    }
    return true;
}

ConcurrencySimulator::~ConcurrencySimulator() {
    if (hInputHandle) {
        hInputHandle.close();
    }
}

