    
    /**
     * @file NRE_Voxel.hpp
     * @brief Declaration of Engine's World's Object : Voxel
     * @author Louis ABEL
     * @date 13/08/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include <cstdint>
    #include <Header/NRE_Utility.hpp>

    #include "NRE_VoxelTypes.hpp"
    
    /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace World
         * @brief Engine's World module
         */
        namespace World {
            
            /**
             * @class Voxel
             * @brief Manage a voxel's information
             */
            class Voxel : public Utility::Stringable<Voxel> {
                public :    // Static
                    typedef std::uint32_t VoxelType;
                
                private :   // Fields
                    float isovalue;    /**< The voxel's isovalue */
                    VoxelType type;    /**< The voxel's material index */
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * Construct the container
                         */
                        Voxel() = default;
                        /**
                         * Construct the voxel's from it's information
                         * @param value the voxel's isovalue
                         * @param t     the voxel's material index
                         */
                        Voxel(float value, VoxelType t = 0);
        
                    //## Copy-Constructor ##//
                        /**
                         * Copy v into this
                         * @param v the voxel to copy
                         */
                        Voxel(Voxel const& v) = default;
        
                    //## Move-Constructor ##//
                        /**
                         * Move v into this
                         * @param v the voxel to move
                         */
                        Voxel(Voxel && v) = default;
    
                    //## Deconstructor ##//
                        /**
                         * Voxel Deconstructor
                         */
                        ~Voxel() = default;
    
                    //## Getter ##//
                        /**
                         * @return the voxel's isovalue
                         */
                        float getIsoValue() const;
                        /**
                         * @return the voxel's material index
                         */
                        VoxelType getType() const;
    
                    //## Setter ##//
                        /**
                         * Set the voxel's isovalue
                         * @param value the new voxel's isovalue
                         */
                        void setIsoValue(float value);
                        /**
                         * Set the voxel's material index
                         * @param t the new voxel's type
                         */
                        void setType(VoxelType t);
    
                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of v into this
                         * @param v the voxel to copy
                         * @return  the reference of himself
                         */
                        Voxel& operator =(Voxel const& v) = default;
                        /**
                         * Move assignment of v into this
                         * @param v the voxel to move into this
                         * @return  the reference of himself
                         */
                        Voxel& operator =(Voxel && c) = default;
    
                    //## Stream Operator ##//
                        /**
                         * Convert the voxel into a string
                         * @return the converted voxel
                         */
                        Utility::String toString() const;
            };
        }
    }

    #include "NRE_Voxel.tpp"