
    /**
     * @file NRE_Texture3DBuffer.hpp
     * @brief Declaration of Engine's GL's Object : Texture3DBuffer
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
             * @class Texture3DBuffer
             * @brief Manage operation on a texture 3D buffer, used with advanced object
             */
            class Texture3DBuffer : public TextureBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Texture3DBuffer() = default;
                        /**
                         * Construct a Texture buffer with his given data type
                         * @param t the texture's data type
                         */
                        Texture3DBuffer(TextureType t);

                    //## Move-Constructor ##//
                        /**
                         * Move b into this
                         * @param b the texture 3D buffer to move
                         */
                        Texture3DBuffer(Texture3DBuffer && b) = default;

                    //## Deconstructor ##//
                        /**
                         * Texture3DBuffer Deconstructor
                         */
                        ~Texture3DBuffer() = default;

                    //## Methods ##//
                        /**
                         * Allocate the texture buffer in memory from a surface
                         * @param level   the mipmap's level
                         * @param z       the number of layer
                         * @param surface the surface to copy the format
                         */
                        void allocate(GLint level, GLsizei z, Surface const& surface);
                        /**
                         * Update the texture buffer with a surface
                         * @param level   the mipmap's level
                         * @param z       the updated layer
                         * @param offset  the data's offset
                         * @param surface the surface to copy the format
                         */
                        void update(GLint level, GLsizei z, Math::Vector3D<GLint> const& offset, Surface& surface);
                        /**
                         * Allocate and fill the texture buffer in memory from a surface
                         * @param level   the mipmap's level
                         * @param z       the number of layer
                         * @param surface the surface to copy the format and move data
                         */
                        void allocateAndFill(GLint level, GLsizei z, Surface& surface);
                        /**
                         * Apply OpenGL filter on the texture
                         */
                        void applyFilter();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of b into this
                         * @param b the texture 3D buffer to move into this
                         * @return      the reference of himself
                         */
                        Texture3DBuffer& operator =(Texture3DBuffer && b) = default;

            };
        }
    }

    #include "NRE_Texture3DBuffer.tpp"
