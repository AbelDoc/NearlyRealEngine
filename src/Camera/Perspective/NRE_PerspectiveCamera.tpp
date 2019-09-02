
    /**
     * @file NRE_PerspectiveCamera.tpp
     * @brief Implementation of Engine's Camera's Object : PerspectiveCamera
     * @author Louis ABEL
     * @date 18/11/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Camera {

            PerspectiveCamera::PerspectiveCamera(float s, Math::Point3D<float> const& e, Math::Point3D<float> const& c, float fieldOfView, float r, Math::Vector2D<float> const& d) : Camera(s, e, c), frustum(fieldOfView, r, d) {
                computePlane();
                computeProjectionMatrix();
            }

            void PerspectiveCamera::computeVector() {
                Camera::computeVector();
                computePlane();
            }

            void PerspectiveCamera::resize(Math::Vector2D<unsigned int> const& size) {
                frustum.resize(size, getEye(), getForward(), getLeft(), getUp());
                computeProjectionMatrix();
            }

            void PerspectiveCamera::computeProjectionMatrix() {
                frustum.computeProjectionMatrix(getProjection());
            }

            void PerspectiveCamera::computePlane() {
                frustum.computePlane(getEye(), getForward(), getLeft(), getUp());
            }

        }
    }
