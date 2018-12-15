#pragma once
#include "msMesh.h"

namespace ms {

enum class VertexArrayEncoding : uint32_t
{
    Plain,
    Constant,
    B8,
    B16,
    S10x3,
    S10x3T = S10x3,
};

struct MeshEncoding
{
    static const int Bits = 3;
    VertexArrayEncoding points : Bits;
    VertexArrayEncoding normals : Bits;
    VertexArrayEncoding tangents : Bits;
    VertexArrayEncoding uv : Bits;
    VertexArrayEncoding colors : Bits;
    VertexArrayEncoding velocities : Bits;
    VertexArrayEncoding bone_weights : Bits;
    VertexArrayEncoding indices : Bits;
    VertexArrayEncoding counts : Bits;
    VertexArrayEncoding material_ids : Bits;

    static MeshEncoding plain();
    static MeshEncoding highp();
    static MeshEncoding mediump();
    static MeshEncoding lowp();

    MeshEncoding();
};

class VertexSerializer
{
public:
    void serialize(std::ostream& os, const RawVector<float>& data, VertexArrayEncoding vae);
    void serialize(std::ostream& os, const RawVector<float2>& data, VertexArrayEncoding vae);
    void serialize(std::ostream& os, const RawVector<float3>& data, VertexArrayEncoding vae);
    void serialize(std::ostream& os, const RawVector<float4>& data, VertexArrayEncoding vae);
    void serialize(std::ostream& os, const RawVector<int>& data, VertexArrayEncoding& vae);

    VertexArrayEncoding deserialize(std::istream& is, RawVector<float>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<float2>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<float3>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<float4>& data);
    VertexArrayEncoding deserialize(std::istream& is, RawVector<int>& data);

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
