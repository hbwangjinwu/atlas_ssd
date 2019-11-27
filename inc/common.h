/**
* @file common.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef INC_COMMON_H_
#define INC_COMMON_H_
#include <hiaiengine/data_type_reg.h>
#include <iostream>
#include <string>

// Defines the global value.
// Defines the file path.
static const std::string TEST_SRC_FILE_PATH =
        "./test_data/data/src_test.bin";
static const std::string TEST_DEST_DATA_NUM_PATH =
        "./test_data/result_data_num_file";
static const std::string TEST_DEST_DATA_BBOX_PATH =
        "./test_data/result_data_bbox_file";
static const std::string GRAPH_CONFIG_FILE_PATH =
        "./test_data/config/graph_sample.prototxt";
static const std::string GRAPH_MODEL_PATH =
        "./test_data/model/SSD-model.om";

// Defines Graph,Engine ID
static const uint32_t GRAPH_ID = 100;
static const uint32_t SRC_ENGINE_ID = 1000;
static const uint32_t SRC_PORT_ID = 0;
static const uint32_t DEST_ENGINE_ID = 1002;
static const uint32_t DEST_PORT_ID_0 = 0;
static const uint32_t DEST_PORT_ID_1 = 1;

// Defines Output shape
const std::vector<uint32_t> DATA_NUM = {1};
const std::vector<uint32_t> DATA_BBOX = {200,7};


// Defines the global value.
static std::mutex local_test_mutex;
static std::condition_variable local_test_cv_;
static const uint32_t MAX_SLEEP_TIMER = 30 * 60;
static const uint32_t MIN_ARG_VALUE = 2;
// Defines image parameters.
static const float IMG_HEIGHT = 374.0;
static const float IMG_WIDTH = 500.0;
static const float IMG_DEPTH = 1.0;

static const uint32_t DETECTION_SSD_OUTPUT_SIZE = 2;

// Defines message_type String
static const std::string message_type_engine_trans = "EngineTransT";

// Define the classification result traversal data.
static const uint32_t TYPE_NUM = 20;
static const uint32_t BBOX_INDEX_0 = 0;
static const uint32_t BBOX_INDEX_1 = 1;
static const uint32_t BBOX_INDEX_2 = 2;
static const uint32_t BBOX_INDEX_3 = 3;


// Defines the number of Engine ports.
// Source Engine
#define SOURCE_ENGINE_INPUT_SIZE    1
#define SOURCE_ENGINE_OUTPUT_SIZE   1

// Dest Engine
#define DEST_ENGINE_INPUT_SIZE      2
#define DEST_ENGINE_OUTPUT_SIZE     2

// DetectionSSD Engine
#define DETECTIONSSD_ENGINE_INPUT_SIZE    1
#define DETECTIONSSD_ENGINE_OUTPUT_SIZE   2

#define IMAGE_INFO_DATA_NUM         (3)

// Defines the transmission structure.
typedef struct EngineTrans
{
    std::string trans_buff;
    uint32_t buffer_size;
    HIAI_SERIALIZE(trans_buff, buffer_size);
}EngineTransT;

#endif  // INC_COMMON_H_
