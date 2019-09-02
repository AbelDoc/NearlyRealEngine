
    /**
     * @file NRE_PerspectiveCamera.hpp
     * @brief Declaration of Engine's Camera's Object : PerspectiveCamera
     * @author Louis ABEL
     * @date 18/11/2018
     * @copyright CC-BY-NC-SA
     */

     #pragma once

     #include "../NRE_Camera.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Camera
         * @brief Engine's Camera module
         */
        namespace Camera {

            /**
             * @class PerspectiveCamera
             * @brief Describe a perspective camera
             */
            class PerspectiveCamera : public Camera {
                private:    //Fields
                    Math::Frustum frustum; /**< The perspective frustum */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        PerspectiveCamera() = delete;
                        /**
                         * Construct a perspective camera from her attributes
                         * @param s           the camera's speed
                         * @param e           the camera's eye position
                         * @param c           the camera's center of view position
                         * @param fieldOfView the camera's field of view
                         * @param r           the perspective ratio
                         * @param d           the far and near clipping plane distance
                         */
                        PerspectiveCamera(float s, Math::Point3D<float> const& e, Math::Point3D<float> const& c, float fieldOfView, float r, Math::Vector2D<float> const& d);

                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the perspective camera to copy
                         */
                        PerspectiveCamera(PerspectiveCamera const& c) = default;

                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the perspective camera to move
                         */
                        PerspectiveCamera(PerspectiveCamera && c) = default;

                    //## Deconstructor ##//
                        /**
                         * PerspectiveCamera Deconstructor
                         */
                        ~PerspectiveCamera() = default;

                    //## Methods ##//
                        /**
                         * Compute the camera's vector from the camera's angle and update frustum plane
                         */
                        void computeVector() override;
                        /**
                         * Resize the camera and the projection matrix
                         * @param size the new window size
                         */
                        void resize(Math::Vector2D<unsigned int> const& size) override;
                        /**
                         * Compute the camera's projection matrix
                         */
                        void computeProjectionMatrix() override;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment of c into this
                         * @param c the perspective camera to copy
                         * @return      the reference of himself
                         */
                        PerspectiveCamera& operator =(PerspectiveCamera const& c) = default;
                        /**
                         * Move assignment of c into this
                         * @param c the perspective camera to move into this
                         * @return      the reference of himself
                         */
                        PerspectiveCamera& operator =(PerspectiveCamera && c) = default;

                private:   // Methods
                    /**
                     * Compute the frustum's planes
                     */
                    void computePlane();

            };
        }
    }

    #include "NRE_PerspectiveCamera.tpp"
