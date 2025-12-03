### **SICT0301B: Evalúa los componentes**

### Breve descripción
Mi proyecto es un gestor simple de `Creadores` para una productora de contenido en RRSS.

La **estructura toral es el gestor**, que se encarga de la carga de los archivos, hacer consultas ordenadas sobre los creadores, añadir y eliminar creadores, así como de montar el grafo: la estructura que utilicé para denotar relaciones. 

Las relaciones denotadas por el grafo toman lugar entre las entidades `Creador`, `Rutina`, y `Network`, y pueden ser accedidas mediante el algoritmo de BFS, que muestra todos los nodos alcanzables, siendo los de hasta arriba los que tienen una conexión directa.

A continuación los headers de los archivos CSV:
- Creadores: "nombre,id,alcance,rutinas,networks"
- Rutinas: "Tipo,Público meta,ID de Rutina,Longitud del ciclo de producción"
- Networks: "id,tematica,descripcion,creadores"

#### 1. Análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados

En el programa se utilizan tres ordenamientos con `std::sort` sobre vectores de objetos `Creador`, los criterios de ordenamiento son el alcance, número de rutinas y nombre del creador.

**Complejidad:**
- Copia de los creadores al vector: **O(n)**
- `std::sort`, **O(n log n)** en todos los casos

**Justificación:** Se usa `std::sort` (Introsort, híbrido de QuickSort/HeapSort) que garantiza O(n log n) en el peor caso. Es el algoritmo de ordenamiento más eficiente disponible en la STL para esots fines.

#### 2. Análisis de complejidad de todas las estructuras de datos y sus usos

| Estructura | Operaciones principales | Complejidad promedio | Complejidad peor caso | Justificación de uso |
|-|-|-|-|-|
| `unordered_map<string, X>`| insert, find, erase | **O(1)** | O(n) | Acceso por ID rápido (clave única) |
| `vector<string>` (listas adjuntas) | push_back, iteración, remove+erase  | O(1) amortizado / O(n) remove | - | Listas pequeñas-medias de relaciones para el sistema simple que hice y además es compatible con `std::sort`|
| `queue<string>` (BFS) | push, pop, empty | O(1) por operación idividual y O(V) como costo total al ser usada en el BFS | - | Cola FIFO óptima para BFS; C/vértice se encola y desencola solamente una vez, en lugar de describir el costo/operación, debí dimensionar el costo por el total de elementos contenidos que puede llegar a ser O(V), por tratarse de BFS |
| `unordered_set<string>` (visitados BFS) | insert, find | O(1) | O(n) |  Búsqueda O(1) de visitados, no permite duplicados, tamaño dinámico |

**Conclusión:** Las estructuras elegidas logran consulta en tiempo constante promedio, lo que es ideal para este sistema en particular; En cuanto a la complejidad del BFS, c/vértice se encola/desencola una sola vez y cada arista se examina una sola vez, esto es óptimo para el tipo de recorrido realizado.

#### 3. Análisis de complejidad de todos los componentes y complejidad final del programa

| Componente | Complejidad |
|-|-|
| Carga de datos (3 archivos) | O(R + C + N), lineal en cantidad de entidades |
| montarGrafo() | O(C × promedio_rutinas + C × promedio_networks) |
| BFS desde un nodo | O(V+E) donde V = nodos totales, E = aristas |
| Ordenar creadores (3 funciones)| O(C log C) |
| getRutina/getCreador/getNetwork | O(1) promedio |
| añadirCreador() | O(C + N) (reescribe archivos completos) |
| eliminarCreador() | O(C + N) (reescribe archivos completos) |

**Complejidad final del programa en operaciones principales:**
- Consultas y búsquedas: O(1) o O(V+E)
- Ordenamientos: O(C log C)
- Modificaciones (añadir/eliminar): O(C + N) porque se reescribe el CSV

**Conclusión:** Diría que el diseño es eficiente para consultas y recorridos, per se rezaga en términos de modificaciones de csv, con rendimiento lineal.

---

### **SICT0302B: Toma decisiones**

#### 1. Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente

- Se seleccionó `std::sort`, algoritmo estándar de la STL con garantía O(n log n)
- Se implementan correctamente comparadores lambda para orden por alfabético por nombre, alcance (en miles, descendente), número de rutinas (descendente) 

#### 2. Selecciona una estructura de datos adecuada al problema y lo usa correctamente

| Necesidad | Estructura elegida | Razón de elección |
|-|-|-|
| Búsqueda rápida por ID | `unordered_map<string, T>` | Acceso O(1) promedio, clave única (ID) |
| Representar relaciones múltiples | Grafo de adyacencia con `unordered_map<string, vector<string>>` | Permite relaciones bidireccionales y recorridos |
| Recorrido de relaciones cercanas | Algoritmo BFS (cola y conjunto visitados)| Encuentra todos los nodos conectados eficientemente |
| Listas de IDs (rutinas, networks) | `vector<string>` | Tamaño moderado, inserción al final frecuente |
| Evitar nodos repetidos en BFS | `unordered_set<string>` | Búsqueda O(1) de visitados, no permite duplicados, tamaño dinámico |

**Las estructuras son adecuadas** para el contexto del problema.

---

### **SICT0303B: Implementa acciones científicas**

#### 1. Implementa mecanismos para consultar información de las estructuras correctos

- Consulta directa por ID: `getRutina()`, `getCreador()`, `getNetwork()`, **O(1)**
- Listado ordenado de creadores bajo 3 criterios diferentes
- Búsqueda de relaciones conectadas, mediante BFS, desde cualquier nodo
- Despliegue claro diferenciando tipo de nodo (Creador/Rutina/Network)

#### 2. Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta

- Lectura correcta de 3 archivos CSV (`rutinas.csv`, `creadores.csv` (con listas separadas por ';'), `networks.csv`)
- Uso correcto de `getline`, `stringstream`, `stoi`

#### 3. Implementa mecanismos de escritura de archivos para guardar los datos de las estructuras de manera correcta

- Al añadir o eliminar un creador:
  - Se actualiza el grafo
  - Se actualizan las listas bidireccionales
  - **Se reescribe completamente** `creadores.csv` y `networks.csv` con los datos actualizados
  - Se usa función auxiliar `joinV` para convertir vectores, strings con ';'
- Las modificaciones se reflejan efectivamente en los 'csv' correspondientes.

### Referencias:

  - Llamas, L. (2024, 21 noviembre). Qué son y cómo usar las funciones lambda en C++. Luis Llamas. https://www.luisllamas.es/cpp-funciones-lambda/
  - std::sort - cppreference.com. (s. f.). https://en.cppreference.com/w/cpp/algorithm/sort.html
  - GeeksforGeeks. (2025, 21 agosto). std::find_if , std::find_if_not in C++. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/stdfind_if-stdfind_if_not-in-c/
  - std::vector - cppreference.com. (s. f.). https://en.cppreference.com/w/cpp/container/vector.html
  - GeeksforGeeks. (2025a, julio 23). Unordered Map in C++ STL. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/unordered_map-in-cpp-stl/
  - std::unordered_set - cppreference.com. (s. f.). https://en.cppreference.com/w/cpp/container/unordered_set.html
  - GeeksforGeeks. (2025, 30 septiembre). Queue in C++ STL. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/queue-cpp-stl/
