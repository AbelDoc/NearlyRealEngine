    
    /**
     * @file Model/NRE_Model.hpp
     * @brief Declaration of Engine's Model's Object : Model
     * @author Louis ABEL
     * @date 08/11/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <Header/NRE_IO.hpp>
    #include "../Mesh/NRE_Mesh.hpp"

    #include "../../GL/VBO/IBO/NRE_IBO.hpp"
    #include "../../GL/VBO/Layout/Model/NRE_ModelVertex.hpp"

    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wfloat-equal"
    #pragma GCC diagnostic ignored "-Wconversion"
    #pragma GCC diagnostic ignored "-Wfloat-conversion"
    
        #include <assimp/Importer.hpp>
        #include <assimp/scene.h>
        #include <assimp/postprocess.h>
    
    #pragma GCC diagnostic pop

    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Model
         * @brief Engine's Model module
         */
        namespace Model {
            
            /**
             * @class Model
             * @brief Manage a collection of mesh
             */
            class Model : public Utility::Uncopyable<Model> {
                protected : // Fields
                    Utility::Vector<std::unique_ptr<Mesh>> meshes;  /**< The model's meshes */
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Model() = default;
                        /**
                         * Construct a model from a collections of meshes
                         * @param ms the collections of meshes
                         */
                        Model(Utility::Vector<std::unique_ptr<Mesh>> && ms);
                        /**
                         * Load an object model
                         * @param path the object's path
                         */
                        Model(IO::File const& path);
    
                    //## Move Constructor ##//
                        /**
                         * Move m into this
                         * @param m the model to move
                         */
                        Model(Model && m) = default;
    
                    //## Deconstructor ##//
                        /**
                         * Model Deconstructor
                         */
                        virtual ~Model() = default;
    
                    //## Getter ##//
                        /**
                         * Query a mesh from the model
                         * @param index the mesh's index
                         * @return the corresponding mesh
                         */
                        Mesh& get(std::size_t index);
                        /**
                         * Query a mesh from the model
                         * @param index the mesh's index
                         * @return the corresponding mesh
                         */
                        Mesh const& get(std::size_t index) const;
                        /**
                         * Query a mesh from the model
                         * @param index the mesh's index
                         * @return the corresponding casted mesh
                         */
                        template <class T>
                        T& get(std::size_t index);
                        /**
                         * Query a mesh from the model
                         * @param index the mesh's index
                         * @return the corresponding casted mesh
                         */
                        template <class T>
                        T const& get(std::size_t index) const;
    
                    //## Methods ##//
                        /**
                         * Reserve a number of mesh
                         * @param capacity the new meshes capacity
                         */
                        void reserve(std::size_t capacity);
                        /**
                         * @return tell if the model can be drawn
                         */
                        virtual bool canBeDrawn() const;
                        /**
                         * Add a mesh in the model
                         * @param mesh the mesh to add
                         */
                        virtual void add(std::unique_ptr<Mesh> && mesh);
                        /**
                         * Add a mesh in the model and take it's ownership
                         * @param mesh the mesh to add
                         */
                        virtual void add(Mesh* mesh);
                        /**
                         * Draw the model
                         * @param mode the drawing mode
                         * @return if the mesh has been drawn
                         */
                        virtual void draw(GL::DrawMode mode = GL_TRIANGLES) const;
    
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m the model to move into this
                         * @return  the reference of himself
                         */
                        Model& operator =(Model && m) = default;
                        
                private :   // Methods
                    /**
                     * Construct a model from an assimp loaded model
                     * @param node  the current assimp's node
                     * @param scene the assimp's scene
                     */
                    void constructNode(aiNode *node, const aiScene *scene);
                    /**
                     * Process an assimp's mesh and turn it into a nre's mesh
                     * @param  mesh the assimp's mesh
                     * @return      the converted mesh
                     */
                    Mesh* processMesh(aiMesh *mesh);
            };
    
        }
    }

    #include "NRE_Model.tpp"