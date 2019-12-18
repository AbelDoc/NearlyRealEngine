
    /**
     * @file NRE_ColoredMatrixInstance.hpp
     * @brief Declaration of Engine's GL's Object : ColoredMatrixInstance
     * @author Louis ABEL
     * @date 18/12/2019
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
             * @class ColoredMatrixInstance
             * @brief A vertex layout : Color - Matrix
             */
            class ColoredMatrixInstance : public Utility::Stringable<ColoredMatrixInstance> {
                public:    //Fields
                    Math::Vector4D<float> color;   /**< The instance color */
                    Math::Matrix4x4<float> matrix; /**< The matrix instance */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ColoredMatrixInstance() = default;

                    //## Methods ##//
                        /**
                         * Access the material vertex for VAO's command's storing
                         */
                        static void access() {
                            Layout::enableAttribute( 1, 4, GL_FLOAT, sizeof(ColoredMatrixInstance), 0);
                            Layout::enableAttribute( 7, 4, GL_FLOAT, sizeof(ColoredMatrixInstance), (void*)(1 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute( 8, 4, GL_FLOAT, sizeof(ColoredMatrixInstance), (void*)(2 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute( 9, 4, GL_FLOAT, sizeof(ColoredMatrixInstance), (void*)(3 * sizeof(Math::Vector4D<float>)));
                            Layout::enableAttribute(10, 4, GL_FLOAT, sizeof(ColoredMatrixInstance), (void*)(4 * sizeof(Math::Vector4D<float>)));
                            Layout::divideAttribute( 1, 1);
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
                            return color.toString() + " - " + matrix.toString();
                        }

            };
        }
    }
