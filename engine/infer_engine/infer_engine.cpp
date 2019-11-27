#include "infer_engine.hpp"
#include <hiaiengine/api.h>
#include <hiaiengine/data_type.h>
#include "error_code.h"
#include <vector>
#include <string>

HIAI_StatusT InferEngine::Init(const hiai::AIConfig &config , const std::vector<hiai::AIModelDescription> &model_desc)
{
    HIAI_ENGINE_LOG(this , HIAI_OK , "DectectiongSSDEngine  Init");

    HIAI_StatusT ret = hiai::SUCCESS;
    config_.clear();

    for(auto item : config.items()){
        config_[item.name()] = item.value();
    }

    if(nullptr == ai_model_manager_){

        ai_model_manager_ = std::make_shared<hiai::AIModelManager>();

    }

    std::vector<hiai::AIModelDescription> mode_desc_vec_;
    const char* model_path = config_["model_path"].c_str();
    hiai::AIModelDescription model_desc_;
    model_desc_.set_path(model_path);
    model_desc_.set_key("");
    mode_desc_vec_.push_back(model_desc_);

    ret = ai_model_manager_->Init(config , mode_desc_vec_);

    if( hiai::SUCCESS != ret){
        HIAI_ENGINE_LOG(this ,HIAI_AI_MODEL_MANAGER_INIT_FAIL,"hiai ai model manage init fail" );
        return HIAI_AI_MODEL_MANAGER_INIT_FAIL;
    }

    HIAI_ENGINE_LOG(this , HIAI_OK , "DetectionSSDEngnie  init success");
    return HIAI_OK;
}

HIAI_IMPL_ENGINE_PROCESS("InferEngine", InferEngine , 1)
{
    HIAI_StatusT ret =  HIAI_OK;
    std::shared_ptr<hiai::RawDataBuffer> input_data_buff = 
        std::static_pointer_cast<hiai::RawDataBuffer>(arg0);
    
    if(nullptr == input_data_buff){
        HIAI_ENGINE_LOG(this , HIAI_INVALID_INPUT_MSG, "failed to process invalid message");
        return HIAI_INVALID_INPUT_MSG;
    }

    std::shared_ptr<hiai::AINeuralNetworkBuffer> neural_buffer_img =
        std::make_shared<hiai::AINeuralNetworkBuffer>();

    neural_buffer_img->SetBuffer((void*)(input_data_buff->data.get()), (uint32_t)(input_data_buff->len_of_byte), false);

    std::shared_ptr<hiai::IAITensor> input_data_img = std::static_pointer_cast<hiai::IAITensor>(neural_buffer_img);

    std::vector<std::shared_ptr<hiai::IAITensor>> input_data_vec;
    input_data_vec.push_back(input_data_img);

    std::vector<std::shared_ptr<hiai::IAITensor> > output_data_vec;
    ret = ai_model_manager_->CreateOutputTensor(input_data_vec, output_data_vec);
    if (hiai::SUCCESS != ret){
        HIAI_ENGINE_LOG(this, HIAI_AI_MODEL_CREATE_OUTPUT_FAIL,
            "Failed to create output tensor");
        return HIAI_AI_MODEL_CREATE_OUTPUT_FAIL;
    }
    hiai::AIContext ai_context;
    ret = ai_model_manager_->Process(ai_context , 
            input_data_vec, output_data_vec , 0);
    if (hiai::SUCCESS != ret){
        HIAI_ENGINE_LOG(this, HIAI_AI_MODEL_MANAGER_PROCESS_FAIL,
            "Fail to process ai model manager");
        return HIAI_AI_MODEL_MANAGER_PROCESS_FAIL;
    }

    for (uint32_t index = 0 ; index < output_data_vec.size() ; index++){
        std::shared_ptr<hiai::AINeuralNetworkBuffer> output_data = 
            std::static_pointer_cast<hiai::AINeuralNetworkBuffer>(
                output_data_vec[index]); 
        std::shared_ptr<std::string> output_string_ptr =
            std::shared_ptr<std::string>(
                    new std::string((char*)output_data->GetBuffer(), output_data->GetSize()));
        hiai::Engine::SendData(index , "string", 
                std::static_pointer_cast<void>(output_string_ptr));
    }
    HIAI_ENGINE_LOG(this, HIAI_OK , "success process message");
    return HIAI_OK;

}
