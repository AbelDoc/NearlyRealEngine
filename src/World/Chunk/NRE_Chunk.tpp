
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
    
             inline typename Chunk::VoxelsContainer& Chunk::getTerrainVoxels() {
                 return terrain;
             }
             
             inline typename Chunk::VoxelsContainer const& Chunk::getTerrainVoxels() const {
                 return terrain;
             }
    
             inline typename Chunk::VoxelsContainer& Chunk::getWaterVoxels() {
                 return water;
             }
    
             inline typename Chunk::VoxelsContainer const& Chunk::getWaterVoxels() const {
                 return water;
             }

             inline void Chunk::setPosition(Math::Point3D<int> const& p) {
                 position = p;
             }
             
             inline void Chunk::setNeighbor(Chunk const& n, std::size_t index) {
                 terrain.setNeighbor(n.terrain, index);
                 water.setNeighbor(n.water, index);
             }

             inline Utility::String Chunk::toString() const {
                 return "Position : " + position.toString() + "\nTerrain : " + terrain.toString() + "\nWater : " + water.toString();
             }
         }
     }
