// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sendReceiveWeights.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_sendReceiveWeights_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_sendReceiveWeights_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3015000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3015008 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_sendReceiveWeights_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_sendReceiveWeights_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[2]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sendReceiveWeights_2eproto;
::PROTOBUF_NAMESPACE_ID::Metadata descriptor_table_sendReceiveWeights_2eproto_metadata_getter(int index);
namespace params {
class WeightsToClient;
struct WeightsToClientDefaultTypeInternal;
extern WeightsToClientDefaultTypeInternal _WeightsToClient_default_instance_;
class WeightsToServer;
struct WeightsToServerDefaultTypeInternal;
extern WeightsToServerDefaultTypeInternal _WeightsToServer_default_instance_;
}  // namespace params
PROTOBUF_NAMESPACE_OPEN
template<> ::params::WeightsToClient* Arena::CreateMaybeMessage<::params::WeightsToClient>(Arena*);
template<> ::params::WeightsToServer* Arena::CreateMaybeMessage<::params::WeightsToServer>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace params {

// ===================================================================

class WeightsToServer PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:params.WeightsToServer) */ {
 public:
  inline WeightsToServer() : WeightsToServer(nullptr) {}
  virtual ~WeightsToServer();
  explicit constexpr WeightsToServer(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  WeightsToServer(const WeightsToServer& from);
  WeightsToServer(WeightsToServer&& from) noexcept
    : WeightsToServer() {
    *this = ::std::move(from);
  }

  inline WeightsToServer& operator=(const WeightsToServer& from) {
    CopyFrom(from);
    return *this;
  }
  inline WeightsToServer& operator=(WeightsToServer&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WeightsToServer& default_instance() {
    return *internal_default_instance();
  }
  static inline const WeightsToServer* internal_default_instance() {
    return reinterpret_cast<const WeightsToServer*>(
               &_WeightsToServer_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(WeightsToServer& a, WeightsToServer& b) {
    a.Swap(&b);
  }
  inline void Swap(WeightsToServer* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WeightsToServer* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WeightsToServer* New() const final {
    return CreateMaybeMessage<WeightsToServer>(nullptr);
  }

  WeightsToServer* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WeightsToServer>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WeightsToServer& from);
  void MergeFrom(const WeightsToServer& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WeightsToServer* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "params.WeightsToServer";
  }
  protected:
  explicit WeightsToServer(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_sendReceiveWeights_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kParametersFieldNumber = 1,
    kTensorTypeFieldNumber = 2,
  };
  // bytes parameters = 1;
  void clear_parameters();
  const std::string& parameters() const;
  void set_parameters(const std::string& value);
  void set_parameters(std::string&& value);
  void set_parameters(const char* value);
  void set_parameters(const void* value, size_t size);
  std::string* mutable_parameters();
  std::string* release_parameters();
  void set_allocated_parameters(std::string* parameters);
  private:
  const std::string& _internal_parameters() const;
  void _internal_set_parameters(const std::string& value);
  std::string* _internal_mutable_parameters();
  public:

  // string tensor_type = 2;
  void clear_tensor_type();
  const std::string& tensor_type() const;
  void set_tensor_type(const std::string& value);
  void set_tensor_type(std::string&& value);
  void set_tensor_type(const char* value);
  void set_tensor_type(const char* value, size_t size);
  std::string* mutable_tensor_type();
  std::string* release_tensor_type();
  void set_allocated_tensor_type(std::string* tensor_type);
  private:
  const std::string& _internal_tensor_type() const;
  void _internal_set_tensor_type(const std::string& value);
  std::string* _internal_mutable_tensor_type();
  public:

  // @@protoc_insertion_point(class_scope:params.WeightsToServer)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr parameters_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr tensor_type_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_sendReceiveWeights_2eproto;
};
// -------------------------------------------------------------------

class WeightsToClient PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:params.WeightsToClient) */ {
 public:
  inline WeightsToClient() : WeightsToClient(nullptr) {}
  virtual ~WeightsToClient();
  explicit constexpr WeightsToClient(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  WeightsToClient(const WeightsToClient& from);
  WeightsToClient(WeightsToClient&& from) noexcept
    : WeightsToClient() {
    *this = ::std::move(from);
  }

  inline WeightsToClient& operator=(const WeightsToClient& from) {
    CopyFrom(from);
    return *this;
  }
  inline WeightsToClient& operator=(WeightsToClient&& from) noexcept {
    if (GetArena() == from.GetArena()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const WeightsToClient& default_instance() {
    return *internal_default_instance();
  }
  static inline const WeightsToClient* internal_default_instance() {
    return reinterpret_cast<const WeightsToClient*>(
               &_WeightsToClient_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(WeightsToClient& a, WeightsToClient& b) {
    a.Swap(&b);
  }
  inline void Swap(WeightsToClient* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(WeightsToClient* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline WeightsToClient* New() const final {
    return CreateMaybeMessage<WeightsToClient>(nullptr);
  }

  WeightsToClient* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<WeightsToClient>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const WeightsToClient& from);
  void MergeFrom(const WeightsToClient& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  ::PROTOBUF_NAMESPACE_ID::uint8* _InternalSerialize(
      ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(WeightsToClient* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "params.WeightsToClient";
  }
  protected:
  explicit WeightsToClient(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    return ::descriptor_table_sendReceiveWeights_2eproto_metadata_getter(kIndexInFileMessages);
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kReplyFieldNumber = 1,
  };
  // string reply = 1;
  void clear_reply();
  const std::string& reply() const;
  void set_reply(const std::string& value);
  void set_reply(std::string&& value);
  void set_reply(const char* value);
  void set_reply(const char* value, size_t size);
  std::string* mutable_reply();
  std::string* release_reply();
  void set_allocated_reply(std::string* reply);
  private:
  const std::string& _internal_reply() const;
  void _internal_set_reply(const std::string& value);
  std::string* _internal_mutable_reply();
  public:

  // @@protoc_insertion_point(class_scope:params.WeightsToClient)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr reply_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_sendReceiveWeights_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// WeightsToServer

// bytes parameters = 1;
inline void WeightsToServer::clear_parameters() {
  parameters_.ClearToEmpty();
}
inline const std::string& WeightsToServer::parameters() const {
  // @@protoc_insertion_point(field_get:params.WeightsToServer.parameters)
  return _internal_parameters();
}
inline void WeightsToServer::set_parameters(const std::string& value) {
  _internal_set_parameters(value);
  // @@protoc_insertion_point(field_set:params.WeightsToServer.parameters)
}
inline std::string* WeightsToServer::mutable_parameters() {
  // @@protoc_insertion_point(field_mutable:params.WeightsToServer.parameters)
  return _internal_mutable_parameters();
}
inline const std::string& WeightsToServer::_internal_parameters() const {
  return parameters_.Get();
}
inline void WeightsToServer::_internal_set_parameters(const std::string& value) {
  
  parameters_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void WeightsToServer::set_parameters(std::string&& value) {
  
  parameters_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:params.WeightsToServer.parameters)
}
inline void WeightsToServer::set_parameters(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  parameters_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:params.WeightsToServer.parameters)
}
inline void WeightsToServer::set_parameters(const void* value,
    size_t size) {
  
  parameters_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:params.WeightsToServer.parameters)
}
inline std::string* WeightsToServer::_internal_mutable_parameters() {
  
  return parameters_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* WeightsToServer::release_parameters() {
  // @@protoc_insertion_point(field_release:params.WeightsToServer.parameters)
  return parameters_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void WeightsToServer::set_allocated_parameters(std::string* parameters) {
  if (parameters != nullptr) {
    
  } else {
    
  }
  parameters_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), parameters,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:params.WeightsToServer.parameters)
}

// string tensor_type = 2;
inline void WeightsToServer::clear_tensor_type() {
  tensor_type_.ClearToEmpty();
}
inline const std::string& WeightsToServer::tensor_type() const {
  // @@protoc_insertion_point(field_get:params.WeightsToServer.tensor_type)
  return _internal_tensor_type();
}
inline void WeightsToServer::set_tensor_type(const std::string& value) {
  _internal_set_tensor_type(value);
  // @@protoc_insertion_point(field_set:params.WeightsToServer.tensor_type)
}
inline std::string* WeightsToServer::mutable_tensor_type() {
  // @@protoc_insertion_point(field_mutable:params.WeightsToServer.tensor_type)
  return _internal_mutable_tensor_type();
}
inline const std::string& WeightsToServer::_internal_tensor_type() const {
  return tensor_type_.Get();
}
inline void WeightsToServer::_internal_set_tensor_type(const std::string& value) {
  
  tensor_type_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void WeightsToServer::set_tensor_type(std::string&& value) {
  
  tensor_type_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:params.WeightsToServer.tensor_type)
}
inline void WeightsToServer::set_tensor_type(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  tensor_type_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:params.WeightsToServer.tensor_type)
}
inline void WeightsToServer::set_tensor_type(const char* value,
    size_t size) {
  
  tensor_type_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:params.WeightsToServer.tensor_type)
}
inline std::string* WeightsToServer::_internal_mutable_tensor_type() {
  
  return tensor_type_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* WeightsToServer::release_tensor_type() {
  // @@protoc_insertion_point(field_release:params.WeightsToServer.tensor_type)
  return tensor_type_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void WeightsToServer::set_allocated_tensor_type(std::string* tensor_type) {
  if (tensor_type != nullptr) {
    
  } else {
    
  }
  tensor_type_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), tensor_type,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:params.WeightsToServer.tensor_type)
}

// -------------------------------------------------------------------

// WeightsToClient

// string reply = 1;
inline void WeightsToClient::clear_reply() {
  reply_.ClearToEmpty();
}
inline const std::string& WeightsToClient::reply() const {
  // @@protoc_insertion_point(field_get:params.WeightsToClient.reply)
  return _internal_reply();
}
inline void WeightsToClient::set_reply(const std::string& value) {
  _internal_set_reply(value);
  // @@protoc_insertion_point(field_set:params.WeightsToClient.reply)
}
inline std::string* WeightsToClient::mutable_reply() {
  // @@protoc_insertion_point(field_mutable:params.WeightsToClient.reply)
  return _internal_mutable_reply();
}
inline const std::string& WeightsToClient::_internal_reply() const {
  return reply_.Get();
}
inline void WeightsToClient::_internal_set_reply(const std::string& value) {
  
  reply_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArena());
}
inline void WeightsToClient::set_reply(std::string&& value) {
  
  reply_.Set(
    ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::move(value), GetArena());
  // @@protoc_insertion_point(field_set_rvalue:params.WeightsToClient.reply)
}
inline void WeightsToClient::set_reply(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  reply_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(value), GetArena());
  // @@protoc_insertion_point(field_set_char:params.WeightsToClient.reply)
}
inline void WeightsToClient::set_reply(const char* value,
    size_t size) {
  
  reply_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, ::std::string(
      reinterpret_cast<const char*>(value), size), GetArena());
  // @@protoc_insertion_point(field_set_pointer:params.WeightsToClient.reply)
}
inline std::string* WeightsToClient::_internal_mutable_reply() {
  
  return reply_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArena());
}
inline std::string* WeightsToClient::release_reply() {
  // @@protoc_insertion_point(field_release:params.WeightsToClient.reply)
  return reply_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}
inline void WeightsToClient::set_allocated_reply(std::string* reply) {
  if (reply != nullptr) {
    
  } else {
    
  }
  reply_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), reply,
      GetArena());
  // @@protoc_insertion_point(field_set_allocated:params.WeightsToClient.reply)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace params

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_sendReceiveWeights_2eproto