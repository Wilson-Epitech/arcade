/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** errorHandling
*/

#include "errorHandling.hpp"

LibError::LibError() : _errorMessage("Library don't exist") {}

const char *LibError::what() const noexcept
{
    return _errorMessage.c_str();
}

SaveError::SaveError() : _errorMessage("Can't save score") {}

const char *SaveError::what() const noexcept
{
    return _errorMessage.c_str();
}