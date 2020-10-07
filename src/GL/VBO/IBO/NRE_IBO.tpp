
    /**
     * @file NRE_IBO.hpp
     * @brief Implementation of Engine's GL's Object : IBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            template <class Layout, class Index>
            inline IBO<Layout, Index>::IBO(StreamUsage stream) : VBO<Layout>(stream), indexCount(0), indexSize(0), indexCounter(0) {
                type = getIndexType();
            }

            template <class Layout, class Index>
            inline IBO<Layout, Index>::IBO(IBO && b) : VBO<Layout>(std::move(b)), element(std::move(b.element)), index(std::move(b.index)), indexCount(b.indexCount), indexSize(b.indexSize), indexCounter(b.indexCounter), type(b.type) {
                b.indexCount = 0;
                b.indexSize = 0;
                b.indexCounter = 0;
            }

            template <class Layout, class Index>
            inline Index IBO<Layout, Index>::getNextIndex() {
                return static_cast <Index> (indexCounter++);
            }

            template <class Layout, class Index>
            inline std::size_t IBO<Layout, Index>::getIndexCount() const {
                return index.getSize();
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::addIndex(Index idx) {
                index.emplaceBack(idx);
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::addIndex(Index* idxs, std::size_t nbIndex) {
                for (std::size_t i = 0; i < nbIndex; i++) {
                    index.emplaceBack(idxs[i]);
                }
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::allocate(std::size_t nb, std::size_t nbIndex) {
                VBO<Layout>::allocate(nb);
                indexCount = nbIndex;
                indexSize = indexCount * sizeof(Index);
                element.allocate(indexSize, this->getUsage());
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::updateIndex(GLintptr offset) {
                element.update(offset, getIndexSize(), getIndexPointer());
                clearIndex();
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::updateIndex(const void* data, std::size_t nb, GLintptr offset) {
                element.update(offset, nb * sizeof(Index), data);
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::allocateAndFill() {
                VBO<Layout>::allocateAndFill();
                allocateAndFillIndex();
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::clearIndex() {
                Core::Vector<Index>().swap(index);
                indexCounter = 0;
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::reserveIndex(std::size_t capacity) {
                index.reserve(capacity);
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::orphanIndex() {
                element.orphan(indexSize,  this->getUsage());
            }

            template <class Layout, class Index>
            inline bool IBO<Layout, Index>::checkReallocation() {
                bool result = VBO<Layout>::checkReallocation();
                if (getIndexSize() > indexSize) {
                    element.regenerateId();
                    result = true;
                } else {
                    orphanIndex();
                }
                static_cast <Core::Allocable<ArrayBuffer>&> (element).deallocate();
                return result;
            }
            
            template <class Layout, class Index>
            inline void IBO<Layout, Index>::deallocate() {
                AbstractVBO::deallocate();
                static_cast <Core::Allocable<ArrayBuffer>&> (element).deallocate();
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::access() const {
                VBO<Layout>::access();
                element.bind();
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::draw(GLenum mode) const {
                drawElements(mode, static_cast <GLsizei> (indexCount), getIndexType(), 0);
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::drawInstanced(int instance, GLenum mode) const {
                drawElementsInstanced(mode, static_cast <GLsizei> (indexCount), getIndexType(), 0, instance);
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::drawMulti(int* indexes, int** offset, int drawCount, GLenum mode) const {
                drawMultiElements(mode, indexes, getIndexType(), offset, drawCount);
            }

            template <class Layout, class Index>
            inline IBO<Layout, Index>& IBO<Layout, Index>::operator =(IBO<Layout, Index> && b) {
                if (this != &b) {
                    VBO<Layout>::operator =(std::move(b));
                    element = std::move(b.element);
                    index = std::move(b.index);
                    indexCount = b.indexCount;
                    indexSize = b.indexSize;
                    indexCounter = b.indexCounter;
                    type = b.type;
                    b.indexCount = 0;
                    b.indexSize = 0;
                    b.indexCounter = 0;
                }
                return *this;
            }

            template <class Layout, class Index>
            inline Core::String IBO<Layout, Index>::toString() const {
                Core::String internal, res;
                internal = std::move(VBO<Layout>::toString());
                res.reserve(20 + internal.getSize());
                res << "Index count : " << static_cast <GLsizei> (indexCount) << "\n";
                res << internal;
                return res;
            }

            template <class Layout, class Index>
            inline std::size_t IBO<Layout, Index>::getIndexSize() const {
                return getIndexCount() * sizeof(Index);
            }

            template <class Layout, class Index>
            inline const void* IBO<Layout, Index>::getIndexPointer() const {
                return &index[0];
            }

            template <class Layout, class Index>
            inline void IBO<Layout, Index>::allocateAndFillIndex() {
                indexCount = getIndexCount();
                indexSize = getIndexSize();
                element.allocateAndFill(indexSize, getIndexPointer(),  this->getUsage());
                clearIndex();
            }

            template <class Layout, class Index>
            inline IndexType IBO<Layout, Index>::getIndexType() const {
                if (sizeof(Index) == 1) {
                    return GL_UNSIGNED_BYTE;
                } else if (sizeof(Index) == 2) {
                    return GL_UNSIGNED_SHORT;
                } else {
                    return GL_UNSIGNED_INT;
                }
            }

        }
    }
