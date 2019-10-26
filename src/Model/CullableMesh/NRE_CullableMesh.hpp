    
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
            class CullableMesh : public TypedMesh<T>,
                                 public Utility::Observer {
                private :   // Fields
                    T& target;
                    Data cacheData;
                
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        CullableMesh() = delete;
                        /**
                         * Construct the mesh with the target object
                         * @param o the object to create the mesh
                         */
                        CullableMesh(T& o);
    
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
                    
                    //## Methods ##//
                        /**
                         * Test if the target is in bound
                         * @param target    the other to test
                         * @param bound     the other object to test
                         * @return if target is in bound
                         */
                        bool inBound(K const& bound) const;
                        /**
                         * Update the observer when the observable notify it
                         * @param obs the observable
                         * @param arg notification data
                         */
                        void update(Utility::Observable* obs, void* arg) override;
                        /**
                         * Draw the mesh
                         * @param boundObject the object to test if the mesh in visible
                         * @param mode        the drawing mode
                         * @return if the mesh has been drawn
                         */
                        bool draw(K const& boundObject, GL::DrawMode mode = GL_TRIANGLES) const;
    
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