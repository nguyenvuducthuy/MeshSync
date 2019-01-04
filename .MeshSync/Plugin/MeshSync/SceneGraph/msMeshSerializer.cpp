#include "pch.h"
#include "msSceneGraph.h"
#include "msMeshSerializer.h"

namespace ms {

MeshEncoding MeshEncoding::plain()
{
    return {};
}

MeshEncoding MeshEncoding::highp()
{
    MeshEncoding ret{};
    ret.points = VertexArrayEncoding::Plain;
    ret.normals = VertexArrayEncoding::Plain;
    ret.tangents = VertexArrayEncoding::Plain;
    ret.uv0 = VertexArrayEncoding::Plain;
    ret.uv1 = VertexArrayEncoding::Plain;
    ret.colors = VertexArrayEncoding::Plain;
    ret.velocities = VertexArrayEncoding::Plain;
    ret.bone_weights = VertexArrayEncoding::Plain;
    ret.indices = VertexArrayEncoding::Adaptive;
    ret.counts = VertexArrayEncoding::Adaptive;
    ret.material_ids = VertexArrayEncoding::Adaptive;
    return ret;
}

MeshEncoding MeshEncoding::mediump()
{
    MeshEncoding ret{};
    ret.points = VertexArrayEncoding::Plain;
    ret.normals = VertexArrayEncoding::S10x3;
    ret.tangents = VertexArrayEncoding::S10x3T;
    ret.uv0 = VertexArrayEncoding::B16;
    ret.uv1 = VertexArrayEncoding::B16;
    ret.colors = VertexArrayEncoding::B16;
    ret.velocities = VertexArrayEncoding::B16;
    ret.bone_weights = VertexArrayEncoding::B16;
    ret.indices = VertexArrayEncoding::Adaptive;
    ret.counts = VertexArrayEncoding::Adaptive;
    ret.material_ids = VertexArrayEncoding::Adaptive;
    return ret;
}

MeshEncoding MeshEncoding::lowp()
{
    MeshEncoding ret{};
    ret.points = VertexArrayEncoding::B16;
    ret.normals = VertexArrayEncoding::S10x3;
    ret.tangents = VertexArrayEncoding::S10x3T;
    ret.uv0 = VertexArrayEncoding::B8;
    ret.uv1 = VertexArrayEncoding::B8;
    ret.colors = VertexArrayEncoding::B8;
    ret.velocities = VertexArrayEncoding::B8;
    ret.bone_weights = VertexArrayEncoding::B8;
    ret.indices = VertexArrayEncoding::Adaptive;
    ret.counts = VertexArrayEncoding::Adaptive;
    ret.material_ids = VertexArrayEncoding::Adaptive;
    return ret;
}

MeshEncoding::MeshEncoding()
{
    points = VertexArrayEncoding::Plain;
    normals = VertexArrayEncoding::Plain;
    tangents = VertexArrayEncoding::Plain;
    uv0 = VertexArrayEncoding::Plain;
    uv1 = VertexArrayEncoding::Plain;
    colors = VertexArrayEncoding::Plain;
    velocities = VertexArrayEncoding::Plain;
    bone_weights = VertexArrayEncoding::Plain;
    indices = VertexArrayEncoding::Plain;
    counts = VertexArrayEncoding::Plain;
    material_ids = VertexArrayEncoding::Plain;
}

bool MeshEncoding::operator==(const MeshEncoding& v) const
{
    return (const uint64_t&)*this == (const uint64_t&)v;
}
bool MeshEncoding::operator!=(const MeshEncoding& v) const
{
    return (const uint64_t&)*this != (const uint64_t&)v;
}
uint64_t MeshEncoding::hash() const
{
    return (const uint64_t&)*this;
}

static_assert(sizeof(MeshEncoding) == sizeof(uint64_t), "");



VertexSerializer& VertexSerializer::getInstance()
{
    static thread_local VertexSerializer s_inst;
    return s_inst;
}

VertexArrayEncoding VertexSerializer::serialize(std::ostream& os, const RawVector<float>& data, VertexArrayEncoding vae)
{
    ms::write(os, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::write(os, data);
        break;
    case VertexArrayEncoding::B8:
        ms::encode(m_u8, data);
        ms::write(os, m_u8.bound_min);
        ms::write(os, m_u8.bound_max);
        ms::write(os, m_u8.packed);
        break;
    case VertexArrayEncoding::B16:
        ms::encode(m_u16, data);
        ms::write(os, m_u16.bound_min);
        ms::write(os, m_u16.bound_max);
        ms::write(os, m_u16.packed);
        break;
    }
    return vae;
}
VertexArrayEncoding VertexSerializer::serialize(std::ostream& os, const RawVector<float2>& data, VertexArrayEncoding vae)
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
    return vae;
}
VertexArrayEncoding VertexSerializer::serialize(std::ostream& os, const RawVector<float3>& data, VertexArrayEncoding vae)
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
    return vae;
}
VertexArrayEncoding VertexSerializer::serialize(std::ostream& os, const RawVector<float4>& data, VertexArrayEncoding vae)
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
    return vae;
}
VertexArrayEncoding VertexSerializer::serialize(std::ostream& os, const RawVector<int>& data, VertexArrayEncoding vae)
{
    if (vae == VertexArrayEncoding::Adaptive) {
        if (data.empty()) {
            vae = VertexArrayEncoding::Constant;
        }
        else {
            int n = 0, x = 0;
            MinMax(data.data(), data.size(), n, x);
            int len = x - n;
            if (len == 0)
                vae = VertexArrayEncoding::Constant;
            else if (len <= 0xFF)
                vae = VertexArrayEncoding::B8;
            else if (len <= 0xFFFF)
                vae = VertexArrayEncoding::B16;
            else
                vae = VertexArrayEncoding::Plain;
        }
    }

    ms::write(os, vae);
    switch (vae) {
    case VertexArrayEncoding::Plain:
        ms::write(os, data);
        break;
    case VertexArrayEncoding::Constant:
        ms::write(os, (uint32_t)data.size());
        if (!data.empty())
            ms::write(os, data[0]);
        break;
    case VertexArrayEncoding::B8:
        ms::encode(m_u8i, data);
        ms::write(os, m_u8i.bound_min);
        ms::write(os, m_u8i.bound_max);
        ms::write(os, m_u8i.packed);
        break;
    case VertexArrayEncoding::B16:
        ms::encode(m_u16i, data);
        ms::write(os, m_u16i.bound_min);
        ms::write(os, m_u16i.bound_max);
        ms::write(os, m_u16i.packed);
        break;
    }
    return vae;
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


uint64_t VertexSerializer::hash(const RawVector<float>& data, VertexArrayEncoding vae)
{
    if (vae == VertexArrayEncoding::Plain) {
        return vhash(data);
    }
    else {
        return 0;
    }
}
uint64_t VertexSerializer::hash(const RawVector<float2>& data, VertexArrayEncoding vae)
{
    if (vae == VertexArrayEncoding::Plain) {
        return vhash(data);
    }
    else {
        return 0;
    }
}
uint64_t VertexSerializer::hash(const RawVector<float3>& data, VertexArrayEncoding vae)
{
    if (vae == VertexArrayEncoding::Plain) {
        return vhash(data);
    }
    else {
        return 0;
    }
}
uint64_t VertexSerializer::hash(const RawVector<float4>& data, VertexArrayEncoding vae)
{
    if (vae == VertexArrayEncoding::Plain) {
        return vhash(data);
    }
    else {
        return 0;
    }
}
uint64_t VertexSerializer::hash(const RawVector<int>& data, VertexArrayEncoding vae)
{
    if (vae == VertexArrayEncoding::Plain) {
        return vhash(data);
    }
    else {
        return 0;
    }
}


} // namespace ms
