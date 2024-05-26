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

  void removeEdge(char from, char to) {
    for (int i = 0; i <= numVertices; i++) {
      for (int j = 0; j <= numVertices; j++) {
        if (adjMatrix[i][0] == from && adjMatrix[j][0] == to) {
          adjMatrix[i][j] = 0;
        }
      }
    }
  }

  int** createReducedMatrix() {
    int **reducedMatrix = new int*[numVertices - 1];
    for (int i = 0; i < numVertices - 1; i++) {
      reducedMatrix[i] = new int[numVertices - 1];
      for (int j = 0; j < numVertices - 1; j++) {
        reducedMatrix[i][j] = adjMatrix[i + 1][j + 1];
      }
    }
    return reducedMatrix;
  }

  void dijkstra(int** matrix, int n, int start) {
    int maxSize = numVertices - 1;
    int cost[maxSize][maxSize], distance[maxSize], pred[maxSize], visited[maxSize];
    int count, minDistance, nextNode;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cost[i][j] = (matrix[i][j] == 0) ? 999 : matrix[i][j];
      }
    }

    for (int i = 0; i < n; i++) {
      distance[i] = cost[start][i];
      pred[i] = start;
      visited[i] = 0;
    }
    distance[start] = 0;
    visited[start] = 1;
    count = 1;

    while (count < n - 1) {
      minDistance = 999;
      for (int i = 0; i < n; i++) {
        if (distance[i] < minDistance && !visited[i]) {
          minDistance = distance[i];
          nextNode = i;
        }
      }
      visited[nextNode] = 1;
      for (int i = 0; i < n; i++) {
        if (!visited[i]) {
          if (minDistance + cost[nextNode][i] < distance[i]) {
            distance[i] = minDistance + cost[nextNode][i];
            pred[i] = nextNode;
          }
        }
      }
      count++;
    }

    int destination = n - 1;
    cout << "Cost: " << distance[destination] << endl;
    cout << "Path: " << (char)adjMatrix[0][destination + 1];
    int trace = destination;
    do {
      trace = pred[trace];
      cout << "<-" << (char)adjMatrix[0][trace + 1];
    } while (trace != start);
    cout << endl;
  }

  void print() {
    for (int i = 0; i < numVertices; i++) {
      for (int j = 0; j < numVertices; j++) {
        if (i == 0 || j == 0) {
          cout << (char)adjMatrix[i][j] << "\t";
        } else {
          cout << adjMatrix[i][j] << "\t";
        }
      }
      cout << "\n\n\n";
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
      cout << "Name vertex with 1 char:" << endl;
      cin >> label1;
      g.addVertex(label1);
    } else if (strcmp(command, "removev") == 0)
{
      cout << "Enter 1 char name for vertex" << endl;
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
    } else if (strcmp(command, "removee") == 0) {
      cout << "Enter start vertex:" << endl;
      cin >> label1;
      cout << "Enter end vertex:" << endl;
      cin >> label2;
      g.removeEdge(label1, label2);
    } else if (strcmp(command, "print") == 0) {
      g.print();
    } else if (strcmp(command, "quit") == 0) {
      break;
    } else if (strcmp(command, "path") == 0) {
      cout << "Enter start vertex:" << endl;
      cin >> label1;
      cout << "Enter end vertex:" << endl;
      cin >> label2;
      g.dijkstra(g.createReducedMatrix(), (int)label2 - 63, (int)label1 - 64);
    }
  }
  return 0;
}
