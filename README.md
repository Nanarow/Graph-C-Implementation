# Graph-C-Implementation
undirected graph implementation in c using adjacency matrix

## Installation

```bash
git clone https://github.com/Nanarow/Graph-C-Implementation.git
```

## Usage
run **`main.exe`**
```bash
main.exe
```

## Example
**graph**
```
(1)-------(2)
   \     / 
    \   /  
     (0)   
    /   \  
   /     \ 
(4)-------(3)
```
example code in **`main`** function
```c
int  main()
{
	num_vertices  =  5; //set the number of vertices
	initGraph();  // fill adjacency matrix with 0
	addEdge(0,  1);  // add edge between vertex 0 and vertex 1
	addEdge(1,  2);
	addEdge(3,  4);
	addEdge(3,  0);
	addEdge(4,  0);
	addEdge(0,  2);

	print_matrix();  // print adjacency matrix
	print_graph();  // print adjacent vertices

	findAllCircuits();  
	printAllCircuits();  

	return  0;
}
```
**output**
```
Adjacency matrix:
 _0_1_2_3_4_
0|0 1 1 1 1
1|1 0 1 0 0
2|1 1 0 0 0
3|1 0 0 0 1
4|1 0 0 1 0

Adjacent vertices
Vertices: 5, Edges: 6
Vertex 0 is connect to (4) Degree: 1, 2, 3, 4,
Vertex 1 is connect to (2) Degree: 0, 2,
Vertex 2 is connect to (2) Degree: 0, 1,
Vertex 3 is connect to (2) Degree: 0, 4,
Vertex 4 is connect to (2) Degree: 0, 3,

All circuits:
Circuit 1 (length 4): 0 1 2 0
Circuit 2 (length 4): 0 3 4 0
Circuit 3 (length 4): 1 0 2 1
Circuit 4 (length 4): 2 0 1 2
Circuit 5 (length 7): 3 0 1 2 0 4 3  is Euler circuit
Circuit 6 (length 7): 4 0 1 2 0 3 4  is Euler circuit
```

find all circuits in graph using **`findAllCircuits()`** function and 
print all circuits in graph using **`printAllCircuits()`** function
> **`printAllCircuits()`** can check circuit that can be Euler circuit
