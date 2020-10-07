
    /**
     * @file NRE_DeferredRenderer.hpp
     * @brief Implementation of Engine's Renderer's Object : DeferredRenderer
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {
    
            inline DeferredRenderer::DeferredRenderer(Math::Vector2D<unsigned int> const& screenSize) : gBuffer(screenSize) {
                gBuffer.createColorBuffer<GL::Texture2D>(4, GL::Surface(gBuffer.getSize(), GL_RGB, GL_RGB16F), GL_FLOAT, false);
                gBuffer.createDepthBuffer<GL::RenderBuffer>(GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT, screenSize.getW(), screenSize.getH());
            }

            inline Math::Vector2D<GLuint> const& DeferredRenderer::getSize() const {
                return gBuffer.getSize();
            }
    
            inline std::unique_ptr<GL::Attachable> const& DeferredRenderer::getColorBuffer(GLuint index) const {
                return gBuffer.getColorBuffer(index);
            }
    
            inline std::unique_ptr<GL::Attachable> const& DeferredRenderer::getDepthBuffer() const {
                return gBuffer.getDepthBuffer();
            }
    
            inline void DeferredRenderer::bind() const {
                gBuffer.bind();
            }
    
            inline void DeferredRenderer::unbind() const {
                gBuffer.unbind();
            }
    
            inline Core::String DeferredRenderer::toString() const {
                return gBuffer.toString();
            }

        }
    }
