
    /**
     * @file Camera/NRE_Camera.tpp
     * @brief Implementation of Engine's Camera's Object : Camera
     * @author Louis ABEL
     * @date 25/09/2018
     * @copyright CC-BY-NC-SA
     */

    namespace NRE {
        namespace Camera {

            inline Camera::Camera(float s, Math::Point3D<float> const& e, Math::Point3D<float> const& c) : speed(s), eye(e), center(c) {
                initAngle();
                computeVector();
            }

            inline Math::Point3D<float> const& Camera::getEye() const {
                return eye;
            }

            inline Math::Point3D<float> const& Camera::getCenter() const {
                return center;
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

            inline Math::Vector3D<float> const& Camera::getLeft() const {
                return left;
            }

            inline Math::Matrix4x4<float> const& Camera::getView() const {
                return view;
            }

            inline Math::Matrix4x4<float> const& Camera::getProjection() const {
                return projection;
            }

            inline void Camera::setEye(Math::Point3D<float> const& p) {
                eye = p;
            }

            inline void Camera::setCenter(Math::Point3D<float> const& p) {
                center = p;
            }

            inline void Camera::setAngle(Math::Vector2D<Math::Angle> const& u) {
                angle = u;
            }

            inline void Camera::updateView() {
                view.lookAt(getEye(), getCenter(), getUp());
            }

            inline void Camera::initAngle() {
                using namespace Math;
                Math::Vector3D<float> dir(getEye() - getCenter());
                dir.normalize();
                angle.setX(std::asin(dir.getZ()) * degree);
                angle.setY(std::atan2(dir.getX(), dir.getY()) * degree);
                if (angle.getY() > 90_deg) {
                    angle.setY(450_deg - angle.getY());
                } else {
                    angle.setY(90_deg - angle.getY());
                }
            }

            inline void Camera::computeAngle() {
                using namespace Math;
                if (angle.getX() > MAX_PHI) {
                    angle.setX(MAX_PHI);
                } else if (angle.getX() < MIN_PHI) {
                    angle.setX(MIN_PHI);
                }
                if (angle.getY() > 360_deg) {
                    angle.setY(angle.getY() - 360_deg);
                } else if (angle.getY() < 0_deg) {
                    angle.setY(angle.getY() + 360_deg);
                }
            }

            inline void Camera::computeVector() {
                float tmp = static_cast <float> (Math::cos(angle.getX()));
                forward.setCoord(tmp * static_cast <float> (Math::cos(angle.getY())),
                                 tmp * static_cast <float> (Math::sin(angle.getY())),
                                 static_cast <float> (Math::sin(angle.getX())));
                forward.normalize();

                left = Math::Vector3D<float>(0, 0, 1) ^ getForward();
                left.normalize();

                up = getForward() ^ getLeft();
                up.normalize();
            }

            inline void Camera::moveFront() {
                setEye(getEye() + (getForward() * speed * Time::Clock::TIMESTEP));
            }

            inline void Camera::moveBack() {
                setEye(getEye() - (getForward() * speed * Time::Clock::TIMESTEP));
            }

            inline void Camera::moveLeft() {
                setEye(getEye() + (getLeft() * speed * Time::Clock::TIMESTEP));
            }

            inline void Camera::moveRight() {
                setEye(getEye() - (getLeft() * speed * Time::Clock::TIMESTEP));
            }

            inline void Camera::moveUp() {
                setEye(getEye() + (getUp() * speed * Time::Clock::TIMESTEP));
            }

            inline void Camera::moveDown() {
                setEye(getEye() - (getUp() * speed * Time::Clock::TIMESTEP));
            }

            inline void Camera::moveCenter() {
                setCenter(getEye() + getForward());
            }

            inline void Camera::turn(Math::Vector2D<Math::Angle> const& a) {
                setAngle(getAngle() - a);
            }

            inline void Camera::update() {
                moveCenter();
                updateView();
                computeAngle();
                computeVector();
            }

            inline Utility::String Camera::toString() const {
                Utility::String res;
                res << eye.toString();
                res << " - ";
                res << center.toString();
                res << " - ";
                res << angle.toString();
                res << '\n';
                res << forward.toString();
                res << " - ";
                res << left.toString();
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

            inline Math::Vector3D<float>& Camera::getLeft() {
                return left;
            }

            inline Math::Vector3D<float>& Camera::getUp() {
                return up;
            }

            inline Math::Matrix4x4<float>& Camera::getProjection() {
                return projection;
            }

            inline std::ostream& operator <<(std::ostream& stream, Camera const& o) {
                return stream << o.toString();
            }
        }
    }
