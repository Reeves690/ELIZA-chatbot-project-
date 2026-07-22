// Entertainment.cpp
#include "Entertainment.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bconcert (.*)$)", std::regex::icase),
          { "What concert did you go to?", "How was the concert?" } },

        { std::regex(R"(\b(movie|movies|film) (.*)$)", std::regex::icase),
          { "What movie are you thinking of?", "What did you like about it?" } },

        { std::regex(R"(\b(dancing|i dance|i danced) (.*)$)", std::regex::icase),
          { "What do you enjoy about dancing?" } },

        { std::regex(R"(\brestaurant (.*)$)", std::regex::icase),
          { "What kind of restaurant is it?", "What did you have there?" } },

        { std::regex(R"(\bbar (.*)$)", std::regex::icase),
          { "What's the occasion?" } },

        { std::regex(R"(\bi (watched|am watching) (.*)$)", std::regex::icase),
          { "What did you think of %R%?" } },

        { std::regex(R"(\bi (played|am playing) (.*)$)", std::regex::icase),
          { "How did %R% go?" } },

        { std::regex(R"(\bparty (.*)$)", std::regex::icase),
          { "Sounds fun -- tell me more." } },
    };
}

bool matchEntertainment(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}
