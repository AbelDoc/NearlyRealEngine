
    /**
     * @file NRE_WaterChunk.tpp
     * @brief Implementation of Engine's World's Object : WaterChunk
     * @author Louis ABEL
     * @date 13/02/2020
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             inline WaterChunk::WaterChunk(Chunk* p) : parent(p) {
             }
             
             inline Chunk const& WaterChunk::getParent() const {
                 return *parent;
             }
    
             inline Chunk& WaterChunk::getParent() {
                 return *parent;
             }
             
             inline void WaterChunk::setParent(Chunk* p) {
                 parent = p;
             }

             inline typename Chunk::Iterator WaterChunk::begin() {
                 return voxels.begin();
             }

             inline typename Chunk::ConstIterator WaterChunk::begin() const {
                 return voxels.begin();
             }

             inline typename Chunk::ConstIterator WaterChunk::cbegin() const {
                 return voxels.cbegin();
             }

             inline typename Chunk::Iterator WaterChunk::end() {
                 return voxels.end();
             }

             inline typename Chunk::ConstIterator WaterChunk::end() const {
                 return voxels.end();
             }

             inline typename Chunk::ConstIterator WaterChunk::cend() const {
                 return voxels.cend();
             }

             inline float& WaterChunk::operator [](std::size_t index) {
                 return voxels[index];
             }

             inline float const& WaterChunk::operator [](std::size_t index) const {
                 return voxels[index];
             }

             inline Utility::String WaterChunk::toString() const {
                 return voxels.toString();
             }
         }
     }
