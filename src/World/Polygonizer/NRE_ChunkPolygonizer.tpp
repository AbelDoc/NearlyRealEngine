
    /**
     * @file NRE_ChunkPolygonizer.tpp
     * @brief Implementation of Engine's World's Object : ChunkPolygonizer
     * @author Louis ABEL
     * @date 12/09/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace World {

            inline Math::Point3D<float> ChunkPolygonizer::interpolateLinearVertex(float threshold, Math::Point3D<float> const& p1, Math::Point3D<float> const& p2, float iso1, float iso2) {
                if (Math::almostEqual(threshold, iso1)) {
                    return(p1);
                }
                if (Math::almostEqual(threshold, iso2)) {
                    return(p2);
                }
                if (Math::almostEqual(iso1, iso2)) {
                    return(p1);
                }
                float mu = (threshold - iso1) / (iso2 - iso1);
                return p1 + (p2 - p1) * mu;
            }

            inline Math::Point3D<float> ChunkPolygonizer::interpolateFlatVertex(float, Math::Point3D<float> const& p1, Math::Point3D<float> const& p2, float, float) {
                return (p1 + p2) * 0.5f;
            }


        }
    }
