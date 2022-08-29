//
// Created by malte on 8/27/2022.
//

#pragma once

// Make sure that the dimension can only be 2 or 3
template<unsigned int d>
concept between_2_and_3 = d == 3 || d == 2;

