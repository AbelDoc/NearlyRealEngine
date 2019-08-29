
    /**
     * @file NRE_RenderBuffer.tpp
     * @brief Implementation of Engine's GL's Object : RenderBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline RenderBuffer::RenderBuffer(RenderInternalFormat internalFormat, GLsizei w, GLsizei h) {
                createId();
                allocate(internalFormat, w, h);
            }

            inline void RenderBuffer::bind() const {
                bindRenderBuffer(GL_RENDERBUFFER, getId());
            }

            inline void RenderBuffer::unbind() const {
                bindRenderBuffer(GL_RENDERBUFFER, 0);
            }

            inline void RenderBuffer::createId() {
                if (exist()) {
                    deleteId();
                }
                id = generateRenderBuffer();
            }

            inline void RenderBuffer::deleteId() {
                deleteRenderBuffer(id);
                id = 0;
            }

            inline bool RenderBuffer::exist() const {
                return isRenderBuffer(id);
            }

            inline void RenderBuffer::allocate(RenderInternalFormat internalFormat, GLsizei w, GLsizei h) const {
                bind();
                    allocateRenderBuffer(GL_RENDERBUFFER, internalFormat, w, h);
                unbind();
            }

            inline void RenderBuffer::attach(AttachPoint target) const {
                attachRenderBuffer(GL_FRAMEBUFFER, target, GL_RENDERBUFFER, getId());
            }

            inline Utility::String RenderBuffer::toString() const {
                Utility::String res;
                res << id;
                return res;
            }

        }
    }
