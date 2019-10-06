#include "IGraph.h"

std::ostream &operator<<(std::ostream &ostr, const IGraph &graph) {
    ostr << graph.toString();
    return ostr;
}