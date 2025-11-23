/**
 * @file cli.hpp
 * @brief This header declares all functions that prints to stderr.
 */

#pragma once
#include <iostream>
#include <string>
#include <cstdlib>

/**
 * @brief Extract filename from parameter.
 * 
 * @param argc argument count (in main() format).
 * @param argv arguments (in main() format).
 * @param i index of current parameter (before filename).
 * @param filename reference to save filename to. Will fail if passed string isn't empty.
 * @note If function fails, calls exitDuplicateParameter() or exitNoFileSpecified().
 */
void getFilename(int argc, char** argv, int i, std::string &filename);

/**
 * @brief Prints usage and exits.
 * 
 * @param exename name used as executable name in usage example.
 */
void exitUsage(std::string exename);

/**
 * @brief Prints bad parameter error and exits.
 * 
 * @param param bad parameter that caused the error.
 */
void exitBadParameter(std::string param);

/**
 * @brief Prints duplicate parameter error and exits.
 * 
 * @param param duplicated parameter.
 */
void exitDuplicateParameter(std::string param);

/**
 * @brief Prints duplicate parameter error and exits.
 * 
 * @param param parameter which needed file.
 */
void exitNoFileSpecified(std::string param);

/**
 * @brief Prints input file doesn't exist error and exits.
 * 
 * @param filename 
 */
void exitInputFileDoesntExists(std::string filename);

/**
 * @brief Prints output file already exists error and exits.
 * 
 * @param filename 
 */
void exitOutputFileExists(std::string filename);

/**
 * @brief Prints error abour using both encode and decode flag and exits.
 * 
 */
void exitFlagsConflict();