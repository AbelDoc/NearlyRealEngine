
    /**
     * @file NRE_ProgramManager.hpp
     * @brief Declaration of Engine's Renderer's Object : ProgramManager
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <memory>
    #include <algorithm>
    #include <bitset>

    #include <Header/NRE_Utility.hpp>
    #include "../NRE_Program.hpp"

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
             * @class ProgramManager
             * @brief Manage programs storing
             */
            class ProgramManager : public Utility::Singleton<ProgramManager>  {
                friend class Utility::Singleton<ProgramManager>;

                /** Shortcut to hide program's variants container type */
                typedef Utility::Vector<std::unique_ptr<Program>> ProgramsVector;
                /** Shortcut to hide programs container type */
                typedef Utility::Vector<ProgramsVector> ProgramsMultiMap;

                private:    //Fields
                    constexpr static int MAX_PROGRAM = 32;      /**< The max numbers of different programs category, doesn't include theirs variants */
                    ProgramsMultiMap programs;                  /**< The managed programs */
                    std::bitset<MAX_PROGRAM> mask;              /**< The programs category mask */

                public:    // Methods
                    //## Getter ##//
                        /**
                         * Shader getter from a T shader and his Spec variant
                         * @return the Spec variant shader
                         */
                        template <class T, class Spec = T>
                        Spec* getShader() {
                            assert(T::getCategory() < MAX_PROGRAM);
                            bool in = mask[T::getCategory()];
                            return (in) ? (static_cast <Spec*> (programs[T::getCategory()].begin()->get()))
                                        : (addShader<T, Spec>());
                        }

                    //## Methods ##//
                        /**
                         * Add a Spec shader to the manager
                         * @return the new Spec shader
                         */
                        template <class T, class Spec>
                        Spec* addShader() {
                            assert(T::getCategory() < MAX_PROGRAM);
                            Spec* shader = new Spec;
                            mask[T::getCategory()] = true;
                            if (programs.getSize() <= T::getCategory()) {
                                programs.resize(T::getCategory() + 1);
                                programs.getLast().emplaceBack(shader);
                            } else {
                                programs[T::getCategory()].emplaceBack(shader);
                            }
                            return shader;
                        }
                        /**
                         * Retrieve the Spec shader variant inside a T shader vector, if not find add it
                         * @param  vector the T shader vector
                         * @return        the pointer to the retrieved shader variant
                         */
                        template <class T, class Spec>
                        std::unique_ptr<Program>& getShaderIn(ProgramsVector& vector) {
                            auto it = std::find_if(vector.begin(), vector.end(), [](std::unique_ptr<Program> const& p) {
                                return p->isCategory(Spec::getCategory());
                            });
                            if (it == vector.end()) {
                                addShader<T, Spec>();
                                it = std::prev(vector.end());
                            }
                            return *it;
                        }
                        /**
                         * Swap the active T shader by one Spec variant
                         */
                        template <class T, class Spec>
                        void swapShader() {
                            assert(T::getCategory() < MAX_PROGRAM);
                            assert(mask[T::getCategory()]);
                            ProgramsVector& vector = programs[T::getCategory()];
                            std::unique_ptr<Program>& other = getShaderIn<T, Spec>(vector);
                            std::unique_ptr<Program>& old = *(vector.begin());

                            other.swap(old);
                        }

                private:   // Methods
                    //## Constructor ##//
                        /**
                         * Default constructor
                         */
                        ProgramManager() = default;

                    //## Deconstructor ##//
                        /**
                         * ProgramManager Deconstructor
                         */
                        ~ProgramManager() = default;

                public:   // Static
                    /**
                     * Shader getter from a T shader and his Spec variant
                     * @return the Spec variant shader
                     */
                    template <class T, class Spec = T>
                    static T* get() {
                        return Utility::Singleton<ProgramManager>::get().getShader<T, Spec>();
                    }
                    /**
                     * Swap the active T shader by one Spec variant
                     */
                    template <class T, class Spec = T>
                    static void swap() {
                        Utility::Singleton<ProgramManager>::get().swapShader<T, Spec>();
                    }
            };
        }
    }
