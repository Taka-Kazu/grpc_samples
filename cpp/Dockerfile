FROM alpine:3.14

RUN apk add \
  cmake \
  gcc \
  g++ \
  make \
  grpc \
  grpc-dev \
  c-ares-dev \
  zlib-dev \
  protoc \
  libprotobuf \
  protobuf-dev \
  bash

COPY ./cpp/cpp /home/cpp

COPY ./proto /home/cpp/proto

RUN cd /home/cpp && mkdir build && cd build && cmake .. && make && make install

WORKDIR /home
