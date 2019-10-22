
    /**
     * @file NRE_TextureBuffer.tpp
     * @brief Implementation of Engine's GL's Object : TextureBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline TextureBuffer::TextureBuffer() : type(GL_UNSIGNED_BYTE) {
            }

            inline TextureBuffer::TextureBuffer(TextureType t) : type(t) {
            }

            inline TextureType TextureBuffer::getType() const {
                return type;
            }

            inline void TextureBuffer::bind() const {
                GL::bindTexture(getTarget(), getId());
            }

            inline void TextureBuffer::unbind() const {
                GL::bindTexture(getTarget(), 0);
            }

            inline void TextureBuffer::createId() {
                id = GL::generateTexture();
            }

            inline void TextureBuffer::deleteId() {
                GL::deleteTexture(id);
            }

            inline bool TextureBuffer::exist() const {
                return GL::isTexture(id);
            }

            inline Utility::String TextureBuffer::toString() const {
                Utility::String res;
                res << id;
                res << " - ";
                res << type;
                return res;
            }
        }
    }
