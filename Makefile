all: cpp

.PHONY: cpp
cpp:
	protoc -I./proto --cpp_out=cpp/cpp/src ./proto/*.proto; protoc -I./proto --grpc_out=cpp/cpp/src --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./proto/*.proto

.PHONY: clean
clean:
	rm -rf ./cpp/cpp/src/*.pb.*
