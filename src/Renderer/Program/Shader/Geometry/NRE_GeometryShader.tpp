
    /**
     * @file NRE_GeometryShader.tpp
     * @brief Implementation of Engine's Renderer's Object : GeometryShader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline GeometryShader::GeometryShader(IO::File const& m) : Shader(m) {
                createId();
            }

            inline GeometryShader::GeometryShader(IO::File const& m, Utility::Vector<IO::File> && inc) : Shader(m, std::move(inc)) {
                createId();
            }

            inline GL::ShaderType GeometryShader::getType() const {
                return GL_GEOMETRY_SHADER;
            }

        }
    }
