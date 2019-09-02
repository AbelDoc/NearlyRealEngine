
    /**
     * @file Camera/NRE_Camera.hpp
     * @brief Declaration of Engine's Camera's Object : Camera
     * @author Louis ABEL
     * @date 25/09/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include "../Header/NRE_GL.hpp"

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
            class Camera {
                private:    //Fields
                    float speed;                            /**< The camera's speed */
                    Math::Point3D<float> eye;               /**< The camera's point of view */
                    Math::Point3D<float> center;            /**< The camera's center of view */
                    Math::Vector3D<float> up;               /**< The camera's up vector */
                    Math::Vector3D<float> forward;          /**< The camera's forward vector */
                    Math::Vector3D<float> left;             /**< The camera's left vector */
                    Math::Vector2D<Math::Angle> angle;      /**< The camera's angle */
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
                         * @param c the camera's center of view position
                         */
                        Camera(float s, Math::Point3D<float> const& e, Math::Point3D<float> const& c);

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
                         * @return the camera's center of view
                         */
                        Math::Point3D<float> const& getCenter() const;
                        /**
                         * @return the camera's angle
                         */
                        Math::Vector2D<Math::Angle> const& getAngle() const;
                        /**
                         * @return the camera's up vector
                         */
                        Math::Vector3D<float> const& getUp() const;
                        /**
                         * @return the camera's forward vector
                         */
                        Math::Vector3D<float> const& getForward() const;
                        /**
                         * @return the camera's left vector
                         */
                        Math::Vector3D<float> const& getLeft() const;
                        /**
                         * @return the camera's view matrix
                         */
                        Math::Matrix4x4<float> const& getView() const;
                        /**
                         * @return the camera's projection view
                         */
                        Math::Matrix4x4<float> const& getProjection() const;

                    //## Setter ##//
                        /**
                         * @param p the new camera's eye
                         */
                        void setEye(Math::Point3D<float> const& p);
                        /**
                         * @param p the new camera's center
                         */
                        void setCenter(Math::Point3D<float> const& p);
                        /**
                         * @param u the new camera's angle
                         */
                        void setAngle(Math::Vector2D<Math::Angle> const& u);

                    //## Methods ##//
                        /**
                         * Update the view matrix
                         */
                        void updateView();
                        /**
                         * Initialize angle from the position and fixed point value
                         */
                        void initAngle();
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
                         * Move the center of view according to the forward vector
                         */
                        void moveCenter();
                        /**
                         * Turn the camera with given angles
                         * @param a the turning angle
                         */
                        void turn(Math::Vector2D<Math::Angle> const& a);
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
                        Utility::String toString() const;

                protected: // Methods
                    /**
                     * @return the camera's eye
                     */
                    Math::Point3D<float>& getEye();
                    /**
                     * @return the camera's forward vector
                     */
                    Math::Vector3D<float>& getForward();
                    /**
                     * @return the camera's left vector
                     */
                    Math::Vector3D<float>& getLeft();
                    /**
                     * @return the camera's up vector
                     */
                    Math::Vector3D<float>& getUp();
                    /**
                     * @return the camera's projection matrix
                     */
                    Math::Matrix4x4<float>& getProjection();

                private:    // Static
                    static constexpr Math::Angle MAX_PHI =  89.9 * Math::degree;    /**< The maximum phi */
                    static constexpr Math::Angle MIN_PHI = -89.9 * Math::degree;    /**< The minimum phi */

            };

            /**
             * Output stream operator for the object
             * @param  stream the stream to add the object's string representation
             * @param  o      the object to add in the stream
             * @return the    modified stream
             */
            std::ostream& operator <<(std::ostream& stream, Camera const& o);
        }
    }

    #include "NRE_Camera.tpp"
