// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sendReceiveWeights.proto

#include "sendReceiveWeights.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace params {
constexpr WeightsToServer::WeightsToServer(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : parameters_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string)
  , tensor_type_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct WeightsToServerDefaultTypeInternal {
  constexpr WeightsToServerDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~WeightsToServerDefaultTypeInternal() {}
  union {
    WeightsToServer _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT WeightsToServerDefaultTypeInternal _WeightsToServer_default_instance_;
constexpr WeightsToClient::WeightsToClient(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : reply_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct WeightsToClientDefaultTypeInternal {
  constexpr WeightsToClientDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~WeightsToClientDefaultTypeInternal() {}
  union {
    WeightsToClient _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT WeightsToClientDefaultTypeInternal _WeightsToClient_default_instance_;
}  // namespace params
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_sendReceiveWeights_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_sendReceiveWeights_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_sendReceiveWeights_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_sendReceiveWeights_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::params::WeightsToServer, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::params::WeightsToServer, parameters_),
  PROTOBUF_FIELD_OFFSET(::params::WeightsToServer, tensor_type_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::params::WeightsToClient, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::params::WeightsToClient, reply_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::params::WeightsToServer)},
  { 7, -1, sizeof(::params::WeightsToClient)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::params::_WeightsToServer_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::params::_WeightsToClient_default_instance_),
};

const char descriptor_table_protodef_sendReceiveWeights_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\030sendReceiveWeights.proto\022\006params\":\n\017We"
  "ightsToServer\022\022\n\nparameters\030\001 \001(\014\022\023\n\013ten"
  "sor_type\030\002 \001(\t\" \n\017WeightsToClient\022\r\n\005rep"
  "ly\030\001 \001(\t2R\n\rweightsPasser\022A\n\013sendWeights"
  "\022\027.params.WeightsToServer\032\027.params.Weigh"
  "tsToClient\"\000b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_sendReceiveWeights_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_sendReceiveWeights_2eproto = {
  false, false, 220, descriptor_table_protodef_sendReceiveWeights_2eproto, "sendReceiveWeights.proto", 
  &descriptor_table_sendReceiveWeights_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_sendReceiveWeights_2eproto::offsets,
  file_level_metadata_sendReceiveWeights_2eproto, file_level_enum_descriptors_sendReceiveWeights_2eproto, file_level_service_descriptors_sendReceiveWeights_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK ::PROTOBUF_NAMESPACE_ID::Metadata
descriptor_table_sendReceiveWeights_2eproto_metadata_getter(int index) {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_sendReceiveWeights_2eproto);
  return descriptor_table_sendReceiveWeights_2eproto.file_level_metadata[index];
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_sendReceiveWeights_2eproto(&descriptor_table_sendReceiveWeights_2eproto);
namespace params {

// ===================================================================

class WeightsToServer::_Internal {
 public:
};

WeightsToServer::WeightsToServer(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:params.WeightsToServer)
}
WeightsToServer::WeightsToServer(const WeightsToServer& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  parameters_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_parameters().empty()) {
    parameters_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_parameters(), 
      GetArena());
  }
  tensor_type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_tensor_type().empty()) {
    tensor_type_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_tensor_type(), 
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:params.WeightsToServer)
}

void WeightsToServer::SharedCtor() {
parameters_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
tensor_type_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

WeightsToServer::~WeightsToServer() {
  // @@protoc_insertion_point(destructor:params.WeightsToServer)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void WeightsToServer::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  parameters_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  tensor_type_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void WeightsToServer::ArenaDtor(void* object) {
  WeightsToServer* _this = reinterpret_cast< WeightsToServer* >(object);
  (void)_this;
}
void WeightsToServer::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void WeightsToServer::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void WeightsToServer::Clear() {
// @@protoc_insertion_point(message_clear_start:params.WeightsToServer)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  parameters_.ClearToEmpty();
  tensor_type_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* WeightsToServer::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // bytes parameters = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_parameters();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string tensor_type = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_tensor_type();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "params.WeightsToServer.tensor_type"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* WeightsToServer::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:params.WeightsToServer)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes parameters = 1;
  if (this->parameters().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_parameters(), target);
  }

  // string tensor_type = 2;
  if (this->tensor_type().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_tensor_type().data(), static_cast<int>(this->_internal_tensor_type().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "params.WeightsToServer.tensor_type");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_tensor_type(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:params.WeightsToServer)
  return target;
}

size_t WeightsToServer::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:params.WeightsToServer)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes parameters = 1;
  if (this->parameters().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_parameters());
  }

  // string tensor_type = 2;
  if (this->tensor_type().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_tensor_type());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void WeightsToServer::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:params.WeightsToServer)
  GOOGLE_DCHECK_NE(&from, this);
  const WeightsToServer* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<WeightsToServer>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:params.WeightsToServer)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:params.WeightsToServer)
    MergeFrom(*source);
  }
}

void WeightsToServer::MergeFrom(const WeightsToServer& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:params.WeightsToServer)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.parameters().size() > 0) {
    _internal_set_parameters(from._internal_parameters());
  }
  if (from.tensor_type().size() > 0) {
    _internal_set_tensor_type(from._internal_tensor_type());
  }
}

void WeightsToServer::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:params.WeightsToServer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WeightsToServer::CopyFrom(const WeightsToServer& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:params.WeightsToServer)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WeightsToServer::IsInitialized() const {
  return true;
}

void WeightsToServer::InternalSwap(WeightsToServer* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  parameters_.Swap(&other->parameters_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  tensor_type_.Swap(&other->tensor_type_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata WeightsToServer::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class WeightsToClient::_Internal {
 public:
};

WeightsToClient::WeightsToClient(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:params.WeightsToClient)
}
WeightsToClient::WeightsToClient(const WeightsToClient& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  reply_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_reply().empty()) {
    reply_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_reply(), 
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:params.WeightsToClient)
}

void WeightsToClient::SharedCtor() {
reply_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

WeightsToClient::~WeightsToClient() {
  // @@protoc_insertion_point(destructor:params.WeightsToClient)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void WeightsToClient::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  reply_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void WeightsToClient::ArenaDtor(void* object) {
  WeightsToClient* _this = reinterpret_cast< WeightsToClient* >(object);
  (void)_this;
}
void WeightsToClient::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void WeightsToClient::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void WeightsToClient::Clear() {
// @@protoc_insertion_point(message_clear_start:params.WeightsToClient)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  reply_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* WeightsToClient::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string reply = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_reply();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "params.WeightsToClient.reply"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* WeightsToClient::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:params.WeightsToClient)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string reply = 1;
  if (this->reply().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_reply().data(), static_cast<int>(this->_internal_reply().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "params.WeightsToClient.reply");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_reply(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:params.WeightsToClient)
  return target;
}

size_t WeightsToClient::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:params.WeightsToClient)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string reply = 1;
  if (this->reply().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_reply());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void WeightsToClient::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:params.WeightsToClient)
  GOOGLE_DCHECK_NE(&from, this);
  const WeightsToClient* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<WeightsToClient>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:params.WeightsToClient)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:params.WeightsToClient)
    MergeFrom(*source);
  }
}

void WeightsToClient::MergeFrom(const WeightsToClient& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:params.WeightsToClient)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.reply().size() > 0) {
    _internal_set_reply(from._internal_reply());
  }
}

void WeightsToClient::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:params.WeightsToClient)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void WeightsToClient::CopyFrom(const WeightsToClient& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:params.WeightsToClient)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool WeightsToClient::IsInitialized() const {
  return true;
}

void WeightsToClient::InternalSwap(WeightsToClient* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  reply_.Swap(&other->reply_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata WeightsToClient::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace params
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::params::WeightsToServer* Arena::CreateMaybeMessage< ::params::WeightsToServer >(Arena* arena) {
  return Arena::CreateMessageInternal< ::params::WeightsToServer >(arena);
}
template<> PROTOBUF_NOINLINE ::params::WeightsToClient* Arena::CreateMaybeMessage< ::params::WeightsToClient >(Arena* arena) {
  return Arena::CreateMessageInternal< ::params::WeightsToClient >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
