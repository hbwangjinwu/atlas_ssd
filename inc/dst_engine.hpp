
#ifndef _DEST_ENGINE_HPP
#define _DEST_ENGINE_HPP
#include <hiaiengine/api.h>
#include <hiaiengine/multitype_queue.h>

class DestEngine:public hiai::Engine
{
public:
    DestEngine():
        input_que_(2){}

    HIAI_DEFINE_PROCESS(2, 2)
private:
    hiai::MultiTypeQueue input_que_;
};


#endif //_DEST_ENGINE_HPP
