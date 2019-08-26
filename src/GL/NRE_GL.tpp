
    /**
     * @file GL/NRE_GL.cpp
     * @brief Implementation of NearlyRealEngine's GL Functions
     * @author Louis ABEL
     * @date 11/08/2019
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
                return glIsShader(id) == GL_TRUE;
            }

            inline Id createProgram() {
                return glCreateProgram();
            }

            inline void deleteProgram(Id id) {
                glDeleteProgram(id);
            }

            inline bool isProgram(Id id) {
                return glIsProgram(id) == GL_TRUE;
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

        }
    }
