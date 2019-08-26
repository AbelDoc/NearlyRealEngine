
    /**
     * @file GL/NRE_GL.hpp
     * @brief Declaration of NearlyRealEngine's GL Functions
     * @author Louis ABEL
     * @date 11/08/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once

    #include <Header/NRE_System.hpp>
    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Utility.hpp>

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

            typedef GLenum ShaderType;

            /**
             * Clear the context screen and fill it with the given color
             * @param r the clear color red value
             * @param g the clear color green value
             * @param b the clear color blue value
             * @param a the clear color alpha value
             */
            void clearColor(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);

            /**
             * Clear the context screen and fill it with the given color
             * @param color the clear color
             */
            void clearColor(Math::Vector4D<float> const& color);

            /**
             * Clear the context screen and fill it with the given color
             * @param color the clear color rgb values
             * @param a     the clear color alpha value
             */
            void clearColor(Math::Vector3D<float> const& color, float a = 1.0f);
            /**
             * Query a uniform location
             * @param  id   the program id
             * @param  name the uniform name
             * @return      the requested location
             */
            GLint getUniformLocation(Id id, Utility::String const& name);
            /**
             * Create a shader id
             * @param  type the shader stage type
             * @return      the created id
             */
            Id createShader(ShaderType type);
            /**
             * Delete a shader
             * @param id the shader id
             */
            void deleteShader(Id id);
            /**
             * Test if the given id is a shader
             * @param  id the shader id
             * @return    the test's result
             */
            bool isShader(Id id);
            /**
             * Create a program id
             * @return the created id
             */
            Id createProgram();
            /**
             * Delete a program
             * @param id the program id
             */
            void deleteProgram(Id id);
            /**
             * Tell if the given id is a program
             * @param  id the program id
             * @return    the test's result
             */
            bool isProgram(Id id);
            /**
             * Replace the source code in a given shader
             * @param id      the shader handler
             * @param count   the number of elements in strs and lengths
             * @param strs    the source code strings
             * @param lengths the strings length, or NULL if strings are null-terminated
             */
            void replaceSource(Id id, GLsizei count, const GLchar** strs, const GLint* lengths);
            /**
             * Replace the source code in a given shader
             * @param id  the shader handler
             * @param str the source code
             */
            void replaceSource(Id id, Utility::String const& str);
            /**
             * Compile the given shader
             * @param id the shader id
             */
            void compileShader(Id id);
            /**
             * Attach a given shader id to a program
             * @param program the program id
             * @param id      the shader id
             */
            void attachShader(Id program, Id id);
            /**
             * Detach a given shader id from a program
             * @param program the program id
             * @param id      the shader id
             */
            void detachShader(Id program, Id id);
            /**
             * Make the given program the currently used
             * @param id the program id
             */
            void useProgram(Id id);
            /**
             * Link a program
             * @param id the program id
             */
            void linkProgram(Id id);
            /**
             * Bind an attribute name to a given lcoation
             * @param id    the program id
             * @param index the attribute location
             * @param name  the attribute name
             */
            void bindAttributeLocation(Id id, GLuint index, Utility::String const& name);
            /**
             * Query the shader info
             * @param  id   the shader id
             * @param  info the requested info name
             * @return      the requested info
             */
            GLint getShaderInfo(Id id, GLenum info);
            /**
             * Query the shader error log
             * @param  id the shader id
             * @return    the requested logs
             */
            Utility::String getShaderLog(Id id);
            /**
             * Query the program info
             * @param  id   the program id
             * @param  info the requested info name
             * @return      the requested info
             */
            GLint getProgramInfo(Id id, GLenum info);
            /**
             * Query the program error log
             * @param  id the program id
             * @return    the requested logs
             */
            Utility::String getProgramLog(Id id);

        }
    }

    #include "NRE_GL.tpp"
