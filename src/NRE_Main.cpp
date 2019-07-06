
    /**
     * @file NRE_Main.cpp
     * @brief Test of System's API
     * @author Louis ABEL
     * @date 06/04/2019
     * @copyright CC-BY-NC-SA
     */

    #include <Header/NRE_System.hpp>

    using namespace NRE::System;
    using namespace NRE::Math;
    using namespace NRE::Event;
    using namespace NRE::Time;
    using namespace NRE::Graphics;
    using namespace std::chrono_literals;

    int main(int, char**) {
        GraphicsSystem& gSys = getGraphicsSystem();
        EventSystem& eSys = getEventSystem();
        Clock& sysClock = getClock();

        gSys.createWindow("NRE-System Devlopment 1", {1280, 720}, WindowStyle::RESIZEABLE);

        EventHandler<KeyEvent> keyHandler([&](KeyEvent& event) {
            std::cout << event.getCode() << std::endl;
            return true;
        });

        EventHandler<WindowCloseEvent> closeHandler([&](WindowCloseEvent& event) {
            std::cout << "One window is closing : " << event.getWindow().getId() << std::endl;
            return true;
        });

        EventHandler<ButtonEvent> buttonHandler([&](ButtonEvent& event) {
            std::cout << event.getCode() << std::endl;
            std::cout << "Cursor : " << event.getPosition() << std::endl;
            return false;
        });

        EventHandler<MotionEvent> motionHandler([&](MotionEvent& event) {
            std::cout << "Motion : " << event.getPosition() << std::endl;
            return true;
        });

        sysClock.update();
        sysClock.showFPS();
        while (gSys.isRunning()) {
            sysClock.updateAndSleep(16ms);
            eSys.update();
        }

        return 0;
    }
