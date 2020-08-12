
    /**
     * @file NRE_World.tpp
     * @brief Implementation of Engine's World's Object : World
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    #include "NRE_World.hpp"
    #include "Factory/NRE_ChunkFactory.hpp"

     namespace NRE {
         namespace World {

             World::World() : chunks(new Chunk[NB_CHUNKS]) {
                 std::size_t index = 0;
                 for (int y = 0; y < SIZE_Y; y++) {
                     for (int z = -H_SIZE_Z; z <= H_SIZE_Z; z++) {
                         for (int x = -H_SIZE_X; x <= H_SIZE_X; x++) {
                             Chunk& chunk = chunks[index++];
                             chunk.setPosition({static_cast <int> (Chunk::SIZE_X) * x, static_cast <int> (Chunk::SIZE_Y) * y, static_cast <int> (Chunk::SIZE_Z) * z});
                             assignNeighbors(chunk, x, y, z);
                             ChunkFactory::createTerrain(chunk);
                         }
                     }
                 }
             }

         }
     }
