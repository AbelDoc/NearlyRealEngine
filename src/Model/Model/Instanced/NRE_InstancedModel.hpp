    
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
            class InstancedModel : public Model {
                private:    //Fields
                    std::unique_ptr<GL::VBO<GL::MatrixInstance>> models;    /**< The matrix instance buffer */
                    Utility::Vector<Math::Matrix4x4<float>> matrixes;       /**< The matrixes */
    
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        InstancedModel() = default;
        
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
    
                    //## Getter ##//
                        /**
                         * @return the matrixes
                         */
                        Utility::Vector<Math::Matrix4x4<float>>& getMatrixes();
        
                    //## Setter ##//
                        /**
                         * Models buffer setter
                         * @param matrix the new models buffer
                         */
                        void setModels(std::unique_ptr<GL::VBO<GL::MatrixInstance>>& matrix);
        
                    //## Methods ##//
                        /**
                         * Update models' matrix
                         * @param data   the external data's source with matrix's data
                         * @param size   the data's size in bytes
                         * @param offset the data's offset
                         */
                        void updateModels(const void* data, std::size_t size, GLintptr offset = 0);
                        /**
                         * Orphan the models buffer
                         */
                        void orphanModels();
                        /**
                         * Draw the model
                         * @param mode     the drawing mode
                         * @return if the mesh has been drawn
                         */
                        bool draw(GL::DrawMode mode = GL_TRIANGLES) const override;
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
            };
    
        }
    }

    #include "NRE_InstancedModel.tpp"