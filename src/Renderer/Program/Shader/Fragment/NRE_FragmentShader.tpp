
    /**
     * @file NRE_FragmentShader.tpp
     * @brief Implementation of Engine's Renderer's Object : FragmentShader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline FragmentShader::FragmentShader(IO::File const& m) : Shader(m) {
                createId();
            }

            inline FragmentShader::FragmentShader(IO::File const& m, Utility::Vector<IO::File> && inc) : Shader(m, std::move(inc)) {
                createId();
            }

            inline GL::ShaderType FragmentShader::getType() const {
                return GL_FRAGMENT_SHADER;
            }
        }
    }
