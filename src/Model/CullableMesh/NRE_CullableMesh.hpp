    
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
                    K const& boundObject;
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
                         * @param bound the object to test if the mesh in visible
                         */
                        CullableMesh(T& o, K const& bound);
    
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
                         * @return if target is in bound
                         */
                        bool inBound() const;
                        /**
                         * @return if the mesh can be drawn
                         */
                        bool canBeDrawn() const override;
                        /**
                         * Draw the mesh
                         * @param mode the drawing mode
                         */
                        void draw(GL::DrawMode mode = GL_TRIANGLES) const override;
                        /**
                         * Draw the mesh as an instanced one
                         * @param instance    the number of instances
                         * @param mode        the drawing mode
                         */
                        void drawInstanced(int instance, GL::DrawMode mode = GL_TRIANGLES) const override;
    
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