    
    /**
     * @file NRE_Rectangle.tpp
     * @brief Implementation of Engine's Physics's Object : Rectangle
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace Physics {
    
            inline Rectangle::Rectangle(Math::Point2D<float> const& c, Math::Vector2D<float> const& s) : coord(c), size(s) {
            }
    
            inline Math::Point2D<float> const& Rectangle::getCoord() const {
                return coord;
            }
    
            inline Math::Vector2D<float> const& Rectangle::getSize() const {
                return size;
            }
    
            inline void Rectangle::setCoord(Math::Point2D<float> const& c) {
                coord = c;
            }
    
            inline void Rectangle::setSize(Math::Vector2D<float> const& s) {
                size = s;
            }
            
        }
    }
