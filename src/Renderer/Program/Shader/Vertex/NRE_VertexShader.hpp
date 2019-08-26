
    /**
     * @file NRE_VertexShader.hpp
     * @brief Declaration of Engine's Renderer's Object : VertexShader
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
             * @class VertexShader
             * @brief Describe the vertex shader stage
             */
            class VertexShader : public Shader {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        VertexShader() = delete;
                        /**
                         * Create the vertex shader from the main shader file
                         * @param m the main shader's file
                         */
                        VertexShader(IO::File const& m);
                        /**
                         * Create the vertex shader from the main shader file and special includes
                         * @param m     the main shader's file
                         * @param inc   the shader's specific includes
                         */
                        VertexShader(IO::File const& m, Utility::Vector<IO::File> && inc);

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the vertex shader to move
                         */
                        VertexShader(VertexShader && s) = default;

                    //## Deconstructor ##//
                        /**
                         * VertexShader Deconstructor
                         */
                        ~VertexShader() = default;

                    //## Getter ##//
                        /**
                         * @return return the shader's stage type
                         */
                        GL::ShaderType getType() const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of s into this
                         * @param s the vertex shader to move into this
                         * @return      the reference of himself
                         */
                        VertexShader& operator =(VertexShader && s) = default;
            };
        }
    }

    #include "NRE_VertexShader.tpp"
