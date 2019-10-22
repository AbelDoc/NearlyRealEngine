
    /**
     * @file Camera/NRE_Camera.tpp
     * @brief Implementation of Engine's Camera's Object : Camera
     * @author Louis ABEL
     * @date 25/09/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Camera {

            inline Camera::Camera(float s, Math::Point3D<float> const& e, Math::Vector3D<float> const& u, Math::Vector2D<Math::Angle> const& a) : speed(s), eye(e), up(u), angle(a) {
                computeVector();
            }

            inline Math::Point3D<float> const& Camera::getEye() const {
                return eye;
            }

            inline Math::Vector2D<Math::Angle> const& Camera::getAngle() const {
                return angle;
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

            inline void Camera::updateView() {
                view.lookAt(eye, eye + forward, up);
            }

            inline void Camera::computeAngle() {
                if (angle.getX() > MAX_PITCH) {
                    angle.setX(MAX_PITCH);
                } else if (angle.getX() < MIN_PITCH) {
                    angle.setX(MIN_PITCH);
                }
            }

            inline void Camera::computeVector() {
                float tmp = static_cast <float> (Math::cos(angle.getX()));
                forward.setX(tmp * static_cast <float> (Math::cos(angle.getY())));
                forward.setY(      static_cast <float> (Math::sin(angle.getX())));
                forward.setZ(tmp * static_cast <float> (Math::sin(angle.getY())));
                forward.normalize();

                right = forward ^ Math::Vector3D<float>(0, 1, 0);
                right.normalize();

                up = right ^ forward;
                up.normalize();
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
                angle += Math::Vector2D<Math::Angle>(static_cast <float> (-motion.getY()) * Math::degree * 0.1f, static_cast <float> (motion.getX()) * Math::degree * 0.1f);
            }

            inline void Camera::update() {
                computeAngle();
                computeVector();
                updateView();
            }

            inline Utility::String Camera::toString() const {
                Utility::String res;
                res << eye.toString();
                res << " - ";
                res << angle.toString();
                res << '\n';
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

            inline Math::Point3D<float>& Camera::getEye() {
                return eye;
            }

            inline Math::Vector3D<float>& Camera::getForward() {
                return forward;
            }

            inline Math::Vector3D<float>& Camera::getRight() {
                return right;
            }

            inline Math::Vector3D<float>& Camera::getUp() {
                return up;
            }

            inline Math::Matrix4x4<float>& Camera::getProjection() {
                return projection;
            }
        }
    }
