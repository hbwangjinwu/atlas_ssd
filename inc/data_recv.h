#ifndef _DATA_RECV_HPP
#define _DATA_RECV_HPP
#include  <hiaiengine/api.h>
#include  <string>


class SSDDataRecvInterface:public hiai::DataRecvInterface{
public:
    SSDDataRecvInterface(const std::string &filename)
        :filePath(filename)
    {

    }
    
    HIAI_StatusT RecvData(const std::shared_ptr<void> &message)override;
private:
    std::string filePath;
};

#endif

