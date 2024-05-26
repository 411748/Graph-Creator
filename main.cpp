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

  void removeVertex(char label) {
    int index = -1;
    for (int i = 0; i <= numVertices; i++) {
      if (adjMatrix[i][0] == label) {
        index = i;
        break;
      }
    }
    if (index == -1) return;

    for (int i = 0; i <= numVertices; i++) {
      for (int j = 0; j <= numVertices; j++) {
        if (i >= index || j >= index) {
	  if (i == j) {
	    adjMatrix[i][j] = 0;
          } else if (i <= 1) {
            adjMatrix[i][j] = adjMatrix[i][j+1];
          } else if (j <= 1) {
            adjMatrix[i][j] = adjMatrix[i+1][j];
          } else {
            adjMatrix[i][j] = adjMatrix[i+1][j+1];
          }
        }
      }
    }
    adjMatrix[0][0] = 32;
    numVertices--;
  }

  void addEdge(char from, char to, int weight) {
    for (int i = 0; i <= numVertices; i++) {
      for (int j = 0; j <= numVertices; j++) {
	if (adjMatrix[i][0] == from && adjMatrix[j][0] == to) {
	  adjMatrix[i][j] = weight;
        }
      }
    }
  }
};

int main() {
  Graph g;
  while (true) {
    char command[10];
    char label1, label2;
    int weight;
    cout << "What would you like to do (addv, removev, adde, removee, path, print, or quit)?" << endl;
    cin >> command;

    if (strcmp(command, "addv") == 0) {
      cout << "Enter label for new vertex (1 char):" << endl;
      cin >> label1;
      g.addVertex(label1);
    } else if (strcmp(command, "removev") == 0) {
      cout << "Enter label of vertex to remove (1 char):" << endl;
      cin >> label1;
      g.removeVertex(label1);
    } else if (strcmp(command, "adde") == 0) {
      cout << "Enter start vertex:" << endl;
      cin >> label1;
      cout << "Enter end vertex:" << endl;
      cin >> label2;
      cout << "Enter weight:" << endl;
      cin >> weight;
      g.addEdge(label1, label2, weight);
    }
  }
  return 0;
}
