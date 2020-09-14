import sys
import time

s = time.time()
# checar como é isso no servidor
#verificar arestas negativas e zero (faço comparação com zero)
input_file_name = sys.argv[1]
output_file = sys.argv[2]

input_file = open(input_file_name, 'r')
num_lines = 0
weights = {}
num_vertex = 0
num_edges = 0

for line in input_file:
    splitted_line = line.replace('\n', '').split(' ')
    if num_lines == 0:
        num_vertex = int(splitted_line[0])
        num_edges = int(splitted_line[1])
    else:
        i = int(splitted_line[0])
        j = int(splitted_line[1])
        weight = int(splitted_line[2])
        if i not in weights:
            weights[i] = {}
            weights[i][j] = weight
        else:
            weights[i][j] = weight
    num_lines += 1

# a leitura dos pesos é do maior pro menor (pode ser que não seja)
# Ex.: ao checar se exite uma aresta de vertex 5 para 6 checar se existe weights[5][6] ou weights[6][5]
my_graph = {}
# print(weights)


def distToVertex(index_vertex):
    infinito = 1000000000000000000
    custs = [infinito] * num_vertex
    openedVertex = [1] * num_vertex

    custs[index_vertex - 1] = 0
    while True:
        for i in range(1, num_vertex + 1):
            if i != index_vertex:
                exist = False
                cust = 0
                if index_vertex in weights:
                    if i in weights[index_vertex]:
                        exist = True
                        cust = weights[index_vertex][i]
                if i in weights:
                    if index_vertex in weights[i]:
                        exist = True
                        cust = weights[i][index_vertex]
                if exist:
                    if custs[i - 1] > custs[index_vertex - 1] + cust:
                        custs[i - 1] = custs[index_vertex - 1] + cust

        openedVertex[index_vertex - 1] = 0
        if 1 not in openedVertex:
            break
        menor = infinito + 1
        for i in range(1, num_vertex + 1):
            if menor > custs[i - 1] and openedVertex[i - 1]:
                menor = custs[i - 1]
                index_vertex = i
        if menor >= infinito:
            break
    return custs


max_dist = 0

vertexV = 0
vertexU = 0
custs_v = []
for v in range(1, num_vertex + 1):
    dists = distToVertex(v)
    for u in range(num_vertex):
        if dists[u] > max_dist:
            vertexU = u + 1
            vertexV = v
            max_dist = dists[u]
            custs_v = dists
    # if max(dists) > max_dist:
    #     max_dist = max(dists)
    # print(distToVertex(v))
print(max_dist)
print(str(vertexV) + " " + str(vertexU))

atual_cust = custs_v[vertexU - 1]
all_vertics = []
all_vertics.append(vertexU)
while vertexU != vertexV:
    for i in range(1, num_vertex+1):

        exist = False
        distVertxItoVertxU = 0
        if vertexU in weights:
            if i in weights[vertexU]:
                exist = True
                distVertxItoVertxU = weights[vertexU][i]
        if i in weights:
            if vertexU in weights[i]:
                exist = True
                distVertxItoVertxU = weights[i][vertexU]
        if exist:
            if atual_cust - distVertxItoVertxU == custs_v[i - 1]:
                atual_cust = atual_cust - distVertxItoVertxU
                all_vertics.append(i)
                vertexU = i
                break

print(len(all_vertics))
end = ""
for i in all_vertics[::-1]:
    end += str(i) + " "
end += "\n"
print(end.replace(" \n", ''))

e = time.time()
# print(e - s)