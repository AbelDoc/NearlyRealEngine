
    /**
     * @file NRE_AttributeBuffer.tpp
     * @brief Implementation of Engine's GL's Object : AttributeBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            BufferTarget AttributeBuffer::getTarget() const {
                return GL_ARRAY_BUFFER;
            }

        }
    }
