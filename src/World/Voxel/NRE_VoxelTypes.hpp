    
    /**
     * @file NRE_VoxelTypes.hpp
     * @brief Declaration of Engine's World's Object : VoxelTypes
     * @author Louis ABEL
     * @date 14/08/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    #include <Header/NRE_Math.hpp>
    
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
             * @class VoxelTypes
             * @brief Store every voxel's types information
             */
            class VoxelTypes {
                public :    // Static
                
                    enum VoxelType {
                        OCEAN,
                        BEACH,
                        SCORCHED,
                        BARE,
                        TUNDRA,
                        SNOW,
                        TEMPERATE_DESERT,
                        SHRUBLAND,
                        TAIGA,
                        GRASSLAND,
                        TEMPERATE_DECIDUOUS_FOREST,
                        TEMPERATE_RAIN_FOREST,
                        SUBTROPICAL_DESERT,
                        TROPICAL_SEASONAL_FORET,
                        TROPICAL_RAIN_FOREST,
                        
                        VOXEL_TYPE_NUM
                    };
                    
                    static constexpr Math::Vector3D<float> VOXEL_COLORS[VOXEL_TYPE_NUM] = {
                        {1.0, 1.0, 1.0},
                        {0.57, 0.52, 0.46},
                        {0.33, 0.33, 0.33},
                        {0.53, 0.53, 0.53},
                        {0.73, 0.73, 0.67},
                        {0.87, 0.87, 0.90},
                        {0.78, 0.82, 0.61},
                        {0.53, 0.60, 0.46},
                        {0.60, 0.66, 0.46},
                        {0.53, 0.67, 0.33},
                        {0.40, 0.58, 0.35},
                        {0.26, 0.53, 0.33},
                        {0.82, 0.72, 0.54},
                        {0.34, 0.60, 0.26},
                        {0.20, 0.46, 0.33},
                    };
                    
                    static constexpr float VOXEL_ROUGHNESS[VOXEL_TYPE_NUM] = {
                        0.1f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                        0.9f,
                    };
                    
                    static constexpr float VOXEL_METALLICS[VOXEL_TYPE_NUM] = {
                        0.9f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                        0.1f,
                    };
            };
        }
    }