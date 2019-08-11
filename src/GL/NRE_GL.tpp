
    /**
     * @file GL/NRE_GL.cpp
     * @brief Implementation of NearlyRealEngine's GL Functions
     * @author Louis ABEL
     * @date 11/08/2019
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace GL {

            inline void clearColor(float r, float g, float b, float a) {
                glClearColor(r, g, b, a);
            }

            inline void clearColor(Math::Vector4D<float> const& color) {
                glClearColor(color.getR(), color.getG(), color.getB(), color.getA());
            }

            inline void clearColor(Math::Vector3D<float> const& color, float a) {
                glClearColor(color.getR(), color.getG(), color.getB(), a);
            }

        }
    }
