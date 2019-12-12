#pragma once
#ifndef AIFACTORY_HPP
#define AIFACTORY_HPP

#include <cstdint>
#include <functional>
#include <map>
#include <string>
#include <utility>

#include "Board.hpp"
#include "Piece.hpp"

typedef std::function<std::pair<std::uint_fast8_t, std::uint_fast8_t>(
    Board const &board, Color myColor)>
    AIFunc;

class AIFactory
{
private:
    std::map<std::string, AIFunc> aiMap;

protected:
public:
    AIFactory();
    AIFactory(AIFactory &&other);
    AIFactory &operator=(AIFactory &&other);

    AIFactory(const AIFactory &other) = delete;
    AIFactory &operator=(const AIFactory &other) = delete;
    ~AIFactory();

    AIFunc GetAI(std::string const &ai);
};

#endif
