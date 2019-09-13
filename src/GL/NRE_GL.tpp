
    /**
     * @file GL/NRE_GL.tpp
     * @brief Implementation of NearlyRealEngine's GL Functions
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline void clearColor(float r, float g, float b, float a) {
                glClearColor(r, g, b, a);
            }

            inline void clearColor(Math::Vector4D<float> const& color) {
                glClearColor(color.getR(), color.getG(), color.getB(), color.getA());
            }

            inline void clearColor(Math::Vector3D<float> const& color, float a) {
                glClearColor(color.getR(), color.getG(), color.getB(), a);
            }

            inline GLint getUniformLocation(Id id, Utility::String const& name) {
                return glGetUniformLocation(id, name.getCData());
            }

            inline Id createShader(ShaderType type) {
                return glCreateShader(type);
            }

            inline void deleteShader(Id id) {
                glDeleteShader(id);
            }

            inline bool isShader(Id id) {
                return glIsShader(id);
            }

            inline Id createProgram() {
                return glCreateProgram();
            }

            inline void deleteProgram(Id id) {
                glDeleteProgram(id);
            }

            inline bool isProgram(Id id) {
                return glIsProgram(id);
            }

            inline void replaceSource(Id id, GLsizei count, const GLchar** strs, const GLint* lengths) {
                glShaderSource(id, count, strs, lengths);
            }

            inline void replaceSource(Id id, Utility::String const& str) {
                const char* ptr = str.getCData();
                glShaderSource(id, 1, &ptr, nullptr);
            }

            inline void compileShader(Id id) {
                glCompileShader(id);
            }

            inline void attachShader(Id program, Id id) {
                glAttachShader(program, id);
            }

            inline void detachShader(Id program, Id id) {
                glDetachShader(program, id);
            }

            inline void useProgram(Id id) {
                glUseProgram(id);
            }

            inline void linkProgram(Id id) {
                glLinkProgram(id);
            }

            inline void bindAttributeLocation(Id id, GLuint index, Utility::String const& name) {
                glBindAttribLocation(id, index, name.getCData());
            }

            inline GLint getShaderInfo(Id id, GLenum info) {
                GLint res = 0;
                glGetShaderiv(id, info, &res);
                return res;
            }

            inline Utility::String getShaderLog(Id id) {
                Utility::String log;
                GLint size = getShaderInfo(id, GL_INFO_LOG_LENGTH);
                log.reserve(size);

                glGetShaderInfoLog(id, size, nullptr, &log[0]);
                return log;
            }

            inline GLint getProgramInfo(Id id, GLenum info) {
                GLint res = 0;
                glGetProgramiv(id, info, &res);
                return res;
            }

            inline Utility::String getProgramLog(Id id) {
                Utility::String log;
                GLint size = getProgramInfo(id, GL_INFO_LOG_LENGTH);
                log.reserve(size);

                glGetProgramInfoLog(id, size, nullptr, &log[0]);
                return log;
            }

            inline void bindBuffer(BufferTarget target, Id id) {
                glBindBuffer(target, id);
            }

            inline Id generateBuffer() {
                Id tmp = 0;
                glGenBuffers(1, &tmp);
                return tmp;
            }

            inline void deleteBuffer(Id id) {
                glDeleteBuffers(1, &id);
            }

            inline bool isBuffer(Id id) {
                return glIsBuffer(id);
            }

            inline void sendData(BufferTarget target, std::size_t size, const void* data, GLenum usage) {
                glBufferData(target, size, data, usage);
            }

            inline void updateData(BufferTarget target, GLintptr offset, std::size_t size, const void* data) {
                glBufferSubData(target, offset, size, data);
            }

            inline void bindBufferBase(BufferTarget target, int index, Id id) {
                glBindBufferBase(target, index, id);
            }

            inline GLuint getUniformBlockIndex(Id id, Utility::String const& name) {
                return glGetUniformBlockIndex(id, name.getCData());
            }

            inline void bindUniformBlock(Id id, GLuint blockIndex, int index) {
                glUniformBlockBinding(id, blockIndex, index);
            }

            inline Id generateRenderBuffer() {
                Id tmp = 0;
                glGenRenderbuffers(1, &tmp);
                return tmp;
            }

            inline void deleteRenderBuffer(Id id) {
                glDeleteRenderbuffers(1, &id);
            }

            inline bool isRenderBuffer(Id id) {
                return glIsRenderbuffer(id);
            }

            inline void bindRenderBuffer(BufferTarget target, Id id) {
                glBindRenderbuffer(target, id);
            }

            inline void allocateRenderBuffer(BufferTarget target, RenderInternalFormat internalFormat, GLsizei w, GLsizei h) {
                glRenderbufferStorage(target, internalFormat, w, h);
            }

            inline void attachRenderBuffer(BufferTarget fboTarget, AttachPoint attach, BufferTarget renderTarget, Id id) {
                glFramebufferRenderbuffer(fboTarget, attach, renderTarget, id);
            }

            inline void attach2DTexture(BufferTarget fboTarget, AttachPoint attach, BufferTarget textureTarget, Id id, GLint level) {
                glFramebufferTexture2D(fboTarget, attach, textureTarget, id, level);
            }

            inline void attachTextureLayer(BufferTarget fboTarget, AttachPoint attach, Id id, GLint level, GLint layer) {
                glFramebufferTextureLayer(fboTarget, attach, id, level, layer);
            }

            inline Id generateTexture() {
                Id tmp = 0;
                glGenTextures(1, &tmp);
                return tmp;
            }

            inline void deleteTexture(Id id) {
                glDeleteTextures(1, &id);
            }

            inline bool isTexture(Id id) {
                return glIsTexture(id);
            }

            inline void bindTexture(BufferTarget target, Id id) {
                glBindTexture(target, id);
            }

            inline void send2DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLint border, TextureFormat format, TextureType type, const void* data) {
                glTexImage2D(target, level, internalFormat, width, height, border, format, type, data);
            }

            inline void send2DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, Math::Vector2D<GLsizei> const& size, GLint border, TextureFormat format, TextureType type, const void* data) {
                glTexImage2D(target, level, internalFormat, size.getW(), size.getH(), border, format, type, data);
            }

            inline void update2DTextureData(BufferTarget target, GLint level, GLint offsetX, GLint offsetY, GLsizei width, GLsizei height, TextureFormat format, TextureType type, const void* data) {
                glTexSubImage2D(target, level, offsetX, offsetY, width, height, format, type, data);
            }

            inline void update2DTextureData(BufferTarget target, GLint level, Math::Vector2D<GLint> const& offset, Math::Vector2D<GLsizei> const& size, TextureFormat format, TextureType type, const void* data) {
                glTexSubImage2D(target, level, offset.getX(), offset.getY(), size.getW(), size.getH(), format, type, data);
            }

            inline void setTextureParameter(BufferTarget target, TextureParameter param, GLint value) {
                glTexParameteri(target, param, value);
            }

            inline void send3DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, TextureFormat format, TextureType type, const void* data) {
                glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, data);
            }

            inline void send3DTextureData(BufferTarget target, GLint level, TextureInternalFormat internalFormat, Math::Vector2D<GLsizei> const& size, GLsizei depth, GLint border, TextureFormat format, TextureType type, const void* data) {
                glTexImage3D(target, level, internalFormat, size.getW(), size.getH(), depth, border, format, type, data);
            }

            inline void update3DTextureData(BufferTarget target, GLint level, GLint offsetX, GLint offsetY, GLint offsetZ, GLsizei width, GLsizei height, GLsizei depth, TextureFormat format, TextureType type, const void* data) {
                glTexSubImage3D(target, level, offsetX, offsetY, offsetZ, width, height, depth, format, type, data);
            }

            inline void update3DTextureData(BufferTarget target, GLint level, Math::Vector3D<GLint> const& offset, Math::Vector2D<GLsizei> const& size, GLsizei depth, TextureFormat format, TextureType type, const void* data) {
                glTexSubImage3D(target, level, offset.getX(), offset.getY(), offset.getZ(), size.getW(), size.getH(), depth, format, type, data);
            }

            inline void bindFrameBuffer(BufferTarget target, Id id) {
                glBindFramebuffer(target, id);
            }

            inline Id generateFrameBuffer() {
                Id tmp = 0;
                glGenFramebuffers(1, &tmp);
                return tmp;
            }

            inline void deleteFrameBuffer(Id id) {
                glDeleteFramebuffers(1, &id);
            }

            inline bool isFrameBuffer(Id id) {
                return glIsFramebuffer(id);
            }

            inline void bindVAO(Id id) {
                glBindVertexArray(id);
            }

            inline Id generateVAO() {
                Id tmp = 0;
                glGenVertexArrays(1, &tmp);
                return tmp;
            }

            inline void deleteVAO(Id id) {
                glDeleteVertexArrays(1, &id);
            }

            inline bool isVAO(Id id) {
                return glIsVertexArray(id);
            }

            inline FrameBufferStatus getFrameBufferStatus(BufferTarget target) {
                return glCheckFramebufferStatus(target);
            }

            inline void drawBuffer(BufferTarget target) {
                glDrawBuffer(target);
            }

            inline void readBuffer(BufferTarget target) {
                glReadBuffer(target);
            }

            inline void drawArrays(DrawMode mode, GLint first, GLsizei count) {
                glDrawArrays(mode, first, count);
            }

            inline void drawArraysInstanced(DrawMode mode, GLint first, GLsizei count, GLsizei instance) {
                glDrawArraysInstanced(mode, first, count, instance);
            }

            inline void drawMultiArrays(DrawMode mode, const GLint* first, const GLsizei* count, GLsizei drawCount) {
                glMultiDrawArrays(mode, first, count, drawCount);
            }

            inline void drawElements(DrawMode mode, GLsizei count, IndexType type, const void* indexes) {
                glDrawElements(mode, count, type, indexes);
            }

            inline void drawElementsInstanced(DrawMode mode, GLsizei count, IndexType type, const void* indexes, GLsizei instanceCount) {
                glDrawElementsInstanced(mode, count, type, indexes, instanceCount);
            }

            inline void drawMultiElements(DrawMode mode, const GLsizei* counts, IndexType type, const void* const* indexes, GLsizei drawCount) {
                glMultiDrawElements(mode, counts, type, indexes, drawCount);
            }

            inline void clear(GLbitfield mask) {
                glClear(mask);
            }

            inline void polygonMode(FaceType face, PolygonMode mode) {
                glPolygonMode(face, mode);
            }

        }
    }
