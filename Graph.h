#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

// 图类：用于表示城市交通网络
class Graph {
private:
    int vertices;                                  // 顶点（城市）数量
    std::vector<std::vector<int>> adjacencyMatrix; // 邻接矩阵，存储城市间的连接权重
    std::vector<std::string> cityNames;            // 存储城市名称

public:
    // 构造函数：初始化具有v个顶点的图
    Graph(int v);

    // 添加一条边：在两个城市之间添加连接
    void addEdge(int from, int to, int weight);

    // 设置城市名称
    void setCityName(int vertex, const std::string& name);

    // 获取城市名称
    std::string getCityName(int vertex) const;

    // 获取顶点数量
    int getVertices() const;

    // 获取两个城市之间的连接权重
    int getWeight(int from, int to) const;

    // 从键盘输入数据
    void loadFromKeyboard();

    // 从文件加载数据
    void loadFromFile(const std::string& filename);

    // 显示图的信息
    void displayGraph() const;
};

#endif 