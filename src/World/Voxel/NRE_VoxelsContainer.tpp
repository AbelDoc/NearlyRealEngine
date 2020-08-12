    
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
            inline float VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(std::size_t index) const {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline float VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(std::size_t x, std::size_t y, std::size_t z) const {
                return getVoxel(y * VOXELS_LAYER_AREA + z * VOXELS_LAYER_WIDTH + x);
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline float VoxelsContainer<SizeX, SizeY, SizeZ>::getVoxel(Math::Point3D<std::size_t> const& p) const {
                return getVoxel(p.getX(), p.getY(), p.getZ());
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Math::Vector3D<float> VoxelsContainer<SizeX, SizeY, SizeZ>::getGradient(std::size_t x, std::size_t y, std::size_t z) const {
                float vXN = (x == 0     ) ? (neighbors[LEFT  ] == nullptr) ? getVoxel(x, y, z) : neighbors[LEFT  ]->getVoxel(SIZE_X - 1, y         , z         ) : getVoxel(x - 1, y    , z);
                float vXP = (x == SIZE_X) ? (neighbors[RIGHT ] == nullptr) ? getVoxel(x, y, z) : neighbors[RIGHT ]->getVoxel(1         , y         , z         ) : getVoxel(x + 1, y    , z);
                float vYN = (y == 0     ) ? (neighbors[BOTTOM] == nullptr) ? getVoxel(x, y, z) : neighbors[BOTTOM]->getVoxel(x         , SIZE_Y - 1, z         ) : getVoxel(x    , y - 1, z);
                float vYP = (y == SIZE_Y) ? (neighbors[TOP   ] == nullptr) ? getVoxel(x, y, z) : neighbors[TOP   ]->getVoxel(x         , 1         , z         ) : getVoxel(x    , y + 1, z);
                float vZN = (z == 0     ) ? (neighbors[BACK  ] == nullptr) ? getVoxel(x, y, z) : neighbors[BACK  ]->getVoxel(x         , y         , SIZE_Z - 1) : getVoxel(x    , y    , z - 1);
                float vZP = (z == SIZE_Z) ? (neighbors[FRONT ] == nullptr) ? getVoxel(x, y, z) : neighbors[FRONT ]->getVoxel(x         , y         , 1         ) : getVoxel(x    , y    , z + 1);
                return Math::Vector3D<float>(vXP - vXN, vYP - vYN, vZP - vZN).normalize();
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Math::Vector3D<float> VoxelsContainer<SizeX, SizeY, SizeZ>::getGradient(Math::Point3D<std::size_t> const& p) const {
                return getGradient(p.getX(), p.getY(), p.getZ());
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline void VoxelsContainer<SizeX, SizeY, SizeZ>::setVoxel(std::size_t index, float v) {
                voxels[index] = v;
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline void VoxelsContainer<SizeX, SizeY, SizeZ>::setVoxel(std::size_t x, std::size_t y, std::size_t z, float v) {
                setVoxel(y * VOXELS_LAYER_AREA + z * VOXELS_LAYER_WIDTH + x, v);
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline void VoxelsContainer<SizeX, SizeY, SizeZ>::setVoxel(Math::Point3D<std::size_t> const& p, float v) {
                setVoxel(p.getX(), p.getY(), p.getZ(), v);
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
            inline float& VoxelsContainer<SizeX, SizeY, SizeZ>::operator [](std::size_t index) {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline float const& VoxelsContainer<SizeX, SizeY, SizeZ>::operator [](std::size_t index) const {
                return voxels[index];
            }
    
            template <std::size_t SizeX, std::size_t SizeY, std::size_t SizeZ>
            inline Utility::String VoxelsContainer<SizeX, SizeY, SizeZ>::toString() const {
                return voxels.toString();
            }
            
        }
    }