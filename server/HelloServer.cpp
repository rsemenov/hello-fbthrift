#include <glog/logging.h>
#include <folly/init/Init.h>
#include <folly/portability/GFlags.h>
#include <proxygen/httpserver/HTTPServerOptions.h>
#include <HelloService.h>
#include <thrift/lib/cpp2/server/ThriftServer.h>
#include <thrift/lib/cpp2/transport/core/ThriftProcessor.h>
#include <thrift/lib/cpp2/transport/http2/common/HTTP2RoutingHandler.h>

DEFINE_int32(hello_port, 7778, "Hello Server port");

using apache::thrift::HTTP2RoutingHandler;
using apache::thrift::ThriftServer;
using apache::thrift::ThriftServerAsyncProcessorFactory;
using example::hello::HelloHandler;
using proxygen::HTTPServerOptions;

std::unique_ptr<HTTP2RoutingHandler> createHTTP2RoutingHandler(
    std::shared_ptr<ThriftServer> server) {
  auto h2_options = std::make_unique<HTTPServerOptions>();
  h2_options->threads = static_cast<size_t>(server->getNumIOWorkerThreads());
  h2_options->idleTimeout = server->getIdleTimeout();
  h2_options->shutdownOn = {SIGINT, SIGTERM};
  return std::make_unique<HTTP2RoutingHandler>(
      std::move(h2_options), server->getThriftProcessor(), *server);
}

template <typename ServiceHandler>
std::shared_ptr<ThriftServer> newServer(int32_t port) {
  auto handler = std::make_shared<ServiceHandler>();
  auto proc_factory =
      std::make_shared<ThriftServerAsyncProcessorFactory<ServiceHandler>>(
          handler);
  auto server = std::make_shared<ThriftServer>();
  server->setPort(port);
  server->setProcessorFactory(proc_factory);
  server->addRoutingHandler(createHTTP2RoutingHandler(server));
  return server;
}

int main(int argc, char** argv) {
  FLAGS_logtostderr = 1;
  folly::init(&argc, &argv);

  //auto chatroom_server = newServer<ChatRoomServiceHandler>(FLAGS_chatroom_port);
  //std::thread t([&] {
  //  LOG(INFO) << "ChatRoom Server running on port: " << FLAGS_chatroom_port;
  //  chatroom_server->serve();
  //});

  auto hello_server = newServer<HelloHandler>(FLAGS_hello_port);
  LOG(INFO) << "Hello Server running on port: " << FLAGS_hello_port;
  hello_server->serve();

  return 0;
}