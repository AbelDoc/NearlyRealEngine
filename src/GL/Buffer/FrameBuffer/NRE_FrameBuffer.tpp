
    /**
     * @file NRE_FrameBuffer.tpp
     * @brief Implementation of Engine's GL's Object : FrameBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline void FrameBuffer::bind() const {
                bindFrameBuffer(GL_FRAMEBUFFER, getId());
            }

            inline void FrameBuffer::unbind() const {
                bindFrameBuffer(GL_FRAMEBUFFER, 0);
            }

            inline void FrameBuffer::createIdImpl() {
                id = generateFrameBuffer();
            }

            inline void FrameBuffer::deleteIdImpl() {
                deleteFrameBuffer(id);
            }

            inline bool FrameBuffer::existImpl() const {
                return isFrameBuffer(id);
            }

            inline void FrameBuffer::attach(AttachPoint attachment, const Attachable* target) const {
                bind();
                    target->attach(attachment);
                unbind();
            }

            inline Utility::String FrameBuffer::toString() const {
                Utility::String res;
                res << id;
                return res;
            }
        }
    }
