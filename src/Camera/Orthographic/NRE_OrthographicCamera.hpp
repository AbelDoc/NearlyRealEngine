    
    /**
     * @file NRE_OrthographicCamera.hpp
     * @brief Declaration of Engine's Camera's Object : OrthographicCamera
     * @author Louis ABEL
     * @date 10/02/2020
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
             * @class OrthographicCamera
             * @brief Describe a orthographic camera
             */
            class OrthographicCamera : public Camera {
                private:    //Fields
                    Math::Vector2D<int> size;      /**< The viewport's size */
                    Math::Vector2D<float> dist;    /**< The far and near clipping plane distance */

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        OrthographicCamera() = delete;
                        /**
                         * Construct an orthographic camera from her attributes
                         * @param s         the camera's speed
                         * @param e         the camera's eye position
                         * @param viewport  the viewport size
                         * @param d         the far and near clipping plane distance
                         * @param y         the camera's yaw
                         * @param p         the camera's pitch
                         */
                        OrthographicCamera(float s, Math::Point3D<float> const& e, Math::Vector2D<int> const& viewport, Math::Vector2D<float> const& d, Math::Angle y = 0 * Math::degree, Math::Angle p = 0 * Math::degree);
        
                    //## Copy-Constructor ##//
                        /**
                         * Copy c into this
                         * @param c the orthographic camera to copy the content
                         */
                        OrthographicCamera(OrthographicCamera const& c) = default;
        
                    //## Move-Constructor ##//
                        /**
                         * Move c into this
                         * @param c the orthographic camera to move
                         */
                        OrthographicCamera(OrthographicCamera && c) = default;
        
                    //## Deconstructor ##//
                        /**
                         * OrthographicCamera Deconstructor
                         */
                        ~OrthographicCamera() = default;
        
                    //## Methods ##//
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
                         * Copy c into this
                         * @param c the object to copy into this
                         * @return  the reference of himself
                         */
                        OrthographicCamera& operator =(OrthographicCamera const& c) = default;
                        /**
                         * Move c into this
                         * @param c the object to move into this
                         * @return  the reference of himself
                         */
                        OrthographicCamera& operator =(OrthographicCamera && c) = default;
            };
        }
    }

    #include "NRE_OrthographicCamera.tpp"