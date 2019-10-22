
    /**
     * @file NRE_AbstractVBO.tpp
     * @brief Implementation of Engine's GL's Object : AbstractVBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline AbstractVBO::AbstractVBO(StreamUsage stream) : count(0), size(0), usage(stream) {
            }

            inline AbstractVBO::AbstractVBO(AbstractVBO && b) : buffer(std::move(b.buffer)), count(b.count), size(b.size), usage(b.usage) {
                b.count = 0;
                b.size = 0;
            }

            inline void AbstractVBO::allocate(int nb) {
                count = nb;
                size = nb * getLayoutSize();
                buffer.allocate(size, usage);
            }

            inline void AbstractVBO::update(GLintptr offset) {
                buffer.update(offset, getDataSize(), getDataPointer());
                clear();
            }

            inline void AbstractVBO::update(const void* data, std::size_t nb, GLintptr offset) {
                assert(data != 0);
                buffer.update(offset, nb * getLayoutSize(), data);
            }

            inline void AbstractVBO::allocateAndFill() {
                count = static_cast <GLsizei> (getDataCount());
                size = getDataSize();
                buffer.allocateAndFill(size, getDataPointer(), usage);
                clear();
            }

            inline void AbstractVBO::orphan() {
                buffer.orphan(size, usage);
            }

            inline bool AbstractVBO::reallocate() {
                bool result = checkReallocation();
                allocateAndFill();
                return result;
            }

            inline bool AbstractVBO::checkReallocation() {
                bool result = false;
                if (getDataSize() > size) {
                    buffer.deleteId();
                    buffer.createId();
                    result = true;
                } else {
                    orphan();
                }
                buffer.deallocate();
                return result;
            }

            inline void AbstractVBO::draw(DrawMode mode) const {
                drawArrays(mode, 0, count);
            }

            inline void AbstractVBO::drawInstanced(int instance, DrawMode mode) const {
                drawArraysInstanced(mode, 0, count, instance);
            }

            inline void AbstractVBO::drawMulti(const int* firsts, const int* counts, int drawCount, DrawMode mode) const {
                drawMultiArrays(mode, firsts, counts, drawCount);
            }

            inline AbstractVBO& AbstractVBO::operator =(AbstractVBO && b) {
                if (this != &b) {
                    buffer = std::move(b.buffer);
                    count = b.count;
                    size = b.size;
                    usage = b.usage;
                    b.count = 0;
                    b.size = 0;
                }
                return *this;
            }

            inline StreamUsage AbstractVBO::getUsage() const {
                return usage;
            }

            inline AttributeBuffer const& AbstractVBO::getAttributeBuffer() const {
                return buffer;
            }

            inline std::size_t AbstractVBO::getDataSize() const {
                return getDataCount() * getLayoutSize();
            }

        }
    }
