
    /**
     * @file NRE_ChunkFactory.tpp
     * @brief Implementation of Engine's World's Object : ChunkFactory
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             void ChunkFactory::createSphere(Chunk& target, float resolution, float radius) {
                 target.changeResolution(resolution);

                 Utility::Vector<float> voxels;
                 voxels.reserve(target.getVoxelsVolume());

                 for (float y = 0; y <= Chunk::SIZE_Y; y += resolution) {
                     for (float z = 0; z <= Chunk::SIZE_Z; z += resolution) {
                         for (float x = 0; x <= Chunk::SIZE_X; x += resolution) {
                             voxels.emplaceBack(Math::Vector3D<float>(x - Chunk::SIZE_X / 2, y - Chunk::SIZE_Y / 2, z - Chunk::SIZE_Z / 2).normSquared());
                         }
                     }
                 }

                 computeCells(target, voxels, radius * radius);
             }

             void ChunkFactory::createTerrain(Chunk& target, float resolution) {
                 target.changeResolution(resolution);

                 FastNoise generator(16'09'2019);

                 Utility::Vector<float> voxels;
                 voxels.reserve(target.getVoxelsVolume());

                 for (float y = 0; y <= Chunk::SIZE_Y; y += resolution) {
                     for (float z = 0; z <= Chunk::SIZE_Z; z += resolution) {
                         for (float x = 0; x <= Chunk::SIZE_X; x += resolution) {
                             float e = generator.GetNoise(x + static_cast <float> (target.getPosition().getX()),
                                                          z + static_cast <float> (target.getPosition().getZ()));
                             float elevation = (e / 2.0f + 0.5f) * Chunk::SIZE_Y;
                             voxels.emplaceBack((y >= elevation) ? (1.0f) : (0.0f));
                         }
                     }
                 }

                 computeCells(target, voxels, 0.5f);
             }

             void ChunkFactory::computeCells(Chunk& target, Utility::Vector<float> const& voxels, float threshold) {
                 std::size_t index = 0;
                 std::size_t topLayerIndex;

                 for (float y = 0; y <= Chunk::SIZE_Y - target.getResolution(); y += target.getResolution()) {
                     for (float z = 0; z <= Chunk::SIZE_Z - target.getResolution(); z += target.getResolution()) {
                         for (float x = 0; x <= Chunk::SIZE_X - target.getResolution(); x += target.getResolution()) {
                             CellCorners corners = 0b00000000;
                             topLayerIndex = index + target.getVoxelsLayerSize();
                             if (voxels[index] < threshold) {
                                 corners |= 0b00000001;
                             }
                             if (voxels[index + target.getVoxelsLayerWidth()] < threshold) {
                                 corners |= 0b00000010;
                             }
                             if (voxels[index + target.getVoxelsLayerWidth() + 1] < threshold) {
                                 corners |= 0b00000100;
                             }
                             if (voxels[index + 1] < threshold) {
                                 corners |= 0b00001000;
                             }
                             if (voxels[topLayerIndex] < threshold) {
                                 corners |= 0b00010000;
                             }
                             if (voxels[topLayerIndex + target.getVoxelsLayerWidth()] < threshold) {
                                 corners |= 0b00100000;
                             }
                             if (voxels[topLayerIndex + target.getVoxelsLayerWidth() + 1] < threshold) {
                                 corners |= 0b01000000;
                             }
                             if (voxels[topLayerIndex + 1] < threshold) {
                                 corners |= 0b10000000;
                             }
                             target.emplaceBack(corners);
                             index++;
                         }
                         index++;
                     }
                     index += target.getVoxelsLayerWidth();
                 }
             }

         }
     }
