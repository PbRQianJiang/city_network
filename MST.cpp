#include "MST.h"
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

// Prim算法的基本实现
pair<int, vector<Edge>> MST::prim(const Graph& graph) {
    int V = graph.getVertices();
    vector<bool> visited(V, false);
    vector<Edge> result;
    int totalWeight = 0;

    visited[0] = true;

    for (int count = 0; count < V - 1; count++) {
        int minWeight = numeric_limits<int>::max();
        int from = -1, to = -1;

        // 在所有连接已访问顶点和未访问顶点的边中找最小权重的边
        for (int i = 0; i < V; i++) {//i是访问的顶点
            if (visited[i]) {
                for (int j = 0; j < V; j++) {//j是未访问的顶点
                    if (!visited[j] && graph.getWeight(i, j) > 0) {
                        if (graph.getWeight(i, j) < minWeight) {//开始设为极大值是为了能进入if
                            minWeight = graph.getWeight(i, j);
                            from = i;
                            to = j;
                            //上面两行确认了最小权值的边
                        }
                    }
                }
            }
        }

        // 添加找到的边到MST中
        if (from != -1 && to != -1) {
            result.emplace_back(from, to, minWeight);
            //emplace_back是vector的成员函数，在末尾添加元素
            //emplace_back(from, to, minWeight)隐式地调用了Edge构造函数，构造一个Edge对象，并添加到result中
            totalWeight += minWeight;
            visited[to] = true;
        }
    }

    return {totalWeight, result};
}

// 使用优先队列优化的Prim算法
pair<int, vector<Edge>> MST::primWithPQ(const Graph& graph) {
    int V = graph.getVertices();
    vector<bool> visited(V, false);
    vector<Edge> result;
    int totalWeight = 0;

//priority_queue是一个类
//priority_queue 是一个会自动对元素进行排序的队列，每次取出的都是优先级最高的元素（基于二叉堆）
//greater<Edge>是一个比较器，用于比较Edge对象的大小,比较的方式是基于我们重载的<
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq;
    
    // 从顶点0开始
    visited[0] = true;
    //将顶点0的所有邻边加入优先队列
    for (int j = 0; j < V; j++) {
        if (graph.getWeight(0, j) > 0) {
            pq.push(Edge(0, j, graph.getWeight(0, j)));
        }
    }

    while (!pq.empty() && result.size() < V - 1) {
        // 1. 取出权重最小的边
        Edge e = pq.top();
        pq.pop();
        // 2. 如果目标顶点已访问，跳过这条边
        if (visited[e.to]) continue;
        // 3. 将这条边加入最小生成树
        visited[e.to] = true;
        result.push_back(e);
        totalWeight += e.weight;
        // 4. 将新顶点的所有邻边加入队列
        for (int j = 0; j < V; j++) {
            if (!visited[j] && graph.getWeight(e.to, j) > 0) {
                pq.push(Edge(e.to, j, graph.getWeight(e.to, j)));
            }
        }
    }

    return {totalWeight, result};
}

// Kruskal算法的基本实现
pair<int, vector<Edge>> MST::kruskal(const Graph& graph) {
    int V = graph.getVertices();
    vector<Edge> edges;//edges是待处理的边
    vector<Edge> result;//result是MST的边
    int totalWeight = 0;

    // 收集所有边，先把graph的边存到edge类型的向量中
    for (int i = 0; i < V; i++) {
        for (int j = i + 1; j < V; j++) {
            if (graph.getWeight(i, j) > 0) {
                edges.emplace_back(i, j, graph.getWeight(i, j));
                //无向图搜集上三角即可
            }
        }
    }

    // 按权重排序
    sort(edges.begin(), edges.end(), 
        [](const Edge& a, const Edge& b) { return a.weight < b.weight; });
        //第三个参数是排序规则
        //第三个参数是lambda表达式（类似匿名函数），返回a.weight < b.weight的bool值

//parent下标是本身，内容是父节点
//我们的parent最后的根节点不是-1而是本身
    vector<int> parent(V);
    for (int i = 0; i < V; i++) parent[i] = i;

    for (const Edge& e : edges) {
        int x = find(parent, e.from);
        int y = find(parent, e.to);

        if (x != y) {//如果x和y不是同一个根节点，也就是不属于同一个集合
            result.push_back(e);
            totalWeight += e.weight;
            parent[x] = y;//让他们属于一个集合
        }
    }

    return {totalWeight, result};
}

// 使用并查集优化的Kruskal算法
pair<int, vector<Edge>> MST::kruskalWithUnionFind(const Graph& graph) {
    int V = graph.getVertices();
    vector<Edge> edges;
    vector<Edge> result;
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
    sort(edges.begin(), edges.end(), 
        [](const Edge& a, const Edge& b) { return a.weight < b.weight; });

    vector<int> parent(V);
    vector<int> rank(V, 0);//优化的改动
    for (int i = 0; i < V; i++) parent[i] = i;

    for (const Edge& e : edges) {
        int x = find(parent, e.from);
        int y = find(parent, e.to);

        if (x != y) {
            result.push_back(e);
            totalWeight += e.weight;
            unionSets(parent, rank, x, y);
            //优化算法改动就在于合并的方法让树更平衡
        }
    }

    return {totalWeight, result};
}

// 并查集的find操作（路径压缩）
int MST::find(vector<int>& parent, int i) {
    if (parent[i] != i) {
        parent[i] = find(parent, parent[i]);
    }
    return parent[i];
}
//这里的根节点元素不是-1而是i本身

// 并查集的union操作（按秩合并）
//按秩合并会让树更平衡
//所有的点都放在parent[i]里,所有的高度都在rank里，rank[i]是i的高度
void MST::unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
    if (rank[x] < rank[y]) { //如果x的树比y的矮
        parent[x] = y; // 将矮树接到高树下
    } else if (rank[x] > rank[y]) {
        parent[y] = x;
    } else {
        parent[y] = x;
        rank[x]++;
    }
} 