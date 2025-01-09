#ifndef GRAPH_H//如果未定义GRAPH_H
#define GRAPH_H//则定义GRAPH_H
//防止重复定义，造成编译错误，比如有两个类的情况

#include <vector>
#include <string>

// 图类：用于表示城市交通网络
//主要做的事情就是把内容存到矩阵里
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
    //const修饰成员函数，表示该函数不会修改类的成员变量
    //const对象只能调用成员函数

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