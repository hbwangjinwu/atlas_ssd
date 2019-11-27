/**
* @file util.h
*
* Copyright (C) 2018. Huawei Technologies Co., Ltd. All rights reserved.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef INC_UTIL_H_
#define INC_UTIL_H_
#include <iostream>
#include <memory>
class Util
{
public:
    static char* ReadBinFile(std::shared_ptr<std::string> file_name_ptr, uint32_t* file_size);
    static bool CheckFileExist(const std::string& file_name);
    static void SSDDump(const std::string& file_name, std::shared_ptr<std::string> data);
};
#endif //INC_UTIL_H_
