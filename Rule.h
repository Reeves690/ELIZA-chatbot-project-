// Rule.h
// A "Rule" pairs a regular expression with one or more response templates.
// A template may contain the marker "%R%" which is replaced with the
// pronoun-reflected text captured by the regex's first capture group
// (if the regex has no capture group, %R% is simply omitted).
// Every major functionality component (GenericVerbs, Relationships,
// Concern, Financial, Wellbeing, Education, Entertainment, Family) is
// implemented as a vector of Rules plus a small dispatch function.
#ifndef RULE_H
#define RULE_H

#include <regex>
#include <string>
#include <vector>

struct Rule {
    std::regex pattern;
    std::vector<std::string> responses; // rotated / picked from
};

#endif // RULE_H
