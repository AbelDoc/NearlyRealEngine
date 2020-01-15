
    /**
     * @file NRE_PerspectiveCamera.tpp
     * @brief Implementation of Engine's Camera's Object : PerspectiveCamera
     * @author Louis ABEL
     * @date 18/11/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Camera {

            inline PerspectiveCamera::PerspectiveCamera(float s, Math::Angle fieldOfView, float r, Math::Vector2D<float> const& d, Math::Point3D<float> const& e, Math::Vector3D<float> const& u, Math::Angle y, Math::Angle p) : Camera(s, e, u, y, p), frustum(fieldOfView, r, d) {
                computePlane();
                computeProjectionMatrix();
            }
            
            inline Math::Frustum const& PerspectiveCamera::getFrustum() const {
                return frustum;
            }

            inline void PerspectiveCamera::setFov(Math::Angle fieldOfView) {
                frustum.setFov(fieldOfView);
                computePlane();
                computeProjectionMatrix();
            }

            inline void PerspectiveCamera::computeVector() {
                Camera::computeVector();
                computePlane();
            }

            inline void PerspectiveCamera::resize(Math::Vector2D<unsigned int> const& size) {
                frustum.resize(size, getEye(), getForward(), getRight(), getUp());
                computeProjectionMatrix();
            }

            inline void PerspectiveCamera::computeProjectionMatrix() {
                frustum.computeProjectionMatrix(getProjection());
            }

            inline void PerspectiveCamera::computePlane() {
                frustum.computePlane(getEye(), getForward(), getRight(), getUp());
            }

        }
    }
