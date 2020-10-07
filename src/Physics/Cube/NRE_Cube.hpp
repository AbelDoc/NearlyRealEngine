    
    /**
     * @file NRE_Cube.hpp
     * @brief Declaration of Engine's Physics's Object : Cube
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
             * @class Cube
             * @brief Represent a cube object
             */
            class Cube : public Core::Observable {
                private :   // Fields
                    Math::Point3D<float> center;
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Cube() = default;
                        /**
                         * Construct the cube from it's position
                         * @param c the cube's center
                         */
                        Cube(Math::Point3D<float> const& c);
    
                    //## Copy Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the cube to copy
                         */
                        Cube(Cube const& c) = default;
    
                    //## Move Constructor ##//
                        /**
                         * Moves c into this
                         * @param c the cube to move
                         */
                        Cube(Cube && c) = default;
    
                    //## Deconstructor ##//
                        /**
                         * Cube Deconstructor
                         */
                        ~Cube() = default;
    
                    //## Getter ##//
                        /**
                         * @return the cube's center
                         */
                        Math::Point3D<float> const& getCenter() const;
    
                    //## Setter ##//
                        /**
                         * Set the cube's center
                         * @param c the new center
                         */
                        void setCenter(Math::Point3D<float> const& c);
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of c into this
                         * @param c the cube to copy
                         * @return  the reference of himself
                         */
                        Cube& operator =(Cube const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the cube to move into this
                         * @return  the reference of himself
                         */
                        Cube& operator =(Cube && c) = default;
            };
            
        }
    }
    
    #include "NRE_Cube.tpp"