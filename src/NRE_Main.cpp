
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
            
            static constexpr std::size_t NB_ASTEROIDS = 32;
    
            static constexpr int worldSizeX = 512;
            static constexpr int worldSizeY = 512;
            static constexpr int worldSizeZ = 512;
            
        private :   // Field
            PerspectiveCamera camera;
    
            Vector<World::World> worlds;
            Vector<ChunkModel> chunks;
        
        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), camera(80.0f, 45_deg, 1280.0f / 720.0f, Vector2D<float>(0.1f, 2000.0f), Vector3D<float>(0, 0, 0)) {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
                    //glEnable(GL_CULL_FACE);
                        //glCullFace(GL_BACK);
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
                    
                    ChunkFactory generator = [&](Chunk& target, int ,Math::Vector3D<float> const& worldOffset) {
                        FastNoise elevation(23'08'2020);
                        for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                            float nz = static_cast <float> (z) + static_cast <float> (target.getPosition().getZ());
                            for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                                float nx = static_cast <float> (x) + static_cast <float> (target.getPosition().getX());
                                for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                                    float ny = static_cast <float> (y) + static_cast <float> (target.getPosition().getY());
    
                                    float distFromCenter = static_cast <float> ((worldOffset + Vector3D<float>(40, 40, 40)).distance(Vector3D<float>(nx, ny, nz)) / 69.28);
                                    
                                    float e = 1.00f * (elevation.GetNoise( 1 * nx,  1 * ny,  1 * nz) / 2.f + 0.5f)
                                            + 0.40f * (elevation.GetNoise( 2 * nx,  2 * ny,  2 * nz) / 2.f + 0.5f)
                                            + 0.30f * (elevation.GetNoise( 4 * nx,  4 * ny,  4 * nz) / 2.f + 0.5f)
                                            + 0.05f * (elevation.GetNoise(16 * nx, 16 * ny, 16 * nz) / 2.f + 0.5f);
                                    e /= (1.00f + 0.40f + 0.30f + 0.05f);
                                    e = static_cast <float> (std::pow(e, 1.80f));
                                    
                                    target.getVoxel(x, y, z).setIsoValue(distFromCenter + e + 0.0001f);
                                    target.getVoxel(x, y, z).setType(0);
                                }
                            }
                        }
                    };
    
                    worlds.reserve(NB_ASTEROIDS);
                    chunks.reserve(NB_ASTEROIDS * World::World::NB_CHUNKS);
                    
                    for (std::size_t i = 0; i < NB_ASTEROIDS; i++) {
                        worlds.emplaceBack(Vector3D<float>((std::rand() % worldSizeX) - worldSizeX / 2, std::rand() % worldSizeY, (std::rand() % worldSizeZ) - worldSizeZ / 2));
                        World::World& world = worlds.getLast();
                        world.setFactory(generator);
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
                        l.assign<Light>(Vector3D<float>((std::rand() % worldSizeX) - worldSizeX / 2, 3 * (worldSizeY / 4), (std::rand() % worldSizeZ) - worldSizeZ / 2), Vector3D<float>(10000 + std::rand() % 40000, 10000 + std::rand() % 40000, 10000 + std::rand() % 40000));
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
