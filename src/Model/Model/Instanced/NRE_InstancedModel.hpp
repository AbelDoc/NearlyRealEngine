    
    /**
     * @file NRE_InstancedModel.hpp
     * @brief Declaration of Engine's Model's Object : InstancedModel
     * @author Louis ABEL
     * @date 29/11/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include "../NRE_Model.hpp"
    #include "../../../GL/VBO/Layout/Matrix/NRE_MatrixInstance.hpp"
    
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
             * @class InstancedModel
             * @brief Manage an instanced model
             */
            template <class InstanceLayout>
            class InstancedModel : public Model {
                public :    // Iterator
                    /**< Shortcut to hide Iterator implementation */
                    typedef typename GL::VBO<InstanceLayout>::Iterator         Iterator;
                    /**< Shortcut to hide ConstIterator implementation */
                    typedef typename GL::VBO<InstanceLayout>::ConstIterator    ConstIterator;
                    
                private:    //Fields
                    GL::VBO<InstanceLayout> models;    /**< The matrix instance buffer */
    
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        InstancedModel() = delete;
                        /**
                         * Construct the instanced model from the buffer's streaming usage
                         * @param nbInstance the number of instance for this model
                         * @param stream     the buffer's streaming usage
                         */
                        InstancedModel(std::size_t nbInstance, GL::StreamUsage stream);
        
                    //## Move-Constructor ##//
                        /**
                         * Move m into this
                         * @param m the model to move
                         */
                        InstancedModel(InstancedModel && m) = default;
        
                    //## Deconstructor ##//
                        /**
                         * InstancedModel Deconstructor
                         */
                        ~InstancedModel() = default;
    
                    //## Iterator Access ##//
                        /**
                         * @return an iterator on the first element
                         */
                        Iterator begin();
                        /**
                         * @return a const iterator on the first element
                         */
                        ConstIterator begin() const;
                        /**
                         * @return a const iterator on the first element
                         */
                        ConstIterator cbegin() const;
                        /**
                         * @return an iterator on the end of the container
                         */
                        Iterator end();
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator end() const;
                        /**
                         * @return a const iterator on the end of the container
                         */
                        ConstIterator cend() const;
        
                    //## Methods ##//
                        /**
                         * Add a mesh in the model
                         * @param mesh the mesh to add
                         */
                        virtual void add(std::unique_ptr<Mesh> && mesh) override;
                        /**
                         * Add a mesh in the model and take it's ownership
                         * @param mesh the mesh to add
                         */
                        virtual void add(Mesh* mesh) override;
                        /**
                         * Draw the model
                         * @param mode     the drawing mode
                         * @return if the mesh has been drawn
                         */
                        void draw(GL::DrawMode mode = GL_TRIANGLES) const override;
                        /**
                         * Update the buffer from the matrixes
                         */
                        void update();
        
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m the model to move into this
                         * @return  the reference of himself
                         */
                        InstancedModel& operator =(InstancedModel && m) = default;
    
                    //## Access Operator ##//
                        /**
                         * Return a reference on a data's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        InstanceLayout& operator [](std::size_t index);
                        /**
                         * Return a const reference on a data's object
                         * @warning No range check performed
                         * @param   index the object's index
                         * @return        the object's reference
                         */
                        InstanceLayout const& operator [](std::size_t index) const;
            };
    
        }
    }

    #include "NRE_InstancedModel.tpp"