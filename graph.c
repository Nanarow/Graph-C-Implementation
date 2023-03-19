#include <stdio.h>
#include <stdlib.h>
#define MAX_CIRCUIT 100
#define MAX_VERTICES 100

int graph[MAX_VERTICES][MAX_VERTICES];      // สร้าง Adjacency matrix ของกราฟ
int isVisiteds[MAX_VERTICES][MAX_VERTICES]; // สร้าง Adjacency matrix ทางที่เราจะใช้เดิน
int paths[MAX_VERTICES];                    // Array เก็บค่าที่เราเดินผ่าน
int circuit_lengths[MAX_CIRCUIT];           // Array  เก็บจำนวน vertex ของแต่ละ circuit
int circuits[MAX_CIRCUIT][MAX_VERTICES];    // Array เก็บ circuitที่เป็นArray ที่เก็บ vertex
int num_vertices = 0, num_edges = 0, num_circuits = 0;

void resetVisit()
{ // set เส้นทางทั้งหมดให้เป็น 0
  for (int i = 0; i < num_vertices; i++)
  {
    for (int j = 0; j < num_vertices; j++)
    {
      isVisiteds[i][j] = 0;
    }
  }
}

void visitEdge(int u, int v)
{ // เมื่อใช้เส้นทาง uv หรอ vu ให้แทนค่าเป็น 1
  isVisiteds[u][v] = 1;
  isVisiteds[v][u] = 1;
}

void walk(int start, int current, int path)
{                        // หา circuit
  paths[path] = current; // เก็บค่า จุดที่เดินผ่าน ไว้ในArray paths

  for (int vertex = 0; vertex < num_vertices; vertex++)
  { // loop ทุกจุด
    if (graph[current][vertex])
    { // check ว่าเชื่อมกับจุดcurrentมั้ย
      if (!isVisiteds[current][vertex])
      { // ถ้ายังไม่เดินผ่านให้ทำ...
        //
        if (vertex == start)
        {                         // ถ้าเป็นจุดเริ่มต้น
          paths[++path] = vertex; // เพิ่มจุดสุดท้ายเข้าไปในทางเดิน
          for (int j = 0; j <= path; j++)
          { // for loop จุดที่เดินผ่านทั้งหมด
            // printf("%d -> ", paths[j]);
            // เก็บจุดที่เดินผ่านเข้าไปในArray circuits[num_circuits]
            circuits[num_circuits][j] = paths[j];
          }
          // printf("[%d] \n", start);
          circuit_lengths[num_circuits] = path + 1; // set จำนวนของ vertex
          num_circuits++;                           // เพิ่มจำนวนของ circuit
          break;                                    // ออกจาก loop
        }
        else
        { // ถ้าไม่ใช่จุดเริ่มต้น
          // ให้ทำเครื่องหมายว่าเดินผ่าน
          visitEdge(current, vertex); // line 23
          // ไปยังจุดถัดไป โดยส่ง จุดเริ่มต้น จุดที่เชื่อมกับจุดcurrent และ indexถัดไป
          // ของทางเดินไป
          walk(start, vertex, path + 1); // recursive
        }
        //
      }
    }
  }
}

void findAllCircuits()
{ // หา circuit ทั้งหมดโดยเริ่มเดินจากทุกจุด(ใช้ for)
  for (int vertex = 0; vertex < num_vertices; vertex++)
  {
    walk(vertex, vertex, 0); // line 28
    resetVisit();            // line 14
  }
}

int canBeEulerGraph()
{ // check ว่ากราฟเป็น Euler ได้มั้ย
  for (int i = 0; i < num_vertices; i++)
  {
    int degree = 0;
    for (int j = 0; j < num_vertices; j++)
    {
      if (graph[i][j])
      {
        degree++;
      }
    }
    if (degree % 2)
    { // ถ้า vertex ไหนมี degree เป้นคี่ก็ไม่สามารถเป็น Euler ได้
      return 0;
    }
  }
  return 1;
}

int isEulerCircuit()
{ // check ว่าเป็น Euler มั้ย เทียบ Adjacency matrix ของกราฟ กับ
  // ทางเดิน
  for (int i = 0; i < num_vertices; i++)
  {
    for (int j = 0; j < num_vertices; j++)
    {
      if (isVisiteds[i][j] != graph[i][j])
      { 
        // ต้องใช้เส้นทางครบทั้งหมด ถ้ามีอันไหนไม่ตรงแปลว่าเดินไม่ครบทำให้ไม่เป็น Euler
        return 0;
      }
    }
  }
  return 1;
}

void printAllCircuits()
{ // printAllCircuits
  printf("\nAll circuits:\n");
  for (int i = 0; i < num_circuits; i++)
  { // for loop circuit
    printf("Circuit %d (length %d): ", i + 1, circuit_lengths[i]);
    for (int j = 0; j < circuit_lengths[i]; j++)
    { // for loop vertices
      printf("%d ", circuits[i][j]);
    }
    if (canBeEulerGraph())
    { // check ว่ากราฟเป็น Euler ได้มั้ย line 65
      // นำ circuit มาแปลงเป็น Adjacency matrix ของทางเดิน
      for (int j = 0; j < circuit_lengths[i] - 1; j++)
      {
        visitEdge(circuits[i][j], circuits[i][j + 1]);
      }
      if (isEulerCircuit())
      { // check ว่าเป็น Euler มั้ย line 80
        printf(" is Euler circuit");
      }
      resetVisit(); // line 14
    }
    printf("\n");
  }
}

void initGraph()
{ // ทำให้ Adjacency matrix ของกราฟเป็น 0 ทั้งหมด
  for (int i = 0; i < num_vertices; i++)
  {
    for (int j = 0; j < num_vertices; j++)
    {
      graph[i][j] = 0;
      resetVisit(); // line 14
    }
  }
}

void addEdge(int u, int v)
{ //  เพิ่ม Edge ระหว่างจุด โดยแทนค่าเป็น 1
  if (!graph[u][v])
  {
    num_edges++;
  }
  graph[u][v] = 1;
  graph[v][u] = 1;
}

void print_matrix()
{ // for loop print Adjacency matrix
  printf("\nAdjacency matrix:\n _");
  for (int i = 0; i < num_vertices; i++)
  {
    printf("%d_", i);
  }
  printf("\n");
  for (int i = 0; i < num_vertices; i++)
  {
    printf("%d|", i);
    for (int j = 0; j < num_vertices; j++)
    {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
}

void print_graph()
{
  printf("\nAdjacent vertices\n");
  printf("Vertices: %d, Edges: %d\n", num_vertices, num_edges);
  for (int i = 0; i < num_vertices; i++)
  {
    // count degree
    int degree = 0;
    for (int j = 0; j < num_vertices; j++)
    {
      if (graph[i][j])
      {
        degree++;
      }
    }
    // print vertices of vertex
    printf("Vertex %d is connect to (%d) Degree: ", i, degree);
    for (int j = 0; j < num_vertices; j++)
    {
      if (graph[i][j])
      {
        printf("%d, ", j);
      }
    }
    printf("\n");
  }
}

int main()
{
  num_vertices = 5;

  initGraph();   // line 106
  addEdge(0, 1); // line 115
  addEdge(1, 2);
  addEdge(3, 4);
  addEdge(3, 0);
  addEdge(4, 0);
  addEdge(0, 2);

  print_matrix(); // line 123
  print_graph();  // line 138

  findAllCircuits();  // line 53
  printAllCircuits(); // line 86

  return 0;
}
