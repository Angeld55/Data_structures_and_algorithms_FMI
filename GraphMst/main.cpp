#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>
#include <climits>


struct MST
{
    std::vector<std::tuple<size_t, size_t, int>> edges;
    size_t sumOfWeights;
};

class UnionFind
{
    std::vector<int> parent;
    std::vector<int> height;
public:
    UnionFind(int n)
    {
        parent.resize(n);
        height.resize(n, 0);
        for(int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int getRoot(int n)
    {
        if(parent[n] != n)
        {
            parent[n] = getRoot(parent[n]);
        }
        return parent[n];
    }
    bool areInOneSet(int n, int k)
    {
        return getRoot(n) == getRoot(k);
    }
    bool Union(int n, int k)
    {
        int root1 = getRoot(n);
        int root2 = getRoot(k);
        if(root1 == root2)
        {
            return false;
        }
        if(height[root1] < height[root2])
        {
            parent[root1] = root2;
        }
        else if(height[root1] > height[root2])
        {
            parent[root2] = root1;
        }
        else
        {
            parent[root2] = root1;
            height[root1]++;
        }
        return true;
    }
};

using Edge = std::tuple<size_t, size_t, int>;

class Graph
{
    bool isOriented;
    size_t V;
    std::vector<std::vector<std::pair<int, int>>> adj;
public:
    Graph(size_t V, bool isOriented)
    {
        this->V = V;
        this->isOriented = isOriented;
        adj.resize(V);
    }
    void addEdge(size_t start, size_t end, int weight)
    {
        adj[start].push_back(std::make_pair(end, weight));
        if(!isOriented)
        {
            adj[end].push_back(std::make_pair(start, weight));
        }
    }
    size_t dijkstra(size_t start, size_t end, std::vector<size_t>& path) const
    {
        
        struct vertexDistance
        {
            size_t vertex;
            size_t distFromStart;
            bool operator>(const vertexDistance& other) const
            {
                return distFromStart > other.distFromStart;
            }
        };
            
        std::vector<size_t> distances(V, INT_MAX);
        std::vector<size_t> prevs(V);
        std::priority_queue<vertexDistance, std::vector<vertexDistance>, std::greater<vertexDistance>> q;
        distances[start] = 0;
        q.push({start, 0});
        while(!q.empty())
        {
            auto current = q.top();
            q.pop();
            if(current.vertex == end)
            {
                size_t temp = end;
                while(temp != start)
                {
                    path.push_back(temp);
                    temp = prevs[temp];
                }
                path.push_back(start);
                std::reverse(path.begin(), path.end());
                return distances[end];
            }
            for(int i = 0; i < adj[current.vertex].size(); i++)
            {
                size_t neighbor = adj[current.vertex][i].first;
                size_t newDist = current.distFromStart + adj[current.vertex][i].second;
                if(distances[neighbor] > newDist)
                {
                    distances[neighbor] = newDist;
                    prevs[neighbor] = current.vertex;
                    q.push({neighbor, newDist});
                }
            }
        }
        return INT_MAX;
    }
    MST Prim() const
    {
        
        
        struct primEdge
        {
            size_t start;
            size_t end;
            int weight;
            bool operator>(const primEdge& other) const
            {
                return weight > other.weight;
            }
        };

        
        MST result;
        result.sumOfWeights = 0;
        std::priority_queue<primEdge, std::vector<primEdge>, std::greater<primEdge>> q;
        std::vector<bool> visited(V,false);
        q.push({0,0,0}); //just for the beginning
        size_t addedEdges = 0;
        bool isFirst = true;
        while(addedEdges < V - 1 && !q.empty())
        {
            auto current = q.top();
            q.pop();
            if(visited[current.end])
            {
                continue;
            }
            visited[current.end] = true;
            for(int i = 0; i < adj[current.end].size(); i++)
            {
                q.push({current.end, (size_t)adj[current.end][i].first, adj[current.end][i].second});
            }
            if(isFirst)
            {
                isFirst = false;
                continue;
            }
            result.edges.push_back({current.start, current.end, current.weight});
            result.sumOfWeights += current.weight;
            addedEdges++;
        }
        return result;
    }
    MST Kruskal() const
    {
        MST result;
        result.sumOfWeights = 0;
        std::vector<Edge> edges;
        for(int i = 0; i < V; i++)
        {
            for(auto& p : adj[i])
            {
                edges.push_back({i, (size_t)p.first, p.second});
            }
        }
        std::sort(edges.begin(), edges.end(), [](const Edge& lhs, const Edge& rhs)
        {
            return std::get<2>(lhs) < std::get<2>(rhs);
        });
        UnionFind uf(V);
        size_t edgesIncluded = 0;
        for(int i = 0; i < edges.size() && edgesIncluded < V - 1; i++)
        {
            auto& e = edges[i];
            if(uf.Union(std::get<0>(e), std::get<1>(e)))
            {
                result.edges.push_back(e);
                result.sumOfWeights += std::get<2>(e);
                edgesIncluded++;
            }
        }
        return result;
    }
};

void printEdge(const Edge& e)
{
    std::cout << std::get<0>(e) << " " << std::get<1>(e) << " " << std::get<2>(e) << std::endl;
}

int main()
{
    Graph g(9, false);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 7, 8);
    g.addEdge(1, 7, 11);
    g.addEdge(1, 2, 8);
    g.addEdge(7, 8, 7);
    g.addEdge(7, 6, 1);
    g.addEdge(8, 6, 6);
    g.addEdge(8, 2, 2);
    g.addEdge(2, 5, 4);
    g.addEdge(6, 5, 2);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 5, 14);
    g.addEdge(3, 4, 9);
    g.addEdge(5, 4, 10);

    {
        std::vector<size_t> path;
        size_t dist = g.dijkstra(0, 4, path);
        std::cout << dist << std::endl;
        for(auto v : path)
        {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    {
        MST mstPrim = g.Prim();
        std::cout << mstPrim.sumOfWeights << std::endl;
        for(auto& e : mstPrim.edges)
        {
            printEdge(e);
        }
    }

    {
        MST mstKruskal = g.Kruskal();
        std::cout << mstKruskal.sumOfWeights << std::endl;
        for(auto& e : mstKruskal.edges)
        {
            printEdge(e);
        }
    }
}
