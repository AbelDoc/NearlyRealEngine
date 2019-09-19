
    /**
     * @file NRE_World.tpp
     * @brief Implementation of Engine's World's Object : World
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

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
