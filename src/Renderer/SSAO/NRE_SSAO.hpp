
    /**
     * @file NRE_SSAO.hpp
     * @brief Declaration of Engine's Renderer's Object : SSAO
     * @author Louis ABEL
     * @date 27/01/2020
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <sstream>
    #include <random>
    #include <memory>

    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Core.hpp>

    #include "../../GL/Texture/Texture2D/NRE_Texture2D.hpp"

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
             * @class SSAO
             * @brief Screen Space Ambient Occlusion kernel
             */
            class SSAO : public Core::Uncopyable<SSAO>, public Core::Stringable<SSAO> {
                private:    //Fields
                    Core::Vector<Math::Vector3D<float>> kernel;  /**< The ssao's kernel */
                    GL::Texture2D noise;                            /**< The ssao's noise */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        SSAO();

                    //## Move-Constructor ##//
                        /**
                         * Move s into this
                         * @param s the ssao to move
                         */
                        SSAO(SSAO && s) = default;

                    //## Deconstructor ##//
                        /**
                         * SSAO Deconstructor
                         */
                        ~SSAO() = default;

                    //## Getter ##//
                        /**
                         * @return the ssao's kernel
                         */
                        Core::Vector<Math::Vector3D<float>> const& getKernel() const;
                        /**
                         * @return the ssao's noise
                         */
                        GL::Texture2D const& getNoise() const;

                    //## Assignment Operator ##//
                        /**
                         * Move assignment of s into this,
                         * @param s the ssao to move into this
                         * @return  the reference of himself
                         */
                        SSAO& operator =(SSAO && s) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the ssao into a string
                         * @return the converted ssao
                         */
                        Core::String toString() const;

                private:   // Methods
                    /**
                     * Generate the ssao's kernel
                     */
                    void generateKernel();
                    /**
                     * Generate the ssao's noise
                     */
                    void generateNoise();

                private:    // Static
                    static std::size_t constexpr NOISE_SIZE = 4;     /**< The ssao's noise texture's size */

                public:     // Static
                    static std::size_t constexpr KERNEL_SIZE = 64;   /**< The ssao's kernel size */

            };
        }
    }
    
    #include "NRE_SSAO.tpp"
