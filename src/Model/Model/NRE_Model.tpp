    
    /**
     * @file Model/NRE_Model.tpp
     * @brief Implementation of Engine's Model's Object : Model
     * @author Louis ABEL
     * @date 08/11/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Model {
            
            inline Model::Model(IO::File const& path) {
                if (!path.exist()) {
                    throw (Exception::FileNotExistingException(path.getPath()));
                }
                Assimp::Importer importer;
                const aiScene* scene = importer.ReadFile(path.getPath().getData(), aiProcess_Triangulate | aiProcess_CalcTangentSpace);
    
                if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
                    throw (Exception::AssimpException(importer.GetErrorString()));
                }
    
                constructModel(scene->mRootNode, scene);
            }
            
            inline void Model::reserve(std::size_t capacity) {
                meshes.reserve(capacity);
            }
    
            inline void Model::addMesh(std::unique_ptr<Mesh> && mesh) {
                meshes.pushBack(std::move(mesh));
            }
    
            inline void Model::addMesh(Mesh* mesh) {
                meshes.emplaceBack(mesh);
            }
            
            inline bool Model::canBeDrawn() const {
                bool drawn = false;
                std::size_t i = 0;
                while (!drawn && i < meshes.getSize()) {
                    drawn = drawn || meshes[i++]->canBeDrawn();
                }
                return drawn;
            }
    
            inline void Model::draw(GL::DrawMode mode) const {
                for (auto& m : meshes) {
                    m->draw(mode);
                }
            }
    
            inline void Model::constructModel(aiNode *node, const aiScene* scene) {
                for (int i = 0; i < static_cast <int> (node->mNumMeshes); i++) {
                    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
                    addMesh(processMesh(mesh));
                }
        
                for (unsigned int i = 0; i < node->mNumChildren; i++) {
                    constructModel(node->mChildren[i], scene);
                }
            }
    
            inline Mesh* Model::processMesh(aiMesh* mesh) {
                GL::IBO<GL::MaterialVertex>* buffer = new GL::IBO<GL::MaterialVertex>(GL_STATIC_DRAW);
    
                buffer->reserve(mesh->mNumVertices);
                Math::Vector3D<int> materials(4, 4, 4);
                for (int i = 0; i < static_cast <int> (mesh->mNumVertices); i++) {
                    Math::Vector3D<float> vector(mesh->mVertices[i].x,  mesh->mVertices[i].y, mesh->mVertices[i].z);
                    Math::Vector3D<float> normal(mesh->mNormals[i].x,   mesh->mNormals[i].y,  mesh->mNormals[i].z);
                    Math::Vector3D<float> tangent(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
                    Math::Vector2D<float> uv;
                    if (mesh->mTextureCoords[0]) {
                        uv.setX(mesh->mTextureCoords[0][i].x);
                        uv.setY(mesh->mTextureCoords[0][i].y);
                    } else {
                        uv.setCoord(-1, -1);
                    }
                    buffer->addData(vector, normal, tangent, uv, materials);
                }
        
                for (int i = 0; i < static_cast <int> (mesh->mNumFaces); i++) {
                    aiFace face = mesh->mFaces[i];
                    for (int j = 0; j < static_cast <int> (face.mNumIndices); j++) {
                        buffer->addIndex(face.mIndices[j]);
                    }
                }
        
                return new Mesh(buffer);
            }
            
        }
    }