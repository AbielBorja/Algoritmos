// Daniel Alejandro Martinez Rosete A01654093
// Abiel Moisès Borja Garcìa A01654937

#include <iostream>
#include <vector>
using namespace std;

void printBoard(vector<vector<int>> b)
{
  int rows = b.size();
  int cols = b[0].size();
  // Rows of the maze
  for (int r = 0; r < rows; r++)
  {
    // Element of the colums
    for (int c = 0; c < cols; c++)
      cout << b[r][c] << " ";
    cout << endl;
  }
}

vector<vector<int>> makeBoard(int n, int m)
{
  vector<vector<int>> maze;
  for (int r = 0; r < m; r++)
  {
    vector<int> row;
    for (int c = 0; c < n; c++)
    {
      int a = 0;
      cin >> a;
      row.push_back(a);
    }
    maze.push_back(row);
  }
  return maze;
}

// Solución del laberinto haciendo backtracking con complejidad O(4log(n)) la cual tiene como parametros
// El laberinto como matriz, x y y que son la posición inicial, n y m que son las longitudes de la matriz
// y el vector solución.
void solveMazeBacktracking(vector<vector<int>> maze, int x, int y, int n, int m, vector<vector<int>> &solution)
{

  // Este es el caso base cuando se llega al final del laberinto
  if (x == n - 1 && y == m - 1)
  {
    // Se marca la casilla final
    solution[n - 1][m - 1] = 1;
    // Se imprime la solución y se hace return
    cout << "Solution with backtracking:" << endl;
    cout << endl;
    printBoard(solution);
    cout << endl;
    return;
  }

  // Este if checa que no nos salgamos del tablero o que no sea una pared o que no hayamos pasado por ahi
  if (x >= n || y >= n || x < 0 || y < 0 || maze[x][y] == 0 || solution[x][y] == 1)
  {
    return;
  }

  // Aqui si ninguna cosa activa el if se pinta la solucion como 1 y se llama recursivamente la función en orden
  // 1.-Derecha, 2.-Abajo, 3.-Izquierda, y 4.- Arriba
  solution[x][y] = 1;
  solveMazeBacktracking(maze, x + 1, y, n, m, solution);
  solveMazeBacktracking(maze, x, y - 1, n, m, solution);
  solveMazeBacktracking(maze, x, y + 1, n, m, solution);
  solveMazeBacktracking(maze, x - 1, y, n, m, solution);
}

// Solución del laberinto haciendo Branch and Bound con complejidad O(4log(n)) la cual tiene como parametros
// El laberinto como matriz, x y y que son la posición inicial, n y m que son las longitudes de la matriz, lastx y lasty son
//  el movimiento anterior.
//  y el vector solución.
void solveMazeBranchAndBound(vector<vector<int>> &maze, int x, int y, int n, int m, int lastx, int lasty, vector<vector<int>> &solution)
{
  // Pintamos como marcada la primera casilla de incio del laberinto
  if (x == 0 && y == 0)
  {
    solution[y][x] = 1;
  }
  // Si encontramos la salida pintamos la casilla de solución e imprimimos solución
  if (x == n - 1 && y == m - 1)
  {
    solution[n - 1][m - 1] = 1;
    cout << "\nSolution Maze by Branch and Bound" << endl;
    printBoard(solution);
    cout << endl;
    return;
  }

  // Identifica si no nos hemos salido del tablero al avanzar a la derecha y si no hemos marcado esa casilla como visitada
  if (x + 1 < n && maze[y][x + 1] == 1)
  {
    // Si el movimiento es el anterior lo marcamos como no opción para visitar
    if (x + 1 == lastx)
    {
      solution[y][x] = 0;
      return;
    }
    else
    {
      // Si no la hemos visitado, la marcamos
      solution[y][x + 1] = 1;
      // La volvemos a llamar de manera recursiva
      solveMazeBranchAndBound(maze, x + 1, y, n, m, x, y, solution);
    }
  }

  // Identifica si no nos hemos salido del tablero al subir y si no hemos marcado esa casilla como visitada
  if (y + 1 < m && maze[y + 1][x] == 1)
  {
    if (y + 1 == lasty)
    {
      // Si el movimiento es el anterior lo marcamos como no opción para visitar
      solution[y][x] = 0;
      return;
    }
    else
    {
      // Si no la hemos visitado, la marcamos
      solution[y + 1][x] = 1;
      // La volvemos a llamar de manera recursiva
      solveMazeBranchAndBound(maze, x, y + 1, n, m, x, y, solution);
    }
  }

  // Identifica si no nos hemos salido del tablero al ir a la izquierda y si no hemos marcado esa casilla como visitada
  if (x - 1 >= 0 && maze[y][x - 1] == 1)
  {
    if (x - 1 == lastx)
    {
      // Si el movimiento es el anterior lo marcamos como no opción para visitar
      solution[y][x] = 0;
      return;
    }
    else
    {
      // Si no la hemos visitado, la marcamos
      solution[y][x - 1] = 1;
      // La volvemos a llamar de manera recursiva
      solveMazeBranchAndBound(maze, x - 1, y, n, m, x, y, solution);
    }
  }
  // Identifica si no nos hemos salido del tablero al bajar y si no hemos marcado esa casilla como visitada
  if (y - 1 >= 0 && maze[y - 1][x] == 1)
  {
    if (y - 1 == lasty)
    {
      // Si el movimiento es el anterior lo marcamos como no opción para visitar
      solution[y][x] = 0;
      return;
    }
    else
    {
      // Si no la hemos visitado, la marcamos
      solution[y - 1][x] = 1;
      // La volvemos a llamar de manera recursiva
      solveMazeBranchAndBound(maze, x, y - 1, n, m, x, y, solution);
    }
  }
  return;
}

int main()
{

  int m, n;

  cout << "Insert how long the board is:" << endl;
  cin >> m;

  cout << "Insert how high the board is:" << endl;
  cin >> n;
  cout << "Insert 0(Wall) or 1(Blank) from left to right and top to bottom: " << endl;

  vector<vector<int>> maze = makeBoard(n, m);
  cout << endl;
  cout << "Board:" << endl;
  cout << endl;
  printBoard(maze);
  cout << endl;

  vector<vector<int>> solutionBacktracking;
  for (int r = 0; r < m; r++)
  {
    vector<int> row;
    for (int c = 0; c < n; c++)
    {
      int a = 0;
      row.push_back(a);
    }
    solutionBacktracking.push_back(row);
  }

  vector<vector<int>> solutionBranchAndBound;
  for (int r = 0; r < m; r++)
  {
    vector<int> row;
    for (int c = 0; c < n; c++)
    {
      int a = 0;
      row.push_back(a);
    }
    solutionBranchAndBound.push_back(row);
  }

  solveMazeBacktracking(maze, 0, 0, n, m, solutionBacktracking);
  solveMazeBranchAndBound(maze, 0, 0, n, m, -1, -1, solutionBranchAndBound);

  return 0;
}