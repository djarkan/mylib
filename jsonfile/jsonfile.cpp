#include "jsonfile.hpp"

namespace mylib
{


JsonFile::JsonFile()
{

}

JsonFile::JsonFile(const std::string fileName)
{
    loadJsonFile(fileName);
}

bool JsonFile::loadJsonFile(const std::string fileName)
{
    std::ifstream jsonFile(fileName, std::ifstream::in);
    Json::CharReaderBuilder reader;
    reader["collectComments"] = true;
    JSONCPP_STRING errs;
    return Json::parseFromStream(reader, jsonFile, &m_Root, &errs);
}

void JsonFile::saveJsonFile(const std::string fileName)
{
    std::ofstream jsonFile(fileName, std::ofstream::out);
    Json::StreamWriterBuilder builder;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(m_Root, &jsonFile);

}

}
