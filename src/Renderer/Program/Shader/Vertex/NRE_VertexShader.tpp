
    /**
     * @file NRE_VertexShader.tpp
     * @brief Implementation of Engine's Renderer's Object : VertexShader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline VertexShader::VertexShader(IO::File const& m) : Shader(m) {
                createId();
            }

            inline VertexShader::VertexShader(IO::File const& m, Utility::Vector<IO::File> && inc) : Shader(m, std::move(inc)) {
                createId();
            }

            inline GL::ShaderType VertexShader::getType() const {
                return GL_VERTEX_SHADER;
            }
        }
    }
