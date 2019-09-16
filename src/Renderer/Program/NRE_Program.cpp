
    /**
     * @file NRE_Program.hpp
     * @brief Implementation of Engine's Renderer's Object : Program
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    #include "NRE_Program.hpp"

    using namespace NRE::Exception;
    using namespace NRE::Utility;
    using namespace NRE::GL;

    namespace NRE {
        namespace Renderer {

            Program::Category Program::counter = 0;

            void Program::load() {
                try {
                    addStages();
                } catch (ShaderException const& e) {
                    throw e;
                }

                bindAttributeLocation(id, 0, "in_Vertex");
                bindAttributeLocation(id, 1, "in_Color");
                bindAttributeLocation(id, 2, "in_Normal");
                bindAttributeLocation(id, 3, "in_UV");
                bindAttributeLocation(id, 4, "in_Material");
                bindAttributeLocation(id, 5, "in_Tangent");
                bindAttributeLocation(id, 6, "in_Particle");
                bindAttributeLocation(id, 7, "in_Matrix");

                linkProgram(id);

                if (getProgramInfo(id, GL_LINK_STATUS) != GL_TRUE) {
                    String error(getProgramLog(id));
                    deleteId();

                    throw (ShaderException("Linking Error : " + error));
                }
                addUniforms();
                detachShaders();
            }
        }
    }
