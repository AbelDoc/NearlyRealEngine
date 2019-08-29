
    /**
     * @file NRE_Main.cpp
     * @brief Test of NearlyRealEngine
     * @author Louis ABEL
     * @date 06/04/2019
     * @copyright CC-BY-NC-SA
     */

    #include "Header/NRE_Core.hpp"

    using namespace NRE::System;
    using namespace NRE::Math;
    using namespace NRE::Event;
    using namespace NRE::Time;
    using namespace NRE::Renderer;
    using namespace NRE::Graphics;
    using namespace NRE::GL;
    using namespace std::chrono_literals;

    class DevApplication : public Application {
        private :   // Field
            VAO vao;
            VBO<PrimitiveVertex> vbo;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {1280, 720}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), vbo(GL_STATIC_DRAW) {
                    vbo.addData(Vector2D<float>(-1, -1), Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));
                    vbo.addData(Vector2D<float>( 1, -1), Vector4D<float>(0.0f, 1.0f, 0.0f, 1.0f));
                    vbo.addData(Vector2D<float>( 1,  1), Vector4D<float>(1.0f, 1.0f, 0.0f, 1.0f));
                    vbo.addData(Vector2D<float>( 1,  1), Vector4D<float>(1.0f, 1.0f, 0.0f, 1.0f));
                    vbo.addData(Vector2D<float>(-1,  1), Vector4D<float>(0.0f, 0.0f, 1.0f, 1.0f));
                    vbo.addData(Vector2D<float>(-1, -1), Vector4D<float>(1.0f, 0.0f, 0.0f, 1.0f));

                    vbo.allocateAndFill();
                    vao.access(&vbo);
                }

            //## Methods ##//
                void create() override {
                    addHandler<KeyEvent>([&](KeyEvent& event) {
                        std::cout << event.getCode() << std::endl;
                        return true;
                    });

                    addHandler<WindowCloseEvent>([&](WindowCloseEvent& event) {
                        std::cout << "One window is closing : " << event.getWindow().getId() << std::endl;
                        return true;
                    });

                    addHandler<ButtonEvent>([&](ButtonEvent& event) {
                        std::cout << event.getCode() << std::endl;
                        std::cout << "Cursor : " << event.getPosition() << std::endl;
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        std::cout << "Motion : " << event.getPosition() << std::endl;
                        return true;
                    });
                }
                void update() override {
                }
                void render() override {
                    clearColor(1.0f, 0.0f, 0.0f, 0.0f);
                    Primitive2D* shader = ProgramManager::get<Primitive2D>();
                    shader->bind();
                        vao.bind();
                            vbo.draw();
                        vao.unbind();
                    shader->unbind();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        try {
            DevApplication app;
            app.NREmain();
        } catch (std::exception const& e) {
            std::cout << e.what() << std::endl;
        }

        return 0;
    }
