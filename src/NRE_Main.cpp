
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
    using namespace NRE::Physics;
    using namespace NRE::IO;
    using namespace NRE::World;
    
    #define NB_INSTANCE 1'000
    
    class Flock;
    
    class Boid {
        private :    // Fields
            Point3D<float> position;
            Vector3D<float> velocity;
            Vector3D<float> acceleration;
            
        public :     // Methods
            //## Constructor ##//
                Boid(Point3D<float> const& p) : position(p), velocity(std::rand() % 3 - 2, std::rand() % 3 - 2, std::rand() % 3 - 2), acceleration(0) {
                }
            //## Getter ##//
                Point3D<float> getPosition() const {
                    return position;
                }
            
            //## Methods ##//
                void applyForce(Vector3D<float> const& force) {
                    acceleration += force;
                }
                void process(Vector<Boid>& flock, Vector3D<float> const& target) {
                    Vector3D<float> separation(0), alignment(0), cohesion(0), sumAlg(0), sumCoh(0);
                    float countSep = 0, count = 0;
                    for (Boid& b : flock) {
                        long double dist = position.distance(b.position);
                        if (dist > 0 && dist < 5) {    // Separation
                            Vector3D<float> diff = position - b.position;
                            diff.normalize();
                            diff /= dist;
                            separation += diff;
                            countSep++;
                        }
                        if (dist > 0 && dist < 50) {    // Alignment
                            sumAlg += target - b.velocity;
                            sumCoh += b.position;
                            count++;
                        }
                    }
                    if (countSep > 0) {
                        separation /= countSep;
                    }
                    if (separation.norm() > 0) {
                        separation.normalize();
                        separation *= 3.5f;
                        separation -= velocity;
                        long double mag = separation.norm();
                        if (mag > 0.5f) {
                            separation /= mag;
                        }
                    }
                    if (count > 0) {
                        sumCoh /= count;
                        Vector3D<float> desired = -sumCoh;
                        desired.normalize();
                        desired *= 3.5f;
                        cohesion = desired - velocity;
                        long double magAcc = cohesion.norm();
                        if (magAcc > 0.5f) {
                            cohesion /= magAcc;
                        }
                        sumAlg /= count;
                        sumAlg.normalize();
                        sumAlg *= 3.5f;
                        alignment = sumAlg - velocity;
                        long double magAlg = alignment.norm();
                        if (magAlg > 0.5f) {
                            alignment /= magAlg;
                        }
                    }
                    separation *= 1.5f;
                    applyForce(separation);
                    applyForce(alignment);
                    applyForce(cohesion);
                }
                void run(Vector<Boid>& flock, Vector3D<float> target) {
                    process(flock, target);
                    update();
                    borders();
                }
                void update() {
                    acceleration *= 0.4f;
                    velocity += acceleration;
                    long double mag = velocity.norm();
                    if (mag > 0.5f) {
                        velocity /= mag;
                    }
                    position += velocity;
                    acceleration *= 0;
                }
                void borders() {
                    if (position.getX() < -500) {
                        position.setX(500);
                    }
                    if (position.getY() < -500) {
                        position.setY(500);
                    }
                    if (position.getZ() < -500) {
                        position.setZ(500);
                    }
                    if (position.getX() > 500) {
                        position.setX(-500);
                    }
                    if (position.getY() > 500) {
                        position.setY(-500);
                    }
                    if (position.getZ() > 500) {
                        position.setZ(-500);
                    }
                }
    };
    
    class Flock {
        public :    // Iterator
            /**< Shortcut to hide Iterator implementation */
            typedef typename Utility::Vector<Boid>::Iterator         Iterator;
            /**< Shortcut to hide ConstIterator implementation */
            typedef typename Utility::Vector<Boid>::ConstIterator    ConstIterator;
            
        private :   // Fields
            Vector<Boid> flock;
        
        public :    // Methods
            //## Constructor ##//
                Flock() {
                    flock.reserve(NB_INSTANCE);
                    for (int i = 0; i < NB_INSTANCE; i++) {
                        flock.emplaceBack(Point3D<float>(0, 0, 0));
                    }
                }
            //## Iterator Access ##//
                /**
                 * @return an iterator on the first element
                 */
                Iterator begin() {
                    return flock.begin();
                }
                /**
                 * @return a const iterator on the first element
                 */
                ConstIterator begin() const {
                    return flock.begin();
                }
                /**
                 * @return a const iterator on the first element
                 */
                ConstIterator cbegin() const {
                    return flock.cbegin();
                }
                /**
                 * @return an iterator on the end of the container
                 */
                Iterator end() {
                    return flock.end();
                }
                /**
                 * @return a const iterator on the end of the container
                 */
                ConstIterator end() const {
                    return flock.end();
                }
                /**
                 * @return a const iterator on the end of the container
                 */
                ConstIterator cend() const {
                    return flock.cend();
                }
            //## Methods ##//
                void flocking(Vector3D<float> target) {
                    for (Boid& b : flock) {
                        b.run(flock, target);
                    }
                }
    
            //## Access Operator ##//
                /**
                 * Return a reference on a data's object
                 * @warning No range check performed
                 * @param   index the object's index
                 * @return        the object's reference
                 */
                Boid& operator [](std::size_t index) {
                    return flock[index];
                }
                /**
                 * Return a const reference on a data's object
                 * @warning No range check performed
                 * @param   index the object's index
                 * @return        the object's reference
                 */
                Boid const& operator [](std::size_t index) const {
                    return flock[index];
                }
    };

    class DevApplication : public Application {
        public :    // Static
            static constexpr int SCREEN_W = 1280;
            static constexpr int SCREEN_H = 720;
            
        private :   // Field
            Angle fov;
            PerspectiveCamera camera;
            
            Flock flock;
            InstancedModel<ColoredMatrixInstance> spheres;
            
            bool wireframeMode;
            bool splitMode;

        public :    // Methods
            //## Constructor ##//
                DevApplication() : Application("NRE-System Devlopment", {SCREEN_W, SCREEN_H}, WindowStyle::RESIZEABLE, {8, 8, 8, 0, 0, 1, 24, 8, 0, 0, 0, 1, 2, 1}), fov(70_deg), camera(90.0f, fov, 1280.0f / 720.0f, Vector2D<float>(0.1f, 3000.0f), Vector3D<float>(8, 8, 8), Vector3D<float>(0, 1, 0)), spheres(NB_INSTANCE, GL_STREAM_DRAW), wireframeMode(false), splitMode(false) {
                    glEnable(GL_DEPTH_TEST);
                    glEnable(GL_CULL_FACE);
                        glCullFace(GL_BACK);
    
                    Sphere s(Vector3D<float>(0, 0, 0), 1);
                    spheres.addMesh(std::unique_ptr<SphereMesh>(new SphereMesh(s)));
        
                    int i = 0;
                    for (ColoredMatrixInstance& m : spheres) {
                        m.color = Vector4D<float>(static_cast <float> (std::rand() % 1000) / 1000, static_cast <float> (std::rand() % 1000) / 1000, static_cast <float> (std::rand() % 1000) / 1000, 1);
                        m.matrix.setIdentity();
                        m.matrix.translate(flock[i++].getPosition());
                        m.matrix.transpose();
                    }
                    spheres.update();
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
                        } else if (event.isCode(KeyCode::M)) {
                            splitMode = !splitMode;
                            return true;
                        }
                        return false;
                    });

                    addHandler<WheelMotionEvent>([&](WheelMotionEvent& event) {
                        fov -= (event.getDelta() * degree);
                        if (fov < 1.0_deg) {
                            fov = 1.0_deg;
                        }
                        if (fov >= 89.9_deg) {
                            fov = 89.9_deg;
                        }
                        camera.setFov(fov);
                        return true;
                    });

                    addHandler<MotionEvent>([&](MotionEvent& event) {
                        camera.turn(event.getMotion());
                        return true;
                    });
                    
                    
                }
                void update() override {
                    camera.update();
                    flock.flocking(static_cast <PerspectiveCamera const&> (camera).getEye());
                    int i = 0;
                    for (ColoredMatrixInstance& m : spheres) {
                        Boid& b = flock[i++];
                        m.matrix.setL4(Vector4D<float>(b.getPosition(), 1.0f));
                    }
                    spheres.update();
                }
                void render() override {
                    clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    InstancedPrimitive3D* instancedShader = ProgramManager::get<InstancedPrimitive3D>();
                    instancedShader->bind();
                        instancedShader->sendCamera(camera);
                        spheres.draw();
                    instancedShader->unbind();
                }
                void destroy() override {
                }
    };

    int main(int, char**) {
        DevApplication app;
        app.NREmain();
        
        return 0;
    }
