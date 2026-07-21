// Financial.cpp
#include "Financial.h"
#include "Rule.h"
#include "Utils.h"
#include <vector>

namespace {
    int rotation = 0;

    const std::vector<Rule> rules = {
        { std::regex(R"(\bmoney (.*)$)", std::regex::icase),
          { "What's going on with %R%?", "How does thinking about %R% make you feel?" } },

        { std::regex(R"(\b(savings|saving money) (.*)$)", std::regex::icase),
          { "What are you saving for?", "How is your saving going?" } },

        { std::regex(R"(\binvest(ing|ment|ments)? (.*)$)", std::regex::icase),
          { "What made you interested in %R%?", "How comfortable do you feel about %R%?" } },

        { std::regex(R"(\bbankrupt(cy)?\b)", std::regex::icase),
          { "That sounds like a very stressful situation. What's been happening financially?" } },

        { std::regex(R"(\b(debt|owe|owing) (.*)$)", std::regex::icase),
          { "How is dealing with %R% affecting you?" } },

        { std::regex(R"(\bi (can't afford|cannot afford) (.*)$)", std::regex::icase),
          { "Not being able to afford %R% -- how does that weigh on you?" } },

        { std::regex(R"(\b(salary|paycheck|income) (.*)$)", std::regex::icase),
          { "How do you feel about %R%?" } },

        { std::regex(R"(\bi (lost|lost my) job\b)", std::regex::icase),
          { "Losing a job is really tough. How are you coping?" } },
    };
}

bool matchFinancial(const std::string& input, std::string& outResponse) {
    return Utils::tryRules(rules, input, outResponse, rotation);
}
