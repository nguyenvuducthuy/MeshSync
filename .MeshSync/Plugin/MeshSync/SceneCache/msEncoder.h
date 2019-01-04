#pragma once

#include "SceneGraph/msSceneGraph.h"

namespace ms {

class BufferEncoder
{
public:
    virtual ~BufferEncoder();
    virtual void encode(RawVector<char>& dst, const RawVector<char>& src) = 0;
    virtual void decode(RawVector<char>& dst, const RawVector<char>& src) = 0;
};
msDeclPtr(BufferEncoder);

BufferEncoderPtr CreatePlainEncoder();
BufferEncoderPtr CreateZSTDEncoder();

} // namespace ms
