
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

            inline void TextureBuffer::createIdImpl() {
                id = GL::generateTexture();
            }

            inline void TextureBuffer::deleteIdImpl() {
                GL::deleteTexture(id);
            }

            inline bool TextureBuffer::existImpl() const {
                return GL::isTexture(id);
            }

            inline Core::String TextureBuffer::toString() const {
                Core::String res;
                res << id;
                res << " - ";
                res << type;
                return res;
            }
        }
    }
