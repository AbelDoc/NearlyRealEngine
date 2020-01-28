
    /**
     * @file GL/NRE_GLUtils.tpp
     * @brief Implementation of NearlyRealEngine's GL Advanced Utilitary Functions
     * @author Louis ABEL
     * @date 27/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {
            
            inline void bindTexture(Attachable const& tex, int index) {
                setCurrentTexture(GL_TEXTURE0 + index);
                tex.bind();
            }
    
            inline void bindTexture(std::unique_ptr<Attachable> const& tex, int index) {
                bindTexture(*tex.get(), index);
            }
    
            inline void unbindTexture(Attachable const& tex, int index) {
                setCurrentTexture(GL_TEXTURE0 + index);
                tex.unbind();
            }
    
            inline void unbindTexture(std::unique_ptr<Attachable> const& tex, int index) {
                unbindTexture(*tex.get(), index);
            }

        }
    }
