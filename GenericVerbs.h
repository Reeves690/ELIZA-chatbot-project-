// GenericVerbs.h
// Major functionality component: "Generic verbs" -- catches everyday
// action verbs (have, purchase, travel, know, learn, want, need, think,
// feel, believe) that don't belong to one of the more specific topic
// components, and reflects them back conversationally.
#ifndef GENERIC_VERBS_H
#define GENERIC_VERBS_H

#include <string>

bool matchGenericVerbs(const std::string& input, std::string& outResponse);

#endif // GENERIC_VERBS_H
