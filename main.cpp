#include <iostream>
#include <cstring>
using namespace std;

class Graph {
public:
  int adjMatrix[21][21];
  int numVertices;
    
  Graph() {
    numVertices = 1;
    memset(adjMatrix, 0, sizeof(adjMatrix));
    adjMatrix[0][0] = 32;
  }

  void addVertex(int label) {
    if (adjMatrix[0][0] == 0) {
      adjMatrix[0][0] = label; 
    } else {
      for (int i = 0; i <= numVertices; i++) {
        for (int j = 0; j <= numVertices; j++) {
          if (adjMatrix[i][j] == 0) {
	    if (i == 0 || j == 0) {
              adjMatrix[i][j] = label;
            } else {
              adjMatrix[i][j] = 0;
            }
          }
        }
      }
    }
  numVertices++;
  }
};

int main() {
  Graph g;
  while (true) {
    char command[10];
    char label1;
    cout << "What would you like to do (addv, removev, adde, removee, path, print, or quit)?" << endl;
    cin >> command;

    if (strcmp(command, "addv") == 0) {
      cout << "Enter label for new vertex (1 char):" << endl;
      cin >> label1;
      g.addVertex(label1);
    }
  }
  return 0;
}
