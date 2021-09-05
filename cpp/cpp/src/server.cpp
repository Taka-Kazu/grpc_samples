#include <grpc++/grpc++.h>
#include <grpc++/ext/proto_server_reflection_plugin.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include "object.pb.h"
#include "object.grpc.pb.h"

class ObjectDetectionImpl final : public grpc_samples::ObjectDetection::Service
{
  virtual ::grpc::Status GetObject(::grpc::ServerContext *context, const ::grpc_samples::ObjectRequest *request, ::grpc_samples::ObjectResponse *response)
  {
    ::grpc_samples::Object obj;
    const char* id_str = "test";
    obj.set_id(id_str);
    std::random_device gen;
    std::mt19937 engine(gen());
    std::uniform_real_distribution<> dist(-1.0, 1.0);
    obj.set_x(dist(engine));
    obj.set_y(dist(engine));
    obj.set_yaw(dist(engine) * M_PI);
    response->mutable_obj()->CopyFrom(obj);
    return ::grpc::Status::OK;
  }
};

int main(int argc, char** argv)
{
  const std::string addr = "0.0.0.0:50051";
  ObjectDetectionImpl service;

  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  builder.AddListeningPort(addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server: Listening on " << addr << std::endl;
  server->Wait();
  return 0;
}
