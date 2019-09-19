
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
        public :    // Static
            static constexpr int H_WIDTH = 5;
            static constexpr int H_DEPTH = 5;
            static constexpr int HEIGHT  = 2;
            static constexpr int SIMULTANEOUS_W = 2;
            static constexpr int SIMULTANEOUS_H = 2;

        private :   // Field
            VAO* vaos;
            IBO<PrimitiveVertex>* ibos;
            PerspectiveCamera camera;

            Chunk*** chunks;

            bool wireframeMode;
            bool linear;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {1280, 720}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), vaos(new VAO[SIMULTANEOUS_H * SIMULTANEOUS_W]), ibos(new IBO<PrimitiveVertex>[SIMULTANEOUS_H * SIMULTANEOUS_W]{GL_STATIC_DRAW, GL_STATIC_DRAW, GL_STATIC_DRAW, GL_STATIC_DRAW}), camera(50.0f, 70.0f, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), wireframeMode(false), linear(true) {
                    chunks = new Chunk**[HEIGHT];
                    for (int j = 0; j < HEIGHT; j++) {
                        chunks[j] = new Chunk*[H_WIDTH * 2 + 1];
                        for (int i = 0; i < H_WIDTH * 2 + 1; i++) {
                            chunks[j][i] = new Chunk[H_DEPTH * 2 + 1];
                        }
                    }

                    Clock clock;
                    clock.update();

                    for (int y = 0; y < HEIGHT; y++) {
                        for (int z = -H_DEPTH; z <= H_DEPTH; z++) {
                            for (int x = -H_WIDTH; x <= H_WIDTH; x++) {
                                chunks[y][z + H_DEPTH][x + H_DEPTH].setPosition({static_cast <int> (Chunk::SIZE_X) * x, static_cast <int> (Chunk::SIZE_Y) * y, static_cast <int> (Chunk::SIZE_Z) * z});
                                ChunkFactory::createTerrain(chunks[y][z + H_DEPTH][x + H_DEPTH]);
                            }
                        }
                    }
                    clock.update();
                    std::cout << "Chunk generation time : " << clock.getDelta() << std::endl;

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
                        } else if (event.isCode(KeyCode::L)) {
                            linear = !linear;
                            updateChunks();
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
                        w = 1280 / SIMULTANEOUS_W;
                        h = 720 / SIMULTANEOUS_H;
                        for (int i = 0; i < SIMULTANEOUS_H; i++) {
                            for (int j = 0; j < SIMULTANEOUS_W; j++) {
                                auto& ibo = ibos[index];
                                auto& vao = vaos[index++];
                                glViewport(j * w, i * h, w, h);
                                vao.bind();
                                    ibo.draw();
                                vao.unbind();
                            }
                        }
                    shader->unbind();
                }
                void destroy() override {
                    delete[] ibos;
                    delete[] vaos;
                    for (int j = 0; j < HEIGHT; j++) {
                        for (int i = 0; i < H_WIDTH * 2 + 1; i++) {
                            delete[] chunks[j][i];
                        }
                        delete[] chunks[j];
                    }
                    delete[] chunks;
                }
                void updateChunks() {
                    Clock clock;
                    clock.update();
                    std::size_t index = 0;
                    for (int i = 0; i < SIMULTANEOUS_H; i++) {
                        for (int j = 0; j < SIMULTANEOUS_W; j++) {
                            auto& ibo = ibos[index];
                            auto& vao = vaos[index];

                            for (int y = 0; y < HEIGHT; y++) {
                                for (int z = -H_DEPTH; z <= H_DEPTH; z++) {
                                    for (int x = -H_WIDTH; x <= H_WIDTH; x++) {
                                        ChunkPolygonizer::polygonize(chunks[y][z + H_DEPTH][x + H_DEPTH], ibo, 8.0f, Chunk::LEVELS[index], linear);
                                    }
                                }
                            }

                            index++;

                            std::cout << "Chunks update :" << std::endl;
                            std::cout << "\tResolution : " << Chunk::LEVELS[index - 1] << std::endl;
                            std::cout << "\tVertex count : " << ibo.getDataCount() << std::endl;

                            ibo.allocateAndFill();
                            vao.access(&ibo);
                        }
                    }
                    clock.update();
                    std::cout << "Time taken for update : " << clock.getDelta() << std::endl;
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();

        return 0;
    }
