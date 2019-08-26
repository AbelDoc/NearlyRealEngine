
    /**
     * @file Core/Primitive/2D/NRE_Primitive2D.hpp
     * @brief Declaration of Engine's Renderer's Object : Primitive2D
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../../../NRE_AbstractProgram.hpp"

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
             * @class Primitive2D
             * @brief Manage a 2D shader to draw simple 2D primitives
             */
            class Primitive2D : public AbstractProgram<Primitive2D> {
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Primitive2D() {
                            load();
                        }

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        void addStages() override {
                            addStage<VertexShader>("Primitive/Primitive2D.vert");
                            addStage<FragmentShader>("Primitive/Primitive2D.frag");
                        }
                        /**
                         * Add program's uniforms
                         */
                        void addUniforms() override {
                        }
            };
        }
    }
