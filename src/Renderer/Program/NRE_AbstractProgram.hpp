
    /**
     * @file NRE_AbstractProgram.hpp
     * @brief Declaration of Engine's Renderer's Object : AbstractProgram
     * @author Louis ABEL
     * @date 26/08/2019
     * @copyright CC-BY-NC-SA
     */

     #pragma once

    #include <iostream>
    #include <string>

    #include "NRE_Program.hpp"

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
             * @class AbstractProgram
             * @brief Manage type differenciation between shader
             */
            template <class T>
            class AbstractProgram : public Program {
            public:     // Methods
                    //## Deconstructor ##//
                        /**
                         * AbstractProgram Deconstructor
                         */
                        virtual ~AbstractProgram() = default;

                    //## Getter ##//
                        /**
                         * Tell if the program's category is equals to the given one
                         * @param  cat the tested category
                         * @return     the test's result
                         */
                        bool isCategory(Category cat) override {
                            return getCategory() == cat;
                        }

                public:     // Static
                    /**
                     * Category getter
                     * @return the program's category
                     */
                    static Category getCategory() {
                        static Category category = counter++;
                        return category;
                    }
            };
        }
    }
