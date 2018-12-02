#coding:utf-8

__author__ = "LzyRapx"

from collections import defaultdict


class Graph():
    def __init__(self, number_of_node):
        self.graph = defaultdict(list)
        self.visited = [False] * number_of_node

    def addEdge(self, u, v):
        self.graph[u].append(v)

    def BFS(self, node):
        que = []
        que.append(node)
        self.visited[node] = True

        while que:
            currentNode = que.pop(0)
            print(currentNode)
            
            children = self.graph[currentNode]
            for i in range(len(children)):
                if not self.visited[children[i]]:
                    que.append(children[i])
                    self.visited[children[i]] = True

if __name__ == "__main__":
    graph = Graph(3) # size of graph

    # add edge no limitation
    graph.addEdge(0,1)
    graph.addEdge(1,2)
    graph.addEdge(0,2)


    print("BFS starting from vertex zero : ")
    graph.BFS(0)
