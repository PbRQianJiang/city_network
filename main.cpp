#include "Graph.h"
#include "MST.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <windows.h>

// 打印MST的结果
void printMSTResult(const std::pair<int, std::vector<Edge>>& result, const Graph& graph) {
    std::cout << "最小生成树的总权重: " << result.first << std::endl;
    std::cout << "边的列表:" << std::endl;
    for (const Edge& e : result.second) {
        std::cout << graph.getCityName(e.from) << " -- " 
                 << graph.getCityName(e.to) << " (权重: " 
                 << e.weight << ")" << std::endl;
    }
    std::cout << std::endl;
}

// 运行性能测试，比较不同算法的执行时间
void runPerformanceTest(const Graph& graph) {
    // 测试基本Prim算法
    auto start = std::chrono::high_resolution_clock::now();
    auto result = MST::prim(graph);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Prim算法执行时间: " << duration.count() << " 微秒" << std::endl;

    // 测试优化的Prim算法
    start = std::chrono::high_resolution_clock::now();
    result = MST::primWithPQ(graph);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "优化的Prim算法执行时间: " << duration.count() << " 微秒" << std::endl;

    // 测试Kruskal算法
    start = std::chrono::high_resolution_clock::now();
    result = MST::kruskal(graph);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Kruskal算法执行时间: " << duration.count() << " 微秒" << std::endl;

    // 测试优化的Kruskal算法
    start = std::chrono::high_resolution_clock::now();
    result = MST::kruskalWithUnionFind(graph);
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "优化的Kruskal算法执行时间: " << duration.count() << " 微秒" << std::endl;
}

int main() {
    // 设置控制台编码为 UTF-8，支持中文显示
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    Graph* graph = nullptr;

    // 主菜单循环
    while (true) {
        std::cout << "\n城市交通网络最小生成树系统\n";
        std::cout << "1. 从键盘输入数据\n";
        std::cout << "2. 从文件输入数据\n";
        std::cout << "3. 显示当前网络\n";
        std::cout << "4. 使用Prim算法生成最小生成树\n";
        std::cout << "5. 使用优化的Prim算法生成最小生成树\n";
        std::cout << "6. 使用Kruskal算法生成最小生成树\n";
        std::cout << "7. 使用优化的Kruskal算法生成最小生成树\n";
        std::cout << "8. 运行性能测试\n";
        std::cout << "0. 退出\n";
        std::cout << "请选择: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                delete graph;
                graph = new Graph(0);
                graph->loadFromKeyboard();
                break;
            }
            case 2: {
                std::string filename;
                std::cout << "请输入文件名: ";
                std::cin >> filename;
                delete graph;
                graph = new Graph(0);
                graph->loadFromFile(filename);
                break;
            }
            case 3: {
                if (graph) graph->displayGraph();
                else std::cout << "请先输入网络数据！\n";
                break;
            }
            case 4: {
                if (graph) {
                    auto result = MST::prim(*graph);
                    std::cout << "\nPrim算法结果：\n";
                    printMSTResult(result, *graph);
                } else std::cout << "请先输入网络数据！\n";
                break;
            }
            case 5: {
                if (graph) {
                    auto result = MST::primWithPQ(*graph);
                    std::cout << "\n优化的Prim算法结果：\n";
                    printMSTResult(result, *graph);
                } else std::cout << "请先输入网络数据！\n";
                break;
            }
            case 6: {
                if (graph) {
                    auto result = MST::kruskal(*graph);
                    std::cout << "\nKruskal算法结果：\n";
                    printMSTResult(result, *graph);
                } else std::cout << "请先输入网络数据！\n";
                break;
            }
            case 7: {
                if (graph) {
                    auto result = MST::kruskalWithUnionFind(*graph);
                    std::cout << "\n优化的Kruskal算法结果：\n";
                    printMSTResult(result, *graph);
                } else std::cout << "请先输入网络数据！\n";
                break;
            }
            case 8: {
                if (graph) {
                    runPerformanceTest(*graph);
                } else std::cout << "请先输入网络数据！\n";
                break;
            }
            case 0: {
                delete graph;
                return 0;
            }
            default: {
                std::cout << "无效的选择！\n";
            }
        }
    }

    return 0;
} 