//
// Created by Matthijs Rog on 11/18/2023.
//

#include <iostream>
#include "../include/Field.h"


/**
 * @brief A brief description of main.
 * @param param1 Description of the first parameter.
 * @param param2 Description of the second parameter.
 * @return Description of the return value.
 */
int main(int argc, const char * argv[]) {
    Field field1 = Field(10, 10);
    Field field2 = Field(10, 10);

    // Fill field1 with ones and field2 with twos.
    field1.fill(1);
    field2.fill(2);

    Field field3 = field1 + field2;
    field1(1,3) = 3;

    std::cout << field1(1, 3) << " " << field3(1, 3) << std::endl;

    return 0;
}