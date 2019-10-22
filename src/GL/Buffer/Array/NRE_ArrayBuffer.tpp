
    /**
     * @file NRE_ArrayBuffer.tpp
     * @brief Implementation of Engine's GL's Object : ArrayBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline void ArrayBuffer::bind() const {
                bindBuffer(getTarget(), getId());
            }

            inline void ArrayBuffer::unbind() const {
                bindBuffer(getTarget(), 0);
            }

            inline void ArrayBuffer::createId() {
                id = generateBuffer();
            }

            inline void ArrayBuffer::deleteId() {
                deleteBuffer(id);
            }

            inline bool ArrayBuffer::exist() const {
                return isBuffer(id);
            }

            inline void ArrayBuffer::allocate() {
            }

            inline void ArrayBuffer::deallocate() {
            }

            inline void ArrayBuffer::allocate(std::size_t size, StreamUsage usage) {
                Utility::Allocable<ArrayBuffer>::allocate();
                bind();
                    sendData(getTarget(), size, nullptr, usage);
                unbind();
            }

            inline void ArrayBuffer::update(GLintptr offset, std::size_t size, const void* data) {
                bind();
                    updateData(getTarget(), offset, size, data);
                unbind();
            }

            inline void ArrayBuffer::allocateAndFill(std::size_t size, const void* data, StreamUsage usage) {
                Utility::Allocable<ArrayBuffer>::allocate();
                bind();
                    sendData(getTarget(), size, data, usage);
                unbind();
            }

            inline void ArrayBuffer::orphan(std::size_t size, StreamUsage usage) {
                bind();
                    sendData(getTarget(), size, nullptr, usage);
                unbind();
            }

        }
    }
