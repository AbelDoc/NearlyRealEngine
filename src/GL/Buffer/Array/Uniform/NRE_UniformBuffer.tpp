
    /**
     * @file NRE_UniformBuffer.tpp
     * @brief Implementation of Engine's GL's Object : UniformBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            BufferTarget UniformBuffer::getTarget() const {
                return GL_UNIFORM_BUFFER;
            }

            void UniformBuffer::bindBase(int index) {
                bindBufferBase(getTarget(), index, getId());
            }

            void UniformBuffer::connect(Id program, int index, Utility::String const& name) {
                GLuint blockIndex = getUniformBlockIndex(program, name);
                bind();
                    bindUniformBlock(program, blockIndex, index);
                unbind();
            }

        }
    }
