# SO2026 — Programação Concorrente com Threads e Semáforos em C

Coleção de exercícios da disciplina de **Sistemas Operacionais**, implementando os problemas clássicos de concorrência com `pthreads` e semáforos POSIX (`sem_t`) em C. Os programas evoluem de forma incremental: primeiro expõem o problema (condição de corrida), depois demonstram as soluções canônicas de sincronização.

## Sumário dos exercícios

| Arquivo | Problema | Conceito demonstrado |
|---------|----------|----------------------|
| [`1.c`](1.c) | Condição de corrida | Duas threads incrementam uma variável compartilhada sem proteção — o resultado final é imprevisível e quase sempre menor que o esperado (2.000.000). |
| [`2.c`](2.c) | Correção com mutex | O mesmo incremento do `1.c`, agora protegido por um semáforo binário (`sem_wait`/`sem_post`), garantindo exclusão mútua e resultado correto. |
| [`3.c`](3.c) | Semáforo contador | Simulação de um estacionamento com **3 vagas** e 8 carros chegando — usa um semáforo inicializado com contagem 3 para limitar o acesso simultâneo a um recurso com múltiplas unidades. |
| [`4.c`](4.c) | Sincronização Ping-Pong | Duas threads alternam impressão de "PING" e "PONG" usando dois semáforos que se revezam, garantindo alternância estrita. |
| [`5.c`](5.c) | Barreira de sincronização | 4 threads processam uma "Parte A" em tempos diferentes, mas só avançam para a "Parte B" depois que **todas** chegarem — implementado com mutex + contador + semáforo de liberação. |
| [`6.c`](6.c) | Produtor-Consumidor (buffer=1) | Versão mínima do problema clássico: um produtor e um consumidor compartilhando uma única posição de buffer, sincronizados por dois semáforos (`empty`/`full`). |
| [`7.c`](7.c) | Produtor-Consumidor (buffer circular) | Generalização do `6.c`: buffer circular de 5 posições, **2 produtores e 2 consumidores** concorrentes, com semáforo de exclusão mútua adicional para proteger os índices do buffer. |
| [`8.c`](8.c) | Jantar dos Filósofos | Solução clássica com 5 filósofos e 5 garfos (semáforos), evitando deadlock ao inverter a ordem de aquisição dos garfos para filósofos de índice par vs. ímpar (quebra a espera circular). |

## Como compilar e executar

Todos os exercícios usam `pthread` e, a partir do `2.c`, também `semaphore.h`. Compile com a flag `-pthread`:

```bash
gcc -pthread 1.c -o ex1 && ./ex1
gcc -pthread 8.c -o ex8 && ./ex8
```

## Por que isso importa

Esses 8 arquivos cobrem, na prática, os principais mecanismos de sincronização vistos em qualquer curso de Sistemas Operacionais:

- **Exclusão mútua** (mutex/semáforo binário) — `2.c`
- **Controle de acesso a recursos limitados** (semáforo contador) — `3.c`
- **Sincronização entre threads sem dados compartilhados** — `4.c`
- **Barreiras de sincronização** — `5.c`
- **O problema Produtor-Consumidor**, do caso trivial ao generalizado — `6.c`, `7.c`
- **Prevenção de deadlock** em recursos compartilhados cíclicos — `8.c`

## Possíveis melhorias

- [ ] Adicionar um `Makefile` para compilar todos os exercícios de uma vez
- [ ] Renomear os arquivos de `1.c`...`8.c` para nomes descritivos (ex: `03_estacionamento_semaforo.c`), o que também ajuda a navegação sem depender só do README
- [ ] Adicionar testes ou asserts automáticos para os casos determinísticos (ex: `1.c` vs `2.c`), em vez de inspeção visual do output

## Autor

Gabriel Almeida Della Croce — [github.com/Gadelc-2004](https://github.com/Gadelc-2004)
