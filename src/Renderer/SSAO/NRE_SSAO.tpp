
    /**
     * @file NRE_SSAO.tpp
     * @brief Implementation of Engine's Renderer's Object : SSAO
     * @author Louis ABEL
     * @date 27/01/2020
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Renderer {

            inline SSAO::SSAO() : noise(GL::Surface(Math::Vector2D<GLsizei>(NOISE_SIZE, NOISE_SIZE), GL_RGB, GL_RGBA32F), GL_FLOAT, false) {
                kernel.reserve(KERNEL_SIZE);
                generateKernel();
                generateNoise();
            }
    
            inline Core::Vector<Math::Vector3D<float>> const& SSAO::getKernel() const {
                return kernel;
            }
    
            inline GL::Texture2D const& SSAO::getNoise() const {
                return noise;
            }
    
            inline void SSAO::generateKernel() {
                std::uniform_real_distribution<float> rFloat(0, 1);
                std::default_random_engine generator;

                for (std::size_t i = 0 ; i < KERNEL_SIZE; i++) {
                    float scale = static_cast <float> (i) / static_cast <float> (KERNEL_SIZE);
                    scale = Math::lerp(0.1f, 1.0f, scale * scale);
                    
                    Math::Vector3D<float> sample(
                        rFloat(generator) * 2.0f - 1.0f,
                        rFloat(generator) * 2.0f - 1.0f,
                        rFloat(generator)
                    );
                    sample.normalize();
                    sample *= rFloat(generator);
                    sample *= scale;
                    kernel.pushBack(sample);
                }
            }

            inline void SSAO::generateNoise() {
                std::uniform_real_distribution<float> rFloat(0, 1);
                std::default_random_engine generator;

                auto ssaoNoise = new Math::Vector3D<float>[NOISE_SIZE * NOISE_SIZE];
                for (std::size_t i = 0; i < NOISE_SIZE * NOISE_SIZE; i++) {
                    ssaoNoise[i].setCoord(
                        rFloat(generator) * 2 - 1,
                        rFloat(generator) * 2 - 1,
                        0
                    );
                }

                noise.update(Math::Vector2D<int>(0, 0), static_cast <void*> (ssaoNoise));
                noise.bind();
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                noise.unbind();
                delete[] ssaoNoise;
            }
    
            inline Core::String SSAO::toString() const {
                Core::String res;
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
