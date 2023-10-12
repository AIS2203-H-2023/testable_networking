
#include <catch2/catch_test_macros.hpp>

#include "network_helper.hpp"

TEST_CASE("Test network helper") {

    int i = 10;
    auto bytes = int_to_bytes(i);
    CHECK(i == bytes_to_int(bytes));

}
