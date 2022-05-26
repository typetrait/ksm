#include <Sphectory/Core/AssetManager.h>

#include <string>

Ksm::FbxLoader AssetManager::fbxLoader;
std::map<std::string, std::vector<Ksm::Mesh>> AssetManager::meshes;
std::map<std::string, std::shared_ptr<Ksm::Texture>> AssetManager::textures;

std::vector<Ksm::Mesh> AssetManager::LoadMeshes(const std::string& path)
{
    if (meshes.contains(path))
        return meshes[path];
    auto modelMeshes = fbxLoader.LoadMesh(path);
    meshes[path] = modelMeshes;
    return modelMeshes;
}

std::shared_ptr<Ksm::Texture> AssetManager::LoadTexture(const std::string& path, bool flip)
{
    if (textures.contains(path))
        return textures[path];

    std::shared_ptr<Ksm::Texture> texture = std::make_shared<Ksm::Texture>(path, flip);
    textures[path] = texture;
    return texture;
}
