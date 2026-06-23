#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Graph
{
private:
    int v;

public:
    std::vector<std::vector<int>> adj;
    std::vector<int> wallNodes;
    
    Graph(int vertices)
        : v(vertices)
    {
        adj.resize(v);
    }

    void addWall(int w)
    {
        wallNodes.push_back(w);
    }

    void addEdge(int u, int v)
    {
        adj[u].push_back(v);
    }

    void createGrid(int rows, int cols, std::vector<int>& wallCheck)
    {
        for (int row = 0; row < rows; ++row) 
        {
            for (int col = 0; col < cols; ++col)
            {
                int current = row * cols + col;

                if (std::find(wallCheck.begin(), wallCheck.end(), current) != wallCheck.end()) { continue; }

                if (row > 0) { addEdge(current, (row - 1) * cols + col); } // Up
                if (row < rows - 1) { addEdge(current, (row + 1) * cols + col); } // Down
                if (col > 0) { addEdge(current, row * cols + (col - 1)); } // Left
                if (col < cols - 1) { addEdge(current, row * cols + (col + 1)); } // Right
                //diagonals
                if (row > 0 && col > 0) { addEdge(current, (row - 1) * cols + (col - 1)); } // Up-Left
                if (row > 0 && col < cols - 1) { addEdge(current, (row - 1) * cols + (col + 1)); } // Up-Right
                if (row < rows - 1 && col > 0) { addEdge(current, (row + 1) * cols + (col - 1)); } // Down-Left
                if (row < rows - 1 && col < cols - 1) { addEdge(current, (row + 1) * cols + (col + 1)); } // Down-Right
            }
        }
    }

    void printAdjList(const std::vector<int>& vec)
    {
        for (int v : vec)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    void bfs(int start, int end)
    {
        std::vector<bool> visited(v, false);
        std::vector<int> cameFrom(v, -1);
        std::queue<int> q;


        visited[start] = true;
        q.push(start);

        while (!q.empty())
        {
            int current = q.front();
            q.pop();

            if (current == end) { break; }

            for (int neighbor : adj[current])
            {
                if (!visited[neighbor])
                {
                    visited[neighbor] = true;
                    cameFrom[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }

        std::vector<int> path;
        int current = end;
        while (current != -1)
        {
            path.push_back(current);
            current = cameFrom[current];
        }

        std::reverse(path.begin(), path.end());
        std::cout << "Start" << std::endl;
        for (int node : path)
        {
            std::cout << node << std::endl;
        }
        std::cout << "End of path" << std::endl;

    }

};



const int rows = 10;
const int cols = 10;

int main() 
{
    int totalNodes = rows * cols;
    Graph g(totalNodes);
    std::vector<int> collisionNodes = {30,31,32,22,12,13,14,6,16,26,36,35,34,44,43,53,63,73,83,96,86,76,66,67};
    
    for (int wNode : collisionNodes)
    {
        g.wallNodes.push_back(wNode);
    }

    g.createGrid(rows, cols, collisionNodes);

    g.printAdjList(g.adj[17]);

    g.bfs(21, 88);

    return 0;
}
