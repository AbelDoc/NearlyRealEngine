
    /**
     * @file NRE_Texture2DBuffer.hpp
     * @brief Declaration of Engine's GL's Object : Texture2DBuffer
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../NRE_TextureBuffer.hpp"
    #include "../../../../Texture/Surface/NRE_Surface.hpp"

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
             * @class Texture2DBuffer
             * @brief Manage operation on a texture 2D buffer, used with advanced object
             */
            class Texture2DBuffer : public TextureBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Texture2DBuffer() = default;
                        /**
                         * Construct a Texture buffer with his given data type
                         * @param t the texture's data type
                         */
                        Texture2DBuffer(TextureType t);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the texture 2D buffer to move
                         */
                        Texture2DBuffer(Texture2DBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * Texture2DBuffer Deconstructor
                         */
                        ~Texture2DBuffer() = default;

                    //## Getter ##//
                        /**
                         * @return the texture buffer's target
                         */
                        BufferTarget getTarget() const override;

                    //## Methods ##//
                        /**
                         * Allocate the texture buffer in memory from a surface
                         * @param level   the mipmap's level
                         * @param surface the surface to copy the format
                         */
                        void allocate(GLint level, Surface const& surface);
                        /**
                         * Update the texture buffer with a surface
                         * @param level   the mipmap's level
                         * @param offset  the data's offset
                         * @param surface the surface to move data
                         */
                        void update(GLint level, Math::Vector2D<GLint> const& offset, Surface& surface);
                        /**
                         * Update the texture buffer from an external data's source
                         * @param level   the mipmap's level
                         * @param offset  the data's offset
                         * @param surface the surface to copy the format
                         * @param data    the external data's source
                         */
                        void update(GLint level, Math::Vector2D<GLint> const& offset, Surface const& surface, const void* data);
                        /**
                         * Allocate and fill the texture buffer in memory from a surface
                         * @param level   the mipmap's level
                         * @param surface the surface to copy the format and move data
                         */
                        void allocateAndFill(GLint level, Surface& surface);
                        /**
                         * Apply OpenGL filter on the texture
                         */
                        void applyFilter();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the texture 2D buffer to move into this
                         * @return      the reference of himself
                         */
                        Texture2DBuffer& operator =(Texture2DBuffer && b) = default;

            };
        }
    }

    #include "NRE_Texture2DBuffer.tpp"
