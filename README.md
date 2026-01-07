# Projeto C: Planeamento e Execução de Robô em Grid

## Descrição
Este projeto simula o planeamento e execução de um robô que navega por uma grelha (grid) para recolher pacotes, evitando obstáculos e retornando à base. O robô utiliza algoritmos de caminho mínimo (Dijkstra) para calcular rotas eficientes.

## Estrutura do Projeto

- `src/` — Código-fonte principal
  - `main.c` — Função principal e fluxo do programa
  - `robot.c` — Lógica do robô (criação, planeamento, execução)
  - `grid.c` — Estruturas e funções para manipulação da grid
  - `map.c` — Geração de mapas aleatórios
  - `pathfinder.c` — Algoritmo de Dijkstra para caminhos
  - `structures.c` — Estruturas auxiliares (heap, node)
  - `utils.c` — Utilitários (delay, limpar ecrã)
- `include/` — Headers das funções e estruturas
- `makefile` — Compilação automatizada

## Como Compilar

1. Certifique-se de que tem o GCC instalado.
2. No terminal, navegue até à pasta do projeto.
3. Execute:

```sh
make
```

O executável será gerado na raiz do projeto.

## Como Executar

Após compilar, execute:

```sh
./robot_project
```

O programa irá:
- Gerar uma grid aleatória com obstáculos e pacotes
- Calcular a rota ótima para o robô recolher todos os pacotes
- Simular o movimento do robô na grid

## Principais Funcionalidades

- Geração de mapas aleatórios com obstáculos e pacotes
- Planeamento de rota usando Dijkstra
- Execução animada do robô na grid
- Estruturas de dados otimizadas (heap mínima)

## Estruturas e Algoritmos

- **Grid:** Representação da grelha, células livres, obstáculos, pacotes e robô
- **Robô:** Guarda posição, pacotes a recolher, caminho completo
- **Dijkstra:** Algoritmo para encontrar o caminho mais curto entre dois pontos
- **Heap:** Usada para otimizar o Dijkstra

## Personalização

Pode alterar o tamanho da grid, número de pacotes e obstáculos editando as variáveis no início de `main.c`.

## Autoria

Trabalho por Tierri Monteiro, para a cadeira de Programação (C), do curso Robótica Colaborativa e Inteligência Industrial (Pós-Laboral), no Instituto Politécnico do Cávado e do Ave