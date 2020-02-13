
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
                 return waters;
             }

             inline typename World::ConstIterator World::begin() const {
                 return waters;
             }

             inline typename World::ConstIterator World::cbegin() const {
                 return begin();
             }

             inline typename World::Iterator World::end() {
                 return waters + NB_CHUNKS;
             }

             inline typename World::ConstIterator World::end() const {
                 return waters + NB_CHUNKS;
             }

             inline typename World::ConstIterator World::cend() const {
                 return end();
             }

             inline World::World(World && w) : chunks(w.chunks), waters(w.waters) {
                 w.chunks = nullptr;
                 w.waters = nullptr;
             }

             inline World::~World() {
                 delete[] chunks;
                 delete[] waters;
                 chunks = nullptr;
                 waters = nullptr;
             }

             inline WaterChunk& World::operator [](std::size_t index) {
                 return waters[index];
             }

             inline WaterChunk const& World::operator [](std::size_t index) const {
                 return waters[index];
             }

             inline World& World::operator=(World && w) {
                 if (this != &w) {
                     chunks = w.chunks;
                     waters = w.waters;
                     w.chunks = nullptr;
                     w.waters = nullptr;
                 }
                 return *this;
             }


         }
     }
