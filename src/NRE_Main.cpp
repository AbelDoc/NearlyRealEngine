
    /**
     * @file NRE_Main.cpp
     * @brief Test of NearlyRealEngine
     * @author Louis ABEL
     * @date 06/04/2019
     * @copyright CC-BY-NC-SA
     */

    #include "Header/NRE_Core.hpp"

    using namespace NRE;
    using namespace NRE::System;
    using namespace NRE::Math;
    using namespace NRE::Event;
    using namespace NRE::Time;
    using namespace NRE::Renderer;
    using namespace NRE::Graphics;
    using namespace NRE::Camera;
    using namespace NRE::Utility;
    using namespace NRE::GL;
    using namespace NRE::World;
    using namespace std::chrono_literals;

    class DevApplication : public Application {
        private :   // Field
            VAO* vaos;
            VBO<PrimitiveVertex>* vbos;
            PerspectiveCamera camera;

            bool wireframeMode;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {1280, 720}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), vaos(new VAO[4]), vbos(new VBO<PrimitiveVertex>[4]{GL_STATIC_DRAW, GL_STATIC_DRAW, GL_STATIC_DRAW, GL_STATIC_DRAW}), camera(50.0f, 70.0f, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), wireframeMode(false) {
                    updateChunks();

                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                }

            //## Methods ##//
                void create() override {
                    Singleton<System::System>::get().setRelativeMode(true);
                    addHandler<KeyEvent>([&](KeyEvent& event) {
                        if (event.isCode(KeyCode::Z)) {
                            camera.moveFront();
                        } else if (event.isCode(KeyCode::S)) {
                            camera.moveBack();
                        } else if (event.isCode(KeyCode::Q)) {
                            camera.moveLeft();
                        } else if (event.isCode(KeyCode::D)) {
                            camera.moveRight();
                        } else if (event.isCode(KeyCode::LEFT_SHIFT)) {
                            camera.moveDown();
                        } else if (event.isCode(KeyCode::SPACE)) {
                            camera.moveUp();
                        } else if (event.isCode(KeyCode::P)) {
                            wireframeMode = !wireframeMode;
                            if (wireframeMode) {
                                polygonMode(GL_FRONT, GL_LINE);
                            } else {
                                polygonMode(GL_FRONT, GL_FILL);
                            }
                            return true;
                        }
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(event.getMotion());
                        return true;
                    });
                }
                void update() override {
                    camera.update();
                }
                void render() override {
                    clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    Primitive3D* shader = ProgramManager::get<Primitive3D>();
                    shader->bind();
                        shader->sendMVP(static_cast <PerspectiveCamera const&> (camera).getProjection() * camera.getView());
                        std::size_t index = 0;
                        unsigned int w, h;
                        w = 1280 / 2;
                        h = 720 / 2;
                        for (int i = 0; i < 2; i++) {
                            for (int j = 0; j < 2; j++) {
                                VBO<PrimitiveVertex>& vbo = vbos[index];
                                VAO& vao = vaos[index++];
                                glViewport(i * w, j * h, w, h);
                                vao.bind();
                                    vbo.draw();
                                vao.unbind();
                            }
                        }
                    shader->unbind();
                }
                void destroy() override {
                    delete[] vbos;
                    delete[] vaos;
                }
                void updateChunks() {
                    std::size_t index = 0;
                    for (int i = 0; i < 2; i++) {
                        for (int j = 0; j < 2; j++) {
                            VBO<PrimitiveVertex>& vbo = vbos[index];
                            VAO& vao = vaos[index];

                            float resolution = static_cast <float> (std::pow(2.0f, index++)) / 2.0f;

                            for (int z = -5; z <= 5; z++) {
                                for (int x = -5; x <= 5; x++) {
                                    Chunk chunk({static_cast <int> (Chunk::SIZE_X) * x, 0, static_cast <int> (Chunk::SIZE_Z) * z});
                                    ChunkFactory::createTerrain(chunk, resolution);
                                    ChunkPolygonizer::polygonize(chunk, vbo);
                                }
                            }

                            std::cout << "Chunks update :" << std::endl;
                            std::cout << "\tResolution : " << resolution << std::endl;
                            std::cout << "\tVertex count : " << vbo.getDataCount() << std::endl;

                            vbo.allocateAndFill();
                            vao.access(&vbo);
                        }
                    }
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();

        return 0;
    }
