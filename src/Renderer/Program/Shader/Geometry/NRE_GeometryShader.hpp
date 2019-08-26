
    /**
     * @file NRE_GeometryShader.hpp
     * @brief Declaration of Engine's Renderer's Object : GeometryShader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../NRE_Shader.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Renderer
         * @brief Engine's Renderer module
         */
        namespace Renderer {

            /**
             * @class GeometryShader
             * @brief Describe the geometry shader stage
             */
            class GeometryShader : public Shader {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        GeometryShader() = delete;
                        /**
                         * Create the geometry shader from the main shader file
                         * @param m the main shader's file
                         */
                        GeometryShader(IO::File const& m);
                        /**
                         * Create the geometry shader from the main shader file and special includes
                         * @param m     the main shader's file
                         * @param inc   the shader's specific includes
                         */
                        GeometryShader(IO::File const& m, Utility::Vector<IO::File> && inc);

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the geometry shader to move
                         */
                        GeometryShader(GeometryShader && s) = default;

                    //## Deconstructor ##//
                        /**
                         * GeometryShader Deconstructor
                         */
                        ~GeometryShader() = default;

                    //## Getter ##//
                        /**
                         * Type getter
                         * @return return the shader program type, used to differentiate derived shader
                         */
                        GL::ShaderType getType() const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of s into this
                         * @param s the geometry shader to move into this
                         * @return      the reference of himself
                         */
                        GeometryShader& operator =(GeometryShader && s) = default;
            };
        }
    }

    #include "NRE_GeometryShader.tpp"
