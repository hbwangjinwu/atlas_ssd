#include <hiaiengine/data_type.h>
#include "error_code.h"
#include "util.h"
#include "src_engine.hpp"
#include <string>
#include <memory>

HIAI_IMPL_ENGINE_PROCESS("SourceEngine", SourceEngine , 1)
{
    HIAI_ENGINE_LOG(this, HIAI_OK , "source engine proces");
    std::shared_ptr<std::string> input_arg = 
        std::static_pointer_cast<std::string>(arg0);
    if(nullptr == input_arg){
        HIAI_ENGINE_LOG(this, HIAI_INVALID_INPUT_MSG , "fail to process invalid message");
        return HIAI_INVALID_INPUT_MSG;
    }
    uint32_t buff_size;
    char* buf_data = Util::ReadBinFile(input_arg, &buff_size);

    std::shared_ptr<hiai::RawDataBuffer> raw_data_ptr = 
        std::make_shared<hiai::RawDataBuffer>();
    raw_data_ptr->data.reset((unsigned char*)buf_data,[](unsigned char *p){delete [] p;});
    raw_data_ptr->len_of_byte=buff_size;

    hiai::Engine::SendData(0 , "RawDataBuffer",std::static_pointer_cast<void >(raw_data_ptr));

    HIAI_ENGINE_LOG(this , HIAI_OK , "Source Engine Process success");
    return HIAI_OK;

}
