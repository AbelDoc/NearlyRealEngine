
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
            VAO vao;
            VBO<PrimitiveVertex> vbo;
            PerspectiveCamera camera;

            bool wireframeMode;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {1280, 720}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), vbo(GL_STATIC_DRAW), camera(50.0f, Point3D<float>(0, 0, 10), Point3D<float>(0, 0, 0), 70.0f, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f)), wireframeMode(false) {
                    Clock& clock = Singleton<System::System>::get().getClock();

                    float radius = 40.0f;
                    float threshold = radius * radius;

                    clock.update();
                    Vector<float> voxels1 = CloudFactory::createCircle({100, 100}, 10);
                    Vector<float> voxels2 = CloudFactory::createCircle({100, 100}, 5);
                    Vector<float> voxels3 = CloudFactory::createCircle({100, 100}, 2);
                    Vector<float> voxels4 = CloudFactory::createCircle({100, 100}, 1);
                    Vector<float> voxels5 = CloudFactory::createCircle({100, 100}, 0.5f);

                    clock.update();
                    std::cout << "Time taken for points cloud generation : " << clock.getDelta() << std::endl;
                    clock.update();
                    CloudPolygonizer::polygonize(vbo, voxels1, {0,   0}, {100, 100},   10, threshold);
                    CloudPolygonizer::polygonize(vbo, voxels2, {0, 100}, {100, 100},    5, threshold);
                    CloudPolygonizer::polygonize(vbo, voxels3, {0, 200}, {100, 100},    2, threshold);
                    CloudPolygonizer::polygonize(vbo, voxels4, {0, 300}, {100, 100},    1, threshold);
                    CloudPolygonizer::polygonize(vbo, voxels5, {0, 400}, {100, 100}, 0.5f, threshold);
                    clock.update();

                    std::cout << "Time taken for cells polygonization : " << clock.getDelta() << std::endl;
                    std::cout << "Vertex size : " << vbo.getDataCount() << std::endl;

                    vbo.allocateAndFill();
                    vao.access(&vbo);
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
                        } else if (event.isCode(KeyCode::R)) {
                            wireframeMode = !wireframeMode;
                            if (wireframeMode) {
                                polygonMode(GL_FRONT_AND_BACK, GL_LINE);
                            } else {
                                polygonMode(GL_FRONT_AND_BACK, GL_FILL);
                            }
                            return true;
                        }
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(Vector2D<Angle>(event.getMotion().getY() * degree * 0.1f, event.getMotion().getX() * degree * 0.1f));
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
                        vao.bind();
                            vbo.draw();
                        vao.unbind();
                    shader->unbind();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();

        return 0;
    }
