    
    /**
     * @file NRE_CullableMesh.hpp
     * @brief Declaration of Engine's Model's Object : CullableMesh
     * @author Louis ABEL
     * @date 25/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../Mesh/NRE_Mesh.hpp"
    
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
        
            template <class T, class K = Math::Frustum, class Data = void*>
            class CullableMesh : public TypedMesh<T> {
                private :   // Fields
                    T& target;
                    const K* boundObject;
                    Data cacheData;
                
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        CullableMesh() = delete;
                        /**
                         * Construct the mesh with the target object
                         * @param o     the object to create the mesh
                         * @param bound the object to test if the mesh is visible
                         */
                        CullableMesh(T& o, const K* bound = nullptr);
    
                    //## Move Constructor ##//
                        /**
                         * Move m into this
                         * @param m the cullable mesh to move
                         */
                        CullableMesh(CullableMesh && m);
    
                    //## Deconstructor ##//
                        /**
                         * CullableMesh Deconstructor
                         */
                        ~CullableMesh() = default;
    
                    //## Setter ##//
                        /**
                         * Set the cullable mesh's bound object
                         * @param bound the new bound object
                         */
                        void setBoundObject(const K* bound);
                    
                    //## Methods ##//
                        /**
                         * @return if target is in bound
                         */
                        bool inBound() const;
                        /**
                         * @return if the mesh can be drawn
                         */
                        bool canBeDrawn() const override;
    
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m cullable mesh to move into this
                         * @return  the reference of himself
                         */
                        CullableMesh& operator =(CullableMesh && m);
            };
            
        }
    }

    #include "NRE_CullableMesh.tpp"