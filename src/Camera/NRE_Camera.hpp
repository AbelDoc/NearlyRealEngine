
    /**
     * @file Camera/NRE_Camera.hpp
     * @brief Declaration of Engine's Camera's Object : Camera
     * @author Louis ABEL
     * @date 25/09/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../Header/NRE_GL.hpp"
     #include <Core/Interfaces/Stringable/NRE_Stringable.hpp>

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Camera
         * @brief Engine's Camera's module
         */
        namespace Camera {

            /**
             * @class Camera
             * @brief A base camera
             */
            class Camera : public Core::Stringable<Camera> {
                private:    //Fields
                    float speed;                            /**< The camera's speed */
                    Math::Angle yaw;                        /**< The camera's yaw */
                    Math::Angle pitch;                      /**< The camera's pitch */
                    
                protected : // Fields
                    Math::Point3D<float> eye;               /**< The camera's point of view */
                    Math::Vector3D<float> forward;          /**< The camera's direction */
                    Math::Vector3D<float> up;               /**< The camera's up vector */
                    Math::Vector3D<float> right;            /**< The camera's right vector */
                    Math::Matrix4x4<float> view;            /**< The camera's view matrix */
                    Math::Matrix4x4<float> projection;      /**< The camera's projection matrix */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        Camera() = delete;
                        /**
                         * Construct a camera from a speed and a pair of point
                         * @param s the camera's speed
                         * @param e the camera's eye position
                         * @param y the camera's yaw
                         * @param p the camera's pitch
                         */
                        Camera(float s, Math::Point3D<float> const& e, Math::Angle y, Math::Angle p);

                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the camera to copy
                         */
                        Camera(Camera const& c) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the camera to move
                         */
                        Camera(Camera && c) = default;

                    //## Deconstructor ##//
                        /**
                         * Camera Deconstructor
                         */
                        virtual ~Camera() = default;

                    //## Getter ##//
                        /**
                         * @return the camera's eye
                         */
                        Math::Point3D<float> const& getEye() const;
                        /**
                         * @return the camera's up vector
                         */
                        Math::Vector3D<float> const& getUp() const;
                        /**
                         * @return the camera's forward vector
                         */
                        Math::Vector3D<float> const& getForward() const;
                        /**
                         * @return the camera's right vector
                         */
                        Math::Vector3D<float> const& getRight() const;
                        /**
                         * @return the camera's view matrix
                         */
                        Math::Matrix4x4<float> const& getView() const;
                        /**
                         * @return the camera's projection view
                         */
                        Math::Matrix4x4<float> const& getProjection() const;
                        /**
                         * @return the camera's yaw angle
                         */
                        Math::Angle getYaw() const;
                        /**
                         * @return the camera's pitch angle
                         */
                        Math::Angle getPitch() const;
    
                    //## Setter ##//
                        /**
                         * Set the camera's eye
                         * @param e the new eye position
                         */
                        void setEye(Math::Point3D<float> const& e);
                        /**
                         * Set the yaw angle
                         * @param y the new angle
                         */
                        void setYaw(Math::Angle y);
                        /**
                         * Set the pitch angle
                         * @param p the new angle
                         */
                        void setPitch(Math::Angle p);

                    //## Methods ##//
                        /**
                         * Update the view matrix
                         */
                        void updateView();
                        /**
                         * Compute angle, just test for phi to be in the min, max range
                         */
                        void computeAngle();
                        /**
                         * Compute the camera's vector from the camera's angle
                         */
                        virtual void computeVector();
                        /**
                         * Resize the camera and the projection matrix
                         * @param size the new window size
                         */
                        virtual void resize(Math::Vector2D<unsigned int> const& size) = 0;
                        /**
                         * Compute the camera's projection matrix
                         */
                        virtual void computeProjectionMatrix() = 0;
                        /**
                         * Move the camera forward
                         */
                        void moveFront();
                        /**
                         * Move the camera backward
                         */
                        void moveBack();
                        /**
                         * Move the camera downward
                         */
                        void moveDown();
                        /**
                         * Move the camera upward
                         */
                        void moveUp();
                        /**
                         * Move the camera to the left
                         */
                        void moveLeft();
                        /**
                         * Move the camera to the right
                         */
                        void moveRight();
                        /**
                         * Turn the camera with the given motions
                         * @param motion the motion to process
                         */
                        void turn(Math::Vector2D<int> const& motion);
                        /**
                         * Update the camera position and view
                         */
                        void update();

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of c into this
                         * @param c the camera to copy
                         * @return  the reference of himself
                         */
                        Camera& operator =(Camera const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the camera to move into this
                         * @return  the reference of himself
                         */
                        Camera& operator =(Camera && c) = default;

                    //## Stream Operator ##//
                        /**
                         * Convert the camera into a string
                         * @return the converted camera
                         */
                        Core::String toString() const;

                private:    // Static
                    static constexpr Math::Angle MAX_PITCH =  89.5 * Math::degree;    /**< The maximum phi */
                    static constexpr Math::Angle MIN_PITCH = -89.5 * Math::degree;    /**< The minimum phi */

            };
        }
    }

    #include "NRE_Camera.tpp"
