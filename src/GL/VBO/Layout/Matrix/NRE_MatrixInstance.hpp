
    /**
     * @file NRE_MatrixInstance.hpp
     * @brief Declaration of Engine's GL's Object : MatrixInstance
     * @author Louis ABEL
     * @date 04/11/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../NRE_Layout.hpp"

    #include <Utility/Interfaces/Stringable/NRE_Stringable.hpp>

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace GL
         * @brief Engine's GL module
         */
        namespace GL {

            /**
             * @class MatrixInstance
             * @brief A vertex layout : Matrix
             */
            class MatrixInstance : public Utility::Stringable<MatrixInstance> {
                private:    //Fields
                    Math::Matrix4x4<float> matrix; /**< The matrix instance */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        MatrixInstance() = delete;
                        /**
                         * Construct the layout from a given matrix
                         * @param mat the layout's matrix
                         */
                        MatrixInstance(Math::Matrix4x4<float> const& mat) : matrix(mat) {
                        }

                    //## Methods ##//
                        /**
                         * Access the material vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute( 7, 4, GL_FLOAT, sizeof(MatrixInstance), 0);
                            Layout::enableAttribute( 8, 4, GL_FLOAT, sizeof(MatrixInstance), (void*)(1 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute( 9, 4, GL_FLOAT, sizeof(MatrixInstance), (void*)(2 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute(10, 4, GL_FLOAT, sizeof(MatrixInstance), (void*)(3 * sizeof(Math::Vector4D<float>)));
                            Layout::divideAttribute( 7, 1);
                            Layout::divideAttribute( 8, 1);
                            Layout::divideAttribute( 9, 1);
                            Layout::divideAttribute(10, 1);
                        }

                    //## Stream Operator ##//
                        /**
                         * Convert the matrix vertex layout into a string
                         * @return the converted matrix vertex layout
                         */
                        Utility::String toString() const {
                            return matrix.toString();
                        }

            };
        }
    }
