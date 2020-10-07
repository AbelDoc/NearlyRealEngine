
    /**
     * @file NRE_Texture2D.hpp
     * @brief Declaration of Engine's GL's Object : Texture2D
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../../Buffer/Attachable/Texture/2D/NRE_Texture2DBuffer.hpp"

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
             * @class Texture2D
             * @brief Manage the link between a 2D buffer and a GL surface
             */
            class Texture2D : public Texture2DBuffer {
                private:    //Fields
                    Surface surface;  /**< The surface itself */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Texture2D() = delete;
                        /**
                         * Construct a texture from a file, and load it or not to the GPU
                         * @param file     the image file
                         * @param allocate tell if the surface is send to the GPU
                         */
                        Texture2D(IO::File const& file, bool allocate);
                        /**
                         * Construct a texture from a surface, and send it or not
                         * @param s    the surface to send
                         * @param t    the texture's type
                         * @param fill tell if the constructor fill on load or just allocate
                         */
                        Texture2D(Surface && s, GLenum t, bool fill);

                    //## Move-Constructor ##//
                        /**
                         * Move t into this
                         * @param t the 2D texture to move
                         */
                        Texture2D(Texture2D && t);

                    //## Deconstructor ##//
                        /**
                         * Texture2D Deconstructor
                         */
                        ~Texture2D() = default;

                    //## Setter ##//
                        /**
                         * Pixels setter
                         * @param px the new pixels pointer
                         */
                        void setPixels(unsigned char* px);

                    //## Methods ##//
                        /**
                         * Allocate the texture storage
                         */
                        void allocate();
                        /**
                         * Update data in the texture
                         * @param offset  the data's offset
                         */
                        void update(Math::Vector2D<GLint> const& offset);
                        /**
                         * Update data in the texture from an external source
                         * @param offset  the data's offset
                         * @param data    the external data's source
                         */
                        void update(Math::Vector2D<GLint> const& offset, const void* data);
                        /**
                         * Allocate and fill the texture storage
                         */
                        void allocateAndFill();
                        /**
                         * Attach the object to a defined point
                         * @param target the attachment point
                         */
                        void attach(AttachPoint target) const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of t into this
                         * @param t the 2D texture to move into this
                         * @return  the reference of himself
                         */
                        Texture2D& operator =(Texture2D && t);

                    //## Stream Operator ##//
                        /**
                         * Convert the 2D texture into a string
                         * @return the converted 2D texture
                         */
                        Core::String toString() const;

            };
        }
    }

    #include "NRE_Texture2D.tpp"
