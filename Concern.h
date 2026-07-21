// Concern.h
// Major functionality component: "Concern" -- detects language around
// hostility, self-harm, or severe distress (keywords such as hate, kill,
// suicide, hopeless, etc.) and responds with a supportive, non-dismissive
// reply that keeps the conversation open and gently points toward real
// support rather than trying to "solve" the feeling itself. This
// component is always checked first by the dispatcher (see Eliza.cpp)
// so that a concerning statement is never missed because an earlier,
// less important rule happened to match first.
#ifndef CONCERN_H
#define CONCERN_H

#include <string>

// Returns true and fills outResponse if the input matches a concern
// pattern.
bool matchConcern(const std::string& input, std::string& outResponse);

#endif // CONCERN_H
