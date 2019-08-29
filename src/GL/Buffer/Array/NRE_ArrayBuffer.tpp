
    /**
     * @file NRE_ArrayBuffer.tpp
     * @brief Implementation of Engine's GL's Object : ArrayBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline ArrayBuffer::ArrayBuffer() : id(0), allocated(false) {
                createId();
            }

            inline ArrayBuffer::ArrayBuffer(ArrayBuffer && b) : id(b.id), allocated(b.allocated) {
                b.id = 0;
                b.allocated = false;
            }

            inline ArrayBuffer::~ArrayBuffer() {
                deallocate();
            }

            inline bool ArrayBuffer::isAllocated() const {
                return allocated;
            }

            inline Id ArrayBuffer::getId() const {
                return id;
            }

            inline void ArrayBuffer::bind() const {
                bindBuffer(getTarget(), getId());
            }

            inline void ArrayBuffer::unbind() const {
                bindBuffer(getTarget(), 0);
            }

            inline void ArrayBuffer::createId() {
                if (exist()) {
                    deleteId();
                }
                id = generateBuffer();
            }

            inline void ArrayBuffer::deleteId() {
                deleteBuffer(id);
                id = 0;
            }

            inline bool ArrayBuffer::exist() const {
                return isBuffer(id);
            }

            inline void ArrayBuffer::allocate() {
                if (isAllocated()) {
                    deallocate();
                    createId();
                }
                allocated = true;
            }

            inline void ArrayBuffer::deallocate() {
                deleteId();
                allocated = false;
            }

            inline void ArrayBuffer::allocate(std::size_t size, StreamUsage usage) {
                allocate();
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
                allocate();
                bind();
                    sendData(getTarget(), size, data, usage);
                unbind();
            }

            inline void ArrayBuffer::orphan(std::size_t size, StreamUsage usage) {
                bind();
                    sendData(getTarget(), size, nullptr, usage);
                unbind();
            }

            inline ArrayBuffer& ArrayBuffer::operator =(ArrayBuffer && b) {
                if (this != &b) {
                    id = b.id;
                    b.id = 0;
                    allocated = b.allocated;
                    b.allocated = false;
                }
                return *this;
            }

        }
    }
