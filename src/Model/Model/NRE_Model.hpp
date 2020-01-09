    
    /**
     * @file Model/NRE_Model.hpp
     * @brief Declaration of Engine's Model's Object : Model
     * @author Louis ABEL
     * @date 08/11/2019
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
                        virtual void addMesh(std::unique_ptr<Mesh> && mesh);
                        /**
                         * Draw the model
                         * @param mode     the drawing mode
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
            };
    
        }
    }

    #include "NRE_Model.tpp"