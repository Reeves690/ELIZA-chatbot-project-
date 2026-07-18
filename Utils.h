// Utils.h
// Small, general-purpose helper functions used across every component of
// the ELIZA system: whitespace trimming, case normalization, and the
// classic "pronoun reflection" transform (e.g. "I am" -> "you are") that
// ELIZA uses to turn a user's statement back into a question.
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include "Rule.h"

namespace Utils {

    // Walks a component's rule table in order, using std::regex_search on
    // each pattern. The first rule that matches "wins": one of its
    // response templates is selected (round-robin, based on timesMatched)
    // and, if the template contains "%R%", the regex's first capture
    // group is pronoun-reflected (see reflect()) and substituted in via
    // std::regex_replace. Returns true and fills outResponse on a match.
    bool tryRules(const std::vector<Rule>& rules,
                  const std::string& input,
                  std::string& outResponse,
                  int& rotationCounter);

    // Removes leading/trailing whitespace from a string.
    std::string trim(const std::string& s);

    // Returns a lowercase copy of the given string.
    std::string toLower(const std::string& s);

    // Swaps first/second person pronouns and matching verb forms so a
    // fragment captured from the user's sentence can be reflected back at
    // them, e.g. "I am worried about my job" -> "you are worried about your job".
    std::string reflect(const std::string& s);

    // Collapses internal runs of whitespace into single spaces.
    std::string normalizeWhitespace(const std::string& s);
}

#endif // UTILS_H
