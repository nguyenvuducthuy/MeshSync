#pragma once

#include <map>
#include "../msFoundation.h"

namespace ms {

// generate IDs based on handle/pointer of DCC's object.
// mainly intended to convert DCC's material object to unique ID.
// (because materials are referenced by ID from polygons' material ID)
template<class T> class ResourceIDGenerator;

template<>
class ResourceIDGenerator<void*>
{
public:
    void clear()
    {
        m_id_seed = 0;
        m_records.clear();
    }

    void eraseStaleRecords()
    {
        for (auto it = m_records.begin(); it != m_records.end(); ) {
            if (!it->second.updated)
                m_records.erase(it++);
            else
                ++it;
        }
    }

protected:
    int getIDImpl(const void *p)
    {
        if (!p)
            return InvalidID;

        auto& rec = m_records[p];
        if (rec.id == InvalidID)
            rec.id = genID();
        rec.updated = true;
        return rec.id;
    }

    int genID()
    {
        return ++m_id_seed;
    }

protected:
    struct Record
    {
        int id = InvalidID;
        bool updated = true;
    };
    int m_id_seed = 0;
    std::map<const void*, Record> m_records;
};

template<class T>
class ResourceIDGenerator<T*> : public ResourceIDGenerator<void*>
{
public:
    int getID(const T *p)
    {
        return getIDImpl(p);
    }
};

template<>
class ResourceIDGenerator<uint32_t> : public ResourceIDGenerator<void*>
{
public:
    int getID(uint32_t handle)
    {
        return getIDImpl((void*)(size_t)handle);
    }
};


} // namespace ms