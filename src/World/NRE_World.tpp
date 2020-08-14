
    /**
     * @file NRE_World.tpp
     * @brief Implementation of Engine's World's Object : World
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             inline World::World(World && w) : chunks(w.chunks) {
                 w.chunks = nullptr;
             }

             inline World::~World() {
                 delete[] chunks;
                 chunks = nullptr;
             }
    
             inline Chunk const& World::getChunk(std::size_t index) const {
                 return chunks[index];
             }
    
             inline Chunk const& World::getChunk(std::size_t x, std::size_t y, std::size_t z) const {
                 return getChunk(y * SIZE_X * SIZE_Z + z * SIZE_X + x);
             }
    
             inline Chunk const& World::getChunk(Math::Point3D<std::size_t> const& p) const {
                 return getChunk(p.getX(), p.getY(), p.getZ());
             }
             
             inline Chunk& World::getChunk(std::size_t index) {
                 return chunks[index];
             }
    
             inline Chunk& World::getChunk(std::size_t x, std::size_t y, std::size_t z) {
                 return getChunk(y * SIZE_X * SIZE_Z + z * SIZE_X + x);
             }
             
             inline Chunk& World::getChunk(Math::Point3D<std::size_t> const& p) {
                return getChunk(p.getX(), p.getY(), p.getZ());
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

             inline Chunk& World::operator [](std::size_t index) {
                 return getChunk(index);
             }

             inline Chunk const& World::operator [](std::size_t index) const {
                 return getChunk(index);
             }

             inline World& World::operator=(World && w) {
                 if (this != &w) {
                     chunks = w.chunks;
                     w.chunks = nullptr;
                 }
                 return *this;
             }
             
             inline void World::assignNeighbors(Chunk& chunk, int x, int y, int z) {
                 if (x > -H_SIZE_X) {
                    chunk.setNeighbor(getChunk(x + H_SIZE_X - 1, y, z + H_SIZE_Z), Chunk::NeighborSide::LEFT);
                 }
                 if (x <  H_SIZE_X) {
                     chunk.setNeighbor(getChunk(x + H_SIZE_X + 1, y, z + H_SIZE_Z), Chunk::NeighborSide::RIGHT);
                 }
                 if (z > -H_SIZE_Z) {
                     chunk.setNeighbor(getChunk(x + H_SIZE_X, y, z + H_SIZE_Z - 1), Chunk::NeighborSide::BACK);
                 }
                 if (z <  H_SIZE_Z) {
                     chunk.setNeighbor(getChunk(x + H_SIZE_X, y, z + H_SIZE_Z + 1), Chunk::NeighborSide::FRONT);
                 }
                 if (y > 0) {
                     chunk.setNeighbor(getChunk(x + H_SIZE_X, y - 1, z + H_SIZE_Z), Chunk::NeighborSide::BOTTOM);
                 }
                 if (y < SIZE_Y - 1) {
                     chunk.setNeighbor(getChunk(x + H_SIZE_X, y + 1, z + H_SIZE_Z), Chunk::NeighborSide::TOP);
                 }
             }


         }
     }
