#conding: utf-8

__author_ = "LzyRapx"

from collections import defaultdict

class Graph:

	# constructor 
	def __init__(self):
		# default dict to store graph
		self.graph = defaultdict(list)
	def addEdge(self, u, v):
		self.graph[u].append(v)

	# A function used by DFS
	def DFSutil(self,v,visited):
		visited[v] = True
		print v

		for i in self.graph[v]:
			if visited[i] is False:
				self.DFSutil(i, visited)
	# main DFS traversal

	def dfs(self, v):
		# first to mark all vertices as not visited
		visited = [False] * (len(self.graph))

		# DFS traversal
		self.DFSutil(v, visited)

if __name__ == '__main__':
	g = Graph()
	g.addEdge(0,1)
	g.addEdge(0,2)
	g.addEdge(1,2)
	g.addEdge(2,3)
	g.addEdge(3,3)
	g.addEdge(2,0)

	print "DFS starting from vextex 2:"
	g.dfs(2)