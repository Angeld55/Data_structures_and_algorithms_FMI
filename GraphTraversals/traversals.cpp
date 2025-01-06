#include <iostream>
#include <vector>
#include <queue>
#include <stack>


class Graph
{
    std::vector<std::vector<int>> adj;
    bool oriented;

    void dfs_help_rec(size_t start, std::vector<bool>& visited, std::vector<size_t>& result) const;
    bool contains_cycle_rec(size_t start, std::vector<bool>& visited, std::vector<bool>& stack) const;

public:
    Graph(size_t vertexCount, bool isOriented);
    void addEdge(size_t start, size_t end);

    void BFS(size_t start) const;
    void DFS_ITER(size_t start) const;
    void DFS_REC(size_t start) const;
    int BFS_shortest_path(size_t start, size_t end) const;
    int BFS_shortest_path_vector(size_t start, size_t end) const;

    bool containsCycle() const;

};

Graph::Graph(size_t vertexCount, bool isOriented) : adj(vertexCount), oriented(isOriented)
{}

void Graph::addEdge(size_t start, size_t end)
{
    adj[start].push_back((int)end);
    if (!oriented)
        adj[end].push_back((int)start);
}

int Graph::BFS_shortest_path(size_t start, size_t end) const
{
    if (start == end) return 0;

    std::vector<bool> visited(adj.size(), false);
    std::queue<size_t> q;
    q.push(start);
    visited[start] = true;

    int dist = 0;

    while (!q.empty())
    {
        size_t currentLevelSize = q.size();
        for (size_t i = 0; i < currentLevelSize; i++)
        {
            size_t currentVertex = q.front();
            q.pop();

            for (auto neighbor : adj[currentVertex])
            {
                if (visited[neighbor])
                    continue;
                if (neighbor == end)
                    return dist + 1;

                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
        dist++;
    }

    return -1;
}

int Graph::BFS_shortest_path_vector(size_t start, size_t end) const
{
    std::vector<size_t> currLevel = { start };
    size_t dist = 0;
    std::vector<bool> visited(adj.size(), false);

    while (!currLevel.empty())
    {
        std::vector<size_t> nextLevel;

        for (size_t currNode : currLevel)
        {
            for (size_t currNodeChild : adj[currNode])
            {
                if (visited[currNodeChild])
                    continue;
                visited[currNodeChild] = true;
                if (currNodeChild == end)
                    return dist + 1;
                else
                    nextLevel.push_back(currNodeChild);
            }
        }
        currLevel.swap(nextLevel);
    }
    return -1;
}

void Graph::DFS_ITER(size_t start) const
{
    std::vector<bool> visited(adj.size(), false);

    std::stack<size_t> s;
    s.push(start);

    while (!s.empty())
    {
        size_t current = s.top();
        s.pop();

        if (visited[current])
            continue;

        visited[current] = true;
        std::cout << current << " ";

        for (auto neighbor : adj[current])
        {
            s.push(neighbor);
        }
    }
}

void Graph::dfs_help_rec(size_t curr, std::vector<bool>& visited, std::vector<size_t>& result) const
{
    visited[curr] = true;
    std::cout << curr << " ";
    for (auto neighbor : adj[curr])
    {
        if (!visited[neighbor])
            dfs_help_rec(neighbor, visited, result);
    }
}

void Graph::DFS_REC(size_t start) const
{
    std::vector<bool> visited(adj.size(), false);
    std::vector<size_t> result;

    dfs_help_rec(start, visited, result);
}

bool Graph::contains_cycle_rec(size_t start, std::vector<bool>& visited, std::vector<bool>& stack) const
{
    if (!visited[start])
    {
        visited[start] = true;
        stack[start] = true;

        for (auto neighbor : adj[start])
        {
            if (!visited[neighbor] && contains_cycle_rec(neighbor, visited, stack))
                return true;
            else if (stack[neighbor])
                return true;
        }
    }
    stack[start] = false;
    return false;
}

bool Graph::containsCycle() const
{
    std::vector<bool> visited(adj.size(), false);
    std::vector<bool> inStack(adj.size(), false);

    for (size_t i = 0; i < adj.size(); i++)
    {
        if (contains_cycle_rec(i, visited, inStack))
            return true;
    }
    return false;
}


int main()
{
    Graph g(9, false);

    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 3);
    g.addEdge(3, 2);

    g.addEdge(2, 1);
    g.addEdge(4, 2);
    g.addEdge(5, 2);
    g.addEdge(6, 1);

    g.addEdge(4, 6);

    g.BFS(0);

    return 0;
}
