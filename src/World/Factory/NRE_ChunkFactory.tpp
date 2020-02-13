
    /**
     * @file NRE_ChunkFactory.tpp
     * @brief Implementation of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             inline void ChunkFactory::createSphere(Chunk& target) {
                 std::size_t index = 0;
                 for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                     for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                         for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                             target[index++] = static_cast <float> (Math::Vector3D<int>(static_cast <int> (x - Chunk::SIZE_X / 2) + target.getPosition().getX(),
                                                                                        static_cast <int> (y - Chunk::SIZE_Y / 2) + target.getPosition().getY(),
                                                                                        static_cast <int> (z - Chunk::SIZE_Z / 2) + target.getPosition().getZ()).normSquared());
                         }
                     }
                 }
             }

             inline void ChunkFactory::createTerrain(Chunk& target, WaterChunk& water) {
                 FastNoise generator(16'09'2019);

                 for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                     float nz = static_cast <float> (z) + static_cast <float> (target.getPosition().getZ());
                     for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                         float nx = static_cast <float> (x) + static_cast <float> (target.getPosition().getX());
                         float e = 1.0f * generator.GetNoise(1  * nx, 1  * nz)
                                +  0.5f * generator.GetNoise(2  * nx, 2  * nz)
                                + 0.25f * generator.GetNoise(4  * nx, 4  * nz)
                                + 0.13f * generator.GetNoise(8  * nx, 8  * nz)
                                + 0.06f * generator.GetNoise(16 * nx, 16 * nz)
                                + 0.03f * generator.GetNoise(32 * nx, 32 * nz);
                         e /= (1.00f + 0.5f + 0.25f + 0.13f + 0.06f + 0.03f);
                         e = (e / 2.0f) + 0.5f;
                         e = static_cast <float> (std::pow(e, 2.0f));
                         e *= Chunk::SIZE_Y * World::SIZE_Y;
                         for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                             float ny = static_cast <float> (y) + static_cast <float> (target.getPosition().getY());
                             std::size_t index = y * Chunk::VOXELS_LAYER_AREA + z * Chunk::VOXELS_LAYER_WIDTH + x;
                             target[index] = (ny - e) + 0.0001f;
                             if (e < 5) {
                                 water[index] = ny - 0.0001f;
                             }
                         }
                     }
                 }
             }

         }
     }
