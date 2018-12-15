#pragma once
#include "msMesh.h"

namespace ms {

class VertexSerializer
{
public:
    static VertexSerializer& getInstance();

    VertexArrayEncoding serialize(std::ostream& os, const RawVector<float>& data, VertexArrayEncoding vae);
    VertexArrayEncoding serialize(std::ostream& os, const RawVector<float2>& data, VertexArrayEncoding vae);
    VertexArrayEncoding serialize(std::ostream& os, const RawVector<float3>& data, VertexArrayEncoding vae);
    VertexArrayEncoding serialize(std::ostream& os, const RawVector<float4>& data, VertexArrayEncoding vae);
    VertexArrayEncoding serialize(std::ostream& os, const RawVector<int>& data, VertexArrayEncoding vae);

    VertexArrayEncoding deserialize(std::istream& is, RawVector<float>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<float2>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<float3>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<float4>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<int>& data);

    uint64_t hash(const RawVector<float>& data, VertexArrayEncoding vae);
    uint64_t hash(const RawVector<float2>& data, VertexArrayEncoding vae);
    uint64_t hash(const RawVector<float3>& data, VertexArrayEncoding vae);
    uint64_t hash(const RawVector<float4>& data, VertexArrayEncoding vae);
    uint64_t hash(const RawVector<int>& data, VertexArrayEncoding vae);

private:
    BoundedArrayU8 m_u8;
    BoundedArrayU8I m_u8i;
    BoundedArrayU16 m_u16;
    BoundedArrayU16I m_u16i;
    BoundedArrayU8x2 m_u8x2;
    BoundedArrayU8x3 m_u8x3;
    BoundedArrayU8x4 m_u8x4;
    BoundedArrayU16x2 m_u16x2;
    BoundedArrayU16x3 m_u16x3;
    BoundedArrayU16x4 m_u16x4;
    PackedArrayS10x3 m_s10x3;
};

} // namespace ms
