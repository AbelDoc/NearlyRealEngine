
    /**
     * @file NRE_Texture2DBuffer.tpp
     * @brief Implementation of Engine's GL's Object : Texture2DBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {


            inline Texture2DBuffer::Texture2DBuffer(TextureType t) : TextureBuffer(t) {
            }

            inline BufferTarget Texture2DBuffer::getTarget() const {
                return GL_TEXTURE_2D;
            }

            inline void Texture2DBuffer::allocate(GLint level, Surface const& surface) {
                Utility::Allocable<Attachable>::allocate();
                bind();
                    send2DTextureData(getTarget(), level, surface.getInternalFormat(), surface.getSize(), 0, surface.getFormat(), getType(), nullptr);
                    applyFilter();
                unbind();
            }

            inline void Texture2DBuffer::update(GLint level, Math::Vector2D<GLint> const& offset, Surface& surface) {
                bind();
                    update2DTextureData(getTarget(), level, offset, surface.getSize(), surface.getFormat(), getType(), surface.getPixels());
                    surface.deallocateSurface();
                unbind();
            }

            inline void Texture2DBuffer::update(GLint level, Math::Vector2D<GLint> const& offset, Surface const& surface, const void* data) {
                bind();
                    update2DTextureData(getTarget(), level, offset, surface.getSize(), surface.getFormat(), getType(), data);
                unbind();
            }

            inline void Texture2DBuffer::allocateAndFill(GLint level, Surface& surface) {
                Utility::Allocable<Attachable>::allocate();
                bind();
                    send2DTextureData(getTarget(), level, surface.getInternalFormat(), surface.getSize(), 0, surface.getFormat(), getType(), surface.getPixels());
                    surface.deallocateSurface();
                    applyFilter();
                unbind();
            }

            inline void Texture2DBuffer::applyFilter() {
                setTextureParameter(getTarget(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                setTextureParameter(getTarget(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                setTextureParameter(getTarget(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                setTextureParameter(getTarget(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }

        }
    }
