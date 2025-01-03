#include "Graph.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <windows.h>
#include <locale>

Graph::Graph(int v) : vertices(v) {
    adjacencyMatrix.resize(v, std::vector<int>(v, 0));
    cityNames.resize(v);
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= 0 && from < vertices && to >= 0 && to < vertices) {
        adjacencyMatrix[from][to] = weight;
        adjacencyMatrix[to][from] = weight; // 因为是无向图
    }
}

void Graph::setCityName(int vertex, const std::string& name) {
    if (vertex >= 0 && vertex < vertices) {
        cityNames[vertex] = name;
    }
}

std::string Graph::getCityName(int vertex) const {
    if (vertex >= 0 && vertex < vertices) {
        return cityNames[vertex];
    }
    return "";
}

int Graph::getVertices() const {
    return vertices;
}

int Graph::getWeight(int from, int to) const {
    if (from >= 0 && from < vertices && to >= 0 && to < vertices) {
        return adjacencyMatrix[from][to];
    }
    return 0;
}

void Graph::loadFromKeyboard() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    std::cout << "请输入城市数量：";
    std::cin >> vertices;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    adjacencyMatrix.resize(vertices, std::vector<int>(vertices, 0));
    cityNames.resize(vertices);

    std::cout << "请输入各个城市的名称：\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << "城市 " << i << " 的名称: ";
        char name[256];
        std::cin.getline(name, 256);
        cityNames[i] = std::string(name);
    }

    std::cout << "请输入城市间的连接和权重（输入-1 -1 -1结束）：\n";
    while (true) {
        int from, to, weight;
        std::cout << "输入起始城市编号、目标城市编号和权重: ";
        std::cin >> from >> to >> weight;
        
        if (from == -1 && to == -1 && weight == -1) break;
        
        if (from < 0 || from >= vertices || to < 0 || to >= vertices) {
            std::cout << "错误：城市编号必须在0到" << (vertices-1) << "之间！\n";
            continue;
        }
        
        addEdge(from, to, weight);
    }
}

void Graph::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "无法打开文件！" << std::endl;
        return;
    }

    file >> vertices;
    adjacencyMatrix.resize(vertices, std::vector<int>(vertices, 0));
    cityNames.resize(vertices);

    for (int i = 0; i < vertices; i++) {
        file >> cityNames[i];
    }

    int from, to, weight;
    while (file >> from >> to >> weight) {
        if (from >= 0 && from < vertices && to >= 0 && to < vertices) {
            addEdge(from, to, weight);
        }
    }

    file.close();
}

void Graph::displayGraph() const {
    std::cout << "城市交通网络信息：\n";
    std::cout << "城市列表：\n";
    for (int i = 0; i < vertices; i++) {
        std::cout << i << ": " << cityNames[i] << "\n";
    }

    std::cout << "\n邻接矩阵：\n";
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            std::cout << adjacencyMatrix[i][j] << "\t";
        }
        std::cout << "\n";
    }
} 