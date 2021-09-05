#include <grpc++/grpc++.h>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include "object.pb.h"
#include "object.grpc.pb.h"

int main(int argc, char** argv)
{
  const std::string addr = "server:50051";

  ::grpc_samples::ObjectDetection::Stub stub(grpc::CreateChannel(addr, grpc::InsecureChannelCredentials()));
  for (unsigned int i = 0; i < 10; i++)
  {
    std::cout << i << std::endl;
    grpc::ClientContext context;
    ::grpc_samples::ObjectRequest req;
    ::grpc_samples::ObjectResponse res;
    grpc::Status status = stub.GetObject(&context, req, &res);
    if (status.ok())
    {
      std::cout << "id: " << res.obj().id() << std::endl;
      std::cout << "x: " << res.obj().x() << std::endl;
      std::cout << "y: " << res.obj().y() << std::endl;
      std::cout << "yaw: " << res.obj().yaw() << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    else
    {
      std::cout << "gRPC failed" << std::endl;
      return -1;
    }
  }
  return 0;
}

