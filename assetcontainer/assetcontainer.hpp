#ifndef ASSETCONTAINER_HPP
#define ASSETCONTAINER_HPP

#include <map>
#include <memory>
#include <string>
#include "SFML/Graphics/Texture.hpp"

template <typename key, typename typeAsset>
class AssetContainer {
    public:
        typeAsset& getAsset(key);
        const typeAsset& getAsset(key) const;
        bool loadAsset(key, const std::string&);
        template <typename parameter>
        bool loadAsset(key, const std::string&, const parameter&);
        bool insertAsset(key, std::unique_ptr<typeAsset>);
        bool removeAsset(key);

    private:
        std::map<key, std::unique_ptr<typeAsset>> m_container;
};

template <typename key, typename typeAsset>
 typeAsset& AssetContainer<key, typeAsset>::getAsset(key id)
 {
    auto reference = m_container.find(id);
    return *reference->second;
 }

template <typename key, typename typeAsset>
 const typeAsset& AssetContainer<key, typeAsset>::getAsset(key id) const
 {
    auto reference = m_container.find(id);
    return *reference->second;
 }

template <typename key, typename typeAsset>
bool AssetContainer<key, typeAsset>::loadAsset(key id, const std::string& fileName)
{
    std::unique_ptr<typeAsset> assetPtr = std::make_unique<typeAsset>();
    if(!assetPtr->loadFromFile(fileName)) { return false; }
    insertAsset(id, std::move(assetPtr));
    return true;
}

template <typename key, typename typeAsset>
template <typename parameter>
bool AssetContainer<key, typeAsset>::loadAsset(key id, const std::string& fileName, const parameter& secondParameter)
{
    std::unique_ptr<typeAsset> assetPtr = std::make_unique<typeAsset>();
    if(!assetPtr->loadFromFile(fileName, secondParameter)) { return false; }
    insertAsset(id, std::move(assetPtr));
    return true;
}

template <typename key, typename typeAsset>
bool AssetContainer<key, typeAsset>::insertAsset(key id, std::unique_ptr<typeAsset> asset)
{
    auto inserted = m_container.insert(std::make_pair(id, std::move(asset)));
    return inserted.second;
}

template <typename key, typename typeAsset>
bool AssetContainer<key, typeAsset>::removeAsset(key id)
{
    if(m_container.erase(id) == 0) { return false; }
    else { return true; }
}

//#include "assetcontainer.inl"
#endif
