    
    /**
     * @file NRE_Mesh.hpp
     * @brief Declaration of Engine's Model's Object : Mesh
     * @author Louis ABEL
     * @date 22/10/2019
     * @copyright CC-BY-NC-SA
     */
    
    #pragma once

    #include "../../GL/VBO/NRE_AbstractVBO.hpp"
    
    /**
    * @namespace NRE
    * @brief The NearlyRealEngine's global namespace
    */
    namespace NRE {
        /**
         * @namespace Model
         * @brief Engine's Model module
         */
        namespace Model {
            
            template <class T>
            class Mesh : public Utility::Bindable<Mesh<T>>,
                         public Utility::Stringable<Mesh<T>>,
                         public Utility::Uncopyable<Mesh<T>> {
                private :   // Field
                    std::unique_ptr<GL::AbstractVBO> vbo;   /**< The mesh buffer */
                    GL::VAO vao;                            /**< The buffer vao */
                    
                public :    // Methods
                    //## Constructor ##//
                        /**
                         * No default constructor
                         */
                        Mesh() = delete;
                        /**
                         * Construct a mesh from the object to render
                         * @param o the object to construct the mesh
                         */
                        Mesh(T const& o);
    
                    //## Move Constructor ##//
                        /**
                         * Move m into this
                         * @param m the mesh to move
                         */
                        Mesh(Mesh && m) = default;
    
                    //## Deconstructor ##//
                        /**
                         * Mesh Deconstructor
                         */
                        ~Mesh() = default;
    
                    //## Getter ##//
                        /**
                         * @return the mesh's buffer
                         */
                        GL::AbstractVBO* getBuffer();
    
                    //## Methods ##//
                        /**
                         * Bind the object
                         */
                        void bind() const;
                        /**
                         * Unbind the object
                         */
                        void unbind() const;
                        /**
                         * Draw the mesh
                         * @param mode the drawing mode
                         */
                        void draw(GL::DrawMode mode = GL_TRIANGLES) const;
                        
                    //## Assignment Operator ##//
                        /**
                         * Move assignment of m into this
                         * @param m the mesh to move into this
                         * @return  the reference of himself
                         */
                        Mesh& operator =(Mesh && b) = default;
            
                        //## Stream Operator ##//
                        /**
                         * Convert the mesh into a string
                         * @return the converted mesh
                         */
                        Utility::String toString() const;
            };
        }
    }

    #include "NRE_Mesh.tpp"