    
    /**
     * @file NRE_FlockSystem.hpp
     * @brief Declaration of Engine's ECS's System : FlockSystem
     * @author Louis ABEL
     * @date 07/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_ECS.hpp>
    
    #include "../Component/Renderable/NRE_InstancedRenderable.hpp"

    #include "../../Header/NRE_Model.hpp"
    #include "../../Header/NRE_Buffer.hpp"
    #include "../../Header/NRE_Physics.hpp"

    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace ECS
         * @brief Engine's ECS module
         */
        namespace ECS {
    
            /**
             * @class Boid
             * @brief Manage a boid
             */
            class Boid {
                public:    //Fields
                    Math::Point3D<float> position;       /**< The position */
                    Math::Vector3D<float> velocity;      /**< The velocity */
                    Math::Vector3D<float> acceleration;  /**< The acceleration */
        
                public:    // Methods
                    //## Constructor ##//
                    /**
                     * Default constructor
                     */
                    Boid() : velocity(std::rand() % 3 - 2, std::rand() % 3 - 2, std::rand() % 3 - 2) {
                    }
            };
            
            /**
             * @class FlockSystem
             * @brief Manage boids simulation
             */
            class FlockSystem : public System<FlockSystem> {
                private :   // Static
                    static constexpr int NB_INSTANCE = 150;
                
                private :   // Fields
                    Camera::Camera const& target;
                    Utility::Vector<Boid> flock;
                    Model::InstancedModel<GL::MatrixInstance> spheres;
                
                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        FlockSystem(Camera::Camera const& t) : target(t), spheres(NB_INSTANCE, GL_STREAM_DRAW) {
                        }
                        
                    //## Methods ##//
                        void configure() override {
                            Entity flockE = Utility::Singleton<EntityManager>::get().create();
                            flockE.assign<InstancedRenderable>(&spheres);
                            
                            flock.resize(NB_INSTANCE);
    
                            Physics::Sphere s(Math::Vector3D<float>(0, 0, 0), 1);
                            spheres.addMesh(std::unique_ptr<Model::SphereMesh>(new Model::SphereMesh(s)));
        
                            int i = 0;
                            for (GL::MatrixInstance& m : spheres) {
                                Entity light = Utility::Singleton<EntityManager>::get().create();
                                light.assign<Light>(flock[i].position, Math::Vector3D<float>((static_cast <float> (std::rand() % 1000) / 1000.0) * 300.0, (static_cast <float> (std::rand() % 1000) / 1000.0) * 300.0, (static_cast <float> (std::rand() % 1000) / 1000.0) * 300.0));
                                m.matrix.setIdentity();
                                m.matrix.translate(flock[i++].position);
                                m.matrix.transpose();
                            }
                            spheres.update();
                        }
                        /**
                         * Update the system
                         */
                        void update() override {
                            int i = 0;
                            for (Boid& b : flock) {
                                Math::Vector3D<float> separation(0), alignment(0), cohesion(0), sumAlg(0), sumCoh(0);
                                float countSep = 0, count = 0;
    
                                for (Boid& otherB : flock) {
                                    long double dist = b.position.distance(otherB.position);
                                    if (dist > 0 && dist < 5) {    // Separation
                                        Math::Vector3D<float> diff = b.position - otherB.position;
                                        diff.normalize();
                                        diff /= dist;
                                        separation += diff;
                                        countSep++;
                                    }
                                    if (dist > 0 && dist < 50) {    // Alignment
                                        sumAlg += otherB.velocity + (target.getEye() - otherB.position);
                                        sumCoh += otherB.position;
                                        count++;
                                    }
                                }
                                if (countSep > 0) {
                                    separation /= countSep;
                                }
                                if (separation.norm() > 0) {
                                    separation.normalize();
                                    separation *= 3.5f;
                                    separation -= b.velocity;
                                    long double mag = separation.norm();
                                    if (mag > 0.5f) {
                                        separation /= mag;
                                    }
                                }
                                if (count > 0) {
                                    sumCoh /= count;
                                    Math::Vector3D<float> desired = -sumCoh;
                                    desired.normalize();
                                    desired *= 3.5f;
                                    cohesion = desired - b.velocity;
                                    long double magAcc = cohesion.norm();
                                    if (magAcc > 0.5f) {
                                        cohesion /= magAcc;
                                    }
                                    sumAlg /= count;
                                    sumAlg.normalize();
                                    sumAlg *= 3.5f;
                                    alignment = sumAlg - b.velocity;
                                    long double magAlg = alignment.norm();
                                    if (magAlg > 0.5f) {
                                        alignment /= magAlg;
                                    }
                                }
                                separation *= 1.5f;
                                b.acceleration += separation;
                                b.acceleration += alignment;
                                b.acceleration += cohesion;
    
                                b.acceleration *= 0.4f;
                                b.velocity += b.acceleration;
                                long double mag = b.velocity.norm();
                                if (mag > 0.5f) {
                                    b.velocity /= mag;
                                }
                                b.position += b.velocity;
                                b.acceleration *= 0;
    
                                if (b.position.getX() < -500) {
                                    b.position.setX(500);
                                }
                                if (b.position.getY() < -500) {
                                    b.position.setY(500);
                                }
                                if (b.position.getZ() < -500) {
                                    b.position.setZ(500);
                                }
                                if (b.position.getX() > 500) {
                                    b.position.setX(-500);
                                }
                                if (b.position.getY() > 500) {
                                    b.position.setY(-500);
                                }
                                if (b.position.getZ() > 500) {
                                    b.position.setZ(-500);
                                }
                                
                                
                                spheres[i].matrix.setIdentity();
                                spheres[i].matrix.translate(b.position);
                                spheres[i++].matrix.transpose();
                            }
                            int nb = 0;
                            Utility::Singleton<EntityManager>::get().each<Light>([this, &nb](Entity, Light& l) {
                                l.position = flock[nb++].position;
                            });
                            spheres.update();
                        }
                        Math::Vector3D<float> getBoidPosition() {
                            return flock[0].position;
                        }
            };
        }
    }
