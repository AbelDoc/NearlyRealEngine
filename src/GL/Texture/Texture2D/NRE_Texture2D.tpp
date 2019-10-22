
    /**
     * @file NRE_Texture2D.tpp
     * @brief Implementation of Engine's GL's Object : Texture2D
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline Texture2D::Texture2D(IO::File const& file, bool allocate) : surface(file) {
                if (allocate) {
                    allocateAndFill();
                }
            }

            inline Texture2D::Texture2D(Surface && s, TextureType t, bool fill) : Texture2DBuffer(t), surface(std::move(s)) {
                if (fill) {
                    allocateAndFill();
                } else {
                    allocate();
                }
            }

            inline Texture2D::Texture2D(Texture2D && t) : Texture2DBuffer(std::move(t)), surface(std::move(t.surface)) {
            }

            inline void Texture2D::setPixels(unsigned char* px) {
                surface.setPixels(px);
            }

            inline void Texture2D::allocate() {
                Texture2DBuffer::allocate(0, surface);
            }

            inline void Texture2D::update(Math::Vector2D<GLint> const& offset) {
                Texture2DBuffer::update(0, offset, surface);
            }

            inline void Texture2D::update(Math::Vector2D<GLint> const& offset, const void* data) {
                Texture2DBuffer::update(0, offset, surface, data);
            }

            inline void Texture2D::allocateAndFill() {
                Texture2DBuffer::allocateAndFill(0, surface);
            }

            inline void Texture2D::attach(AttachPoint target) const {
                attach2DTexture(GL_FRAMEBUFFER, target, getTarget(), getId(), 0);
            }

            inline Utility::String Texture2D::toString() const {
                return Texture2DBuffer::toString();
            }

            inline Texture2D& Texture2D::operator =(Texture2D && t) {
                if (this != &t) {
                    Texture2DBuffer::operator =(std::move(t));
                    surface = std::move(t.surface);
                }
                return *this;
            }
        }
    }
