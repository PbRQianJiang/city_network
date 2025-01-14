以下是基于实验报告和相关内容编写的GitHub仓库README文档，使用Markdown格式：

---

# 城市交通网络最小生成树系统

## 项目简介

本项目旨在实现一个城市交通网络的最小生成树系统，通过不同的算法计算城市之间的最优连接方案。系统支持 **Prim 算法**、**优化的 Prim 算法**、**Kruskal 算法** 以及 **优化的 Kruskal 算法**，并对这些算法的性能进行比较分析。项目适用于城市规划和交通网络优化等实际场景。

## 系统功能

1. 支持通过键盘和文件两种方式输入城市交通网络数据。
2. 实现以下算法构建最小生成树：
   - Prim 算法
   - 优化的 Prim 算法
   - Kruskal 算法
   - 优化的 Kruskal 算法
3. 支持显示当前网络信息（城市列表及邻接矩阵）。
4. 提供算法性能测试功能，展示每种算法的执行时间。
5. 支持文件输入包含中文城市名称，并正确显示。

## 系统架构

### 功能模块图

![功能模块图](path/to/your/module_diagram.png)

### 流程图

![流程图](path/to/your/flowchart.png)

## 用户页面

### 菜单

![功能模块图](path/to/your/module_diagram.png)

## 算法性能测试

![功能模块图](path/to/your/module_diagram.png)


## 输入与输出规范

### 输入形式
- **城市数量**：正整数 \( n > 0 \)
- **城市名称**：支持中文名称，允许包含空格。
- **城市间连接及权重**：
  - 起始城市编号（整数，范围：0 ~ \( n-1 \)）
  - 目标城市编号（整数，范围：0 ~ \( n-1 \)）
  - 权重（正整数）
  - 输入 `-1 -1 -1` 结束。

### 输出形式
- 最小生成树的总权重：
  ```
  最小生成树的总权重: [总权重]
  ```
- 生成树的边列表：
  ```
  [起始城市名称] -- [目标城市名称] (权重: [权重])
  ```

### 错误处理
- 无效城市编号：提示“城市编号必须在 0 到 \( n-1 \) 之间！”
- 无效权重：提示“权重必须为正整数！”
- 城市数量为 0：提示“城市数量必须大于 0！”

## 文件结构

```plaintext
├── /src                   # 源代码
│   ├── main.cpp           # 主程序入口
│   ├── Graph.h/.cpp       # 图类的定义与实现
│   ├── MST.h/.cpp         # 最小生成树算法的定义与实现
├── /data                  # 测试数据
│   ├── sample_input.txt   # 示例输入文件
├── /docs                  # 文档与图示
│   ├── module_diagram.png # 功能模块图
│   ├── flowchart.png      # 系统流程图
├── README.md              # 项目说明
├── LICENSE                # 开源协议
```

## 安装与运行

1. 克隆项目：
   ```bash
   git clone https://github.com/your-repository.git
   cd your-repository
   ```

2. 编译程序（需要 C++ 编译器）：
   ```bash
   g++ -o mst main.cpp Graph.cpp MST.cpp
   ```

3. 运行程序：
   ```bash
   ./mst
   ```

## 测试数据

### 示例输入
```
城市数量：4
城市名称：北京 上海 广州 深圳
城市间连接：
0 1 1200
0 2 2200
1 2 2000
1 3 1300
2 3 800
-1 -1 -1
```

### 示例输出
```
Prim算法结果：
最小生成树的总权重: 3300
边的列表:
北京 -- 上海 (权重: 1200)
上海 -- 深圳 (权重: 1300)
深圳 -- 广州 (权重: 800)
```

## 性能测试

以下为四种算法在不同图上的性能对比图：

![性能测试图](path/to/your/performance_chart.png)

## 未来展望

1. 添加图形化用户界面（GUI）。
2. 支持更大规模网络的实时更新和优化。
3. 提供更多最小生成树算法以扩展功能。

## 参考文献

1. [《算法导论》](https://www.algorist.com/) - Thomas H. Cormen 等
2. 《数据结构与算法分析：C++描述》 - Mark Allen Weiss

---

如果有任何问题或建议，请提交 [Issue](https://github.com/your-repository/issues)。欢迎贡献代码！
