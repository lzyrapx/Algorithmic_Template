<!--
 * @Author: zhaoyang.liang
 * @Github: https://github.com/LzyRapx
 * @Date: 2019-06-13 00:02:05
 -->
### [ACM-OI 's Strategy](https://github.com/LzyRapx/Algorithmic_Template/blob/master/ACM-OI%20's%20Strategy.md)
# Algorithmic_Library
#### LzyRapx 's code Library for competitive-programming.
## Black_magic
+ [x] 手写bitset
+ [x] fastIO
+ [x] pb_ds
+ [x] rope
+ [x] 扩栈
+ [x] O(1)快速乘
## Class
+ [x] BigInt
+ [x] Frac
+ [x] 对拍
## DataStructure
+ [x] CDQ分治
+ [x] Dancing Links X (DLX)
+ [x] HASH
+ [x] KMP
+ [x] LCA
+ [x] LCT
+ [x] Splay Tree
+ [x] merge_sort
## Geometry
+ [ ] 基本类型 - 点, 线
+ [ ] 多边形
+ [ ] 半平面交
+ [ ] 圆
+ [ ] 三维几何
+ [ ] 球面几何
+ [ ] 平面最近点对
+ [ ] 曼哈顿距离生成树
+ [ ] 最大空凸包
+ [ ] 平面图求域
## Graph-theory
+ [x] Connectivity
  + [x] BCC
  + [x] BCC_edge
  + [x] BCC_vertex
  + [x] Kosaraju
  + [x] Tarjan_SCC
+ [x] Flows and cuts
  + [x] Dinic
  + [x] Edmonds–Karp
  + [x] Ford-Fulkerson
  + [x] MinCostMaxFlow
  + [x] edge-disjoint-path
  + [x] maximum_flow_goldberg_tarjan
+ [x] Matching
  + [x] Kuhn-Munkras
  + [x] Hungarian method (匈牙利算法)
+ [x] Shortest-path
   + [x] Bellman-Ford
   + [x] Dijkstra
   + [x] Floyd–Warshall
   + [x] K短路
   + [x] SPFA
+ [x] Spanning-tree
   + [x] Kruskal (MST和次小生成树)
   + [x] prim
   + [x] 曼哈顿距离MST
## Mathematics
+ [x] BSGS
+ [x] Berlekamp-Massey
+ [x] Berlekamp-Massey (杜教版)
+ [x] CRT（模数不互质）
+ [x] CRT（模数互质）
+ [x] Cantor
+ [x] Check_primitive_root
+ [x] Dirichlet卷积
+ [x] EX_BSGS
+ [x] Euler_Function
+ [x] Extends_GCD
+ [x] FFT+CDQ
+ [x] FFT大整数乘法
+ [x] MTT
+ [x] Fib数模n的循环节
+ [x] Guass
+ [x] [1,n]与a互素个数
+ [x] bernoulli_number
+ [x] factorial
+ [x] gauss_elimination
+ [x] 任意模数FFT+多项式取逆
+ [x] 康拓展开和逆康拓展开
+ [x] 快速幂
+ [x] 杜教筛
+ [x] 线性筛prime+phi+mu
## String
 + [x] AhoCorasick (AC自动机)
 + [x] EX_KMP
 + [x] KMP
 + [x] LIS
 + [x] Manacher
 + [x] SA
 + [x] String Hash
 + [x] suffix array
 + [x] 回文树
 + [x] 动态Trie
 + [x] 静态Trie
## Others

```
├── ACM-OI 's Strategy.md
├── ACM-Tech.txt
├── Basic
│   ├── BFS
│   │   ├── BFS
│   │   ├── BFS.cpp
│   │   └── BFS.py
│   ├── BackTracking
│   │   ├── Hamilton path.cpp
│   │   ├── Knight_tour.cpp
│   │   ├── Nqueue.cpp
│   │   └── Sudoku.cpp
│   ├── BinarySearchTree
│   │   ├── BST_Count&height&diameter.cpp
│   │   ├── BST_Normal_Operation.cpp
│   │   ├── BST_traverse.cpp
│   │   └── Banlancing of BST.cpp
│   ├── ConvexHullTrick.cpp
│   └── DFS
│       ├── dfs
│       ├── dfs.cpp
│       └── dfs.py
├── Black_magic
│   ├── &与%效率.txt
│   ├── O(1)快速乘.cpp
│   ├── bitset.h
│   ├── fastIO.cpp
│   ├── pb_ds（笔记）.txt
│   ├── rope.txt
│   ├── 扩栈.cpp
│   └── 二进制数中1的个数.cpp
├── Class
│   ├── BigInt.cpp
│   ├── Frac.cpp
│   └── 对拍.cpp
├── DataStructure
│   ├── 01Tire求区间异或和的最大值.cpp
│   ├── CDQ分治.cpp
│   ├── Cartesian_Tree.cpp
│   ├── Circle-Square-Tree Maximum independent set.cpp
│   ├── DLX.cpp
│   ├── HASH.cpp
│   ├── KMP.cpp
│   ├── LCA.cpp
│   ├── LCT.cpp
│   ├── Splay_Tree - v1.cpp
│   ├── Splay_Tree - v2.cpp
│   └── merge_sort.cpp
├── Geometry
│   ├── Geometry2d (Basic).h
│   ├── Geometry3d (Basic).h
│   └── polygon.cpp
├── Graph-theory
│   ├── Connectivity
│   │   ├── BCC (multi-version).cpp
│   │   ├── BCC_edge(1).cpp
│   │   ├── BCC_edge(2).cpp
│   │   ├── BCC_vertex(1).cpp
│   │   ├── BCC_vertex(2).cpp
│   │   ├── Kosaraju.cpp
│   │   └── Tarjan_SCC.cpp
│   ├── Flows and cuts
│   │   ├── Dinic(1).cpp
│   │   ├── Dinic(2).cpp
│   │   ├── Edmonds–Karp.cpp
│   │   ├── Ford-Fulkerson.cpp
│   │   ├── MinCostMaxFlow.cpp
│   │   ├── edge-disjoint-path(1).cpp
│   │   ├── edge-disjoint-path(2).cpp
│   │   └── maximum_flow_goldberg_tarjan.cpp
│   ├── Matching
│   │   ├── Kuhn-Munkras (KM).cpp
│   │   ├── 匈牙利算法 O(n^3）.cpp
│   │   └── 匈牙利算法 O(nm).cpp
│   ├── Shortest-path
│   │   ├── Bellman-Ford.cpp
│   │   ├── Dijkstra(1).cpp
│   │   ├── Dijkstra(2).cpp
│   │   ├── Dijkstra(求最短路和次短路以及其路径数).cpp
│   │   ├── Floyd–Warshall.cpp
│   │   ├── K短路.cpp
│   │   ├── SPFA(1).cpp
│   │   └── SPFA(2).cpp
│   └── Spanning-tree
│       ├── Kruskal (MST和次小生成树).cpp
│       ├── prim.cpp
│       └── 曼哈顿距离MST.cpp
├── Mathematics
│   ├── BSGS.cpp
│   ├── Berlekamp-Massey.cpp
│   ├── Berlekamp-Massey（Complete）.cpp
│   ├── CRT（模数互质）.cpp
│   ├── CRT（模数不互质）.cpp
│   ├── Cantor.cpp
│   ├── Check_primitive_root.cpp
│   ├── Determinant.cpp
│   ├── Dirichlet卷积.cpp
│   ├── EX_BSGS.cpp
│   ├── Euler_Function.cpp
│   ├── Extends_GCD.cpp
│   ├── FFT+CDQ.cpp
│   ├── FFT大整数乘法.cpp
│   ├── Fib数模n的循环节.cpp
│   ├── Guass.cpp
│   ├── MTT.cpp
│   ├── [1,n]与a互素个数.cpp
│   ├── bernoulli_number.cpp
│   ├── factorial.cpp
│   ├── gauss_elimination.cpp
│   ├── main.out
│   ├── 快速乘.cpp
│   ├── 快速幂.cpp
│   ├── 杜教筛.cpp
│   ├── 线性筛prime+phi+mu.cpp
│   ├── 任意模数FFT+多项式取逆.cpp
│   ├── 类欧几里得.cpp
│   └── 康拓展开和逆康拓展开.cpp
├── Others
│   └── README.md
├── README.md
├── Skill Trees.txt
└── String
    ├── AC自动机.cpp
    ├── AhoCorasick.cpp
    ├── EX_KMP.cpp
    ├── KMP(含注释）.cpp
    ├── KMP.cpp
    ├── LIS.cpp
    ├── Manacher.cpp
    ├── SA.cpp
    ├── manacher (2).cpp
    ├── multi - String Hash.cpp
    ├── suffix array.cpp
    ├── 动态Trie.cpp
    ├── 静态Trie.cpp
    └── 回文树.cpp
```