
    /**
     * @file NRE_FragmentShader.hpp
     * @brief Declaration of Engine's Renderer's Object : FragmentShader
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
             * @class FragmentShader
             * @brief Describe the fragment shader stage
             */
            class FragmentShader : public Shader {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        FragmentShader() = delete;
                        /**
                         * Create the fragment shader from the main shader file
                         * @param m the main shader's file
                         */
                        FragmentShader(IO::File const& m);
                        /**
                         * Create the fragment shader from the main shader file and special includes
                         * @param m     the main shader's file
                         * @param inc   the shader's specific includes
                         */
                        FragmentShader(IO::File const& m, Utility::Vector<IO::File> && inc);

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the fragment shader to move
                         */
                        FragmentShader(FragmentShader && s) = default;

                    //## Deconstructor ##//
                        /**
                         * FragmentShader Deconstructor
                         */
                        ~FragmentShader() = default;

                    //## Getter ##//
                        /**
                         * @return return the shader's stage type
                         */
                        GL::ShaderType getType() const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of s into this
                         * @param s the fragment shader to move into this
                         * @return      the reference of himself
                         */
                        FragmentShader& operator =(FragmentShader && s) = default;
            };
        }
    }

    #include "NRE_FragmentShader.tpp"
