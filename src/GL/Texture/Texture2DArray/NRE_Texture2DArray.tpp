
    /**
     * @file NRE_Texture2DArray.tpp
     * @brief Implementation of Engine's GL's Object : Texture2DArray
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline BufferTarget Texture2DArray::getTarget() const {
                return GL_TEXTURE_2D_ARRAY;
            }
    
            inline void Texture2DArray::allocate(GLsizei z, Surface const& surface) {
                Texture3DBuffer::allocate(0, z, surface);
            }
    
            inline void Texture2DArray::sendTexture(Surface& surface, GLint layer) {
                Texture3DBuffer::update(0, 1, Math::Vector3D<GLint>(0, 0, layer), surface);
            }
    
            inline void Texture2DArray::attach(AttachPoint target) const {
                attachTextureLayer(GL_FRAMEBUFFER, target, getId(), 0, 0);
            }

        }
    }
