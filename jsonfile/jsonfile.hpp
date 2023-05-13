#ifndef    __jsonFile__
#define    __jsonFile__

#include <fstream>
#include "json\json.h"

namespace mylib
{


class JsonFile{

public:
    JsonFile();
    JsonFile(const std::string fileName);
    bool loadJsonFile(const std::string fileName);
    void saveJsonFile(const std::string fileName);

    Json::Value m_Root;
private:

};

}
#endif
