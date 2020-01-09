
    /**
     * @file Texture/SkyBox/NRE_SkyBox.cpp
     * @brief Implementation of Engine's GL's Object : SkyBox
     * @author Louis ABEL
     * @date 06/11/2018
     * @copyright CC-BY-NC-SA
     */

    #include "NRE_SkyBox.hpp"
    #include "../../../Header/NRE_GL.hpp"
    #include "../../../Header/NRE_Model.hpp"

    namespace NRE {
        namespace GL {

            using namespace Math;
            using namespace IO;
            using namespace Exception;
            using namespace Renderer;
            using namespace Model;
            using namespace Physics;
            using namespace Utility;

            void SkyBox::capture(File const& file) {
                if (!file.exist()) {
                    throw (FileNotExistingException(file.getPath()));
                }
                int w, h, nrComponents;
                stbi_set_flip_vertically_on_load(true);
                float* data = stbi_loadf(file.getPath().getCData(), &w, &h, &nrComponents, 0);
                

                Texture2D hdrMap(Surface(Vector2D<GLsizei>(w, h), GL_RGB, GL_RGB16), GL_FLOAT, false);
                hdrMap.update(Vector2D<GLint>(0, 0), data);
                
                stbi_image_free(data);
                
                FBO captureBuffer(Vector2D<GLuint>(SIZE, SIZE));
                captureBuffer.createDepthBuffer<RenderBuffer>(GL_DEPTH_ATTACHMENT, GL_DEPTH_COMPONENT24, SIZE, SIZE);
                
                Matrix4x4<float> modelviews[6];
                modelviews[0].lookAt(Point3D<float>(0.0), Point3D<float>( -1.0,  0.0,  0.0), Vector3D<float>(0.0,  1.0,  0.0));
                modelviews[1].lookAt(Point3D<float>(0.0), Point3D<float>(1.0,  0.0,  0.0), Vector3D<float>(0.0,  1.0,  0.0));
                modelviews[2].lookAt(Point3D<float>(0.0), Point3D<float>( 0.0, 1.0,  0.0), Vector3D<float>(0.0,  0.0,  -1.0));
                modelviews[3].lookAt(Point3D<float>(0.0), Point3D<float>( 0.0,  -1.0,  0.0), Vector3D<float>(0.0,  0.0, 1.0));
                modelviews[4].lookAt(Point3D<float>(0.0), Point3D<float>( 0.0,  0.0,  1.0), Vector3D<float>(0.0,  1.0,  0.0));
                modelviews[5].lookAt(Point3D<float>(0.0), Point3D<float>( 0.0,  0.0, -1.0), Vector3D<float>(0.0,  1.0,  0.0));

                ProgramManager::get<Capture>()->bind();
                    hdrMap.bind();
                        glViewport(0, 0, SIZE, SIZE);
                        captureBuffer.bind();
                            for (int i = 0; i < FACE_NUM; i++) {
                                ProgramManager::get<Capture>()->sendModelview(modelviews[i]);
                                map.attach(GL_COLOR_ATTACHMENT0, i);

                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                                mesh.draw();
                            }
                        captureBuffer.unbind();
                    hdrMap.unbind();
                ProgramManager::get<Capture>()->unbind();
                
                captureBuffer.bind();
                    static_cast <RenderBuffer*> (captureBuffer.getDepthBuffer())->deallocate();
                    static_cast <RenderBuffer*> (captureBuffer.getDepthBuffer())->allocate(GL_DEPTH_COMPONENT24, 32, 32);
                captureBuffer.unbind();
                
                ProgramManager::get<Irradiance>()->bind();
                    map.bind();
                        glViewport(0, 0, 32, 32);
                        captureBuffer.bind();
                            for (int i = 0; i < FACE_NUM; i++) {
                                ProgramManager::get<Irradiance>()->sendModelview(modelviews[i]);
                                irradiance.attach(GL_COLOR_ATTACHMENT0, i);

                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                                mesh.draw();
                            }
                        captureBuffer.unbind();
                    map.unbind();
                ProgramManager::get<Irradiance>()->unbind();
                
                for (int i = 0; i < FACE_NUM; i++) {
                    modelviews[i].rotate(90_deg, Vector3D<float>(-1, 0, 0));
                }

                ProgramManager::get<Prefilter>()->bind();
                    map.bind();
                        captureBuffer.bind();
                        int maxMipLevels = 5;
                        for (int mip = 0; mip < maxMipLevels; mip++) {
                            int mipWidth = static_cast <int> (256 * std::pow(0.5f, static_cast <float> (mip)));
                            int mipHeight = static_cast <int> (256 * std::pow(0.5f, static_cast <float> (mip)));
                            static_cast <RenderBuffer*> (captureBuffer.getDepthBuffer())->deallocate();
                            static_cast <RenderBuffer*> (captureBuffer.getDepthBuffer())->allocate(GL_DEPTH_COMPONENT24, mipWidth, mipHeight);

                            glViewport(0, 0, mipWidth, mipHeight);

                            float roughness = static_cast <float> (mip) / static_cast <float> (maxMipLevels - 1);
                            ProgramManager::get<Prefilter>()->sendRoughness(roughness);
                                for (int i = 0; i < FACE_NUM; i++) {
                                ProgramManager::get<Prefilter>()->sendModelview(modelviews[i]);
                                prefilter.attach(GL_COLOR_ATTACHMENT0, i, mip);

                                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                                mesh.draw();
                            }
                        }
                        captureBuffer.unbind();
                    map.unbind();
                ProgramManager::get<Prefilter>()->unbind();
                
                ProgramManager::get<BRDF>()->bind();
                    captureBuffer.bind();
                        static_cast <RenderBuffer*> (captureBuffer.getDepthBuffer())->deallocate();
                        static_cast <RenderBuffer*> (captureBuffer.getDepthBuffer())->allocate(GL_DEPTH_COMPONENT24, SIZE, SIZE);
                        brdfLUT.attach(GL_COLOR_ATTACHMENT0);

                        glViewport(0, 0, SIZE, SIZE);

                        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                        RectangleMesh screen(Rectangle(Point2D<float>(-1, -1), Vector2D<float>(2, 2)));
                        screen.draw();
                    captureBuffer.unbind();
                ProgramManager::get<BRDF>()->unbind();
            }
        }
    }
