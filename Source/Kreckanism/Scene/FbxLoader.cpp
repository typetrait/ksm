#include <Kreckanism/Scene/FbxLoader.h>

#include <vector>

#include <fbxsdk.h>
#include <fmt/format.h>

#include <Kreckanism/Core/Logger.h>
#include <Kreckanism/Render/Mesh.h>
#include <Kreckanism/Render/Vertex.h>

namespace Ksm
{
    std::vector<Mesh> FbxLoader::LoadMesh(const std::string& path)
    {
        auto fbxManager = FbxManager::Create();

        auto fbxIOSettings = FbxIOSettings::Create(fbxManager, IOSROOT);
        fbxManager->SetIOSettings(fbxIOSettings);

        auto fbxImporter = FbxImporter::Create(fbxManager, "");

        if (!fbxImporter->Initialize(path.c_str(), -1, fbxManager->GetIOSettings()))
        {
            auto reason = fbxImporter->GetStatus().GetErrorString();
            KLOG_FAIL(fmt::format("FbxImporter::Initialize() failed. Reason: {}.", reason));
            return meshBuffer;
        }

        auto fbxScene = FbxScene::Create(fbxManager, "KsmScene");

        fbxImporter->Import(fbxScene);

        FbxGeometryConverter converter(fbxManager);
        converter.Triangulate(fbxScene, true);

        fbxImporter->Destroy();

        auto rootNode = fbxScene->GetRootNode();
        if (rootNode)
        {
            for (int i = 0; i < rootNode->GetChildCount(); i++)
            {
                auto currentNode = rootNode->GetChild(i);
                ProcessNode(currentNode);
            }
        }

        fbxManager->Destroy();

        return meshBuffer;
    }

    void FbxLoader::ProcessNode(FbxNode* node)
    {
        auto nodeName = node->GetName();
        auto nodeAttribute = node->GetNodeAttribute();

        KLOG_INFO(fmt::format("Found node with name \"{}\".", nodeName));

        if (nodeAttribute->GetAttributeType() == FbxNodeAttribute::eMesh)
        {
            KLOG_INFO(fmt::format("\"{}\" is a mesh node.", nodeName));

            auto mesh = node->GetMesh();
            ProcessMesh(mesh);
        }

        for (int i = 0; i < node->GetChildCount(); i++)
        {
            auto currentNode = node->GetChild(i);
            ProcessNode(currentNode);
        }
    }

    void FbxLoader::ProcessMesh(FbxMesh* mesh)
    {
        auto fbxVertices = mesh->GetControlPoints();
        auto fbxVertexCount = mesh->GetControlPointsCount();

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;

        for (int i = 0; i < fbxVertexCount; i++)
        {
            Vertex v{};
            v.Position.x = fbxVertices[i].mData[0];
            v.Position.y = fbxVertices[i].mData[1];
            v.Position.z = fbxVertices[i].mData[2];
            v.Color = { 0.8f, 0.6f, 0.1f };
            v.Texture = { 0.0f, 0.0f };

            vertices.push_back(v);
        }

        auto fbxIndexCount = mesh->GetPolygonVertexCount();
        auto fbxIndices = mesh->GetPolygonVertices();

        for (int i = 0; i < fbxIndexCount; i++)
        {
            indices.push_back((unsigned int)fbxIndices[i]);
        }

        Mesh m(vertices, indices);
        meshBuffer.push_back(m);
    }
}
