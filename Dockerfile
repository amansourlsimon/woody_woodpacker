FROM ubuntu

WORKDIR /usr/src/app

RUN apt-get update && \
    apt-get -y install clang && \
	apt-get -y install make && \
	apt-get -y install nasm

COPY . .
