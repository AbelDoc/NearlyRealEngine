
    /**
     * @file NRE_Uniforms.hpp
     * @brief Declaration of Engine's Renderer's Object : Uniforms
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include <Header/NRE_Core.hpp>
     #include "../../../Header/NRE_GL.hpp"

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
             * @class Uniforms
             * @brief Manage a collection of uniforms
             */
            class Uniforms : public Core::Stringable<Uniforms> {
                private:    //Fields
                    Core::UnorderedMap<Core::String, GLint> uniforms;  /**< Uniform's location associate with his name */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Uniforms() = default;

                    //## Copy-Constructor ##//
                        /**
                         * Copy u into this
                         * @param u the uniform collection to copy the content
                         */
                        Uniforms(Uniforms const& u) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move u into this, leaving u empty
                         * @param u the uniform collection to move
                         */
                        Uniforms(Uniforms && u) = default;

                    //## Deconstructor ##//
                        /**
                         * Uniforms Deconstructor
                         */
                        ~Uniforms() = default;

                    //## Getter ##//
                        /**
                         * Location getter
                         * @param  name the uniform's name
                         * @return      the uniform's location
                         */
                        GLint getLocation(Core::String const& name) const;

                    //## Methods ##//
                        /**
                         * Add a uniform's location associate with the given name
                         * @param id   the program's id
                         * @param name the uniform's name
                         */
                        void addLocation(Id id, Core::String const& name);

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of u into this
                         * @param u the uniform collection to copy into this
                         * @return      the reference of himself
                         */
                        Uniforms& operator =(Uniforms const& u) = default;
                        /**
                         * Move assignment of u into this, leaving u empty
                         * @param u the uniform collection to move into this
                         * @return      the reference of himself
                         */
                        Uniforms& operator =(Uniforms && u) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the uniform collection into a string
                         * @return the converted uniform collection
                         */
                        Core::String toString() const;

            };
        }
    }

    #include "NRE_Uniforms.tpp"
