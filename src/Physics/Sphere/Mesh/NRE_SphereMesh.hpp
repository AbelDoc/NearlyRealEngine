    
    /**
     * @file NRE_SphereMesh.hpp
     * @brief Declaration of Engine's Model's Mesh specialization : SphereMesh
     * @author Louis ABEL
     * @date 26/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include "../NRE_Sphere.hpp"
    #include "../../../Header/NRE_Model.hpp"
    
    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Model
         * @brief Engine's Model module
         */
        namespace Model {
            /**
             * @class MeshFactory
             * @brief Manage the creation of mesh's buffer
             */
            template <>
            class MeshFactory<Physics::Sphere> {
            public :    // Static
                /**
                 * Create a buffer from a given object
                 * @param o the object to create the buffer
                 * @return  the created buffer
                 */
                static GL::AbstractVBO* create(Physics::Sphere const& o) {
                    using namespace NRE::Math;
                    
                    GL::IBO<GL::PrimitiveVertex>* buffer = new GL::IBO<GL::PrimitiveVertex>(GL_STATIC_DRAW);
                    int rings = 10;
                    int sectors = 10;
                    float ring = 1.0f / static_cast <float> (rings - 1);
                    float sector = 1.0f / static_cast <float> (sectors - 1);
    
                    for (int r = 0; r < rings; r++) {
                        for (int s = 0; s < sectors; s++) {
                            Math::Vector3D<float> normal(cos(2.0_pi * static_cast <float> (s) * sector) * sin(PI * static_cast <float> (r) * ring),
                                                         sin(-(1.0_pi / 2.0) + 1.0_pi * static_cast <float> (r) * ring),
                                                         sin(2.0_pi * static_cast <float> (s) * sector) * sin(1_pi * static_cast <float> (r) * ring));
    
                            Math::Vector3D<float> vertex(o.getCenter() + (normal * o.getRadius()));
                            buffer->addData(vertex, normal);
                        }
                    }
    
                    std::uint32_t idx1, idx2, idx3, idx4;
    
                    for (GLint r = 0; r < rings - 1; r++) {
                        for (GLint s = 0; s < sectors - 1; s++) {
                            idx1 = r * sectors + s;
                            idx2 = idx1 + 1;
                            idx3 = idx2 + sectors;
                            idx4 = idx1 + sectors;
    
                            buffer->addIndex(idx4);
                            buffer->addIndex(idx2);
                            buffer->addIndex(idx1);
                            buffer->addIndex(idx2);
                            buffer->addIndex(idx4);
                            buffer->addIndex(idx3);
                        }
                    }
                    
                    return buffer;
                }
            };
            
            typedef TypedMesh<Physics::Sphere> SphereMesh;
        }
    }