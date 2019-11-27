
#ifndef _SOURCE_ENGINE_HPP
#define _SOURCE_ENGINE_HPP
#include <hiaiengine/api.h>
#include <hiaiengine/multitype_queue.h>

class SourceEngine:public hiai::Engine
{
public:
    HIAI_DEFINE_PROCESS(1, 1)
};


#endif //_SOURCE_ENGINE_HPP
