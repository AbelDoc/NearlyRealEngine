    
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
    #include "../../../Header/NRE_Buffer.hpp"
    
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
                        using namespace Math;
                        using namespace GL;
                        
                        IBO<ModelVertex>* buffer = new IBO<ModelVertex>(GL_STATIC_DRAW);
                        float rings = 50;
                        float sectors = 50;
                        
                        float x, y, z, xy;
                        
                        float ringStep = static_cast <float> (PI) / rings;
                        float sectorStep = 2.0f * static_cast <float> (PI) / sectors;
        
                        float sectorAngle, ringAngle;
                        float lengthInv = 1.0f / o.getRadius();
    
                        for (int r = 0; r <= static_cast <int> (rings); r++) {
                            ringAngle = static_cast <float> (PI) / 2.0f - static_cast <float> (r) * ringStep;
                            xy = o.getRadius() * std::cos(ringAngle);
                            z  = o.getRadius() * std::sin(ringAngle);
                            
                            for (int s = 0; s <= static_cast <int> (sectors); s++) {
                                sectorAngle = static_cast <float> (s) * sectorStep;
                                
                                x = xy * std::cos(sectorAngle);
                                y = xy * std::sin(sectorAngle);
                                
                                Vector3D<float> vertex(x, y, z);
                                Vector3D<float> normal(vertex * lengthInv);
                                
                                buffer->addData(vertex, normal, 3);
                            }
                        }
        
                        std::uint32_t k1, k2;
                        
                        for (int s = 0; s < static_cast <int> (sectors); s++) {
                            k1 = s * (static_cast <std::uint32_t> (sectors) + 1);
                            k2 = k1 + static_cast <std::uint32_t> (sectors) + 1;
                            
                            for (int r = 0; r < static_cast <int> (rings); r++, k1++, k2++) {
                                if (s != 0) {
                                    buffer->addIndex(k1);
                                    buffer->addIndex(k2);
                                    buffer->addIndex(k1 + 1);
                                }
                                
                                if (s != static_cast <int> (sectors) - 1) {
                                    buffer->addIndex(k1 + 1);
                                    buffer->addIndex(k2);
                                    buffer->addIndex(k2 + 1);
                                }
                            }
                        }
                        
                        return buffer;
                    }
            };
            
            typedef TypedMesh<Physics::Sphere> SphereMesh;
        }
    }