
    /**
     * @file NRE_VAO.tpp
     * @brief Implementation of Engine's GL's Object : VAO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline void VAO::bind() const {
                bindVAO(getId());
            }

            inline void VAO::unbind() const {
                bindVAO(0);
            }

            inline void VAO::createIdImpl() {
                id = generateVAO();
            }

            inline void VAO::deleteIdImpl() {
                deleteVAO(id);
            }

            inline bool VAO::existImpl() const {
                return isVAO(id);
            }

            inline void VAO::access(const AbstractVBO* buffer) const {
                bind();
                    buffer->access();
                unbind();
            }

            inline Core::String VAO::toString() const {
                Core::String res;
                res << id;
                return res;
            }
        }
    }
