# 📌 CSE331 Assignment #2
20211061 Jaemin Kim
<br>
<br>

# 🗺️ Solving the Traveling Salesman Problem

## 🚀 Quick Start
```bash
make
python3 auto_eval.py
```
<br>

## 🧠 Algorithms
### 1. MST-Based 2-Approximation Algorithm
### 2. Held-Karp Algorithm
### 3. Node-Greedy Algorithm (Nearest Neighbor)
### 4. Edge-Greedy Algorithm
### 5. Jam Algorithm (Edge + Node Greedy): Ours

<br>

## 📄 Paper
[View pdf](https://unistackr0-my.sharepoint.com/:b:/g/personal/jm611_unist_ac_kr/EfY3arcyGj5Pp2UPgQoVFT4BUryAKzRDnb9bz4jxDa1kzg?e=SVdBtx)

<br>

## 📊 Experiments
### Datasets

- jam20 (jam20.tsp) created for this experiment
- a280 dataset (a280.tsp.gz) from TSPLIB
- XQL662 (xql662.tsp) from TTD
- Kazakhstan data (kz9976.tsp) from TTD
- Mona Lisa TSP Challenge (mona-lisa100K.tsp) from TTD

| Dataset            | Number of Nodes | Optimal Tour Length            |
|--------------------|-----------------|--------------------------------|
| jam20              | 20              | 1,008                          |
| a280               | 280             | 2,579                          |
| XQL662             | 662             | 2,513                          |
| Kazakhstan (OPEN)  | 9,976           | 1,061,881 (best known)         |
| Mona Lisa (OPEN)   | 100,000         | 5,757,191 (best known)         |

![[jam20] Optimal TSP Tour](images/jam20_optimal_tsp_tour.png)

<br>

### Results
| Dataset           | Algorithm          | Tour Length | Approx. Ratio | Running Time (s) | Peak Memory (KB) |
|-------------------|--------------------|-------------|---------------|------------------|------------------|
| jam20             | MST-Based          | 1,414       | 1.4028        | 0.000012         | 256              |
| jam20             | Held-Karp          | 1,008       | 1.0000        | 0.4220           | 6,229,528        |
| jam20             | Nearest Neighbor   | 1,022       | 1.0139        | **0.000003**     | 128              |
| jam20             | Edge-Greedy        | **1,023**   | **1.0149**    | 0.000014         | 128              |
| jam20             | *Jam*              | **1,023**   | **1.0149**    | 0.000022         | 128              |
|                   |                    |             |               |                  |                  |
| a280              | MST-Based          | 3,791       | 1.4700        | 0.000754         | 128              |
| a280              | Held-Karp          | OOM         | OOM           | OOM              | OOM              |
| a280              | Nearest Neighbor   | 3,157       | 1.2241        | **0.000211**     | 128              |
| a280              | Edge-Greedy        | **2,940**   | **1.1400**    | 0.002677         | 128              |
| a280              | *Jam*              | 3,154       | 1.2230        | 0.000637         | 128              |
|                   |                    |             |               |                  |                  |
| xql662            | MST-Based          | 3,691       | 1.4688        | 0.004513         | 128              |
| xql662            | Held-Karp          | OOM         | OOM           | OOM              | OOM              |
| xql662            | Nearest Neighbor   | 3,124       | 1.2431        | **0.000659**     | 128              |
| xql662            | Edge-Greedy        | **2,977**   | **1.1846**    | 0.017083         | 128              |
| xql662            | *Jam*              | 3,093       | 1.2308        | 0.002518         | 128              |
|                   |                    |             |               |                  |                  |
| kz9976            | MST-Based          | 1,455,573   | 1.3708        | 0.725799         | 26,892           |
| kz9976            | Held-Karp          | OOM         | OOM           | OOM              | OOM              |
| kz9976            | Nearest Neighbor   | 1,358,249   | 1.2791        | **0.19234**      | **4,096**        |
| kz9976            | Edge-Greedy        | **1,254,627** | **1.1815**  | 4.888047         | 739,008          |
| kz9976            | *Jam*              | 1,320,994   | 1.2440        | 0.233221         | 6,468            |
|                   |                    |             |               |                  |                  |
| mona-lisa100K     | MST-Based          | 8,390,648   | 1.4574        | 39.045299        | 269,952          |
| mona-lisa100K     | Held-Karp          | OOM         | OOM           | OOM              | OOM              |
| mona-lisa100K     | Nearest Neighbor   | 6,846,598   | 1.1892        | 28.103539        | **6,740**        |
| mona-lisa100K     | Edge-Greedy        | OOM         | OOM           | OOM              | OOM              |
| mona-lisa100K     | *Jam*              | **6,591,603** | **1.1449**  | **21.284041**    | 49,536           |
