#pragma once

#define msReleaseDate 20181231
#define msReleaseDateStr "20181231"
#define msVendor "Unity Technologies"
#define msProtocolVersion 113
//#define msEnableProfiling

namespace mu {}
namespace ms {
using namespace mu;
#define msLogInfo(...)    ::mu::Print("MeshSync info: " __VA_ARGS__)
#define msLogWarning(...) ::mu::Print("MeshSync warning: " __VA_ARGS__)
#define msLogError(...)   ::mu::Print("MeshSync error: " __VA_ARGS__)
} // namespace ms
