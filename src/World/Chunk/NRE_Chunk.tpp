
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
    
             inline Voxel const& Chunk::getVoxel(std::size_t index) const {
                 return voxels[index];
             }
    
             inline Voxel const& Chunk::getVoxel(std::size_t x, std::size_t y, std::size_t z) const {
                 return getVoxel(y * VOXELS_LAYER_AREA + z * VOXELS_LAYER_WIDTH + x);
             }
    
             inline Voxel const& Chunk::getVoxel(Math::Point3D<std::size_t> const& p) const {
                 return getVoxel(p.getX(), p.getY(), p.getZ());
             }
    
             inline Voxel& Chunk::getVoxel(std::size_t index) {
                 return voxels[index];
             }
    
             inline Voxel& Chunk::getVoxel(std::size_t x, std::size_t y, std::size_t z) {
                 return getVoxel(y * VOXELS_LAYER_AREA + z * VOXELS_LAYER_WIDTH + x);
             }
    
             inline Voxel& Chunk::getVoxel(Math::Point3D<std::size_t> const& p) {
                 return getVoxel(p.getX(), p.getY(), p.getZ());
             }
    
             inline Math::Vector3D<float> Chunk::getGradient(std::size_t x, std::size_t y, std::size_t z) const {
                 float vXN = (x == 0     ) ? (neighbors[LEFT  ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[LEFT  ]->getVoxel(SIZE_X - 1, y         , z         ).getIsoValue() : getVoxel(x - 1, y    , z).getIsoValue();
                 float vXP = (x == SIZE_X) ? (neighbors[RIGHT ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[RIGHT ]->getVoxel(1         , y         , z         ).getIsoValue() : getVoxel(x + 1, y    , z).getIsoValue();
                 float vYN = (y == 0     ) ? (neighbors[BOTTOM] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[BOTTOM]->getVoxel(x         , SIZE_Y - 1, z         ).getIsoValue() : getVoxel(x    , y - 1, z).getIsoValue();
                 float vYP = (y == SIZE_Y) ? (neighbors[TOP   ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[TOP   ]->getVoxel(x         , 1         , z         ).getIsoValue() : getVoxel(x    , y + 1, z).getIsoValue();
                 float vZN = (z == 0     ) ? (neighbors[BACK  ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[BACK  ]->getVoxel(x         , y         , SIZE_Z - 1).getIsoValue() : getVoxel(x    , y    , z - 1).getIsoValue();
                 float vZP = (z == SIZE_Z) ? (neighbors[FRONT ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[FRONT ]->getVoxel(x         , y         , 1         ).getIsoValue() : getVoxel(x    , y    , z + 1).getIsoValue();
                 return Math::Vector3D<float>(vXP - vXN, vYP - vYN, vZP - vZN).normalize();
             }
    
             inline Math::Vector3D<float> Chunk::getGradient(Math::Point3D<std::size_t> const& p) const {
                 return getGradient(p.getX(), p.getY(), p.getZ());
             }

             inline void Chunk::setPosition(Math::Point3D<int> const& p) {
                 position = p;
             }
             
             inline void Chunk::setNeighbor(Chunk const& n, std::size_t index) {
                 neighbors[index] = &n;
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
