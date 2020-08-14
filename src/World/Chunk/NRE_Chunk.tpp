
    /**
     * @file NRE_Chunk.tpp
     * @brief Implementation of Engine's World's Object : Chunk
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

     namespace NRE {
         namespace World {

             inline Chunk::Chunk(Math::Point3D<int> const& pos) : position(pos) {
             }

             inline Math::Point3D<int> const& Chunk::getPosition() const {
                 return position;
             }
    
             inline typename Chunk::VoxelsContainer& Chunk::getVoxels() {
                 return voxels;
             }
             
             inline typename Chunk::VoxelsContainer const& Chunk::getVoxels() const {
                 return voxels;
             }

             inline void Chunk::setPosition(Math::Point3D<int> const& p) {
                 position = p;
             }
             
             inline void Chunk::setNeighbor(Chunk const& n, std::size_t index) {
                 voxels.setNeighbor(n.voxels, index);
             }
    
             inline typename Chunk::Iterator Chunk::begin() {
                 return voxels.begin();
             }
    
             inline typename Chunk::ConstIterator Chunk::begin() const {
                 return voxels.begin();
             }
    
             inline typename Chunk::ConstIterator Chunk::cbegin() const {
                 return voxels.cbegin();
             }
    
             inline typename Chunk::Iterator Chunk::end() {
                 return voxels.end();
             }
    
             inline typename Chunk::ConstIterator Chunk::end() const {
                 return voxels.end();
             }
    
             inline typename Chunk::ConstIterator Chunk::cend() const {
                 return voxels.cend();
             }
    
             inline Voxel& Chunk::operator [](std::size_t index) {
                 return voxels[index];
             }
    
             inline Voxel const& Chunk::operator [](std::size_t index) const {
                 return voxels[index];
             }

             inline Utility::String Chunk::toString() const {
                 return "Position : " + position.toString() + "\nVoxels : " + voxels.toString();
             }
         }
     }
