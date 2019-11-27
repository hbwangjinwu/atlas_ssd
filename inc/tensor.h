#ifndef DDK_TENSOR_H_
#define DDK_TENSOR_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#include <cstdarg>
#include <iomanip>
#include "common.h"
namespace ddk{

    template <class T>
    class Tensor
    {
    public:
        Tensor():data(nullptr) {}
        ~Tensor() {clear();}

        /**
        * @ingroup Tensor
        * @brief fromarray
        * @param [in]:  pdata
        * @param [in]:  shape
        */

        void fromarray(const T* pdata, const std::vector<uint32_t>& shape)
        {
            clear();
            uint32_t size = 1;
            for (auto dim : shape)
            {
                size *= dim;
            }
            data = new T[size];
            memcpy_s(data, size*sizeof(T), pdata, size*sizeof(T));
            dims = shape;
        }

        /**
        * @ingroup Tensor
        * @brief dump
        * @param [in]:  filepath
        */

        bool dump(const std::string& filepath) const
        {
            std::ofstream ofs(filepath, std::ios::binary);
            if(ofs.fail())
            {
                std::cerr << "[ERROR] Failed to open \"" << filepath << "\"."<< std::endl;
                return false;
            }
            uint32_t rank = dims.size();
            ofs << "rank: ";
            ofs << rank;
            ofs << " ";
            uint32_t size = 1;
            ofs << "dim: ";
            for (uint32_t dim: dims)
            {
                size *= dim;
                ofs << dim;
                ofs << " ";
            }
            ofs << "data: \n";
            for (uint32_t count = 0; count < size; count++)
            {
                if (filepath == TEST_DEST_DATA_BBOX_PATH) {
                    ofs << std::setw(10) << std::setprecision(6) << data[count];
                    if((count + 1) % 7 ==0){
                        ofs << "   bbox"<< (count + 1) / 7 << "\n";
                    }
                 }
                if (filepath == TEST_DEST_DATA_NUM_PATH){
                    ofs << std::setw(10) << std::setprecision(6) << data[count];
                }
            }
            ofs.close();
            return true;
        }

    private:
        void clear()
        {
            if (data)
            {
                delete []data;
                data = nullptr;
            }
            dims.clear();
        }
        std::vector<uint32_t> dims;
        T* data;
    };
}


#endif
