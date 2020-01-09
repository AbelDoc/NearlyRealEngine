    
    /**
     * @file NRE_Cube.tpp
     * @brief Implementation of Engine's Physics's Object : Cube
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Physics {
            
            inline Cube::Cube(Math::Point3D<float> const& c) : center(c) {
            }
    
            inline Math::Point3D<float> const& Cube::getCenter() const {
                return center;
            }
    
            inline void Cube::setCenter(Math::Point3D<float> const& c) {
                center = c;
            }
            
        }
    }
