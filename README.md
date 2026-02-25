_This project has been created as part of the 42 curriculum by homura._

# Philosophers

## Description
The Philosophers project is a simulation of the classic "Dining Philosophers Problem" implemented in C. This is a famous computer science puzzle about sharing resources, designed to explore the fundamentals of multi-threading and concurrency.

The goal of this project is to understand the issues that arise when using multi-threading and to learn how to resolve them.

The Rules:  
![Dining Philosophers Problem](https://upload.wikimedia.org/wikipedia/commons/thumb/7/7b/An_illustration_of_the_dining_philosophers_problem.png/250px-An_illustration_of_the_dining_philosophers_problem.png)
- Philosophers sit around a circular table.
- They alternate between eating, sleeping, and thinking.
- To eat, a philosopher must pick up two forks (one on their left and one on their right).
- When they finish eating, they put down their forks and start sleeping.

The Goal:  
The goal is to keep all philosophers alive as long as possible.
To achieve this, I learned how to use Threads and Mutex to solve two big problems:

- Deadlock: Philosophers waiting for each other forever.
- Data Race: Two threads changing the same data at the same time.

The simulation demonstrates proper use of threading, mutex synchronization, and race condition prevention in a multi-threaded environment.

## Instructions
### Compilation

```bash
cd philo
make
```

### Execution

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

#### Arguments:

- `number_of_philosophers`: Number of philosophers (and forks)
- `time_to_die`(in milliseconds): If a philosopher has not started eating within time_to_die milliseconds since the start of their last meal or the start of the simulation, they die.
- `time_to_eat`(in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
- `time_to_sleep`(in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat`(Optional): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

#### Examples:

##### Basic simulation with 4 philosophers (even)
```bash
./philo 4 1000 200 200
```

##### Simulation with meal limit
```bash
./philo 5 1000 200 200 3
```
### Outputs
```bush
./philo 4 1000 200 200
<time(ms)> <ID of Philo> <action>

#example
1403 4 is eating
```

## Leak check & debugging (Linux/Ubuntu)

Use Valgrind for detecting data races and memory leaks:

1. Data race check (recommended):
```
valgrind --tool=drd ./philo args...
```
2. Detailed data race check:
```
valgrind --tool=helgrind ./philo args...
```
3. Memory leak check:
```
valgrind --leak-check=full ./philo args...
```
## Resources

- [Philosophers visualizer](https://nafuka11.github.io/philosophers-visualizer/)
- [食事する哲学者の問題](https://ja.wikipedia.org/wiki/%E9%A3%9F%E4%BA%8B%E3%81%99%E3%82%8B%E5%93%B2%E5%AD%A6%E8%80%85%E3%81%AE%E5%95%8F%E9%A1%8C)


### AI Usage

AI was used to assist with:
- Debugging threading synchronization issues
- Explanation of complex threading concepts using analogies
