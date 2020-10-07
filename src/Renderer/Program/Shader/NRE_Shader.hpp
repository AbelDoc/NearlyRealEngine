
    /**
     * @file Shader/NRE_Shader.hpp
     * @brief Declaration of Engine's Renderer's Object : Shader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_IO.hpp>
     #include <Header/NRE_Core.hpp>

     #include "../../../Header/NRE_GL.hpp"
     #include "../../../Header/NRE_Exception.hpp"

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
             * @pure Shader
             * @brief An abstract class for specific shader stage
             */
            class Shader {
                private:    //Fields
                    Id id;                              /**< The shader's id */
                    IO::File main;                      /**< The shader's main file */
                    Core::Vector<IO::File> includes; /**< The shader's specific includes */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Shader() = delete;
                        /**
                         * Create the shader from the main shader file
                         * @param m the main shader's file
                         */
                        Shader(IO::File const& m);
                        /**
                         * Create the shader from the main shader file and special includes
                         * @param m     the main shader's file
                         * @param inc   the shader's specific includes
                         */
                        Shader(IO::File const& m, Core::Vector<IO::File> && inc);

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param s the shader to copy
                         */
                        Shader(Shader const& s) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the shader to move
                         */
                        Shader(Shader && s);

                    //## Deconstructor ##//
                        /**
                         * Shader Deconstructor
                         */
                        virtual ~Shader();

                    //## Getter ##//
                        /**
                         * @return return the shader's stage type
                         */
                        virtual GL::ShaderType getType() const = 0;
                        /**
                         * @return the shader's id
                         */
                        Id getId() const;

                    //## Methods ##//
                        /**
                         * Compile the current shader
                         * @param program   the program where the stage will be added
                         * @return if the shader compiled
                         */
                        bool compile(Id program);
                        /**
                         * Create the object's id
                         */
                        void createId();
                        /**
                         * Delete the object's id
                         */
                        void deleteId();
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool exist() const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param s the shader to copy into this
                         * @return  the reference of himself
                         */
                        Shader& operator =(Shader const& s) = delete;
                        /**
                         * Move assignment of s into this
                         * @param s the shader to move into this
                         * @return  the reference of himself
                         */
                        Shader& operator =(Shader && s);

                private:   // Methods
                    /**
                     * Read a shader file
                     * @param  line       the shader's file line
                     * @param  sourceCode the shader's source code
                     * @param  file       a shader's file
                     * @return            if the shader's file exists
                     */
                    bool readFile(Core::String& line, Core::String& sourceCode, IO::File const& file) const;

                public:     // Static
                    static const IO::File BASE_PATH;    /**< Programs base directory */
            };
        }
    }

    #include "NRE_Shader.tpp"
