// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: sdk_transport.proto
#ifndef GRPC_sdk_5ftransport_2eproto__INCLUDED
#define GRPC_sdk_5ftransport_2eproto__INCLUDED

#include "sdk_transport.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace params {

// service WeightsPasser {
// //rpc sendWeights (WeightsToServer) returns (WeightsToClient) {}
// rpc streamWeights (stream Parameters) returns (stream Parameters) {}
// rpc sendWeights (Parameters) returns (stream Parameters) {}
// }
//
class FlowerServiceSDK final {
 public:
  static constexpr char const* service_full_name() {
    return "params.FlowerServiceSDK";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>> Join(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>>(JoinRaw(context));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>> AsyncJoin(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>>(AsyncJoinRaw(context, cq, tag));
    }
    std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>> PrepareAsyncJoin(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>>(PrepareAsyncJoinRaw(context, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void Join(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::params::ClientMessage,::params::ServerMessage>* reactor) = 0;
      #else
      virtual void Join(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::params::ClientMessage,::params::ServerMessage>* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>* JoinRaw(::grpc::ClientContext* context) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>* AsyncJoinRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) = 0;
    virtual ::grpc::ClientAsyncReaderWriterInterface< ::params::ClientMessage, ::params::ServerMessage>* PrepareAsyncJoinRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());
    std::unique_ptr< ::grpc::ClientReaderWriter< ::params::ClientMessage, ::params::ServerMessage>> Join(::grpc::ClientContext* context) {
      return std::unique_ptr< ::grpc::ClientReaderWriter< ::params::ClientMessage, ::params::ServerMessage>>(JoinRaw(context));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::params::ClientMessage, ::params::ServerMessage>> AsyncJoin(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::params::ClientMessage, ::params::ServerMessage>>(AsyncJoinRaw(context, cq, tag));
    }
    std::unique_ptr<  ::grpc::ClientAsyncReaderWriter< ::params::ClientMessage, ::params::ServerMessage>> PrepareAsyncJoin(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncReaderWriter< ::params::ClientMessage, ::params::ServerMessage>>(PrepareAsyncJoinRaw(context, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void Join(::grpc::ClientContext* context, ::grpc::ClientBidiReactor< ::params::ClientMessage,::params::ServerMessage>* reactor) override;
      #else
      void Join(::grpc::ClientContext* context, ::grpc::experimental::ClientBidiReactor< ::params::ClientMessage,::params::ServerMessage>* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientReaderWriter< ::params::ClientMessage, ::params::ServerMessage>* JoinRaw(::grpc::ClientContext* context) override;
    ::grpc::ClientAsyncReaderWriter< ::params::ClientMessage, ::params::ServerMessage>* AsyncJoinRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) override;
    ::grpc::ClientAsyncReaderWriter< ::params::ClientMessage, ::params::ServerMessage>* PrepareAsyncJoinRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Join_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    virtual ::grpc::Status Join(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* stream);
  };
  template <class BaseClass>
  class WithAsyncMethod_Join : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_Join() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Join() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Join(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestJoin(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Join<Service > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_Join : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_Join() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::params::ClientMessage, ::params::ServerMessage>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context) { return this->Join(context); }));
    }
    ~ExperimentalWithCallbackMethod_Join() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Join(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerBidiReactor< ::params::ClientMessage, ::params::ServerMessage>* Join(
      ::grpc::CallbackServerContext* /*context*/)
    #else
    virtual ::grpc::experimental::ServerBidiReactor< ::params::ClientMessage, ::params::ServerMessage>* Join(
      ::grpc::experimental::CallbackServerContext* /*context*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_Join<Service > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_Join<Service > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_Join : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_Join() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Join() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Join(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Join : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_Join() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Join() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Join(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestJoin(::grpc::ServerContext* context, ::grpc::ServerAsyncReaderWriter< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* stream, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncBidiStreaming(0, context, stream, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_Join : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_Join() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackBidiHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context) { return this->Join(context); }));
    }
    ~ExperimentalWithRawCallbackMethod_Join() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Join(::grpc::ServerContext* /*context*/, ::grpc::ServerReaderWriter< ::params::ServerMessage, ::params::ClientMessage>* /*stream*/)  override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* Join(
      ::grpc::CallbackServerContext* /*context*/)
    #else
    virtual ::grpc::experimental::ServerBidiReactor< ::grpc::ByteBuffer, ::grpc::ByteBuffer>* Join(
      ::grpc::experimental::CallbackServerContext* /*context*/)
    #endif
      { return nullptr; }
  };
  typedef Service StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef Service StreamedService;
};

}  // namespace params


#endif  // GRPC_sdk_5ftransport_2eproto__INCLUDED
