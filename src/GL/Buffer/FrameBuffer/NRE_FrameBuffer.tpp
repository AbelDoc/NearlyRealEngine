
    /**
     * @file NRE_FrameBuffer.tpp
     * @brief Implementation of Engine's GL's Object : FrameBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline FrameBuffer::FrameBuffer() : id(0) {
                createId();
            }

            inline FrameBuffer::FrameBuffer(FrameBuffer && b) : id(b.id) {
                b.id = 0;
            }

            inline FrameBuffer::~FrameBuffer() {
                unbind();
                deleteId();
            }

            inline Id FrameBuffer::getId() const {
                return id;
            }

            inline void FrameBuffer::bind() const {
                bindFrameBuffer(GL_FRAMEBUFFER, getId());
            }

            inline void FrameBuffer::unbind() const {
                bindFrameBuffer(GL_FRAMEBUFFER, 0);
            }

            inline void FrameBuffer::createId() {
                if (exist()) {
                    unbind();
                    deleteId();
                }
                id = generateFrameBuffer();
            }

            inline void FrameBuffer::deleteId() {
                deleteFrameBuffer(id);
                id = 0;
            }

            inline bool FrameBuffer::exist() const {
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

            inline FrameBuffer& FrameBuffer::operator =(FrameBuffer && b) {
                if (this != &b) {
                    id = b.id;
                    b.id = 0;
                }
                return *this;
            }

            inline std::ostream& operator <<(std::ostream& stream, FrameBuffer const& o) {
                return stream << o.toString();
            }

        }
    }
