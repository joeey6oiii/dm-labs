#include <iostream>
#include <vector>
#include <algorithm>


struct Path
{
    int from;
    int to;

    bool operator==(const Path& other) const {
        return (from == other.from) && (to == other.to);
    }
};


bool checkEdgesVertices(int edges, int vertices)
{
    if ((edges == 0) && (vertices == 0)) {
        std::cout << "For an empty graph, all relations are satisfied";
        return false;
    } else if ((edges == 0) && (vertices != 0)) {
        std::cout << "A graph without edges is antireflexive, the remaining relations are arbitrary";
        return false;
    }
    return true;
}


bool processInput(std::vector<Path>& paths, 
                  int& vertexCount)
{
    int edges, vertices;
    std::cin >> edges >> vertices;

    if (checkEdgesVertices(edges, vertices))
    {
        paths.reserve(edges);
        for (int i = 0; i < edges; i++) {
            int from, to;
            std::cin >> from >> to;
            paths.push_back({from, to});
        }

        vertexCount = vertices;
    } 
    else
    {
        return false;
    }

    return true;
}


void analyzeRelations(const int i, const int j, 
                      std::vector<Path>& paths, bool& transitive, 
                      bool& antitransitive, int& symmetricCount)
{
    if ((i != j) && (paths[i].to == paths[j].from) && (paths[j].from != paths[j].to)) {
        if (paths[i].from != paths[j].to) {
            if (!(transitive && antitransitive)) {
                if (std::find(paths.begin(), paths.end(), Path{paths[i].from, paths[j].to}) != paths.end()) {
                    transitive = true;
                } else {
                    antitransitive = true;
                }
            }
        } else {
            symmetricCount--;
        }
    }
}


void findRelations(std::vector<Path>& paths, bool& transitive, 
                   bool& antitransitive, int& symmetricCount, 
                   int& reflexivityCount)
{
    for (int i = 0; i < paths.size(); i++) {
        if (paths[i].from != paths[i].to) {
            for (int j = 0; j < paths.size(); j++) {
                analyzeRelations(i, j, paths, transitive, antitransitive, symmetricCount);
            }
        } else {
            symmetricCount--;
            reflexivityCount--;
        }
    }
}


void printSymmetric(const int symmetricCount, 
                    const std::vector<Path> paths)
{
    if (symmetricCount == 0) {
        std::cout << "Symmetric relation" << std::endl;
    } else if (symmetricCount == paths.size()) {
        std::cout << "Antisymmetric relation" << std::endl;
    } else {
        std::cout << "Non-symmetric relation" << std::endl;
    }
}


void printReflexivity(const int reflexivityCount, 
                      const int vertexCount)
{
    if (reflexivityCount == 0) {
        std::cout << "Reflexive relation" << std::endl;
    } else if (reflexivityCount == vertexCount) {
        std::cout << "Antireflexive relation" << std::endl;
    } else {
        std::cout << "Non-reflexive relation" << std::endl;
    }
}


void printTransitivity(const bool transitive, 
                       const bool antitransitive)
{
    if (transitive && antitransitive) {
        std::cout << "Non-Transitive relation";
    } else if (transitive && !antitransitive) {
        std::cout << "Transitive relation";
    } else if (!transitive && antitransitive) {
        std::cout << "Antitransitive relation";
    } else {
        std::cout << "Transitive/Antitransitive/Non-Transitive relation";
    }
}


int main(int argc, char *argv[])
{   
    do
    {
        std::cout << ">> Waiting for input >>" << std::endl;

        std::vector<Path> paths;
        int vertexCount = 0;

        if (processInput(paths, vertexCount))
        {
            int symmetricCount = paths.size();
            int reflexivityCount = vertexCount;
            bool transitive = false;
            bool antitransitive = false;

            findRelations(paths, transitive, 
                        antitransitive, symmetricCount, 
                        reflexivityCount);

            printSymmetric(symmetricCount, paths);
            printReflexivity(reflexivityCount, vertexCount);
            printTransitivity(transitive, antitransitive);
        }

        std::cout << std::endl;
    } 
    while (argc > 1);

    return 0;
}