    
    /**
     * @file NRE_Rectangle.hpp
     * @brief Declaration of Engine's Physics's Object : Rectangle
     * @author Louis ABEL
     * @date 08/01/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Core.hpp>
    
    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Physics
         * @brief Engine's Physics module
         */
        namespace Physics {
        
            /**
             * @class Rectangle
             * @brief Represent a rectangle object
             */
            class Rectangle : public Core::Observable {
                private :   // Fields
                    Math::Point2D<float> coord;
                    Math::Vector2D<float> size;
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Rectangle() = default;
                        /**
                         * Construct the rectangle from it's position and size
                         * @param c the rectangle's coordinate
                         * @param s the rectangle's size
                         */
                        Rectangle(Math::Point2D<float> const& c, Math::Vector2D<float> const& s);
    
                    //## Copy Constructor ##//
                        /**
                         * Copy r into this
                         * @param r the rectangle to copy
                         */
                        Rectangle(Rectangle const& r) = default;
    
                    //## Move Constructor ##//
                        /**
                         * Moves r into this
                         * @param r the rectangle to move
                         */
                        Rectangle(Rectangle && r) = default;
    
                    //## Deconstructor ##//
                        /**
                         * Rectangle Deconstructor
                         */
                        ~Rectangle() = default;
    
                    //## Getter ##//
                        /**
                         * @return the rectangle's coord
                         */
                        Math::Point2D<float> const& getCoord() const;
                        /**
                         * @return the rectangle's size
                         */
                        Math::Vector2D<float> const& getSize() const;
    
                    //## Setter ##//
                        /**
                         * Set the rectangle's coord
                         * @param c the new center
                         */
                        void setCoord(Math::Point2D<float> const& c);
                        /**
                         * Set the rectangle's size
                         * @param s the new size
                         */
                        void setSize(Math::Vector2D<float> const& s);
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of r into this
                         * @param r the rectangle to copy
                         * @return  the reference of himself
                         */
                        Rectangle& operator =(Rectangle const& r) = default;
                        /**
                         * Move assignment of r into this
                         * @param r the rectangle to move into this
                         * @return  the reference of himself
                         */
                        Rectangle& operator =(Rectangle && r) = default;
            };
            
        }
    }
    
    #include "NRE_Rectangle.tpp"