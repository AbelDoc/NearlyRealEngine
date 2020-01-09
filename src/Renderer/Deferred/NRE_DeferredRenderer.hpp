
    /**
     * @file NRE_DeferredRenderer.hpp
     * @brief Declaration of Engine's Renderer's Object : DeferredRenderer
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once
    
     #include "../../Header/NRE_Buffer.hpp"
     #include "../../Header/NRE_Utility.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Renderer
         * @brief Engine's Renderer module
         */
        namespace Renderer {

            /**
             * @class DeferredRenderer
             * @brief Manage the deferred rendering to a gBuffer
             */
            class DeferredRenderer : public Utility::Bindable<DeferredRenderer>, public Utility::Uncopyable<DeferredRenderer>, public Utility::Stringable<DeferredRenderer> {
                private:    //Fields
                    GL::FBO gBuffer;        /**< The gBuffer framebuffer */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        DeferredRenderer() = delete;
                        /**
                         * Construct the deferred renderer from the screen size
                         * @param screen the screen size
                         */
                        DeferredRenderer(Math::Vector2D<unsigned int> const& screen);

                    //## Move-Constructor ##//
                        /**
                         * Move r into this
                         * @param r the deferred renderer to move
                         */
                        DeferredRenderer(DeferredRenderer && r) = default;

                    //## Deconstructor ##//
                        /**
                         * DeferredRenderer Deconstructor
                         */
                        ~DeferredRenderer() = default;

                    //## Getter ##//
                        /**
                         * @return the renderer size getter
                         */
                        Math::Vector2D<GLuint> const& getSize() const;
                        /**
                         * GBuffer's colorbuffer getter
                         * @param  index the buffer's index
                         * @return       the corresponding colorbuffer
                         */
                        std::unique_ptr<GL::Attachable> const& getColorBuffer(GLuint index) const;
                        /**
                         * @return the gBuffer's depthbuffer
                         */
                        std::unique_ptr<GL::Attachable> const& getDepthBuffer() const;

                    //## Methods ##//
                        /**
                         * Bind the object
                         */
                        void bind() const;
                        /**
                         * Unbind the object
                         */
                        void unbind() const;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of r into this
                         * @param r the deferred renderer to move into this
                         * @return      the reference of himself
                         */
                        DeferredRenderer& operator =(DeferredRenderer && r) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the deferred renderer into a string
                         * @return the converted deferred renderer
                         */
                        Utility::String toString() const;
            };
        }
    }
    
    #include "NRE_DeferredRenderer.tpp"