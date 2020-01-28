    
    /**
     * @file NRE_Mesh.hpp
     * @brief Declaration of Engine's Model's Object : Mesh
     * @author Louis ABEL
     * @date 22/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../../GL/VBO/NRE_AbstractVBO.hpp"
    #include "../../GL/Buffer/VAO/NRE_VAO.hpp"
    
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
            
            template<class> class MeshFactory;
            
            template <class T>
            class TypedMesh : public Mesh {
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        TypedMesh() = delete;
                        /**
                         * Construct a mesh from the object to render
                         * @param o the object to construct the mesh
                         */
                        TypedMesh(T const& o);
                        /**
                         * Construct a mesh from the object to render
                         * @param args the parameters to construct the mesh objets
                         */
                        template <class ... Args>
                        TypedMesh(Args && ... args);
                    
                    //## Move Constructor ##//
                        /**
                         * Move m into this
                         * @param m the typed mesh to move
                         */
                        TypedMesh(TypedMesh && m) = default;
                    
                    //## Deconstructor ##//
                        /**
                         * TypedMesh Deconstructor
                         */
                        ~TypedMesh() = default;
                    
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m the typed mesh to move into this
                         * @return  the reference of himself
                         */
                        TypedMesh& operator =(TypedMesh && b) = default;
            };
        }
    }
    
    #include "NRE_TypedMesh.tpp"