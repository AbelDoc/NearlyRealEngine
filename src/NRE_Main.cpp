
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
    using namespace NRE::Core;
    using namespace NRE::Model;
    using namespace NRE::GL;
    using namespace NRE::ECS;
    using namespace NRE::Physics;
    using namespace NRE::IO;
    using namespace NRE::World;
    using namespace NRE::Data;
    
    class DevApplication : public Application {
        public :    // Static
            static constexpr int SCREEN_W = 1280;
            static constexpr int SCREEN_H = 720;
            
            static constexpr std::size_t NB_ASTEROIDS = 1;
    
            static constexpr int worldSizeX = 128;
            static constexpr int worldSizeY = 128;
            static constexpr int worldSizeZ = 128;
            
        private :   // Field
            PerspectiveCamera camera;
    
            Vector<World::World> worlds;
            Vector<ChunkModel> chunks;
            
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(80.0f, 45_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 2000.0f), Vector3D<float>(0, 0, 0)) {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
                    glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
                }

            //## Methods ##//
                void create() override {
                    NRE::System::System::get().setRelativeMode(true);
                    NRE::System::System::get().showCursor(false);
    
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
                        }
                        return false;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(event.getMotion());
                        return true;
                    });
    
                    worlds.reserve(NB_ASTEROIDS);
                    chunks.reserve(NB_ASTEROIDS * World::World::NB_CHUNKS);
                    
                    for (std::size_t i = 0; i < NB_ASTEROIDS; i++) {
                        //worlds.emplaceBack(Vector3D<float>((std::rand() % worldSizeX) - worldSizeX / 2, std::rand() % worldSizeY, (std::rand() % worldSizeZ) - worldSizeZ / 2));
                        worlds.emplaceBack(Vector3D<float>(0, 0, 0));
                        World::World& world = worlds.getLast();
                        world.setFactory(Factory::createAsteroid);
                        world.generate();
    
                        for (Chunk const& c : world) {
                            Entity r = Singleton<EntityManager>::get().create();
                            chunks.emplaceBack(&c);
                            auto& voxels = chunks.getLast().get<ChunkMesh>(0);
                            voxels.setBoundObject(&camera.getFrustum());
                            r.assign<VoxelRenderable>(voxels);
                        }
                    }
                    
                    for (int i = 0; i < 32; i++) {
                        Entity l = Singleton<EntityManager>::get().create();
                        l.assign<Light>(Vector3D<float>((std::rand() % worldSizeX) - worldSizeX / 2, 3 * (worldSizeY / 4), (std::rand() % worldSizeZ) - worldSizeZ / 2), Vector3D<float>(100 + std::rand() % 400, 100 + std::rand() % 400, 100 + std::rand() % 400));
                    }
                    
                    Singleton<SystemManager>::get().add<DeferredSystem>(camera, Vector2D<unsigned int>(SCREEN_W, SCREEN_H), "Data/SkyBox/Space_2K.hdr");
                    Singleton<SystemManager>::get().configure();
                }
                void update() override {
                    camera.update();
                }
                void render() override {
                    Singleton<SystemManager>::get().getSystem<DeferredSystem>()->update();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();
        
        return 0;
    }
