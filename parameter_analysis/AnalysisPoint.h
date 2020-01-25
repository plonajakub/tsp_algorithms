#ifndef PEA_P1_ANALYSISPOINT_H
#define PEA_P1_ANALYSISPOINT_H


#include <string>

template<class T>
struct AnalysisPoint {
    int instanceSize;
    double time;
    int fileSolution;
    int algorithmBeastSolution;
    int algorithmMeanSolution;

    std::string parameterName;
    // T = numeric value
    T parameterValue;

    AnalysisPoint()  : instanceSize(-1), time(0), fileSolution(-1), algorithmBeastSolution(-1), algorithmMeanSolution(0),
                       parameterName(""),
                       parameterValue(-1) {}
};

template<> inline
AnalysisPoint<std::string>::AnalysisPoint() : instanceSize(-1), time(0), fileSolution(-1), algorithmBeastSolution(-1),
                                              algorithmMeanSolution(0),
                                              parameterName(""),
                                              parameterValue("") {}




#endif //PEA_P1_ANALYSISPOINT_H
