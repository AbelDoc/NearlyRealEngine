
    /**
     * @file GL/NRE_GL.hpp
     * @brief Declaration of NearlyRealEngine's GL Functions
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    #pragma once


    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wstrict-overflow"
    #pragma GCC diagnostic ignored "-Warray-bounds"

    #include <stb_image.h>

    #pragma GCC diagnostic pop

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

            typedef GLenum BufferTarget;

            typedef GLenum RenderInternalFormat;
            typedef GLenum AttachPoint;

            typedef GLenum TextureType;
            typedef GLenum ShaderType;
            typedef GLenum IndexType;

            typedef GLenum TextureFormat;
            typedef GLenum TextureParameter;
            typedef GLint TextureInternalFormat;

            typedef GLenum FrameBufferStatus;

            typedef GLenum StreamUsage;
            typedef GLenum DrawMode;

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
            /**
             * Bind a buffer to a given target
             * @param target the bind target
             * @param id     the buffer id
             */
            void bindBuffer(BufferTarget target, Id id);
            /**
             * Generate a buffer id
             * @return the generated buffer
             */
            Id generateBuffer();
            /**
             * Delete a buffer
             * @param id the buffer id
             */
            void deleteBuffer(Id id);
            /**
             * Tell if the given id is a buffer
             * @param  id the buffer id
             * @return    the test's result
             */
            bool isBuffer(Id id);
            /**
             * Send data to the current buffer with a given target
             * @param target the data target
             * @param size   the data size
             * @param data   the data to send, nullptr for allocation only
             * @param usage  the buffer usage
             */
            void sendData(BufferTarget target, std::size_t size, const void* data, GLenum usage);
            /**
             * Update data from the current buffer with a given target
             * @param target the data target
             * @param offset the update offset
             * @param size   the data size
             * @param data   the data to send
             */
            void updateData(BufferTarget target, GLintptr offset, std::size_t size, const void* data);
            /**
             * Bind a buffer base
             * @param target the buffer target
             * @param index  the binding point
             * @param id     the buffer id
             */
            void bindBufferBase(BufferTarget target, int index, Id id);
            /**
             * Query a uniform block index
             * @param  id   the program id
             * @param  name the block name
             * @return      the block index
             */
            GLuint getUniformBlockIndex(Id id, Utility::String const& name);
            /**
             * Bind a uniform block
             * @param id         the program id
             * @param blockIndex the block index
             * @param index      the binding index
             */
            void bindUniformBlock(Id id, GLuint blockIndex, int index);
            /**
             * Generate a render buffer id
             * @return the generated render buffer
             */
            Id generateRenderBuffer();
            /**
             * Delete a render buffer
             * @param id the render buffer id
             */
            void deleteRenderBuffer(Id id);
            /**
             * Tell if the given id is a render buffer
             * @param  id the render buffer id
             * @return    the test's result
             */
            bool isRenderBuffer(Id id);
            /**
             * Bind a render buffer
             * @param target the buffer target
             * @param id     the buffer id
             */
            void bindRenderBuffer(BufferTarget target, Id id);
            /**
             * Allocate video memory for the current render buffer
             * @param target         the buffer target
             * @param internalFormat the buffer internal format
             * @param w              the buffer width
             * @param h              the buffer height
             */
            void allocateRenderBuffer(BufferTarget target, RenderInternalFormat internalFormat, GLsizei w, GLsizei h);
            /**
             * Attach a render buffer to the current framebuffer
             * @param fboTarget    the frame buffer target
             * @param attach       the attach point
             * @param renderTarget the render buffer target
             * @param id           the render buffer id
             */
            void attachRenderBuffer(BufferTarget fboTarget, AttachPoint attach, BufferTarget renderTarget, Id id);
            /**
             * Attach a 2D texture to the current framebuffer
             * @param fboTarget     the frame buffer target
             * @param attach        the attach point
             * @param textureTarget the texture target
             * @param id            the texture id
             * @param level         the texture level
             */
            void attach2DTexture(BufferTarget fboTarget, AttachPoint attach, BufferTarget textureTarget, Id id, GLint level);
            /**
             * Attach a texture layer to the current framebuffer
             * @param fboTarget the frame buffer target
             * @param attach    the attach point
             * @param id        the texture id
             * @param level     the texture level
             * @param layer     the texture layer
             */
            void attachTextureLayer(BufferTarget fboTarget, AttachPoint attach, Id id, GLint level, GLint layer);
            /**
             * Generate a texture id
             * @return the generated texture
             */
            Id generateTexture();
            /**
             * Delete a texture
             * @param id the texture id
             */
            void deleteTexture(Id id);
            /**
             * Tell if the given id is a texture
             * @param  id the texture id
             * @return    the test's result
             */
            bool isTexture(Id id);
            /**
             * Bind a texture
             * @param target the buffer target
             * @param id     the buffer id
             */
            void bindTexture(BufferTarget target, Id id);
            /**
             * Send data to a 2D texture
             * @param target         the texture target
             * @param level          the texture level
             * @param internalFormat the texture internal format
             * @param width          the texture width
             * @param height         the texture height
             * @param border         the border size
             * @param format         the texture format
             * @param type           the texture type
             * @param data           the data to send, nullptr for allocation only
             */
            void send2DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLint border, TextureFormat format, TextureType type, const void* data);
            /**
             * Send data to a 2D texture
             * @param target         the texture target
             * @param level          the texture level
             * @param internalFormat the texture internal format
             * @param size           the texture size
             * @param border         the border size
             * @param format         the texture format
             * @param type           the texture type
             * @param data           the data to send, nullptr for allocation only
             */
            void send2DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, Math::Vector2D<GLsizei> const& size, GLint border, TextureFormat format, TextureType type, const void* data);
            /**
             * Update a 2D texture area
             * @param target  the texture target
             * @param level   the texture level
             * @param offsetX the update offset X
             * @param offsetY the update offset Y
             * @param width   the update width
             * @param height  the update height
             * @param format  the texture format
             * @param type    the texture type
             * @param data    the data to send
             */
            void update2DTextureData(BufferTarget target, GLint level, GLint offsetX, GLint offsetY, GLsizei width, GLsizei height, TextureFormat format, TextureType type, const void* data);
            /**
             * Update a 2D texture area
             * @param target  the texture target
             * @param level   the texture level
             * @param offset  the update offset
             * @param size    the update size
             * @param format  the texture format
             * @param type    the texture type
             * @param data    the data to send
             */
            void update2DTextureData(BufferTarget target, GLint level, Math::Vector2D<GLint> const& offset, Math::Vector2D<GLsizei> const& size, TextureFormat format, TextureType type, const void* data);
            /**
             * Set the current texture parameter
             * @param target the texture target
             * @param param  the parameter to set
             * @param value  the new value
             */
            void setTextureParameter(BufferTarget target, TextureParameter param, GLint value);
            /**
             * Send data to a 3D texture
             * @param target         the texture target
             * @param level          the texture level
             * @param internalFormat the texture internal format
             * @param width          the texture width
             * @param height         the texture height
             * @param depth          the texture depth
             * @param border         the border size
             * @param format         the texture format
             * @param type           the texture type
             * @param data           the data to send, nullptr for allocation only
             */
            void send3DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, TextureFormat format, TextureType type, const void* data);
            /**
             * Send data to a 3D texture
             * @param target         the texture target
             * @param level          the texture level
             * @param internalFormat the texture internal format
             * @param size           the texture size
             * @param depth          the texture depth
             * @param border         the border size
             * @param format         the texture format
             * @param type           the texture type
             * @param data           the data to send, nullptr for allocation only
             */
            void send3DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, Math::Vector2D<GLsizei> const& size, GLsizei depth, GLint border, TextureFormat format, TextureType type, const void* data);
            /**
             * Update a 3D texture area
             * @param target  the texture target
             * @param level   the texture level
             * @param offsetX the update offset X
             * @param offsetY the update offset Y
             * @param offsetZ the update offset Z
             * @param width   the update width
             * @param height  the update height
             * @param depth   the update depth
             * @param format  the texture format
             * @param type    the texture type
             * @param data    the data to send
             */
            void update3DTextureData(BufferTarget target, GLint level, GLint offsetX, GLint offsetY, GLint offsetZ, GLsizei width, GLsizei height, GLsizei depth, TextureFormat format, TextureType type, const void* data);
            /**
             * Update a 3D texture area
             * @param target  the texture target
             * @param level   the texture level
             * @param offset  the update offset
             * @param size    the update size
             * @param depth   the update depth
             * @param format  the texture format
             * @param type    the texture type
             * @param data    the data to send
             */
            void update3DTextureData(BufferTarget target, GLint level, Math::Vector3D<GLint> const& offset, Math::Vector2D<GLsizei> const& size, GLsizei depth, TextureFormat format, TextureType type, const void* data);
            /**
             * Bind a frame buffer to a given target
             * @param target the bind target
             * @param id     the frame buffer id
             */
            void bindFrameBuffer(BufferTarget target, Id id);
            /**
             * Generate a frame buffer id
             * @return the generated frame buffer
             */
            Id generateFrameBuffer();
            /**
             * Delete a frame buffer
             * @param id the frame buffer id
             */
            void deleteFrameBuffer(Id id);
            /**
             * Tell if the given id is a frame buffer
             * @param  id the frame buffer id
             * @return    the test's result
             */
            bool isFrameBuffer(Id id);
            /**
             * Bind a vao
             * @param id the vao id
             */
            void bindVAO(Id id);
            /**
             * Generate a vao id
             * @return the generated vao
             */
            Id generateVAO();
            /**
             * Delete a vao
             * @param id the vao id
             */
            void deleteVAO(Id id);
            /**
             * Tell if the given id is a vao
             * @param  id the vao id
             * @return    the test's result
             */
            bool isVAO(Id id);
            /**
             * Query the current frame buffer status
             * @param  target the frame buffer target
             * @return        the current status
             */
            FrameBufferStatus getFrameBufferStatus(BufferTarget target);
            /**
             * Set the draw target for the current frame buffer
             * @param target the new draw target
             */
            void drawBuffer(BufferTarget target);
            /**
             * Set the read target for the current frame buffer
             * @param target the new read target
             */
            void readBuffer(BufferTarget target);
            /**
             * Draw a number of vertex
             * @param mode  the draw mode
             * @param first the first index to draw
             * @param count the number of vertex to draw
             */
            void drawArrays(DrawMode mode, GLint first, GLsizei count);
            /**
             * Draw a number of vertex with a number of instance
             * @param mode          the draw mode
             * @param first         the first index to draw
             * @param count         the number of vertex to draw
             * @param instanceCount the number of instance count
             */
            void drawArraysInstanced(DrawMode mode, GLint first, GLsizei count, GLsizei instanceCount);
            /**
             * Draw multiple arrays in one call
             * @param mode      the draw mode
             * @param first     an array of first index to draw
             * @param count     an array of vertex count to draw
             * @param drawCount the number of draw count
             */
            void drawMultiArrays(DrawMode mode, const GLint* first, const GLsizei* count, GLsizei drawCount);
            /**
             * Draw a number of indexed vertex
             * @param mode    the draw mode
             * @param count   the number of elements
             * @param type    the index type
             * @param indexes the index pointer, nullptr if currently binded
             */
            void drawElements(DrawMode mode, GLsizei count, IndexType type, const void* indexes);
            /**
             * Draw a number of indexed vertex with a number of instance
             * @param mode          the draw mode
             * @param count         the number of elements
             * @param type          the index type
             * @param indexes       the index pointer, nullptr if currently binded
             * @param instanceCount the number of instance count
             */
            void drawElementsInstanced(DrawMode mode, GLsizei count, IndexType type, const void* indexes, GLsizei instanceCount);
            /**
             * Draw multiples indexed arrays in one call
             * @param mode      the draw mode
             * @param counts    an array of elements counts
             * @param type      the index type
             * @param indexes   an array of index pointer
             * @param drawCount the number of draw count
             */
            void drawMultiElements(DrawMode mode, const GLsizei* counts, IndexType type, const void* const* indexes, GLsizei drawCount);
            /**
             * Clear the current buffer with a given clear mask
             * @param mask the clear mask
             */
            void clear(GLbitfield mask);


        }
    }

    #include "NRE_GL.tpp"
