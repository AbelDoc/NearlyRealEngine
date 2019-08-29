
    /**
     * @file NRE_Texture2DArray.hpp
     * @brief Declaration of Engine's GL's Object : Texture2DArray
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../../Buffer/Attachable/Texture/3D/NRE_Texture3DBuffer.hpp"
    #include "../Texture2D/NRE_Texture2D.hpp"

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
             * @class Texture2DArray
             * @brief Manage the link between a texture 3D buffer and a texture 2D array
             */
            class Texture2DArray : public Texture3DBuffer {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Texture2DArray() = default;

                    //## Move-Constructor ##//
                        /**
                         * Move t into this
                         * @param t the texture 2D array to move
                         */
                        Texture2DArray(Texture2DArray && t) = default;

                    //## Deconstructor ##//
                        /**
                         * Texture2DArray Deconstructor
                         */
                        ~Texture2DArray() = default;

                    //## Getter ##//
                        /**
                         * @return the texture buffer's target
                         */
                        BufferTarget getTarget() const override;

                    //## Methods ##//
                        /**
                         * Allocate the texture array storage
                         * @param z       the number of layer
                         * @param surface the surface to copy the format
                         */
                        void allocate(GLsizei z, Surface const& surface);
                        /**
                         * Send a texture into the array storage
                         * @param surface the surface to send
                         * @param layer   the surface's layer
                         */
                        void sendTexture(Surface& surface, GLint layer);
                        /**
                         * Attach the object to a defined point
                         * @param target the attachment point
                         */
                        void attach(AttachPoint target) const override;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of t into this
                         * @param t the texture 2D array to move into this
                         * @return  the reference of himself
                         */
                        Texture2DArray& operator =(Texture2DArray && t) = default;

            };
        }
    }

    #include "NRE_Texture2DArray.tpp"
