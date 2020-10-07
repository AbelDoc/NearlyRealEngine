
    /**
     * @file NRE_FBO.hpp
     * @brief Implementation of Engine's GL's Object : FBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline FBO::FBO(Math::Vector2D<GLuint> const& s) : size(s), depthBuffer(nullptr) {
            }

            inline FBO::FBO(FBO && b) : FrameBuffer(std::move(b)), size(std::move(b.size)), colorBuffers(std::move(b.colorBuffers)), depthBuffer(std::move(b.depthBuffer)) {
            }

            inline std::unique_ptr<Attachable> const& FBO::getColorBuffer(GLuint index) const {
                return colorBuffers[index];
            }

            inline Attachable* FBO::getDepthBuffer() {
                return depthBuffer.get();
            }

            inline std::unique_ptr<Attachable> const& FBO::getDepthBuffer() const {
                return depthBuffer;
            }

            inline Math::Vector2D<GLuint> const& FBO::getSize() const {
                return size;
            }

            inline void FBO::checkIntegrity() {
                bind();
                    FrameBufferStatus status = getFrameBufferStatus(GL_FRAMEBUFFER);
                    if (status != GL_FRAMEBUFFER_COMPLETE) {
                        Core::String error;
                        error << status;
                        throw (Exception::GLException("FBO Integrity Error : " + error));
                    }
                unbind();
            }

            inline void FBO::setEmptyDraw() {
                bind();
                    drawBuffer(GL_NONE);
                    readBuffer(GL_NONE);
                unbind();
            }

            inline Core::String FBO::toString() const {
                Core::String res;
                res.reserve(40 + colorBuffers.getSize() * 5);
                res << FrameBuffer::toString() << " :\n";
                res << "Color Buffer : " << static_cast <unsigned int> (colorBuffers.getSize()) << "\n";
                for (auto const& b : colorBuffers) {
                    res << *b << "\n";
                }
                res << "Depth Buffer : " << *depthBuffer << "\n";
                return res;
            }

            inline FBO& FBO::operator =(FBO && b) {
                if (this != &b) {
                    FrameBuffer::operator =(std::move(b));
                    size = std::move(b.size);
                    colorBuffers = std::move(b.colorBuffers);
                    depthBuffer = std::move(b.depthBuffer);
                }
                return *this;
            }
        }
    }
