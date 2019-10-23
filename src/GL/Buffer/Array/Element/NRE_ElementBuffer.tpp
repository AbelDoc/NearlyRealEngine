
    /**
     * @file NRE_ElementBuffer.tpp
     * @brief Implementation of Engine's GL's Object : ElementBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline BufferTarget ElementBuffer::getTarget() const {
                return GL_ELEMENT_ARRAY_BUFFER;
            }

        }
    }
