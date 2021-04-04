#include <gtest/gtest.h>

#include <iostream>
#include <meta/info.hpp>

#include "mktview/version.hpp"

TEST(ut_version, version) {
    std::cout << miu::mktview::version() << std::endl;
    std::cout << miu::mktview::build_info() << std::endl;

    std::cout << miu::meta::info() << std::endl;
}
