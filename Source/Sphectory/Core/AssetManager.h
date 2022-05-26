#pragma once

#include <map>
#include <string>
#include <vector>

#include <Kreckanism/Kreckanism.h>

class Entity;

class AssetManager
{
public:
    static std::vector<Ksm::Mesh> LoadMeshes(const std::string& path);
    static std::shared_ptr<Ksm::Texture> LoadTexture(const std::string& path, bool flip = true);
private:
    static Ksm::FbxLoader fbxLoader;
    static std::map<std::string, std::vector<Ksm::Mesh>> meshes;
    static std::map<std::string, std::shared_ptr<Ksm::Texture>> textures;
};
