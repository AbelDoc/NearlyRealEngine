
    /**
     * @file NRE_UniformBuffer.tpp
     * @brief Implementation of Engine's GL's Object : UniformBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline BufferTarget UniformBuffer::getTarget() const {
                return GL_UNIFORM_BUFFER;
            }

            inline void UniformBuffer::bindBase(int index) {
                bindBufferBase(getTarget(), index, getId());
            }

            inline void UniformBuffer::connect(Id program, int index, Core::String const& name) {
                GLuint blockIndex = getUniformBlockIndex(program, name);
                bind();
                    bindUniformBlock(program, blockIndex, index);
                unbind();
            }

        }
    }
