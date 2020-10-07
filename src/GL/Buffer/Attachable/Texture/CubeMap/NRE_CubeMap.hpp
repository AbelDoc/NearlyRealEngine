
    /**
     * @file NRE_CubeMap.hpp
     * @brief Declaration of Engine's GL's Object : CubeMap
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
             * @class CubeMap
             * @brief Manage operation on a cube map buffer, used with advanced object
             */
            class CubeMap : public TextureBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        CubeMap();
                        /**
                         * Construct the cubemap from a base surface
                         * @param surface the base surface for all 6 layers
                         */
                        CubeMap(Surface const& surface);

                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the cube map to move
                         */
                        CubeMap(CubeMap && c) = default;

                    //## Deconstructor ##//
                        /**
                         * CubeMap Deconstructor
                         */
                        ~CubeMap() = default;

                    //## Getter ##//
                        /**
                         * @return the texture buffer's target
                         */
                        BufferTarget getTarget() const override;

                    //## Methods ##//
                        /**
                         * Allocate the cube map in memory from a surface parameters
                         * @param level   the mipmap's level
                         * @param surface the surface to copy the format
                         */
                        void allocate(GLint level, Surface const& surface);
                        /**
                         * Update the cube map with 6 surface
                         * @param level    the mipmap's level
                         * @param offsets  the data's offset
                         * @param surfaces the surface array to move data
                         */
                        void update(GLint level, Core::Vector<Math::Vector2D<GLint>> const& offsets, Core::Vector<Surface>& surfaces);
                        /**
                         * Update a cube map face
                         * @param level    the mipmap's level
                         * @param offset   the data's offset
                         * @param surface  the surface to copy the format
                         * @param target   the cube face target
                         */
                        void update(GLint level, Math::Vector2D<GLint> const& offset, Surface& surface, GLenum target);
                        /**
                         * Allocate and fill the cube map in memory from 6 surface
                         * @param level    the mipmap's level
                         * @param surfaces the surface array to move data
                         */
                        void allocateAndFill(GLint level, Core::Vector<Surface>& surfaces);
                        /**
                         * Attach the object to a defined point
                         * @param target the attachment point
                         */
                        void attach(AttachPoint target) const override;
                        /**
                         * Attach the object to a defined point
                         * @param target the attachment point
                         * @param face   the face to attach
                         * @param level  the mipmap's level
                         */
                        void attach(AttachPoint target, GLint face, GLint level = 0) const;
                        /**
                         * Apply OpenGL filter on the cube map faces
                         */
                        void applyFilter();

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of c into this
                         * @param c the cube map to move into this
                         * @return      the reference of himself
                         */
                        CubeMap& operator =(CubeMap && c) = default;
    
                    using TextureBuffer::allocate;
            };
        }
    }

    #include "NRE_CubeMap.tpp"
