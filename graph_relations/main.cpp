#include <iostream>
#include <vector>
#include <algorithm>

struct Path {
    int from;
    int to;

    bool operator==( const Path& other ) const {
        return ( from == other.from ) && ( to == other.to );
    }
};

void processInput( std::vector<Path>& paths, int& vertexCount ) {
    int edges, vertices;
    std::cin >> edges >> vertices;

    if ( ( edges == 0 ) && ( vertices == 0 ) ) {
        std::cout << "For an empty graph, all relations are satisfied";
        exit( 0 );
    } else if ( ( edges == 0 ) && ( vertices != 0 ) ) {
        std::cout << "A graph without edges is antireflexive, the remaining relations are arbitrary";
        exit( 0 );
    }

    paths.reserve( edges );

    for ( int i = 0; i < edges; i++ ) {
        int from, to;
        std::cin >> from >> to;
        paths.push_back( { from, to } );
    }

    vertexCount = vertices;
}

void analyzeRelations( const int i, const int j,
 std::vector<Path>& paths, bool& transitive,
  bool& antitransitive, int& symmetricCount ) {
    if ( ( i != j ) && ( paths[ i ].to == paths[ j ].from ) && ( paths[ j ].from != paths[ j ].to ) ) {
        if ( paths[ i ].from != paths[ j ].to ) {
            if ( !( transitive && antitransitive ) ) {
                if ( std::find( paths.begin(), paths.end(), Path{ paths[ i ].from, paths[ j ].to } ) != paths.end() ) {
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

int main() {
    std::vector<Path> paths;
    int vertexCount;

    processInput( paths, vertexCount );

    int symmetricCount = paths.size();
    int reflexivityCount = vertexCount;
    bool transitive = false;
    bool antitransitive = false;

    for ( int i = 0; i < paths.size(); i++ ) {
        if ( paths[ i ].from != paths[ i ].to ) {
            for ( int j = 0; j < paths.size(); j++ ) {
                analyzeRelations( i, j, paths, transitive, antitransitive, symmetricCount );
            }
        } else {
            symmetricCount--;
            reflexivityCount--;
        }
    }

    if ( symmetricCount == 0 ) {
        std::cout << "Symmetric relation" << std::endl;
    } else if ( symmetricCount == paths.size() ) {
        std::cout << "Antisymmetric relation" << std::endl;
    } else {
        std::cout << "Non-symmetric relation" << std::endl;
    }

    if ( reflexivityCount == 0 ) {
        std::cout << "Reflexive relation" << std::endl;
    } else if ( reflexivityCount == vertexCount ) {
        std::cout << "Antireflexive relation" << std::endl;
    } else {
        std::cout << "Non-reflexive relation" << std::endl;
    }

    if ( transitive && antitransitive ) {
        std::cout << "Non-Transitive relation";
    } else if ( transitive && !antitransitive ) {
        std::cout << "Transitive relation";
    } else if ( !transitive && antitransitive ) {
        std::cout << "Antitransitive relation";
    } else {
        std::cout << "Transitive/Antitransitive/Non-Transitive relation";
    }

    return 0;
}