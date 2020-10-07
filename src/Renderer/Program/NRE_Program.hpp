
    /**
     * @file NRE_Program.hpp
     * @brief Declaration of Engine's Renderer's Object : Program
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <memory>

    #include <Header/NRE_Math.hpp>
    #include <Header/NRE_Core.hpp>

    #include "../../Header/NRE_GL.hpp"
    #include "../../Header/NRE_Exception.hpp"

    #include "Uniforms/NRE_Uniforms.hpp"
    #include "Shader/Vertex/NRE_VertexShader.hpp"
    #include "Shader/Fragment/NRE_FragmentShader.hpp"
    #include "Shader/Geometry/NRE_GeometryShader.hpp"

     /**
     * @namespace NRE
     * @brief The NearlyRealEngine's global namespace
     */
    namespace NRE {
        /**
         * @namespace Renderer
         * @brief Engine's Renderer module
         */
        namespace Renderer {

            /**
             * @pure Program
             * @brief Manage a single GLSL program
             */
            class Program {
                private:    //Fields
                    Id id;                                              /**< The program's id */
                    Uniforms uniforms;                                  /**< The program's uniforms */
                    Core::Vector<std::unique_ptr<Shader>> stages;    /**< The program's shader stages */

                public:     //Fields
                    /**< Shortcut to hide the Category type */
                    typedef std::size_t Category;

                public:    // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        Program();

                    //## Copy-Constructor ##//
                        /**
                         * Copy forbidden
                         * @param p the program to copy
                         */
                        Program(Program const& p) = delete;

                    //## Move-Constructor ##//
                        /**
                         * Move p into this, leaving p empty
                         * @param p the program to move
                         */
                        Program(Program && p);

                    //## Deconstructor ##//
                        /**
                         * Program Deconstructor
                         */
                        virtual ~Program();

                    //## Getter ##//
                        /**
                         * Tell if the program's category is equals to the given one
                         * @param  cat the tested category
                         * @return     the test's result
                         */
                        virtual bool isCategory(Category cat) = 0;
                        /**
                         * @return the program's id
                         */
                        Id getId() const;

                    //## Methods ##//
                        /**
                         * Add program's stages
                         */
                        virtual void addStages() = 0;
                        /**
                         * Add program's uniforms
                         */
                        virtual void addUniforms() = 0;
                        /**
                         * Bind the object
                         */
                        void bind() const;
                        /**
                         * Unbind the object
                         */
                        void unbind() const;
                        /**
                         * Create the object's id
                         */
                        void createId();
                        /**
                         * Delete the object's id
                         */
                        void deleteId();
                        /**
                         * Test if the id already exist
                         * @return the test's result
                         */
                        bool exist() const;
                        /**
                         * Compile all shader stage and link them into the program
                         */
                        void load();
                        /**
                         * Detach all program's shaders
                         */
                        void detachShaders();
                        /**
                         * Add a program's stage
                         * @param args the stage's construction arguments
                         */
                        template <class T, class ... Args>
                        void addStage(Args && ... args) {
                            stages.pushBack(std::make_unique<T>(std::forward<Args>(args)...));
                            stages.getLast()->compile(getId());
                        }
                        /**
                         * Add a uniform
                         * @param uniform the uniform to add
                         */
                        void addUniform(Core::String const& uniform);
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the value to pass
                         */
                        void use1I(Core::String const& location, GLint v0) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         */
                        void use2I(Core::String const& location, GLint v0, GLint v1) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         * @param v2       the third value to pass
                         */
                        void use3I(Core::String const& location, GLint v0, GLint v1, GLint v2) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         * @param v2       the third value to pass
                         * @param v3       the fourth value to pass
                         */
                        void use4I(Core::String const& location, GLint v0, GLint v1, GLint v2, GLint v3) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the value to pass
                         */
                        void use1F(Core::String const& location, GLfloat v0) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         */
                        void use2F(Core::String const& location, GLfloat v0, GLfloat v1) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         * @param v2       the third value to pass
                         */
                        void use3F(Core::String const& location, GLfloat v0, GLfloat v1, GLfloat v2) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         * @param v2       the third value to pass
                         * @param v3       the fourth value to pass
                         */
                        void use4F(Core::String const& location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the value to pass
                         */
                        void use1UI(Core::String const& location, GLuint v0) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         */
                        void use2UI(Core::String const& location, GLuint v0, GLuint v1) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         * @param v2       the third value to pass
                         */
                        void use3UI(Core::String const& location, GLuint v0, GLuint v1, GLuint v2) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value
                         * @param location the uniform to query the location
                         * @param v0       the first value to pass
                         * @param v1       the second value to pass
                         * @param v2       the third value to pass
                         * @param v3       the fourth value to pass
                         */
                        void use4UI(Core::String const& location, GLuint v0, GLuint v1, GLuint v2, GLuint v3) const;
                        /**
                         * Call the OpengGL command to bind 3x3 matrix
                         * @param location the uniform to query the location
                         * @param count    the number of matrix passed
                         * @param value    the pointer to the first matrix to passed
                         */
                        void useMat3(Core::String const& location, GLsizei count, const Math::Matrix3x3<float>* const value) const;
                        /**
                         * Call the OpengGL command to bind 4x4 matrix
                         * @param location the uniform to query the location
                         * @param count    the number of matrix passed
                         * @param value    the pointer to the first matrix to passed
                         */
                        void useMat4(Core::String const& location, GLsizei count, const Math::Matrix4x4<float>* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 1 value by 1 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use1IV(Core::String const& location, GLsizei count, const GLint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 2 value by 2 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use2IV(Core::String const& location, GLsizei count, const GLint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 3 value by 3 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use3IV(Core::String const& location, GLsizei count, const GLint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 4 value by 4 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use4IV(Core::String const& location, GLsizei count, const GLint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 1 value by 1 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use1FV(Core::String const& location, GLsizei count, const GLfloat* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 2 value by 2 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use2FV(Core::String const& location, GLsizei count, const GLfloat* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 3 value by 3 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use3FV(Core::String const& location, GLsizei count, const GLfloat* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 4 value by 4 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use4FV(Core::String const& location, GLsizei count, const GLfloat* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 1 value by 1 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use1UIV(Core::String const& location, GLsizei count, const GLuint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 2 value by 2 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use2UIV(Core::String const& location, GLsizei count, const GLuint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 3 value by 3 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use3UIV(Core::String const& location, GLsizei count, const GLuint* const value) const;
                        /**
                         * Call the OpenGL command to bind specific uniform value from a pointer, 4 value by 4 value
                         * @param location the uniform to query the location
                         * @param count    the number of values passed
                         * @param value    the pointer to the first value to passed
                         */
                        void use4UIV(Core::String const& location, GLsizei count, const GLuint* const value) const;

                    //## Assignment Operator ##//
                        /**
                         * Copy assignment forbidden
                         * @param p the program to copy into this
                         * @return      the reference of himself
                         */
                        Program& operator =(Program const& p) = delete;
                        /**
                         * Move assignment of p into this, leaving p empty
                         * @param p the program to move into this
                         * @return      the reference of himself
                         */
                        Program& operator =(Program && p);

                protected:  // Static
                    static Category counter;    /**< The category counter */
            };
        }
    }

    #include "NRE_Program.tpp"
