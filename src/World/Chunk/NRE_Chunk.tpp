
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

             inline void Chunk::setPosition(Math::Point3D<int> const& p) {
                 position = p;
             }

             inline float& Chunk::operator [](std::size_t baseIndex) {
                 return voxels[baseIndex];
             }

             inline float const& Chunk::operator [](std::size_t baseIndex) const {
                 return voxels[baseIndex];
             }

             inline Utility::String Chunk::toString() const {
                 return voxels.toString();
             }

             inline std::ostream& operator <<(std::ostream& stream, Chunk const& o) {
                 return stream << o.toString();
             }

         }
     }
