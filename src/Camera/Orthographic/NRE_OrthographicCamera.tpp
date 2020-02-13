    
    /**
     * @file NRE_OrthographicCamera.hpp
     * @brief Implementation of Engine's Camera's Object : OrthographicCamera
     * @author Louis ABEL
     * @date 10/02/2020
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once
    
    namespace NRE {
        namespace Camera {
        
            inline OrthographicCamera::OrthographicCamera(float s, Math::Point3D<float> const& e, Math::Vector2D<int> const& viewport, Math::Vector2D<float> const& d, Math::Angle y, Math::Angle p) : Camera(s, e, y, p), size(viewport), dist(d) {
                computeProjectionMatrix();
            }
    
            inline void OrthographicCamera::resize(Math::Vector2D<unsigned int> const& s) {
                size = s;
                computeProjectionMatrix();
            }
    
            inline void OrthographicCamera::computeProjectionMatrix() {
                auto v = Math::Vector2D<float>(static_cast <float> (size.getH()) / 2.0f);
                auto h = Math::Vector2D<float>(static_cast <float> (size.getW()) / 2.0f);
                v.setX(-v.getX());
                h.setX(-h.getX());
                projection.ortho(h, v, dist);
            }
    
        }
    }
