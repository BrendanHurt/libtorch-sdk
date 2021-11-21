// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: sdk_transport.proto

#include "sdk_transport.pb.h"
#include "sdk_transport.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace flower_sdk {

static const char* FlowerServiceSDK_method_names[] = {
  "/flower_sdk.FlowerServiceSDK/Join",
};

std::unique_ptr< FlowerServiceSDK::Stub> FlowerServiceSDK::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< FlowerServiceSDK::Stub> stub(new FlowerServiceSDK::Stub(channel, options));
  return stub;
}

FlowerServiceSDK::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_Join_(FlowerServiceSDK_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::ClientReaderWriter< ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>* FlowerServiceSDK::Stub::JoinRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>::Create(channel_.get(), rpcmethod_Join_, context);
}

void FlowerServiceSDK::Stub::experimental_async::Join(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::flower_sdk::ClientMessage,::flower_sdk::ServerMessage>* reactor) {
  ::grpc::internal::ClientCallbackReaderWriterFactory< ::flower_sdk::ClientMessage,::flower_sdk::ServerMessage>::Create(stub_->channel_.get(), stub_->rpcmethod_Join_, context, reactor);
}

::grpc::ClientAsyncReaderWriter< ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>* FlowerServiceSDK::Stub::AsyncJoinRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>::Create(channel_.get(), cq, rpcmethod_Join_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>* FlowerServiceSDK::Stub::PrepareAsyncJoinRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>::Create(channel_.get(), cq, rpcmethod_Join_, context, false, nullptr);
}

FlowerServiceSDK::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      FlowerServiceSDK_method_names[0],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< FlowerServiceSDK::Service, ::flower_sdk::ClientMessage, ::flower_sdk::ServerMessage>(
          [](FlowerServiceSDK::Service* service,
             ::grpc::ServerContext* ctx,
             ::grpc::ServerReaderWriter<::flower_sdk::ServerMessage,
             ::flower_sdk::ClientMessage>* stream) {
               return service->Join(ctx, stream);
             }, this)));
}

FlowerServiceSDK::Service::~Service() {
}

::grpc::Status FlowerServiceSDK::Service::Join(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::flower_sdk::ServerMessage, ::flower_sdk::ClientMessage>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace flower_sdk
