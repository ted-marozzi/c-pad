# C pad

A scratch pad to play with C

## Running

```shell
clang main.c -g -o main
./main
```

## Debugging

Debugging is supported in VSC

## Valgrind

To use valgrind on macOS ARM machines

```shell
docker build --tag 'valgrind' .
docker run -tiv $PWD:/build valgrind
# Inside the container
clang main.c -g -o main
valgrind --leak-check=full --track-origins=yes ./main
```
