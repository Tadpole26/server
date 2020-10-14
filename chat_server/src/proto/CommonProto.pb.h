// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CommonProto.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_CommonProto_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_CommonProto_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3012000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3012004 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_CommonProto_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_CommonProto_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_CommonProto_2eproto;
namespace sa {
namespace unity {
namespace proto {
class Position;
class PositionDefaultTypeInternal;
extern PositionDefaultTypeInternal _Position_default_instance_;
}  // namespace proto
}  // namespace unity
}  // namespace sa
PROTOBUF_NAMESPACE_OPEN
template<> ::sa::unity::proto::Position* Arena::CreateMaybeMessage<::sa::unity::proto::Position>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace sa {
namespace unity {
namespace proto {

// ===================================================================

class Position PROTOBUF_FINAL :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:sa.unity.proto.Position) */ {
 public:
  inline Position() : Position(nullptr) {};
  virtual ~Position();

  Position(const Position& from);
  Position(Position&& from) noexcept
    : Position() {
    *this = ::std::move(from);
  }

  inline Position& operator=(const Position& from) {
    CopyFrom(from);
    return *this;
  }
  inline Position& operator=(Position&& from) noexcept {
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
  static const Position& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const Position* internal_default_instance() {
    return reinterpret_cast<const Position*>(
               &_Position_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Position& a, Position& b) {
    a.Swap(&b);
  }
  inline void Swap(Position* other) {
    if (other == this) return;
    if (GetArena() == other->GetArena()) {
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Position* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline Position* New() const final {
    return CreateMaybeMessage<Position>(nullptr);
  }

  Position* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<Position>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const Position& from);
  void MergeFrom(const Position& from);
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
  void InternalSwap(Position* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "sa.unity.proto.Position";
  }
  protected:
  explicit Position(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_CommonProto_2eproto);
    return ::descriptor_table_CommonProto_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPosMapFieldNumber = 1,
    kPosXFieldNumber = 2,
    kPosYFieldNumber = 3,
    kPosDirFieldNumber = 4,
  };
  // uint32 posMap = 1;
  void clear_posmap();
  ::PROTOBUF_NAMESPACE_ID::uint32 posmap() const;
  void set_posmap(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_posmap() const;
  void _internal_set_posmap(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // sint32 posX = 2;
  void clear_posx();
  ::PROTOBUF_NAMESPACE_ID::int32 posx() const;
  void set_posx(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_posx() const;
  void _internal_set_posx(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // sint32 posY = 3;
  void clear_posy();
  ::PROTOBUF_NAMESPACE_ID::int32 posy() const;
  void set_posy(::PROTOBUF_NAMESPACE_ID::int32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::int32 _internal_posy() const;
  void _internal_set_posy(::PROTOBUF_NAMESPACE_ID::int32 value);
  public:

  // uint32 posDir = 4;
  void clear_posdir();
  ::PROTOBUF_NAMESPACE_ID::uint32 posdir() const;
  void set_posdir(::PROTOBUF_NAMESPACE_ID::uint32 value);
  private:
  ::PROTOBUF_NAMESPACE_ID::uint32 _internal_posdir() const;
  void _internal_set_posdir(::PROTOBUF_NAMESPACE_ID::uint32 value);
  public:

  // @@protoc_insertion_point(class_scope:sa.unity.proto.Position)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::uint32 posmap_;
  ::PROTOBUF_NAMESPACE_ID::int32 posx_;
  ::PROTOBUF_NAMESPACE_ID::int32 posy_;
  ::PROTOBUF_NAMESPACE_ID::uint32 posdir_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_CommonProto_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// Position

// uint32 posMap = 1;
inline void Position::clear_posmap() {
  posmap_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Position::_internal_posmap() const {
  return posmap_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Position::posmap() const {
  // @@protoc_insertion_point(field_get:sa.unity.proto.Position.posMap)
  return _internal_posmap();
}
inline void Position::_internal_set_posmap(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  posmap_ = value;
}
inline void Position::set_posmap(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_posmap(value);
  // @@protoc_insertion_point(field_set:sa.unity.proto.Position.posMap)
}

// sint32 posX = 2;
inline void Position::clear_posx() {
  posx_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Position::_internal_posx() const {
  return posx_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Position::posx() const {
  // @@protoc_insertion_point(field_get:sa.unity.proto.Position.posX)
  return _internal_posx();
}
inline void Position::_internal_set_posx(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  posx_ = value;
}
inline void Position::set_posx(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_posx(value);
  // @@protoc_insertion_point(field_set:sa.unity.proto.Position.posX)
}

// sint32 posY = 3;
inline void Position::clear_posy() {
  posy_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Position::_internal_posy() const {
  return posy_;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 Position::posy() const {
  // @@protoc_insertion_point(field_get:sa.unity.proto.Position.posY)
  return _internal_posy();
}
inline void Position::_internal_set_posy(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  posy_ = value;
}
inline void Position::set_posy(::PROTOBUF_NAMESPACE_ID::int32 value) {
  _internal_set_posy(value);
  // @@protoc_insertion_point(field_set:sa.unity.proto.Position.posY)
}

// uint32 posDir = 4;
inline void Position::clear_posdir() {
  posdir_ = 0u;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Position::_internal_posdir() const {
  return posdir_;
}
inline ::PROTOBUF_NAMESPACE_ID::uint32 Position::posdir() const {
  // @@protoc_insertion_point(field_get:sa.unity.proto.Position.posDir)
  return _internal_posdir();
}
inline void Position::_internal_set_posdir(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  
  posdir_ = value;
}
inline void Position::set_posdir(::PROTOBUF_NAMESPACE_ID::uint32 value) {
  _internal_set_posdir(value);
  // @@protoc_insertion_point(field_set:sa.unity.proto.Position.posDir)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace unity
}  // namespace sa

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_CommonProto_2eproto
