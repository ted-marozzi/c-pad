# C pad

A scratch pad to play with C

## Running

```shell
./sake
```

## Valgrind

To use valgrind on macOS ARM machines

```shell
docker build --tag 'valgrind' .
docker run -tiv $PWD:/build valgrind
# Inside the container
./sake build -d
valgrind --leak-check=full --track-origins=yes ./bin/main
```
