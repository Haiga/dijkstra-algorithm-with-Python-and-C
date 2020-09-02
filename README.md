# dijkstraPython


Diâmetro 

Input file:standard input
Output file:standard outputTime limit:1 
secondMemory limit:256 megabytes

SejaG= (V, E) um grafo conexo ponderado comn=|V|vértices e m=|E|arestas, tal que o peso da arestae i∈E ́e dado por i.
Definimos a distância entre dois vértices como o peso do caminho mínimo entre eles. 

E o diâmetro desse grafo como a maior distância entre dois de seus vértices. 
Se dois vértices atingirem essa maior distância, eles podem ser chamados de vértices diametrais.

Encontre o diâmetro do grafo G, dois vértices diametrais e um caminho m ́ınimo entre esses vértices.

InputA primeira linha da entrada contém dois inteiros separados por um espaço, representando
respectivamente o número de vértices do grafo e o número de arestas entre eles. Seguem m linhas, cada
uma com três inteiros, ui,vi e wi, indicando que existe uma aresta de peso wi entre os vértices ui e vi.

OutputA primeira linha da saída deve conter um inteiro representando o valor do diâmetro do grafo. 
A segunda linha da sa ́ıda deve conter o  ́ındice de dois vértices diametrais, separados por espaços. 

A terceira linhadeve conter a quantidade de vértices em um caminho m ́ınimo entre o par de vértices diametrais da linha 2. 
A última linha deve conter o índices dos v ́ertices do caminho mínimo escolhido na linha 3.

O diâmetro  ́e um valor  ́unico, mas um grafo pode possuir mais de um par de v ́ertices diametrais e mais de um caminho mınimo entre eles. 
Você pode escolher qualquer par de vertices diametrais e caminho mınimo, desde que eles realmente sejam validos.
