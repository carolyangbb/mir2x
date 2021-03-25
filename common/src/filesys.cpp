/*
 * =====================================================================================
 *
 *       Filename: filesys.cpp
 *        Created: 02/08/2016 22:17:08
 *    Description: 
 *
 *        Version: 1.0
 *       Revision: none
 *       Compiler: gcc
 *
 *         Author: ANHONG
 *          Email: anhonghe@gmail.com
 *   Organization: USTC
 *
 * =====================================================================================
 */

#include <regex>
#include <cerrno>
#include <cstdio>
#include <string>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include "fileptr.hpp"
#include "filesys.hpp"
#include "fflerror.hpp"

bool filesys::makeDir(const char *dirName)
{
    return std::filesystem::create_directory(dirName);
}

bool filesys::removeDir(const char *dirName)
{
    return std::filesystem::remove_all(dirName);
}

bool filesys::hasFile(const char *fileName)
{
    return std::filesystem::exists(fileName);
}

void filesys::copyFile(const char *dstFileName, const char *srcFileName)
{
    auto src_fptr = make_fileptr(srcFileName, "rb+");
    auto dst_fptr = make_fileptr(dstFileName, "wb+");

    auto src_fp = src_fptr.get();
    auto dst_fp = dst_fptr.get();

    constexpr long copySize = 4096;
    char fileBuf[copySize];

    if(std::fseek(src_fp, 0L, SEEK_END)){
        throw fflerror("failed to fseek file %s: %s", srcFileName, std::strerror(errno));
    }

    const long fileSize = ftell(src_fp);
    if(fileSize < 0){
        throw fflerror("failed to ftell file %s: %s", srcFileName, std::strerror(errno));
    }

    if(std::fseek(src_fp, 0L, SEEK_SET)){
        throw fflerror("failed to fseek file %s: %s", srcFileName, std::strerror(errno));
    }

    long copyDone = 0;
    while(copyDone < fileSize){
        const auto currCopySize = std::min<long>(copySize, fileSize - copyDone);
        if(std::fread (fileBuf, currCopySize, 1, src_fp) != 1){
            throw fflerror("failed to read file %s: %s", srcFileName, std::strerror(errno));
        }

        if(std::fwrite(fileBuf, currCopySize, 1, dst_fp) != 1){
            throw fflerror("failed to write file %s: %s", dstFileName, std::strerror(errno));
        }
        copyDone += currCopySize;
    }
}

std::tuple<std::string, std::string> filesys::decompFileName(const char *fullName)
{
    fflassert(str_haschar(fullName));
    if(const auto p = std::strrchr(fullName, '/')){
        return {std::string(fullName, p), std::string(p + 1)};
    }
    else{
        return {"", fullName};
    }
}

std::vector<std::string> filesys::getFileList(const char *dir, const char *reg)
{
    fflassert(str_haschar(dir));
    std::vector<std::string> result;
    std::regex matchRegex(str_haschar(reg) ? reg : ".*");

    for(auto &p: std::filesystem::directory_iterator(dir)){
        if(!p.is_regular_file()){
            continue;
        }

        auto fileName = p.path().filename().u8string();
        if(str_haschar(reg)){
            if(!std::regex_match(reinterpret_cast<const char *>(fileName.c_str()), matchRegex)){
                continue;
            }
        }

        result.push_back(reinterpret_cast<const char *>(p.path().u8string().c_str()));
    }
    return result;
}
