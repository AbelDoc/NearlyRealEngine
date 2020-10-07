
    /**
     * @file NRE_CubeMap.tpp
     * @brief Implementation of Engine's GL's Object : CubeMap
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline CubeMap::CubeMap() : TextureBuffer(GL_FLOAT) {
            }

            inline CubeMap::CubeMap(Surface const& surface) : TextureBuffer(GL_FLOAT) {
                allocate(0, surface);
            }

            inline BufferTarget CubeMap::getTarget() const {
                return GL_TEXTURE_CUBE_MAP;
            }

            inline void CubeMap::allocate(GLint level, Surface const& surface) {
                allocate();
                bind();
                    for (unsigned int i = 0; i < Math::FACE_NUM; i++) {
                        send2DTextureData(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, surface.getInternalFormat(), surface.getSize(), 0, surface.getFormat(), getType(), nullptr);
                    }
                    applyFilter();
                unbind();
            }

            inline void CubeMap::update(GLint level, Core::Vector<Math::Vector2D<GLint>> const& offsets, Core::Vector<Surface>& surfaces) {
                bind();
                    for (unsigned int i = 0; i < Math::FACE_NUM; i++) {
                        update2DTextureData(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, offsets[i], surfaces[i].getSize(), surfaces[i].getFormat(), getType(), surfaces[i].getPixels());
                        surfaces[i].deallocateSurface();
                    }
                unbind();
            }

            inline void CubeMap::update(GLint level, Math::Vector2D<GLint> const& offset, Surface& surface, GLenum target) {
                bind();
                    update2DTextureData(target, level, offset, surface.getSize(), surface.getFormat(), getType(), surface.getPixels());
                    surface.deallocateSurface();
                unbind();
            }

            inline void CubeMap::allocateAndFill(GLint level, Core::Vector<Surface>& surfaces) {
                allocate();
                bind();
                    for (unsigned int i = 0; i < Math::FACE_NUM; i++) {
                        send2DTextureData(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, level, surfaces[i].getInternalFormat(), surfaces[i].getSize(), 0, surfaces[i].getFormat(), getType(), surfaces[i].getPixels());
                        surfaces[i].deallocateSurface();
                    }
                    applyFilter();
                unbind();
            }

            inline void CubeMap::attach(AttachPoint target) const {
                attach(target, 0);
            }

            inline void CubeMap::attach(AttachPoint target, GLint face, GLint level) const {
                attach2DTexture(GL_FRAMEBUFFER, target, GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, getId(), level);
            }

            inline void CubeMap::applyFilter() {
                setTextureParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                setTextureParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                setTextureParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                setTextureParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                setTextureParameter(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
            }

        }
    }
