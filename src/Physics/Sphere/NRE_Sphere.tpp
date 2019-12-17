    
    /**
     * @file NRE_Sphere.tpp
     * @brief Implementation of Engine's Physics's Object : Sphere
     * @author Louis ABEL
     * @date 17/12/2019
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Physics {
            
            Sphere::Sphere(Math::Point3D<float> const& c, float r) : center(c), radius(r) {
            }
            
            Math::Point3D<float> const& Sphere::getCenter() const {
                return center;
            }
    
            float Sphere::getRadius() const {
                return radius;
            }
            
            void Sphere::setCenter(Math::Point3D<float> const& c) {
                center = c;
            }
            
            void Sphere::setRadius(float r) {
                radius = r;
            }
        
        }
    }
