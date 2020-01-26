
    /**
     * @file NRE_SSAO.tpp
     * @brief Implementation of Engine's Renderer's Object : SSAO
     * @author Louis ABEL
     * @date 27/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline SSAO::SSAO() : noise(GL::Surface(Math::Vector2D<GLsizei>(NOISE_SIZE, NOISE_SIZE), GL_RGBA, GL_RGBA32F), GL_FLOAT, false) {
                kernel.reserve(KERNEL_SIZE);
                generateKernel();
                generateNoise();
            }
    
            inline Utility::Vector<Math::Vector3D<float>> const& SSAO::getKernel() const {
                return kernel;
            }
    
            inline GL::Texture2D const& SSAO::getNoise() const {
                return noise;
            }
    
            inline void SSAO::generateKernel() {
                std::uniform_real_distribution<float> rFloat(0, 1);
                std::default_random_engine generator;

                for (std::size_t i = 0 ; i < KERNEL_SIZE; i++) {
                    kernel.pushBack(Math::Vector3D<float>(
                        rFloat(generator) * 2.0f - 1.0f,
                        rFloat(generator) * 2.0f - 1.0f,
                        rFloat(generator)
                    ) * rFloat(generator));
                    kernel[i].normalize();
                    float scale = static_cast <float> (i) / static_cast <float> (KERNEL_SIZE);
                    scale = Math::lerp(0.1f, 1.0f, scale * scale);
                    kernel[i] = kernel[i] * scale;
                }
            }

            inline void SSAO::generateNoise() {
                std::uniform_real_distribution<float> rFloat(0, 1);
                std::default_random_engine generator;

                auto ssaoNoise = new Math::Vector3D<float>[KERNEL_SIZE];
                for (std::size_t i = 0; i < KERNEL_SIZE; i++) {
                    ssaoNoise[i].setCoord(
                        rFloat(generator) * 2 - 1,
                        rFloat(generator) * 2 - 1,
                        0
                    );
                    ssaoNoise[i].normalize();
                }

                noise.setPixels(reinterpret_cast <unsigned char*> (ssaoNoise));
                noise.update(Math::Vector2D<int>(0, 0));
                noise.bind();
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                noise.unbind();
            }
    
            inline Utility::String SSAO::toString() const {
                Utility::String res;
                res << "Noise : " << noise.toString() << "\n";
                res << "Kernel : [\n";
                for (std::size_t i = 0; i < KERNEL_SIZE; i++) {
                    res << kernel[i];
                }
                res << "]\n";
                return res;
            }

        }
    }
