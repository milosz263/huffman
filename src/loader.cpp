#include "loader.hpp"

bool ILoader::end()
{
    return (pos() == size()-1);
}
