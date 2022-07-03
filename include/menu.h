#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "entry.h"

auto print_logbook(const std::vector<entry>& entries) -> void {
    // Prints all entries from the logbook table
    for (const auto& e : entries)
        std::cout << e.exercise_name << ": " << e.weight << "kg, " << e.sets << " x " << e.reps << std::endl;
}
