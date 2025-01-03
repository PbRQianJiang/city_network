#include "MST.h"
#include <queue>
#include <algorithm>
#include <limits>

// Prim算法的基本实现
// 返回值：pair的first是总权重，second是选中的边
std::pair<int, std::vector<Edge>> MST::prim(const Graph& graph) {
    int V = graph.getVertices();
    std::vector<bool> visited(V, false);     // 记录顶点是否访问
    std::vector<Edge> result;                // 存储MST的边
    int totalWeight = 0;                     // MST的总权重

    visited[0] = true;  // 从第一个顶点开始

    // 需要选择V-1条边
    for (int count = 0; count < V - 1; count++) {
        int minWeight = std::numeric_limits<int>::max();
        int from = -1, to = -1;

        // 在所有连接已访问顶点和未访问顶点的边中找最小权重的边
        for (int i = 0; i < V; i++) {
            if (visited[i]) {
                for (int j = 0; j < V; j++) {
                    if (!visited[j] && graph.getWeight(i, j) > 0) {
                        if (graph.getWeight(i, j) < minWeight) {
                            minWeight = graph.getWeight(i, j);
                            from = i;
                            to = j;
                        }
                    }
                }
            }
        }

        // 添加找到的边到MST中
        if (from != -1 && to != -1) {
            result.emplace_back(from, to, minWeight);
            totalWeight += minWeight;
            visited[to] = true;
        }
    }

    return {totalWeight, result};
}

// 使用优先队列优化的Prim算法
std::pair<int, std::vector<Edge>> MST::primWithPQ(const Graph& graph) {
    int V = graph.getVertices();
    std::vector<bool> visited(V, false);
    std::vector<Edge> result;
    int totalWeight = 0;

    std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;
    
    // 从顶点0开始
    visited[0] = true;
    for (int j = 0; j < V; j++) {
        if (graph.getWeight(0, j) > 0) {
            pq.push(Edge(0, j, graph.getWeight(0, j)));
        }
    }

    while (!pq.empty() && result.size() < V - 1) {
        Edge e = pq.top();
        pq.pop();

        if (visited[e.to]) continue;

        visited[e.to] = true;
        result.push_back(e);
        totalWeight += e.weight;

        for (int j = 0; j < V; j++) {
            if (!visited[j] && graph.getWeight(e.to, j) > 0) {
                pq.push(Edge(e.to, j, graph.getWeight(e.to, j)));
            }
        }
    }

    return {totalWeight, result};
}

// Kruskal算法的基本实现
std::pair<int, std::vector<Edge>> MST::kruskal(const Graph& graph) {
    int V = graph.getVertices();
    std::vector<Edge> edges;
    std::vector<Edge> result;
    int totalWeight = 0;

    // 收集所有边
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph.getWeight(i, j) > 0) {
                edges.emplace_back(i, j, graph.getWeight(i, j));
            }
        }
    }

    // 按权重排序
    std::sort(edges.begin(), edges.end(), 
        [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

    std::vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;

    for (const Edge& e : edges) {
        int x = find(parent, e.from);
        int y = find(parent, e.to);

        if (x != y) {
            result.push_back(e);
            totalWeight += e.weight;
            parent[x] = y;
        }
    }

    return {totalWeight, result};
}

// 使用并查集优化的Kruskal算法
std::pair<int, std::vector<Edge>> MST::kruskalWithUnionFind(const Graph& graph) {
    int V = graph.getVertices();
    std::vector<Edge> edges;
    std::vector<Edge> result;
    int totalWeight = 0;

    // 收集所有边
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph.getWeight(i, j) > 0) {
                edges.emplace_back(i, j, graph.getWeight(i, j));
            }
        }
    }

    // 按权重排序
    std::sort(edges.begin(), edges.end(), 
        [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

    std::vector<int> parent(V);
    std::vector<int> rank(V, 0);
    for (int i = 0; i < V; i++) parent[i] = i;

    for (const Edge& e : edges) {
        int x = find(parent, e.from);
        int y = find(parent, e.to);

        if (x != y) {
            result.push_back(e);
            totalWeight += e.weight;
            unionSets(parent, rank, x, y);
        }
    }

    return {totalWeight, result};
}

// 并查集的find操作（路径压缩）
int MST::find(std::vector<int>& parent, int i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}

// 并查集的union操作（按秩合并）
void MST::unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y) {
    if (rank[x] < rank[y]) {
        parent[x] = y;
    } else if (rank[x] > rank[y]) {
        parent[y] = x;
    } else {
        parent[y] = x;
        rank[x]++;
    }
} 