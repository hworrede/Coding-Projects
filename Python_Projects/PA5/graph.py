# CSE30 PA5
# Hagos Worrede
# graph.py
class Vertex:

    def __init__(self,key):
        self.id = key
        self.connectedTo = {}
        self.color = 'white'

    def addNeighbor(self,nbr,weight=0):
        self.connectedTo[nbr] = weight

    def __str__(self):
        return str(self.id) + ' connectedTo: ' + str([x.id for x in self.connectedTo])

    def getConnections(self):
        return self.connectedTo.keys()

    def getId(self):
        return self.id

    def getWeight(self,nbr):
        return self.connectedTo[nbr]

class Graph:

    def __init__(self):
        self.vertList = {}
        self.numVertices = 0

    def addVertex(self,key):
        self.numVertices = self.numVertices + 1
        check_vert = Vertex(key)
        self.vertList[key] = check_vert
        return check_vert

    def getVertex(self,n):
        if n in self.vertList:
            return self.vertList[n]
        else:
            return None

    def __contains__(self,n):
        return n in self.vertList

    def addEdge(self,f,t,weight=0):
        if f not in self.vertList:
            check_edge = self.addVertex(f)
        if t not in self.vertList:
            check_edge = self.addVertex(t)
        self.vertList[f].addNeighbor(self.vertList[t], weight)

    def getVertices(self):

        return self.vertList.keys()

    def __iter__(self):
        return iter(self.vertList.values())

    def breadth_first_search(self, s):
        v = []
        v.append(s)
        s.color = 'gray'
        while len(v) > 0:
            check_pop = v.pop(0)
            for k in check_pop.getConnections():
                if k.color == 'white':
                    k.color = 'gray'
                    v.append(k)
            check_pop.color = 'black'

    def depth_first_search(self):
        check_firstsearch = []
        for k in self:
            k.color = 'white'
        for k in self:
            if k.color == 'white':
                self.DFS(k, check_firstsearch)
        return check_firstsearch
        

    def DFS(self, vid, path):
        vid.color = 'gray'
        for k in vid.getConnections():
            if k.color == 'white':
                self.DFS(k, path)
        vid.color = 'black'
        path.append(vid)