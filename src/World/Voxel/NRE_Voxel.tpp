    
    /**
     * @file NRE_Voxel.tpp
     * @brief Implementation of Engine's World's Object : Voxel
     * @author Louis ABEL
     * @date 13/08/2020
     * @copyright CC-BY-NC-SA
     */
    
    namespace NRE {
        namespace World {
            
            inline Voxel::Voxel(float value, VoxelType t) : isovalue(value), type(t) {
            }
            
            inline float Voxel::getIsoValue() const {
                return isovalue;
            }
            
            inline typename Voxel::VoxelType Voxel::getType() const {
                return type;
            }
            
            inline void Voxel::setIsoValue(float value) {
                isovalue = value;
            }
            
            inline void Voxel::setType(VoxelType t) {
                type = t;
            }
            
            inline Utility::String Voxel::toString() const {
                Utility::String res;
                res.reserve(8);
                return res << isovalue << " -> " << type;
            }
        
        }
    }