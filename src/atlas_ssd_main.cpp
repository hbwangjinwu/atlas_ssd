#include "data_recv.h"
#include "common.h"
#include "util.h"
#include <thread>
#include <unistd.h>

const int MAX_SLEEP_TIMES = 16;
static bool is_test_result_ready = false;

HIAI_StatusT InitAndStartGraph()
{
    HIAI_StatusT status = HIAI_Init(0);
    HIAI_ENGINE_LOG(status , "init and create graph");
    status = hiai::Graph::CreateGraph(GRAPH_CONFIG_FILE_PATH);
    if(HIAI_OK != status){
        HIAI_ENGINE_LOG(status , "Fail to Create Graph");
        return status;
    }

    std::shared_ptr<hiai::Graph> graph =  hiai::Graph::GetInstance(GRAPH_ID);
    if(nullptr == graph){
        HIAI_ENGINE_LOG(status , "Failed to get the graph-%u", GRAPH_ID);
        return status;
    }

    hiai::EnginePortID target_port_config;
    
    target_port_config.graph_id = GRAPH_ID;
    target_port_config.engine_id = DEST_ENGINE_ID;
    target_port_config.port_id = DEST_PORT_ID_0;
    graph->SetDataRecvFunctor( target_port_config , 
            std::make_shared<SSDDataRecvInterface>(TEST_DEST_DATA_BBOX_PATH));
    
    target_port_config.port_id = DEST_PORT_ID_1;
    graph->SetDataRecvFunctor( target_port_config , 
            std::make_shared<SSDDataRecvInterface>(TEST_DEST_DATA_NUM_PATH));
}

/**
* @ingroup CheckAllFileExist
* @brief Check whether all files are generated.
*/
void CheckAllFileExist()
{
    for (int i = 0; i < MAX_SLEEP_TIMES; ++i) {
        if (Util::CheckFileExist(TEST_DEST_DATA_NUM_PATH)
            && Util::CheckFileExist(TEST_DEST_DATA_BBOX_PATH)) {
            std::unique_lock <std::mutex> lck(local_test_mutex);
            is_test_result_ready = true;
            printf("File %s generated\n", TEST_DEST_DATA_NUM_PATH.c_str());
            printf("File %s generated\n", TEST_DEST_DATA_BBOX_PATH.c_str());
            HIAI_ENGINE_LOG("Check Result success");
            return;
        }
        printf("Check Result, go into sleep 1 sec\n");
        HIAI_ENGINE_LOG("Check Result, go into sleep 1 sec");
        sleep(1);
    }
    printf("Check Result failed, timeout\n");
    HIAI_ENGINE_LOG("Check Result failed, timeout");
}


int main( )
{
    remove(TEST_DEST_DATA_BBOX_PATH.c_str()); 
    remove(TEST_DEST_DATA_NUM_PATH.c_str()); 
    HIAI_StatusT ret  = HIAI_OK;
    ret = InitAndStartGraph();
    std::shared_ptr<hiai::Graph> graph =  hiai::Graph::GetInstance(GRAPH_ID);
    if(nullptr == graph){
        HIAI_ENGINE_LOG(ret , "Failed to get the graph-%u", GRAPH_ID);
        return ret;
    }

    hiai::EnginePortID target_engine;
    target_engine.graph_id = GRAPH_ID;
    target_engine.engine_id = SRC_ENGINE_ID;
    target_engine.port_id = SRC_PORT_ID;

    std::shared_ptr<std::string> src_string = 
        std::make_shared<std::string>(TEST_SRC_FILE_PATH);

    graph->SendData(target_engine , "string", std::static_pointer_cast<void>(src_string));

    std::thread check_thread(CheckAllFileExist);
    check_thread.join();
    hiai::Graph::DestroyGraph(GRAPH_ID);
    return 0;
}


