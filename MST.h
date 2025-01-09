#ifndef MST_H
#define MST_H

#include "Graph.h"
#include <vector>
#include <utility>

//主要做的事情添加边的数据结构，构造MST
// 边结构体：表示图中的一条边
struct Edge {
    int from;   // 起始顶点
    int to;     // 目标顶点
    int weight; // 边的权重
    
    // 构造函数
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
    
    // 重载大于运算符，用于优先队列
    bool operator>(const Edge& other) const {
        return weight > other.weight;
    }
};

// 最小生成树类：实现各种MST算法
class MST {
public:
    // 基本Prim算法实现
    //键对分别是权值和 和 边（strcut）
    static std::pair<int, std::vector<Edge>> prim(const Graph& graph);

    // 使用优先队列优化的Prim算法
    static std::pair<int, std::vector<Edge>> primWithPQ(const Graph& graph);

    // 基本Kruskal算法实现
    static std::pair<int, std::vector<Edge>> kruskal(const Graph& graph);

    // 使用并查集优化的Kruskal算法
    static std::pair<int, std::vector<Edge>> kruskalWithUnionFind(const Graph& graph);
    
private:
    // 并查集的查找操作（带路径压缩）
    static int find(std::vector<int>& parent, int i);

    // 并查集的合并操作（按秩合并）
    static void unionSets(std::vector<int>& parent, std::vector<int>& rank, int x, int y);
};

#endif 