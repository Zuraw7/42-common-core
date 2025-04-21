# push_swap

**push_swap** is a project developed as part of the **42** program. The goal is to design and implement an algorithm that sorts integers using a limited set of operations on two stacks — `a` and `b`.

The project focuses on minimizing the number of operations and is written in **C**. Algorithm I used is called Turk Algorith, closly described here: https://medium.com/@ayogun/push-swap-c1f5d2d41e97

## Repository Structure

- `sources/` – main part of the program responsible for generating and executing sorting operations  
- `includes/` – contains the header file for push_swap and the custom libft library  
- `bonus/` – additional program called `checker`, which validates the correctness of the operations  
- `Makefile` – used to build the project


## Project Objective

The goal is to write a program `push_swap` that:
- takes a list of integers as input
- sorts them using two stacks (`a` and `b`) and a limited set of allowed operations
- prints the sequence of operations to standard output
- performs the sorting using the **fewest possible moves**


## 🔧 Allowed Operations

- **Swap** – swaps the first two elements at the top of a stack  
    - `sa` – on stack a  
    - `sb` – on stack b  
    - `ss` – on both stacks simultaneously

- **Push** – moves the top element from one stack to the other  
    - `pa` – from stack b to stack a  
    - `pb` – from stack a to stack b

- **Rotate** – shifts all elements of a stack up by one (first becomes last)  
    - `ra` – on stack a  
    - `rb` – on stack b  
    - `rr` – on both stacks simultaneously

- **Reverse rotate** – shifts all elements of a stack down by one (last becomes first)  
    - `rra` – on stack a  
    - `rrb` – on stack b  
    - `rrr` – on both stacks simultaneously


## Sorting Algorithm

To minimize the number of operations, I implemented the **Turk Algorithm** – a strategy optimized for the constraints of the `push_swap` project.  

It works as follows:
- Push the first 2 elements from stack A to stack B  
- For every remaining number in stack A, calculate the cost for it to be placed in the correct position in stack B  
- Push the element with the **lowest cost** to stack B  
- Repeat until stack A contains only 3 elements  
- Sort the 3 remaining elements in stack A in ascending order  
- For each number in stack B, calculate the cost of placing it in the correct position in stack A  
- Push the element with the **lowest cost** to stack A  
- Repeat until stack B is empty  
- If stack A is not fully sorted, find the **lowest number** and rotate it to the top of the stack

More details can be found in [this article about the Turk Algorithm](https://medium.com/@ayogun/push-swap-c1f5d2d41e97).


## Bonus – `checker`

The `checker` program:
- takes the same input as `push_swap`
- reads a sequence of operations from the terminal
- checks whether the result leaves stack `a` sorted in ascending order and stack `b` empty


## Usage Example

push_swap
```bash
./push_swap 3 2 1
# output: ra sa

./push_swap 5 1 3 2 3
# output: ra pb ra pb rra sa pa pa
```

bonus
```bash
./push_swap 3 2 1 | ./checker 3 2 1
# output: OK

ARG="5 1 4 2 3"; ./push_swap $ARG | ./checker $ARG
# output: OK
```
