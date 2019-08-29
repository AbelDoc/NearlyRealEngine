
    /**
     * @file NRE_FBO.hpp
     * @brief Declaration of Engine's GL's Object : FBO
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <memory>

    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Utility.hpp>

    #include "../Buffer/FrameBuffer/NRE_FrameBuffer.hpp"
    #include "../Texture/Texture2D/NRE_Texture2D.hpp"

    #include "../../Header/NRE_Exception.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace GL
         * @brief Engine's GL module
         */
        namespace GL {

            /**
             * @class FBO
             * @brief Manage frame buffer storing and managing
             */
            class FBO : public FrameBuffer {
                private:    //Fields
                    Math::Vector2D<GLuint> size;                                /**< The frame buffer's size */
                    Utility::Vector<std::unique_ptr<Attachable>> colorBuffers;  /**< The frame buffer's color buffers */
                    std::unique_ptr<Attachable> depthBuffer;                    /**< The frame buffer's render buffer */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        FBO() = delete;
                        /**
                         * Construct a frame buffer from his size
                         * @param s the frame buffer's size
                         */
                        FBO(Math::Vector2D<GLuint> const& s);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the fbo to move
                         */
                        FBO(FBO && b);

                    //## Deconstructor ##//
                        /**
                         * FBO Deconstructor
                         */
                        ~FBO() = default;

                    //## Getter ##//
                        /**
                         * Color buffer getter
                         * @param  index the buffer's index
                         * @return       the corresponding color buffer
                         */
                        std::unique_ptr<Attachable> const& getColorBuffer(GLuint index) const;
                        /**
                         * Depth buffer getter
                         * @return the frame buffer's depth buffer
                         */
                        Attachable* getDepthBuffer();
                        /**
                         * Depth buffer getter
                         * @return the frame buffer's depth buffer
                         */
                        std::unique_ptr<Attachable> const& getDepthBuffer() const;
                        /**
                         * Size getter
                         * @return the frame buffer's size
                         */
                        Math::Vector2D<GLuint> const& getSize() const;

                    //## Methods ##//
                        /**
                         * Check the frame buffer's integrity
                         */
                        void checkIntegrity();
                        /**
                         * Create a depth buffer and attach it to the frame buffer
                         * @param target the depth buffer's attachment point
                         * @param args   the depth buffer's construction arguments
                         */
                        template <class T, class ... Args>
                        void createDepthBuffer(AttachPoint target, Args && ... args) {
                            depthBuffer = std::move(std::unique_ptr<Attachable>(new T(std::forward<Args>(args)...)));
                            bind();
                                depthBuffer->attach(target);
                            unbind();
                        }
                        /**
                         * Create multiples color buffers and attach them to the frame buffer
                         * @param count the number of color buffer to create
                         * @param args  the color buffer's construction arguments
                         */
                        template <class T, class ... Args>
                        void createColorBuffer(GLuint count, Args && ... args) {
                            bind();
                                for (GLuint i = 0; i < count; i++) {
                                    std::unique_ptr<Attachable> ptr(new T(std::forward<Args>(args)...));
                                    ptr->attach(GL_COLOR_ATTACHMENT0 + i);
                                    colorBuffers.pushBack(std::move(ptr));
                                }
                            unbind();
                        }
                        /**
                         * Set the frame buffer target to draw nothing beside into the depth buffer
                         */
                        void setEmptyDraw();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the fbo to move into this
                         * @return  the reference of himself
                         */
                        FBO& operator =(FBO && b);

                    //## Stream Operator ##//
                        /**
                         * Convert the fbo into a string
                         * @return the converted fbo
                         */
                        Utility::String toString() const;

            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, FBO const& o);
        }
    }

    #include "NRE_FBO.tpp"
