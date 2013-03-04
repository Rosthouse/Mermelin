/**
* @file Test.h
* @brief Does some tests in Debug-mode.
*
* @author Patrick Joos, Eduardo Hahn Paredes
*/
#ifndef TEST_H
#define TEST_H

#include "stdafx.h"
#include "Engine.h"
#include "Entities/Sphere.h"
#include "Resources/Files/Level.h"

namespace CotopaxiEngine {

    /**
     * @class Test
     * @brief Does some tests in Debug-mode.
     *
     * Some parts of the application can be tested with this class.
     */
    class Test
    {
    public:
        /**
         * @fn checkComponents
         * Checks some components.
         * @return true if test was successful
         * @todo Implementation pending
         */
        static bool checkComponents();
        
        /**
         * @fn checkConditionTree
         * Checks if the condition tree is correctly built.
         * @return true if test was successful
         * @todo Implementation pending
         */
        static bool checkConditionTree(Level* level);
        
        /**
         * @fn checkWrongSyntax
         * Checks if wrong syntax is recognized.
         * @return true if test was successful
         * @todo Implementation pending
         */
        static bool checkWrongSyntax();
    };
}

#endif