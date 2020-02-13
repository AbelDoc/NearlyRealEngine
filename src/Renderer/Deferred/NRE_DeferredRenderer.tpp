
    /**
     * @file NRE_DeferredRenderer.hpp
     * @brief Implementation of Engine's Renderer's Object : DeferredRenderer
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {
    
            inline DeferredRenderer::DeferredRenderer(Math::Vector2D<unsigned int> const& screenSize) : gBuffer(screenSize), shadowMap(Math::Vector2D<unsigned int>(512)) {
                gBuffer.createColorBuffer<GL::Texture2D>(3, GL::Surface(gBuffer.getSize(), GL_RGBA, GL_RGBA16F), GL_FLOAT, false);
                gBuffer.createDepthBuffer<GL::Texture2D>(GL_DEPTH_ATTACHMENT, GL::Surface(gBuffer.getSize(), GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT32F), GL_FLOAT, false);
                shadowMap.createDepthBuffer<GL::Texture2D>(GL_DEPTH_ATTACHMENT, GL::Surface(shadowMap.getSize(), GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT), GL_FLOAT, false);
                shadowMap.getDepthBuffer()->bind();
                    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
                    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
                shadowMap.getDepthBuffer()->unbind();
                shadowMap.setEmptyDraw();
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
    
            inline std::unique_ptr<GL::Attachable> const& DeferredRenderer::getShadowMap() const {
                return shadowMap.getDepthBuffer();
            }
    
            inline GL::FBO const& DeferredRenderer::getShadowBuffer() const {
                return shadowMap;
            }
    
            inline void DeferredRenderer::bind() const {
                gBuffer.bind();
            }
    
            inline void DeferredRenderer::unbind() const {
                gBuffer.unbind();
            }
    
            inline Utility::String DeferredRenderer::toString() const {
                return gBuffer.toString();
            }

        }
    }
