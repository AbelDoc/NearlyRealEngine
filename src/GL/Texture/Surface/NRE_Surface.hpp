
    /**
     * @file NRE_Surface.hpp
     * @brief Declaration of Engine's GL's Object : Surface
     * @author Louis ABEL
     * @date 29/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <Header/NRE_IO.hpp>
    #include <Header/NRE_Utility.hpp>

    #include "../../../Header/NRE_GL.hpp"

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
             * @class Surface
             * @brief Manage a surface
             */
            class Surface {
                private:    //Fields
                    Math::Vector2D<GLsizei> size;           /**< The surface's size */
                    unsigned char* pixels;                  /**< The surface's pixels */
                    TextureFormat format;                   /**< The surface's pixel format */
                    TextureInternalFormat internalFormat;   /**< The surface's internal pixel format */
                    bool allocated;                         /**< Tell if the surface is allocated */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Surface();
                        /**
                         * Construct a surface from an image file
                         * @param file the image file
                         */
                        Surface(IO::File const& file);
                        /**
                         * Construct a surface from a size and formats
                         * @param s  the surface's size
                         * @param f  the surface's format
                         * @param iF the surface's internal format
                         */
                        Surface(Math::Vector2D<GLsizei> const& s, TextureFormat f, TextureInternalFormat iF);

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param s the surface object to copy
                         */
                        Surface(Surface const& s) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the surface to move
                         */
                        Surface(Surface && s);

                    //## Deconstructor ##//
                        /**
                         * Surface Deconstructor
                         */
                        ~Surface();

                    //## Getter ##//
                        /**
                         * @return if the surface is allocated
                         */
                        bool isAllocated() const;
                        /**
                         * @return the surface's size
                         */
                        Math::Vector2D<GLsizei> const& getSize() const;
                        /**
                         * @return the surface's format
                         */
                        TextureFormat getFormat() const;
                        /**
                         * @return the surface's internal format
                         */
                        TextureInternalFormat getInternalFormat() const;
                        /**
                         * @return the surface's pixels
                         */
                        const unsigned char* getPixels() const;

                    //## Setter ##//
                        /**
                         * @param s the new surface's size
                         */
                        void setSize(Math::Vector2D<GLsizei> const& s);
                        /**
                         * @param f the new surface's format
                         */
                        void setFormat(TextureFormat f);
                        /**
                         * @param f the new surface's internal format
                         */
                        void setInternalFormat(TextureInternalFormat f);
                        /**
                         * @param px the new pixels source
                         */
                        void setPixels(unsigned char* px);

                    //## Methods ##//
                        /**
                         * Allocate the object
                         */
                        void allocate();
                        /**
                         * Deallocate the object
                         */
                        void deallocate();
                        /**
                         * Deallocate the internal surface, keep surface parameter
                         */
                        void deallocateSurface();
                        /**
                         * Load the internal surface from a file
                         * @param file the surface to load
                         */
                        void load(IO::File const& file);
                        /**
                         * Update format and size from the internal surface
                         * @param file the surface to load
                         */
                        void update(IO::File const& file);

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param s the surface object to copy
                         * @return  the reference of himself
                         */
                        Surface& operator =(Surface const& s) = delete;
                        /**
                         * Move assignment of s into this
                         * @param s the surface to move into this
                         * @return  the reference of himself
                         */
                        Surface& operator =(Surface && s);

            };
        }
    }

    #include "NRE_Surface.tpp"
