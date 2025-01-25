#include <iostream>
#include <vector>
#include <queue>
#include <stack>

// <X,4>    --4-->X

class Graph
{
    std::vector<std::vector<std::pair<int, int>>> adj;
    bool oriented;

public:
    Graph(size_t vertexCount, bool isOriented);
    void addEdge(size_t start, size_t end, int weight);

    size_t shortestPath(size_t start, size_t end, std::vector<size_t>& path) const;
};

Graph::Graph(size_t vertexCount, bool isOriented) : adj(vertexCount), oriented(isOriented)
{}

void Graph::addEdge(size_t start, size_t end, int weight)
{
    adj[start].push_back({ end, weight });
    if (!oriented)
        adj[end].push_back({ start, weight });
}

size_t Graph::shortestPath(size_t start, size_t end, std::vector<size_t>& path) const
{
    struct VertexAndDist
    {
        size_t currVertex;
        size_t dist;

        bool operator<(const VertexAndDist& other) const
        {
            return dist > other.dist;
        }
    };

    std::vector<size_t> distances(adj.size(), INT_MAX);
    std::vector<bool> found(adj.size(), false);
    std::vector<size_t> prev(adj.size(), INT_MAX);
    
    distances[start] = 0;
    std::priority_queue<VertexAndDist> pq; //MAX HEAP 

    pq.push({start, 0 });

    while (!pq.empty())
    {
        auto currentClosest = pq.top();
        pq.pop();

        if (found[currentClosest.currVertex])
            continue;
        found[currentClosest.currVertex] = true;


        if (end == currentClosest.currVertex)
        {
            while (end != start)
            {
                path.push_back(end);
                end = prev[end];
            }
            path.push_back(start);

            std::reverse(path.begin(), path.end());

            return currentClosest.dist;
        }

        for (auto& edge : adj[currentClosest.currVertex])
        {
            size_t n = edge.first;
            size_t edgeWeight = edge.second;

            if (distances[n] > distances[currentClosest.currVertex] + edgeWeight)
            {
                distances[n] = distances[currentClosest.currVertex] + edgeWeight;
                pq.push({ n, distances[currentClosest.currVertex] + edgeWeight });
                prev[n] = currentClosest.currVertex;
            }
        }
    }   


    return 0;
}



int main()
{
    Graph g(3, true);
    g.addEdge(0,1, 3);
    g.addEdge(0, 2, 10);
    g.addEdge(1, 2, 4);

    std::vector<size_t> path;
    std::cout << g.shortestPath(0, 2, path) << std::endl;

    for (int i = 0; i < path.size(); i++)
        std::cout << path[i] << " ";
    return 0;
}