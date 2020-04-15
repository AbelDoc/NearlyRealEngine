    
    /**
     * @file Texture/SkyBox/NRE_SkyBox.tpp
     * @brief Implementation of Engine's GL's Object : SkyBox
     * @author Louis ABEL
     * @date 06/11/2018
     * @copyright CC-BY-NC-SA
     */
    
    #include "NRE_SkyBox.hpp"
    #include "../../../Header/NRE_Model.hpp"
    
    namespace NRE {
        namespace GL {
            
            inline SkyBox::SkyBox(IO::File const& file) : brdfLUT(Surface(Math::Vector2D<GLsizei>(SIZE, SIZE), GL_RG, GL_RG16), GL_FLOAT, false), mesh(Physics::Cube(Math::Vector3D<float>(0))) {
                allocate();
                capture(file);
            }
    
            inline CubeMap const& SkyBox::getIrradiance() const {
                return irradiance;
            }
    
            inline CubeMap const& SkyBox::getPrefilter() const {
                return prefilter;
            }
            
            inline CubeMap const& SkyBox::getMap() const {
                return map;
            }
    
            inline Texture2D const& SkyBox::getBRDFLUT() const {
                return brdfLUT;
            }
            
            inline Model::CubeMesh const& SkyBox::getMesh() const {
                return mesh;
            }
    
            inline void SkyBox::allocate() {
                map.allocate(0, Surface(Math::Vector2D<GLsizei>(SIZE, SIZE), GL_RGB, GL_RGB16));
                irradiance.allocate(0, Surface(Math::Vector2D<GLsizei>(32, 32), GL_RGB, GL_RGB16));
                prefilter.allocate(0, Surface(Math::Vector2D<GLsizei>(256, 256), GL_RGB, GL_RGB16));
                map.bind();
                    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // enable pre-filter mipmap sampling (combatting visible dots artifact)
                    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                map.unbind();
                irradiance.bind();
                    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                prefilter.unbind();
                prefilter.bind();
                    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                prefilter.unbind();
            }
            
        }
    }
