FROM ubuntu:latest

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install sudo build-essential clang valgrind git-core -y

WORKDIR /build
