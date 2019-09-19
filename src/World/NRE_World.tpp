
    /**
     * @file NRE_World.tpp
     * @brief Implementation of Engine's World's Object : World
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             inline World::World() : chunks(new Chunk[NB_CHUNKS]) {
                 std::size_t index = 0;
                 for (int y = 0; y < SIZE_Y; y++) {
                     for (int z = -H_SIZE_Z; z <= H_SIZE_Z; z++) {
                         for (int x = -H_SIZE_X; x <= H_SIZE_X; x++) {
                             Chunk& chunk = chunks[index++];
                             chunk.setPosition({static_cast <int> (Chunk::SIZE_X) * x, static_cast <int> (Chunk::SIZE_Y) * y, static_cast <int> (Chunk::SIZE_Z) * z});
                             ChunkFactory::createTerrain(chunk);
                         }
                     }
                 }
             }

             inline typename World::Iterator World::begin() {
                 return chunks;
             }

             inline typename World::ConstIterator World::begin() const {
                 return chunks;
             }

             inline typename World::ConstIterator World::cbegin() const {
                 return begin();
             }

             inline typename World::Iterator World::end() {
                 return chunks + NB_CHUNKS;
             }

             inline typename World::ConstIterator World::end() const {
                 return chunks + NB_CHUNKS;
             }

             inline typename World::ConstIterator World::cend() const {
                 return end();
             }

             inline World::World(World && w) : chunks(w.chunks) {
                 w.chunks = nullptr;
             }

             inline World::~World() {
                 delete[] chunks;
                 chunks = nullptr;
             }

             inline Chunk& World::operator [](std::size_t index) {
                 return chunks[index];
             }

             inline Chunk const& World::operator [](std::size_t index) const {
                 return chunks[index];
             }

             inline World& World::operator=(World && w) {
                 if (this != &w) {
                     chunks = w.chunks;
                     w.chunks = nullptr;
                 }
                 return *this;
             }


         }
     }
