
    /**
     * @file NRE_ChunkFactory.tpp
     * @brief Implementation of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             void ChunkFactory::createSphere(Chunk& target) {
                 std::size_t index = 0;
                 for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                     for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                         for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                             target[index++] = Math::Vector3D<int>(static_cast <int> (x - Chunk::SIZE_X / 2) + target.getPosition().getX(),
                                                                   static_cast <int> (y - Chunk::SIZE_Y / 2) + target.getPosition().getY(),
                                                                   static_cast <int> (z - Chunk::SIZE_Z / 2) + target.getPosition().getZ()).normSquared();
                         }
                     }
                 }
             }

             void ChunkFactory::createTerrain(Chunk& target) {
                 FastNoise generator(16'09'2019);

                 std::size_t index = 0;
                 for (std::size_t y = 0; y <= Chunk::SIZE_Y; ++y) {
                     for (std::size_t z = 0; z <= Chunk::SIZE_Z; ++z) {
                         for (std::size_t x = 0; x <= Chunk::SIZE_X; ++x) {
                             float nx = static_cast <float> (x) + static_cast <float> (target.getPosition().getX());
                             float ny = static_cast <float> (y) + static_cast <float> (target.getPosition().getY()) - 0.5f;
                             float nz = static_cast <float> (z) + static_cast <float> (target.getPosition().getZ());
                             float e = 1.0f * generator.GetNoise(1 * nx, 1 * nz)
                                    +  0.5f * generator.GetNoise(2 * nx, 2 * nz)
                                    + 0.25f * generator.GetNoise(4 * nx, 4 * nz);
                             e /= (1.0f + 0.5f + 0.25f);
                             e = (e / 2.0f) + 0.5f;
                             e = static_cast <float> (std::pow(e, 1.74f));
                             e *= Chunk::SIZE_Y;
                             target[index++] = ny - e;
                         }
                     }
                 }
             }

         }
     }
