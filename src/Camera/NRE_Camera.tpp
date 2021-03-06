
    /**
     * @file Camera/NRE_Camera.tpp
     * @brief Implementation of Engine's Camera's Object : Camera
     * @author Louis ABEL
     * @date 25/09/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Camera {

            inline Camera::Camera(float s, Math::Point3D<float> const& e, Math::Angle y, Math::Angle p) : speed(s), yaw(y), pitch(p), eye(e) {
                computeAngle();
                computeVector();
            }

            inline Math::Point3D<float> const& Camera::getEye() const {
                return eye;
            }

            inline Math::Vector3D<float> const& Camera::getUp() const {
                return up;
            }

            inline Math::Vector3D<float> const& Camera::getForward() const {
                return forward;
            }

            inline Math::Vector3D<float> const& Camera::getRight() const {
                return right;
            }

            inline Math::Matrix4x4<float> const& Camera::getView() const {
                return view;
            }

            inline Math::Matrix4x4<float> const& Camera::getProjection() const {
                return projection;
            }
            
            inline Math::Angle Camera::getYaw() const {
                return yaw;
            }
    
            inline Math::Angle Camera::getPitch() const {
                return pitch;
            }

            inline void Camera::setEye(Math::Point3D<float> const& e) {
                eye = e;
            }
            
            inline void Camera::setYaw(Math::Angle y) {
                yaw = y;
            }
            
            inline void Camera::setPitch(Math::Angle p) {
                pitch = p;
            }
            
            inline void Camera::updateView() {
                view.lookAt(eye, eye + forward, up);
            }

            inline void Camera::computeAngle() {
                if (pitch > MAX_PITCH) {
                    pitch = MAX_PITCH;
                } else if (pitch < MIN_PITCH) {
                    pitch = MIN_PITCH;
                }
            }

            inline void Camera::computeVector() {
                float tmp = static_cast <float> (cos(pitch));
                forward.setX(tmp * static_cast <float> (cos(yaw)));
                forward.setY(      static_cast <float> (sin(pitch)));
                forward.setZ(tmp * static_cast <float> (sin(yaw)));
                forward.normalize();
                
                right = forward ^ Math::Vector3D<float>(0, 1, 0);
                right.normalize();

                up = right ^ forward;
            }

            inline void Camera::moveFront() {
                eye += forward * speed * Time::Clock::TIMESTEP;
            }

            inline void Camera::moveBack() {
                eye -= forward * speed * Time::Clock::TIMESTEP;
            }

            inline void Camera::moveLeft() {
                eye -= right * speed * Time::Clock::TIMESTEP;
            }

            inline void Camera::moveRight() {
                eye += right * speed * Time::Clock::TIMESTEP;
            }

            inline void Camera::moveUp() {
                eye += up * speed * Time::Clock::TIMESTEP;
            }

            inline void Camera::moveDown() {
                eye -= up * speed * Time::Clock::TIMESTEP;
            }

            inline void Camera::turn(Math::Vector2D<int> const& motion) {
                yaw   += static_cast <float> ( motion.getX()) * Math::degree * 0.1f;
                pitch += static_cast <float> (-motion.getY()) * Math::degree * 0.1f;
            }

            inline void Camera::update() {
                computeAngle();
                computeVector();
                updateView();
            }

            inline Core::String Camera::toString() const {
                Core::String res;
                res << eye.toString();
                res << " - (";
                res << yaw.toString();
                res << ", ";
                res << pitch.toString();
                res << ")\n";
                res << forward.toString();
                res << " - ";
                res << right.toString();
                res << " - ";
                res << up.toString();
                res << '\n';
                res << view.toString();
                res << '\n';
                res << projection.toString();
                return res;
            }
        }
    }
