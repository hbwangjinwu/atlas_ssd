#include "data_recv.h"
#include <iostream>
#include "error_code.h"
#include "util.h"
HIAI_StatusT SSDDataRecvInterface::RecvData(const std::shared_ptr<void> &message)
{
    std::shared_ptr<std::string>  data = 
        std::static_pointer_cast<std::string>(message);
    if(nullptr == data){
        HIAI_ENGINE_LOG("failed to receive data");
        return HIAI_INVALID_INPUT_MSG;
    }
    std::cout <<"save " << filePath << std::endl;
    Util::SSDDump(filePath, data);
    return HIAI_OK;
}
