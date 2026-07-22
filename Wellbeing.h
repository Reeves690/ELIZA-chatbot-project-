// Wellbeing.h
// Major functionality component: "Wellbeing" -- keywords like exercise,
// vitamins, relaxing, sleeping. This component only reflects the user's
// statements conversationally; it never issues medical, dietary, or
// exercise advice.
#ifndef WELLBEING_H
#define WELLBEING_H

#include <string>

bool matchWellbeing(const std::string& input, std::string& outResponse);

#endif // WELLBEING_H
