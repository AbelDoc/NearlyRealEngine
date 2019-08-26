
    /**
     * @file Shader/NRE_Shader.tpp
     * @brief Implementation of Engine's Renderer's Object : Shader
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {


            inline Shader::Shader(IO::File const& m) : main(m) {
            }

            inline Shader::Shader(IO::File const& m, Utility::Vector<IO::File> && inc) : main(m), includes(std::move(inc)) {
            }

            inline Shader::Shader(Shader && s) : id(s.id), main(std::move(s.main)), includes(std::move(s.includes)) {
                s.id = 0;
            }

            inline Shader::~Shader() {
                deleteId();
            }

            inline Id Shader::getId() const {
                return id;
            }

            inline void Shader::createId() {
                if (exist()) {
                    deleteId();
                }
                id = GL::createShader(getType());
            }

            inline void Shader::deleteId() {
                GL::deleteShader(getId());
                id = 0;
            }

            inline bool Shader::exist() const {
                return GL::isShader(id);
            }

            inline Shader& Shader::operator =(Shader && s) {
                if (this != &s) {
                    id = s.id;
                    s.id = 0;

                    main = std::move(s.main);
                    includes = std::move(s.includes);
                }
                return *this;
            }

            inline bool Shader::readFile(Utility::String& line, Utility::String& sourceCode, IO::File const& file) const {
                IO::InputFile shaderFile(BASE_PATH + file);
                shaderFile.open();
                if (shaderFile.isOpen()) {
                    while(shaderFile.readLine(line)) {
                        sourceCode += line;
                        sourceCode += '\n';
                    }
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
