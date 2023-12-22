# C pad

A scratch pad to play with C

## Valgrind

To use valgrind on macOS ARM machines

```shell
docker build --tag 'valgrind' .
docker run -tiv $PWD:/build valgrind
# Inside the container
clang main.c -g -o main
valgrind ./main
```
