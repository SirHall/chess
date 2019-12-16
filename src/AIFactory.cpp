#include "AIFactory.hpp"

#include "ai/Player.hpp"
#include "ai/Test.hpp"

#include <ncurses.h>

#include <chrono>

void AddAIs(std::map<std::string, AIFunc> &aiMap);

AIFactory::AIFactory() { AddAIs(this->aiMap); }

AIFactory::AIFactory(AIFactory &&other)
{
    this->aiMap = std::move(other.aiMap);
}

AIFactory &AIFactory::operator=(AIFactory &&other)
{
    this->aiMap = std::move(other.aiMap);
    return *this;
}

AIFactory::~AIFactory() {}

AIFunc AIFactory::GetAI(std::string const &ai) { return this->aiMap[ai]; }

void AddAIs(std::map<std::string, AIFunc> &aiMap)
{
    aiMap["player"] = ai::Player;
    aiMap["test"]   = ai::Test;
}
