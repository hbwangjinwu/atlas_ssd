#include <hiaiengine/data_type.h>
#include "error_code.h"
#include "util.h"
#include "dst_engine.hpp"
#include <string>
#include <memory>
#include <iostream>

HIAI_IMPL_ENGINE_PROCESS("DestEngine", DestEngine , 2)
{
    HIAI_ENGINE_LOG(this, HIAI_OK , "dest engine proces");

    input_que_.PushData(0, arg0);
    input_que_.PushData(1, arg1);
    std::shared_ptr<std::string> box_data_arg = 
        std::static_pointer_cast<std::string>(arg0);
    std::shared_ptr<std::string> box_num_arg = 
        std::static_pointer_cast<std::string>(arg1);
    
    if(!input_que_.PopAllData(box_data_arg , box_num_arg)){

        HIAI_ENGINE_LOG("fail to get all message");    
        return HIAI_INVALID_INPUT_MSG;

    }
    
    hiai::Engine::SendData(0, "string", std::static_pointer_cast<void>(box_data_arg));

    hiai::Engine::SendData(1, "string", std::static_pointer_cast<void>(box_num_arg));

    HIAI_ENGINE_LOG(this , HIAI_OK , "Dest Engine Process success");
    return HIAI_OK;

}

