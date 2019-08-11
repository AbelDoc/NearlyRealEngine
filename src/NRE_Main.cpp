
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
    using namespace NRE::Graphics;
    using namespace NRE::GL;
    using namespace std::chrono_literals;

    class DevApplication : public Application {
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {1280, 720}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}) {
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
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();

        return 0;
    }
