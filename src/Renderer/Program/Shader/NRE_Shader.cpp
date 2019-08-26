
    /**
     * @file Shader/NRE_Shader.cpp
     * @brief Implementation of Engine's Renderer's Object : Shader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    #include "NRE_Shader.hpp"

    using namespace NRE::Utility;
    using namespace NRE::IO;
    using namespace NRE::Exception;
    using namespace NRE::GL;

    namespace NRE {
        namespace Renderer {

            File const Shader::BASE_PATH = "Shaders/";

            bool Shader::compile(Id program) {
                String line, sourceCode;
                bool state = true;
                unsigned int current = 0;

                state = state && readFile(line, sourceCode, main);
                while (state && current < includes.getSize()) {
                    state = state && readFile(line, sourceCode, includes[current++]);
                }

                if (state) {
                    replaceSource(id, sourceCode);
                    compileShader(getId());

                    if (getShaderInfo(id, GL_COMPILE_STATUS) != GL_TRUE) {
                        String error(getShaderLog(id));
                        deleteId();

                        throw (ShaderException(main.toString() + " or includes : " + error));
                    }
                    attachShader(program, getId());
                }
                return state;
            }
        }
    }
