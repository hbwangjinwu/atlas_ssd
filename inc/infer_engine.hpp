#ifndef _INFER_ENGINE_HPP
#define _INFER_ENGINE_HPP
#include <hiaiengine/api.h>
#include <hiaiengine/ai_model_manager.h>
#include <string>
#include <vector>
#include <map>
class InferEngine:public hiai::Engine
{
public:
    HIAI_StatusT Init(const hiai::AIConfig &config , 
        const std::vector<hiai::AIModelDescription> &mode_desc);
    HIAI_DEFINE_PROCESS(1, 2)
private:
    std::map<std::string, std::string> config_;
    std::shared_ptr<hiai::AIModelManager> ai_model_manager_;

};


#endif
