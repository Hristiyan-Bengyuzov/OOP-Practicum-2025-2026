#pragma once
#include <variant>

struct Rock {};
struct Paper {};
struct Scissors {};
struct Lizard {};
struct Spock {};

using Gesture = std::variant<Rock, Paper, Scissors, Lizard, Spock>;