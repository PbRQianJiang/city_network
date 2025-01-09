#include "Graph.h"
#include "MST.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <windows.h>

using namespace std;

void printMSTResult(const pair<int, vector<Edge>>& result, const Graph& graph) {
    cout << "最小生成树的总权重: " << result.first << endl;
    cout << "边的列表:" << endl;
    for (const Edge& e : result.second) {
        cout << graph.getCityName(e.from) << " -- " 
             << graph.getCityName(e.to) << " (权重: " 
             << e.weight << ")" << endl;
    }
    cout << endl;
}

void runPerformanceTest(const Graph& graph) {
    auto start = chrono::high_resolution_clock::now();
    auto result = MST::prim(graph);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Prim算法执行时间: " << duration.count() << " 微秒" << endl;

    // 测试优化的Prim算法
    start = chrono::high_resolution_clock::now();
    result = MST::primWithPQ(graph);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "优化的Prim算法执行时间: " << duration.count() << " 微秒" << endl;

    // 测试Kruskal算法
    start = chrono::high_resolution_clock::now();
    result = MST::kruskal(graph);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Kruskal算法执行时间: " << duration.count() << " 微秒" << endl;

    // 测试优化的Kruskal算法
    start = chrono::high_resolution_clock::now();
    result = MST::kruskalWithUnionFind(graph);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "优化的Kruskal算法执行时间: " << duration.count() << " 微秒" << endl;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int choice;
    Graph* graph = nullptr;

    while (true) {
        cout << "\n城市交通网络最小生成树系统\n";
        cout << "1. 从键盘输入数据\n";
        cout << "2. 从文件输入数据\n";
        cout << "3. 显示当前网络\n";
        cout << "4. 使用Prim算法生成最小生成树\n";
        cout << "5. 使用优化的Prim算法生成最小生成树\n";
        cout << "6. 使用Kruskal算法生成最小生成树\n";
        cout << "7. 使用优化的Kruskal算法生成最小生成树\n";
        cout << "8. 运行性能测试\n";
        cout << "0. 退出\n";
        cout << "请选择: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                delete graph;
                graph = new Graph(0);
                graph->loadFromKeyboard();
                break;
            }
            case 2: {
                string filename;
                cout << "请输入文件名: ";
                cin >> filename;
                delete graph;
                graph = new Graph(0);
                graph->loadFromFile(filename);
                break;
            }
            case 3: {
                if (graph) graph->displayGraph();
                else cout << "请先输入网络数据！\n";
                break;
            }
            case 4: {
                if (graph) {
                    auto result = MST::prim(*graph);
                    cout << "\nPrim算法结果：\n";
                    printMSTResult(result, *graph);
                } else cout << "请先输入网络数据！\n";
                break;
            }
            case 5: {
                if (graph) {
                    auto result = MST::primWithPQ(*graph);
                    cout << "\n优化的Prim算法结果：\n";
                    printMSTResult(result, *graph);
                } else cout << "请先输入网络数据！\n";
                break;
            }
            case 6: {
                if (graph) {
                    auto result = MST::kruskal(*graph);
                    cout << "\nKruskal算法结果：\n";
                    printMSTResult(result, *graph);
                } else cout << "请先输入网络数据！\n";
                break;
            }
            case 7: {
                if (graph) {
                    auto result = MST::kruskalWithUnionFind(*graph);
                    cout << "\n优化的Kruskal算法结果：\n";
                    printMSTResult(result, *graph);
                } else cout << "请先输入网络数据！\n";
                break;
            }
            case 8: {
                if (graph) {
                    runPerformanceTest(*graph);
                } else cout << "请先输入网络数据！\n";
                break;
            }
            case 0: {
                delete graph;
                return 0;
            }
            default: {
                cout << "无效的选择！\n";
            }
        }
    }

    return 0;
} 