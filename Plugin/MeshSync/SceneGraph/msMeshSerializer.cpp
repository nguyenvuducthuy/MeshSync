#include "pch.h"
#include "msSceneGraph.h"
#include "msMeshSerializer.h"

namespace ms {

MeshEncoding MeshEncoding::plain()
{
    MeshEncoding ret;
    ret.points = VertexArrayEncoding::Plain;
    ret.normals = VertexArrayEncoding::Plain;
    ret.tangents = VertexArrayEncoding::Plain;
    ret.uv = VertexArrayEncoding::Plain;
    ret.colors = VertexArrayEncoding::Plain;
    ret.velocities = VertexArrayEncoding::Plain;
    ret.bone_weights = VertexArrayEncoding::Plain;
    ret.indices = VertexArrayEncoding::Plain;
    return ret;
}

MeshEncoding MeshEncoding::highp()
{
    return plain();
}

MeshEncoding MeshEncoding::mediump()
{
    MeshEncoding ret;
    ret.points = VertexArrayEncoding::Plain;
    ret.normals = VertexArrayEncoding::S10x3;
    ret.tangents = VertexArrayEncoding::S10x3T;
    ret.uv = VertexArrayEncoding::B16;
    ret.colors = VertexArrayEncoding::B16;
    ret.velocities = VertexArrayEncoding::B16;
    ret.bone_weights = VertexArrayEncoding::B16;
    ret.indices = VertexArrayEncoding::Plain;
    return ret;
}

MeshEncoding MeshEncoding::lowp()
{
    MeshEncoding ret;
    ret.points = VertexArrayEncoding::B16;
    ret.normals = VertexArrayEncoding::S10x3;
    ret.tangents = VertexArrayEncoding::S10x3T;
    ret.uv = VertexArrayEncoding::B8;
    ret.colors = VertexArrayEncoding::B8;
    ret.velocities = VertexArrayEncoding::B8;
    ret.bone_weights = VertexArrayEncoding::B8;
    ret.indices = VertexArrayEncoding::Plain;
    return ret;
}

MeshEncoding::MeshEncoding()
{
    *this = plain();
}



void VertexSerializer::serialize(std::ostream& os, const RawVector<float>& data, VertexArrayEncoding vae)
{
    ms::write(os, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::write(os, data);
        break;
    case VertexArrayEncoding::B8:
        ms::encode(m_u8, data);
        ms::write(os, m_u8x2.bound_min);
        ms::write(os, m_u8x2.bound_max);
        ms::write(os, m_u8x2.packed);
        break;
    case VertexArrayEncoding::B16:
        ms::encode(m_u16, data);
        ms::write(os, m_u16.bound_min);
        ms::write(os, m_u16.bound_max);
        ms::write(os, m_u16.packed);
        break;
    }
}
void VertexSerializer::serialize(std::ostream& os, const RawVector<float2>& data, VertexArrayEncoding vae)
{
    ms::write(os, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::write(os, data);
        break;
    case VertexArrayEncoding::B8:
        ms::encode(m_u8x2, data);
        ms::write(os, m_u8x2.bound_min);
        ms::write(os, m_u8x2.bound_max);
        ms::write(os, m_u8x2.packed);
        break;
    case VertexArrayEncoding::B16:
        ms::encode(m_u16x2, data);
        ms::write(os, m_u16x2.bound_min);
        ms::write(os, m_u16x2.bound_max);
        ms::write(os, m_u16x2.packed);
        break;
    }
}
void VertexSerializer::serialize(std::ostream& os, const RawVector<float3>& data, VertexArrayEncoding vae)
{
    ms::write(os, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::write(os, data);
        break;
    case VertexArrayEncoding::B8:
        ms::encode(m_u8x3, data);
        ms::write(os, m_u8x3.bound_min);
        ms::write(os, m_u8x3.bound_max);
        ms::write(os, m_u8x3.packed);
        break;
    case VertexArrayEncoding::B16:
        ms::encode(m_u16x3, data);
        ms::write(os, m_u16x3.bound_min);
        ms::write(os, m_u16x3.bound_max);
        ms::write(os, m_u16x3.packed);
        break;
    case VertexArrayEncoding::S10x3:
        ms::encode(m_s10x3, data);
        ms::write(os, m_s10x3.packed);
        break;
    }
}
void VertexSerializer::serialize(std::ostream& os, const RawVector<float4>& data, VertexArrayEncoding vae)
{
    ms::write(os, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::write(os, data);
        break;
    case VertexArrayEncoding::B8:
        ms::encode(m_u8x4, data);
        ms::write(os, m_u8x4.bound_min);
        ms::write(os, m_u8x4.bound_max);
        ms::write(os, m_u8x4.packed);
        break;
    case VertexArrayEncoding::B16:
        ms::encode(m_u16x4, data);
        ms::write(os, m_u16x4.bound_min);
        ms::write(os, m_u16x4.bound_max);
        ms::write(os, m_u16x4.packed);
        break;
    case VertexArrayEncoding::S10x3T:
        ms::encode_tangents(m_s10x3, data);
        ms::write(os, m_s10x3.packed);
        break;
    }
}
void VertexSerializer::serialize(std::ostream& os, const RawVector<int>& data, VertexArrayEncoding& vae)
{
    int n, x;
    MinMax(data.data(), data.size(), n, x);
    int len = x - n;

    if (data.empty() || len == 0) {
        vae = VertexArrayEncoding::Constant;
        ms::write(os, vae);
        ms::write(os, (uint32_t)data.size());
        if (len > 0)
            ms::write(os, data[0]);
    }
    else if (len <= 0xFF) {
        vae = VertexArrayEncoding::B8;
        ms::write(os, vae);
        ms::encode(m_u8i, data);
        ms::write(os, m_u8i.bound_min);
        ms::write(os, m_u8i.bound_max);
        ms::write(os, m_u8i.packed);
    }
    else if (len <= 0xFFFF) {
        vae = VertexArrayEncoding::B16;
        ms::write(os, vae);
        ms::encode(m_u16i, data);
        ms::write(os, m_u16i.bound_min);
        ms::write(os, m_u16i.bound_max);
        ms::write(os, m_u16i.packed);
    }
    else {
        vae = VertexArrayEncoding::Plain;
        ms::write(os, vae);
        ms::write(os, data);
    }
}

VertexArrayEncoding VertexSerializer::deserialize(std::istream& is, RawVector<float>& data)
{
    VertexArrayEncoding vae;
    ms::read(is, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::read(is, data);
        break;
    case VertexArrayEncoding::B8:
        ms::read(is, m_u8.bound_min);
        ms::read(is, m_u8.bound_max);
        ms::read(is, m_u8.packed);
        ms::decode(data, m_u8);
        break;
    case VertexArrayEncoding::B16:
        ms::read(is, m_u16.bound_min);
        ms::read(is, m_u16.bound_max);
        ms::read(is, m_u16.packed);
        ms::decode(data, m_u16);
        break;
    }
    return vae;
}
VertexArrayEncoding VertexSerializer::deserialize(std::istream& is, RawVector<float2>& data)
{
    VertexArrayEncoding vae;
    ms::read(is, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::read(is, data);
        break;
    case VertexArrayEncoding::B8:
        ms::read(is, m_u8x2.bound_min);
        ms::read(is, m_u8x2.bound_max);
        ms::read(is, m_u8x2.packed);
        ms::decode(data, m_u8x2);
        break;
    case VertexArrayEncoding::B16:
        ms::read(is, m_u16x2.bound_min);
        ms::read(is, m_u16x2.bound_max);
        ms::read(is, m_u16x2.packed);
        ms::decode(data, m_u16x2);
        break;
    }
    return vae;
}
VertexArrayEncoding VertexSerializer::deserialize(std::istream& is, RawVector<float3>& data)
{
    VertexArrayEncoding vae;
    ms::read(is, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::read(is, data);
        break;
    case VertexArrayEncoding::B8:
        ms::read(is, m_u8x3.bound_min);
        ms::read(is, m_u8x3.bound_max);
        ms::read(is, m_u8x3.packed);
        ms::decode(data, m_u8x3);
        break;
    case VertexArrayEncoding::B16:
        ms::read(is, m_u16x3.bound_min);
        ms::read(is, m_u16x3.bound_max);
        ms::read(is, m_u16x3.packed);
        ms::decode(data, m_u16x3);
        break;
    case VertexArrayEncoding::S10x3:
        ms::read(is, m_s10x3.packed);
        ms::decode(data, m_s10x3);
        break;
    }
    return vae;
}
VertexArrayEncoding VertexSerializer::deserialize(std::istream& is, RawVector<float4>& data)
{
    VertexArrayEncoding vae;
    ms::read(is, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::read(is, data);
        break;
    case VertexArrayEncoding::B8:
        ms::read(is, m_u8x4.bound_min);
        ms::read(is, m_u8x4.bound_max);
        ms::read(is, m_u8x4.packed);
        ms::decode(data, m_u8x4);
        break;
    case VertexArrayEncoding::B16:
        ms::read(is, m_u16x4.bound_min);
        ms::read(is, m_u16x4.bound_max);
        ms::read(is, m_u16x4.packed);
        ms::decode(data, m_u16x4);
        break;
    case VertexArrayEncoding::S10x3T:
        ms::read(is, m_s10x3.packed);
        ms::decode_tangents(data, m_s10x3);
        break;
    }
    return vae;
}
VertexArrayEncoding VertexSerializer::deserialize(std::istream& is, RawVector<int>& data)
{
    VertexArrayEncoding vae;
    ms::read(is, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::read(is, data);
        break;
    case VertexArrayEncoding::Constant:
        {
            uint32_t len;
            ms::read(is, len);
            if (len > 0) {
                int e;
                ms::read(is, e);
                data.clear();
                data.resize(len, e);
            }
        }
        break;
    case VertexArrayEncoding::B8:
        ms::read(is, m_u8i.bound_min);
        ms::read(is, m_u8i.bound_max);
        ms::read(is, m_u8i.packed);
        ms::decode(data, m_u8i);
        break;
    case VertexArrayEncoding::B16:
        ms::read(is, m_u16i.bound_min);
        ms::read(is, m_u16i.bound_max);
        ms::read(is, m_u16i.packed);
        ms::decode(data, m_u16i);
        break;
    }
    return vae;
}


} // namespace ms
