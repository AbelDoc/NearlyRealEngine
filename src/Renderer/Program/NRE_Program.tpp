
    /**
     * @file NRE_Program.tpp
     * @brief Implementation of Engine's Renderer's Object : Program
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline Program::Program() : id(0) {
                createId();
            }

            inline Program::Program(Program && p) : id(p.id), uniforms(std::move(p.uniforms)), stages(std::move(p.stages)) {
                p.id = 0;
            }

            inline Program::~Program() {
                deleteId();
            }

            inline Id Program::getId() const {
                return id;
            }

            inline void Program::bind() const {
                GL::useProgram(getId());
            }

            inline void Program::unbind() const {
                GL::useProgram(0);
            }

            inline void Program::createId() {
                if (exist()) {
                    deleteId();
                }
                id = GL::createProgram();
            }

            inline void Program::deleteId() {
                GL::deleteProgram(getId());
                id = 0;
            }

            inline bool Program::exist() const {
                return GL::isProgram(getId());
            }

            inline void Program::detachShaders() {
                for (auto& shader : stages) {
                    GL::detachShader(getId(), shader->getId());
                }
                Core::Vector<std::unique_ptr<Shader>>().swap(stages);
            }

            inline void Program::addUniform(Core::String const& uniform) {
                uniforms.addLocation(getId(), uniform);
            }

            inline void Program::use1I(Core::String const& location, GLint v0) const {
                glUniform1i(uniforms.getLocation(location), v0);
            }

            inline void Program::use2I(Core::String const& location, GLint v0, GLint v1) const {
                glUniform2i(uniforms.getLocation(location), v0, v1);
            }

            inline void Program::use3I(Core::String const& location, GLint v0, GLint v1, GLint v2) const {
                glUniform3i(uniforms.getLocation(location), v0, v1, v2);
            }

            inline void Program::use4I(Core::String const& location, GLint v0, GLint v1, GLint v2, GLint v3) const {
                glUniform4i(uniforms.getLocation(location), v0, v1, v2, v3);
            }

            inline void Program::use1F(Core::String const& location, GLfloat v0) const {
                glUniform1f(uniforms.getLocation(location), v0);
            }

            inline void Program::use2F(Core::String const& location, GLfloat v0, GLfloat v1) const {
                glUniform2f(uniforms.getLocation(location), v0, v1);
            }

            inline void Program::use3F(Core::String const& location, GLfloat v0, GLfloat v1, GLfloat v2) const {
                glUniform3f(uniforms.getLocation(location), v0, v1, v2);
            }

            inline void Program::use4F(Core::String const& location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
                glUniform4f(uniforms.getLocation(location), v0, v1, v2, v3);
            }

            inline void Program::use1UI(Core::String const& location, GLuint v0) const {
                glUniform1ui(uniforms.getLocation(location), v0);
            }

            inline void Program::use2UI(Core::String const& location, GLuint v0, GLuint v1) const {
                glUniform2ui(uniforms.getLocation(location), v0, v1);
            }

            inline void Program::use3UI(Core::String const& location, GLuint v0, GLuint v1, GLuint v2) const {
                glUniform3ui(uniforms.getLocation(location), v0, v1, v2);
            }

            inline void Program::use4UI(Core::String const& location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const {
                glUniform4ui(uniforms.getLocation(location), v0, v1, v2, v3);
            }

            inline void Program::useMat3(Core::String const& location, GLsizei count, const Math::Matrix3x3<float>* const value) const {
                glUniformMatrix3fv(uniforms.getLocation(location), count, GL_TRUE, value->value());
            }


            inline void Program::useMat4(Core::String const& location, GLsizei count, const Math::Matrix4x4<float>* const value) const {
                glUniformMatrix4fv(uniforms.getLocation(location), count, GL_TRUE, value->value());
            }
            
            inline void Program::use1IV(Core::String const& location, GLsizei count, const GLint* const value) const {
                glUniform1iv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use2IV(Core::String const& location, GLsizei count, const GLint* const value) const {
                glUniform2iv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use3IV(Core::String const& location, GLsizei count, const GLint* const value) const {
                glUniform3iv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use4IV(Core::String const& location, GLsizei count, const GLint* const value) const {
                glUniform4iv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use1FV(Core::String const& location, GLsizei count, const GLfloat* const value) const {
                glUniform1fv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use2FV(Core::String const& location, GLsizei count, const GLfloat* const value) const {
                glUniform2fv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use3FV(Core::String const& location, GLsizei count, const GLfloat* const value) const {
                glUniform3fv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use4FV(Core::String const& location, GLsizei count, const GLfloat* const value) const {
                glUniform4fv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use1UIV(Core::String const& location, GLsizei count, const GLuint* const value) const {
                glUniform1uiv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use2UIV(Core::String const& location, GLsizei count, const GLuint* const value) const {
                glUniform2uiv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use3UIV(Core::String const& location, GLsizei count, const GLuint* const value) const {
                glUniform3uiv(uniforms.getLocation(location), count, value);
            }

            inline void Program::use4UIV(Core::String const& location, GLsizei count, const GLuint* const value) const {
                glUniform4uiv(uniforms.getLocation(location), count, value);
            }

            inline Program& Program::operator=(Program && p) {
                if (this != &p) {
                    id = p.id;
                    p.id = 0;
                    uniforms = std::move(p.uniforms);
                    stages = std::move(p.stages);
                }
                return *this;
            }
        }
    }
