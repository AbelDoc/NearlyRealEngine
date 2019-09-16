
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

             inline std::size_t Chunk::getVolume() const {
                 return static_cast <std::size_t> ((SIZE_X / resolution) * (SIZE_Y / resolution) * (SIZE_Z / resolution));
             }

             inline std::size_t Chunk::getVoxelsVolume() const {
                 return static_cast <std::size_t> (((SIZE_X / resolution) + 1) * ((SIZE_Y / resolution) + 1) * ((SIZE_Z / resolution) + 1));
             }

             inline std::size_t Chunk::getVoxelsLayerSize() const {
                 return static_cast <std::size_t> (((SIZE_X / resolution) + 1) * ((SIZE_Z / resolution) + 1));
             }

             inline std::size_t Chunk::getVoxelsLayerWidth() const {
                 return static_cast <std::size_t> ((SIZE_X / resolution) + 1);
             }

             inline float Chunk::getResolution() const {
                 return resolution;
             }

             inline void Chunk::changeResolution(float res) {
                 resolution = res;

                 cells.clear();
                 cells.reserve(getVolume());
             }

             inline void Chunk::emplaceBack(CellCorners corners) {
                 cells.emplaceBack(corners);
             }

             inline Cell& Chunk::operator [](std::size_t index) {
                 return cells[index];
             }

             inline Cell const& Chunk::operator [](std::size_t index) const {
                 return cells[index];
             }

             inline Utility::String Chunk::toString() const {
                 return cells.toString();
             }

             inline std::ostream& operator <<(std::ostream& stream, Chunk const& o) {
                 return stream << o.toString();
             }

         }
     }
