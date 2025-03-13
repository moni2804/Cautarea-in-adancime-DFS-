## Algoritmi de Căutare în Adâncime și Sortare Topologică

### Descriere
Această temă presupune implementarea și analiza unor algoritmi fundamentali pentru procesarea grafurilor:

- **Căutarea în Adâncime (DFS)** - explorarea recursivă a unui graf.
- **Sortarea Topologică** - ordonarea nodurilor unui graf orientat aciclic.
- **Algoritmul lui Tarjan** - determinarea componentelor tare conexe (SCC).

Grafurile vor fi reprezentate utilizând **liste de adiacență**.

### Implementare
Fiecare algoritm este implementat într-o funcție separata, iar rezultatele vor fi afișate pentru verificarea corectitudinii.

#### 1. Căutarea în Adâncime (DFS)
- Se parcurge graful folosind strategia DFS.
- Se construiește arborele DFS.

**Demonstrație:**  
1. Afișarea listei de adiacență a grafului inițial.  
2. Executarea DFS și afișarea arborelui rezultat.

#### 2. Sortare Topologică
- Se aplică DFS și se extrag nodurile în ordinea finalizării explorării.

**Demonstrație:**  
1. Afișarea listei de adiacență.  
2. Afișarea ordinii sortate sau motivul imposibilității acesteia.

#### 3. Algoritmul lui Tarjan pentru SCC
- Identifică componentele puternic conexe ale unui graf orientat.

**Demonstrație:**  
1. Afișarea listei de adiacență.  
2. Afișarea componentelor tare conexe.

### Analiză și Comparare

#### 1. Analiza Complexității
| Algoritm            | Complexitate |
|---------------------|-------------|
| **DFS**            | O(V + E)     |
| **Sortare Topologică** | O(V + E) |
| **Tarjan SCC**     | O(V + E)     |

#### 2. Evaluare Performanță pentru DFS
1. **Fixăm |V| = 100** și variem **|E| între 1000 și 4500** (pas 100).  
   - Generăm grafuri aleatoare.
   - Executăm DFS și contorizăm operațiile efectuate.
   - Construim graficul cu numărul de operațiuni în funcție de |E|.

2. **Fixăm |E| = 4500** și variem **|V| între 100 și 200** (pas 10).  
   - Repetăm experimentul și construim graficul cu numărul de operațiuni în funcție de |V|.

### Cum să Rulezi Proiectul
1. **Compilare:**  
   ```bash
   g++ main.cpp -o dfs_program
   ```
2. **Executare:**  
   ```bash
   ./dfs_program
   ```
3. **Interpretarea rezultatelor:**  
   - Verifică corectitudinea algoritmilor prin afișările intermediare.
   - Analizează graficele generate pentru evaluarea performanței.

### Resurse
- **Cormen, Thomas H. et al.** - *Introduction to Algorithms*  
  - DFS: Capitolul 22.3  
  - Sortare Topologică: Capitolul 22.4  
  - Algoritmul lui Tarjan pentru SCC

