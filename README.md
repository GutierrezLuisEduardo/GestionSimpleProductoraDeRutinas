# **GestionSimpleProductoraDeRutinas**
# Introducción General al Código
Programa en c++ que ejemplifica de manera muy simplificada la gestión de información (rutinas, networks, creadores) de una productora de rutinas de contenido en RRSS. Se centra en la consulta ordenada de datos.

El programa carga datos desde archivos CSV (rutinas.csv, creadores.csv y networks.csv), los almacena en estructuras de clases interconectadas y ofrece un menú interactivo para visualizarlos.

# Cómo funciona
1. Se modelan las entidades Rutina, Creador, Network empleando vectores en el proceso y denotando cómo se asocian. (un creador sabe sus networks, y ctdad. de rutinas y una network sabe la ctdad. de  creadores)

2. Permite seleccionar (a través de cin) el orden de la vista de creadores, según los siguientes criterios: 1. Nombre (ascendente, a.getNombre() < b.getNombre()), 2. Alcance en miles (descendente, a.getAlcance() > b.getAlcance()), 3. Rutinas (descendente, a.getNumRutinas() > b.getNumRutinas()); usa std:sort, que requiere de un comparador que en este caso son lambdas.

3. Parsea tres archivos csv (rutinas, creadores, networks.csv) e instancia las entidades modeladas a partir de ello. Y finalmente dispone un menú que permite ver la información de las entidades: rutinas, networks y creadores, para estos últmos permite

### Clases Principales
El código define tres clases que representan las entidades principales. Cada una tiene atributos privados, un constructor, getters y un método `mostrar()` para imprimir información en CLi.

1. **Clase Rutina**:
   - **Atributos**:
     - `idRutina`: String único para identificar la rutina.
     - `tipo`: String que describe el tipo de rutina
     - `publicoMeta`: String para el público objetivo.
     - `cicloProduccion`: Entero que indica un ciclo de producción (número de semanas).
   - **Constructor**: Inicializa todos los atributos directamente.
   - **Getters**: Devuelven los valores de los atributos.
   - **Método mostrar()**: Delimitándolos con " | ", imprime en consola una línea con todos los atributos.
  
2. **Clase Creador**:
   - **Atributos**:
     - `idCreador`: String único para el creador.
     - `nombre`: String con el nombre del creador.
     - `alcance`: String que representa el alcance (en miles de seguidores).
     - `rutinas`: Vector de punteros a alguna Rutina, para varias rutinas.
     - `networks`: Vector de strings con IDs de networks asociadas.
   - **Constructor**: Inicializa id, nombre y alcance; los vectores comienzan vacíos.
   - **Getters**: Incluyen `getNumRutinas()` y `getNumNetworks()` que devuelven el tamaño de los vectores.
   - **Métodos add**:
     - `addRutina(Rutina* r)`: Agrega un puntero a una rutina al vector.
     - `addNetwork(const string& netId)`: Agrega un ID de network al vector.
   - **Método mostrar()**: Imprime ID, nombre, alcance, número de rutinas y número de networks.
   - **Cómo funciona**: Esta clase es central. Los punteros a Rutina permiten referencias sin copiar objetos (eficiente en memoria), pero requieren que las Rutinas existan durante la vida del Creador (lo que se asegura al cargar rutinas primero). No hay borrado de elementos, solo adición.

3. **Clase Network**:
   - **Atributos**:
     - `idNetwork`: String único (ej: "N001").
     - `tematica`: String con la temática (ej: "Fitness").
     - `creadores`: Vector de strings con IDs de creadores asociados.
   - **Constructor**: Inicializa id y tematica; vector vacío.
   - **Getters**: Incluye `getNumCreadores()` para el tamaño del vector.
   - **Método addCreador(const string& id)`: Agrega un ID de creador al vector.
   - **Método mostrar()**: Imprime ID, temática y número de creadores.
   - **Cómo funciona**: Similar a Creador, pero inversa: una network agrupa creadores. La asociación es bidireccional durante la carga (un creador agrega network, y la network agrega al creador).

# Carga de Archivos (Parsing de CSV)
Estas funciones leen archivos CSV y crean objetos. Asumen formato estricto.
**Orden de campos**: Asumen CSV apegado a formato rígido.
- **void cargarRutinas(const string& archivo, vector<Rutina>& rutinas)**:
- **void cargarNetworks(const string& archivo, vector<Network>& networks)**:
- **void cargarCreadores(const string& archivo, vector<Creador>& creadores, vector<Rutina>& rutinas, vector<Network>& networks)**:

# Menú Principal y Programa Principal (main)
Muestra en CLi las opciones del menú y requiere una selección. También se inicialiizan los vectores (Pto. de entrada).
- **void mostrarMenu()**: Imprime opciones del menú y pide selección.
- **int main()**: Pto. de entrada; inicializa vectores, carga datos, entra en bucle de menú.
  - **Cómo funciona paso a paso**:
    1. Declara vectores vacíos: rutinas, creadores, networks.
    2. Llama a cargarRutinas("rutinas.csv", rutinas).
    3. Llama a cargarNetworks("networks.csv", networks).
    4. Llama a cargarCreadores("creadores.csv", creadores, rutinas, networks) y aquí se vinculan.
    5. Bucle do-while:
       - Muestra menú.
       - Lee opción con cin.
       - Switch:
         - 1: Llama ordenarCreadores, luego itera y llama mostrar() por cada creador.
         - 2: Itera y muestra cada rutina.
         - 3: Itera y muestra cada network.
         - 0: Imprime "Programa finalizado." y sale.
         - Default: "Opción inválida."
    6. Retorna 0 (éxito).
  - **Detalles**: 
    - No maneja errores ni valida formatos de los CSV
    - **USA `cin` PARA INPUT**
    - Memoria: los vectores se liberan al terminar la ejecución


# Análisis de complejidad
El algoritmo `std::sort` implementa _Introsort_, una estrategia híbrida basada en división y conquista. Comienza utilizando _Quicksort_, que en promedio logra una complejidad de `O(N·log(N))`, pero que en su peor escenario puede degradarse a `O(N²)`.

Para evitarlo, _Introsort_ combina _Quicksort_ con _Heapsort_, garantizando en todos los casos un rendimiento de `O(N·log(N))`, y utiliza _Insertion Sort_ en subconjuntos pequeños para optimizar la eficiencia práctica.

Cabe mencionar que la complejidad se mide principalmente en el número de comparaciones. Con comparadores simples (como `<` o `std::less{}`), el costo de cada comparación es constante, por lo que se mantiene estrictamente en `O(N·log(N))`. En el caso de comparadores personalizados (como las lambdas que usé), la complejidad sigue siendo la misma TODA VEZ que tienen complejidad `O(1)`, pues únicamente acceden a un atributo y hacen una comparación con `>`.

Finalmente, desde mi opinión y en el contexto de este proyecto, donde los conjuntos de datos no son masivos, la implementación hecha de `std::sort` resulta ser una elección óptima al ofrecer un balance ideal entre eficiencia y desempeño.

# Explicación de consecución de competencias
> SICT0301 - Evalúa los componentes: Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

Evalué los componentes e hice un análisis de complejidad para la implementación de los algoritmos del programa al indagar sobre std::sort, comprenderlo y finalmente implementarlo de manera que, pese a utilizar un comparador distinto de `<`/`std::less{}` (los lambdas), me aseguré de que no estropearan la complejidad de `O(N·log(N))`.

> SICT0302 - Toma decisiones: Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

Justifiqué por qué el algoritmo, que implementé sin contratiempos en el código, es adecuado al problema.

# Referencias:
- Llamas, L. (2024, 21 noviembre). Qué son y cómo usar las funciones lambda en C++. Luis Llamas. https://www.luisllamas.es/cpp-funciones-lambda/
- std::sort - cppreference.com. (s. f.). https://en.cppreference.com/w/cpp/algorithm/sort.html
- GeeksforGeeks. (2025, 21 agosto). std::find_if , std::find_if_not in C++. GeeksforGeeks. https://www.geeksforgeeks.org/cpp/stdfind_if-stdfind_if_not-in-c/
