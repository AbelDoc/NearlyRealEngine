    
    /**
     * @file NRE_VoxelsContainer.tpp
     * @brief Implementation of Engine's World's Object : VoxelsContainer
     * @author Louis ABEL
     * @date 20/07/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace World {
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel const& VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(std::size_t index) const {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel const& VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(std::size_t x, std::size_t y, std::size_t z) const {
                return getVoxel(y * VOXELS_LAYER_AREA + z * VOXELS_LAYER_WIDTH + x);
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel const& VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(Math::Point3D<std::size_t> const& p) const {
                return getVoxel(p.getX(), p.getY(), p.getZ());
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel& VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(std::size_t index) {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel& VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(std::size_t x, std::size_t y, std::size_t z) {
                return getVoxel(y * VOXELS_LAYER_AREA + z * VOXELS_LAYER_WIDTH + x);
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel& VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(Math::Point3D<std::size_t> const& p) {
                return getVoxel(p.getX(), p.getY(), p.getZ());
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Math::Vector3D<float> VoxelsContainer<SizeX, SizeY, SizeZ>::getGradient(std::size_t x, std::size_t y, std::size_t z) const {
                float vXN = (x == 0     ) ? (neighbors[LEFT  ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[LEFT  ]->getVoxel(SIZE_X - 1, y         , z         ).getIsoValue() : getVoxel(x - 1, y    , z).getIsoValue();
                float vXP = (x == SIZE_X) ? (neighbors[RIGHT ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[RIGHT ]->getVoxel(1         , y         , z         ).getIsoValue() : getVoxel(x + 1, y    , z).getIsoValue();
                float vYN = (y == 0     ) ? (neighbors[BOTTOM] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[BOTTOM]->getVoxel(x         , SIZE_Y - 1, z         ).getIsoValue() : getVoxel(x    , y - 1, z).getIsoValue();
                float vYP = (y == SIZE_Y) ? (neighbors[TOP   ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[TOP   ]->getVoxel(x         , 1         , z         ).getIsoValue() : getVoxel(x    , y + 1, z).getIsoValue();
                float vZN = (z == 0     ) ? (neighbors[BACK  ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[BACK  ]->getVoxel(x         , y         , SIZE_Z - 1).getIsoValue() : getVoxel(x    , y    , z - 1).getIsoValue();
                float vZP = (z == SIZE_Z) ? (neighbors[FRONT ] == nullptr) ? getVoxel(x, y, z).getIsoValue() : neighbors[FRONT ]->getVoxel(x         , y         , 1         ).getIsoValue() : getVoxel(x    , y    , z + 1).getIsoValue();
                return Math::Vector3D<float>(vXP - vXN, vYP - vYN, vZP - vZN).normalize();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Math::Vector3D<float> VoxelsContainer<SizeX, SizeY, SizeZ>::getGradient(Math::Point3D<std::size_t> const& p) const {
                return getGradient(p.getX(), p.getY(), p.getZ());
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline void VoxelsContainer<SizeX, SizeY, SizeZ>::setNeighbor(VoxelsContainer const& n, std::size_t index) {
                neighbors[index] = &n;
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline typename VoxelsContainer<SizeX, SizeY, SizeZ>::Iterator VoxelsContainer<SizeX, SizeY, SizeZ>::begin() {
                return voxels.begin();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline typename VoxelsContainer<SizeX, SizeY, SizeZ>::ConstIterator VoxelsContainer<SizeX, SizeY, SizeZ>::begin() const {
                return voxels.begin();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline typename VoxelsContainer<SizeX, SizeY, SizeZ>::ConstIterator VoxelsContainer<SizeX, SizeY, SizeZ>::cbegin() const {
                return voxels.cbegin();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline typename VoxelsContainer<SizeX, SizeY, SizeZ>::Iterator VoxelsContainer<SizeX, SizeY, SizeZ>::end() {
                return voxels.end();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline typename VoxelsContainer<SizeX, SizeY, SizeZ>::ConstIterator VoxelsContainer<SizeX, SizeY, SizeZ>::end() const {
                return voxels.end();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline typename VoxelsContainer<SizeX, SizeY, SizeZ>::ConstIterator VoxelsContainer<SizeX, SizeY, SizeZ>::cend() const {
                return voxels.cend();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel& VoxelsContainer<SizeX, SizeY, SizeZ>::operator [](std::size_t index) {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Voxel const& VoxelsContainer<SizeX, SizeY, SizeZ>::operator [](std::size_t index) const {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Utility::String VoxelsContainer<SizeX, SizeY, SizeZ>::toString() const {
                return voxels.toString();
            }
            
        }
    }