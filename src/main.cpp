//
// Created by Timm Felden on 15.06.18.
//

#include "empty/File.h"

#include <iostream>

int main(int argc, char **argv) {
    if (2 != argc) {
        std::cout << "provide exactly one argument" << std::endl;
        return 1;
    }

    auto sf =
            std::unique_ptr<empty::api::SkillFile>(
                    empty::api::SkillFile::open(
                            argv[1],
                            skill::api::read,
                            skill::api::readOnly
                    )
            );

    for (auto &t : *sf) {
        std::cout << t->name->c_str() << ";" << t->size() << std::endl;
    }

    return 0;
}