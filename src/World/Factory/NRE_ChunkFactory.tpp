
    /**
     * @file NRE_ChunkFactory.tpp
     * @brief Implementation of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {
             namespace Factory {
    
                 inline void createTerrain(Chunk& target, Math::Vector3D<float> const& worldSize, Math::Vector3D<float> const&) {
                     FastNoise elevation(16'09'2019);
                     FastNoise moisture(14'08'2020);
        
                     for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                         float nz = static_cast <float> (z) + static_cast <float> (target.getPosition().getZ());
                         for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                             float nx = static_cast <float> (x) + static_cast <float> (target.getPosition().getX());
                             float e = 0.85f * (elevation.GetNoise(1 * nx, 1 * nz) / 2.f + 0.5f)
                                       + 0.40f * (elevation.GetNoise(2 * nx, 2 * nz) / 2.f + 0.5f)
                                       + 0.15f * (elevation.GetNoise(4 * nx, 4 * nz) / 2.f + 0.5f)
                                       + 0.05f * (elevation.GetNoise(16 * nx, 16 * nz) / 2.f + 0.5f);
                             e /= (0.85f + 0.40f + 0.15f + 0.05f);
                             e = static_cast <float> (std::pow(e, 1.40f));
                             float biasedE = e * Chunk::SIZE_Y * static_cast <float> (worldSize.getY());
                
                             float m = 1.00f * (moisture.GetNoise(1 * nx, 1 * nz) / 2.f + 0.5f)
                                       + 0.50f * (moisture.GetNoise(2 * nx, 2 * nz) / 2.f + 0.5f);
                             m /= (1.00f + 0.50f);
                
                             for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                                 float ny = static_cast <float> (y) + static_cast <float> (target.getPosition().getY());
                                 std::size_t index = y * Chunk::VOXELS_LAYER_AREA + z * Chunk::VOXELS_LAYER_WIDTH + x;
                                 if (e < 0.18f) {
                                     target[index].setIsoValue(ny - 0.18f * Chunk::SIZE_Y * static_cast <float> (worldSize.getY()) + 0.0001f);
                                 } else {
                                     target[index].setIsoValue(ny - biasedE + 0.0001f);
                                 }
                                 target[index].setType(createBiome(e, m));
                             }
                         }
                     }
                 }
    
                 inline void createAsteroid(Chunk& target, Math::Vector3D<float> const& worldSize, Math::Vector3D<float> const& worldOffset) {
                     FastNoise elevation(23'08'2020);
                     Math::Vector3D<float> asteroidHalfSize = Math::Vector3D<float>(Chunk::SIZE_X, Chunk::SIZE_Y, Chunk::SIZE_Z) / 2;
                     float maxDist = static_cast <float> ((worldSize * asteroidHalfSize).norm());
                     asteroidHalfSize.setY(worldSize.getY() * asteroidHalfSize.getY());
                     
                     for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                         float nz = static_cast <float> (z) + static_cast <float> (target.getPosition().getZ());
                         for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                             float nx = static_cast <float> (x) + static_cast <float> (target.getPosition().getX());
                             for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                                 float ny = static_cast <float> (y) + static_cast <float> (target.getPosition().getY());
                                 float distFromCenter = static_cast <float> ((worldOffset + asteroidHalfSize).distance(Math::Vector3D<float>(nx, ny, nz)) / maxDist);

                                 float e = 1.00f * (elevation.GetNoise( 1 * nx,  1 * ny,  1 * nz) / 2.f + 0.5f)
                                           + 0.40f * (elevation.GetNoise( 2 * nx,  2 * ny,  2 * nz) / 2.f + 0.5f)
                                           + 0.30f * (elevation.GetNoise( 4 * nx,  4 * ny,  4 * nz) / 2.f + 0.5f)
                                           + 0.05f * (elevation.GetNoise(16 * nx, 16 * ny, 16 * nz) / 2.f + 0.5f);
                                 e /= (1.00f + 0.40f + 0.30f + 0.05f);
                                 e = static_cast <float> (std::pow(e, 1.80f));
                                 
                                 target.getVoxel(x, y, z).setIsoValue(distFromCenter + e + 0.0001f);
                                 target.getVoxel(x, y, z).setType(createBiome(distFromCenter, distFromCenter + e));
                             }
                         }
                     }
                 }
    
                 inline Voxel::VoxelType createBiome(float e, float m) {
                     if (e < 0.18f) {
                         return 0;
                     }
                     if (e < 0.2f) {
                         return 1;
                     }
                     if (e > 0.8f) {
                         if (m < 0.1f) {
                             return 2;
                         }
                         if (m < 0.2f) {
                             return 3;
                         }
                         if (m < 0.5f) {
                             return 4;
                         }
                         return 5;
                     }
                     if (e > 0.6f) {
                         if (m < 0.33f) {
                             return 6;
                         }
                         if (m < 0.66f) {
                             return 7;
                         }
                         return 8;
                     }
                     if (e > 0.4f) {
                         if (m < 0.16f) {
                             return 6;
                         }
                         if (m < 0.5f) {
                             return 9;
                         }
                         if (m < 0.83f) {
                             return 10;
                         }
                         return 11;
                     }
                     if (m < 0.16f) {
                         return 12;
                     }
                     if (m < 0.33f) {
                         return 9;
                     }
                     if (m < 0.66) {
                         return 13;
                     }
                     return 14;
                 }
             }
         }
     }
