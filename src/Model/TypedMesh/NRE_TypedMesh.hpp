    
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
    
            /**
             * @class TypedMesh
             * @brief Manage the creation of mesh from a given object, simplifying the process
             */
            template <class T>
            class TypedMesh : public Mesh {
                private : // Fields
                    const T* target;      /**< The typed object */
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        TypedMesh() = delete;
                        /**
                         * Construct a mesh from the mesh buffer, used for special cullable mesh construction
                         * @param buffer the mesh buffer
                         */
                        TypedMesh(GL::AbstractVBO* buffer);
                        /**
                         * Construct a mesh from the object to render
                         * @param o the typed object used to construct the mesh
                         */
                        TypedMesh(const T* o);
                        /**
                         * Construct a mesh from the object to render
                         * @param args the parameters to construct the mesh, doesn't keep the target in memory
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
    
                    //## Getter ##//
                        /**
                         * @return the mesh's typed object
                         */
                        const T* getTarget() const;
    
                    //## Setter ##//
                        /**
                         * Set the mesh's typed object
                         * @param t the new object
                         */
                        void setTarget(const T* t);
                    
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