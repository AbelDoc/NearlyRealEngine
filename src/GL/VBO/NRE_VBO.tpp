
    /**
     * @file NRE_VBO.tpp
     * @brief Implementation of Engine's GL's Object : VBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            template <class Layout>
            inline VBO<Layout>::VBO(StreamUsage stream) : AbstractVBO(stream) {
            }

            template <class Layout>
            inline VBO<Layout>::VBO(VBO && b) : AbstractVBO(std::move(b)), datas(std::move(b.datas)) {
            }
    
            template <class Layout>
            inline typename VBO<Layout>::Iterator VBO<Layout>::begin() {
                return datas.begin();
            }
    
            template <class Layout>
            inline typename VBO<Layout>::ConstIterator VBO<Layout>::begin() const {
                return datas.begin();
            }
    
            template <class Layout>
            inline typename VBO<Layout>::ConstIterator VBO<Layout>::cbegin() const {
                return datas.cbegin();
            }
    
            template <class Layout>
            inline typename VBO<Layout>::Iterator VBO<Layout>::end() {
                return datas.end();
            }
    
            template <class Layout>
            inline typename VBO<Layout>::ConstIterator VBO<Layout>::end() const {
                return datas.end();
            }
    
            template <class Layout>
            inline typename VBO<Layout>::ConstIterator VBO<Layout>::cend() const {
                return datas.cend();
            }

            template <class Layout>
            inline std::size_t VBO<Layout>::getDataCount() const {
                return datas.getSize();
            }

            template <class Layout>
            inline Layout& VBO<Layout>::getData(std::size_t index) {
                return datas[index];
            }

            template <class Layout>
            inline void VBO<Layout>::access() const {
                getAttributeBuffer().bind();
                    Layout::access();
                getAttributeBuffer().unbind();
            }

            template <class Layout>
            template <class ... Args>
            inline std::size_t VBO<Layout>::addData(Args && ... args) {
                datas.emplaceBack(std::forward<Args>(args)...);
                return datas.getSize() - 1;
            }

            template <class Layout>
            inline void VBO<Layout>::clear() {
                Utility::Vector<Layout>().swap(datas);
            }

            template <class Layout>
            inline void VBO<Layout>::reserve(std::size_t capacity) {
                datas.reserve(capacity);
            }
    
            template <class Layout>
            inline void VBO<Layout>::resize(std::size_t capacity) {
                datas.resize(capacity);
            }

            template <class Layout>
            inline Utility::String VBO<Layout>::toString() const {
                Utility::String res;
                res.reserve(5 * datas.getSize());
                res << "[";
                if (datas.getSize() > 0) {
                    for (unsigned int i = 0; i < datas.getSize(); i++) {
                        res << datas[i] << "\n";
                    }
                    res << datas[datas.getSize() - 1];
                }
                res << "]";
                return res;
            }

            template <class Layout>
            inline VBO<Layout>& VBO<Layout>::operator =(VBO<Layout> && b) {
                if (this != &b) {
                    AbstractVBO::operator=(std::move(b));
                    datas = std::move(b.datas);
                }
                return *this;
            }

            template <class Layout>
            inline std::size_t VBO<Layout>::getLayoutSize() const {
                return sizeof(Layout);
            }

            template <class Layout>
            inline const void* VBO<Layout>::getDataPointer() const {
                return &datas[0];
            }

        }
    }
