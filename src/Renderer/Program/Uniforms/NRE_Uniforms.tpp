
    /**
     * @file NRE_Uniforms.tpp
     * @brief Implementation of Engine's Renderer's Object : Uniforms
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline GLint Uniforms::getLocation(Core::String const& name) const {
                return uniforms.get(name);
            }

            inline void Uniforms::addLocation(Id id, Core::String const& name) {
                uniforms.emplace(name, GL::getUniformLocation(id, name));
            }

            inline Core::String Uniforms::toString() const {
                Core::String r;
                r.reserve(15 * uniforms.getSize());
                for (auto& it : uniforms) {
                    r << "(";
                    r << it.first;
                    r << ", ";
                    r << it.second;
                    r << ")\n";
                }
                return r;
            }
        }
    }
