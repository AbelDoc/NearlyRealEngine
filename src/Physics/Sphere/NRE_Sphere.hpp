    
    /**
     * @file NRE_Sphere.hpp
     * @brief Declaration of Engine's Physics's Object : Sphere
     * @author Louis ABEL
     * @date 17/12/2019
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
             * @class Sphere
             * @brief Represent a sphere object
             */
            class Sphere : public Core::Observable {
                private :   // Fields
                    Math::Point3D<float> center;
                    float radius;
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Sphere() = default;
                        /**
                         * Construct the sphere from it's position and center
                         * @param c the sphere's center
                         * @param r the sphere's radius
                         */
                        Sphere(Math::Point3D<float> const& c, float r);
    
                    //## Copy Constructor ##//
                        /**
                         * Copy s into this
                         * @param s the sphere to copy
                         */
                        Sphere(Sphere const& s) = default;
    
                    //## Move Constructor ##//
                        /**
                         * Moves s into this
                         * @param s the sphere to move
                         */
                        Sphere(Sphere && s) = default;
    
                    //## Deconstructor ##//
                        /**
                         * Sphere Deconstructor
                         */
                        ~Sphere() = default;
    
                    //## Getter ##//
                        /**
                         * @return the sphere's center
                         */
                        Math::Point3D<float> const& getCenter() const;
                        /**
                         * @return the sphere's radius
                         */
                        float getRadius() const;
    
                    //## Setter ##//
                        /**
                         * Set the sphere's center
                         * @param c the new center
                         */
                        void setCenter(Math::Point3D<float> const& c);
                        /**
                         * Set the sphere's radius
                         * @param r the new radius
                         */
                        void setRadius(float r);
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of s into this
                         * @param s the sphere to copy
                         * @return  the reference of himself
                         */
                        Sphere& operator =(Sphere const& s) = default;
                        /**
                         * Move assignment of s into this
                         * @param s the sphere to move into this
                         * @return  the reference of himself
                         */
                        Sphere& operator =(Sphere && s) = default;
            };
            
        }
    }
    
    #include "NRE_Sphere.tpp"