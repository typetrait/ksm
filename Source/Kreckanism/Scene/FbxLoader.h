#pragma once

#include <memory>
#include <vector>

#include <fbxsdk.h>

#include <Kreckanism/Render/Mesh.h>

namespace Ksm
{
    class FbxLoader
    {
    public:
        std::vector<Mesh> LoadMesh(const std::string& path);

    private:
        void ProcessNode(FbxNode* node);
        void ProcessMesh(FbxMesh* mesh);
        std::vector<Mesh> meshBuffer;
    };
}
