
    /**
     * @file NRE_Texture3DBuffer.tpp
     * @brief Implementation of Engine's GL's Object : Texture3DBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline Texture3DBuffer::Texture3DBuffer(TextureType t) : TextureBuffer(t) {
            }

            inline void Texture3DBuffer::allocate(GLint level, GLsizei z, Surface const& surface) {
                allocate();
                bind();
                    send3DTextureData(getTarget(), level, surface.getInternalFormat(), surface.getSize(), z, 0, surface.getFormat(), getType(), nullptr);
                    applyFilter();
                unbind();
            }

            inline void Texture3DBuffer::update(GLint level, GLsizei z, Math::Vector3D<GLint> const& offset, Surface& surface) {
                bind();
                    update3DTextureData(getTarget(), level, offset, surface.getSize(), z, surface.getFormat(), getType(), surface.getPixels());
                    surface.deallocateSurface();
                unbind();
            }

            inline void Texture3DBuffer::allocateAndFill(GLint level, GLsizei z, Surface& surface) {
                allocate();
                bind();
                    send3DTextureData(getTarget(), level, surface.getInternalFormat(), surface.getSize(), z, 0, surface.getFormat(), getType(), surface.getPixels());
                    surface.deallocateSurface();
                    applyFilter();
                unbind();
            }

            inline void Texture3DBuffer::applyFilter() {
                setTextureParameter(getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                setTextureParameter(getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                setTextureParameter(getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                setTextureParameter(getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }
        }
    }
