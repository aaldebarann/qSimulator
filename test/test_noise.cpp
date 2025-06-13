//
// Created by Ivanchenko Aleksey on 12/06/25.
//

#include <gtest/gtest.h>
#include "StateVector.h"

TEST(StateVector, DISABLED_amp_dump_noise) {
    StateVector s{2};

    double gamma = 0.9;
    s.h(0);
    s.h(1);
    s.z(0);
    s.ampDamp(gamma);

    Complex i(0, 1);
    vector<Complex> expected{0, -(Complex)0.0176703 + (Complex)0.51704543*i,
         0, (Complex)0.35311154-(Complex)0.32812196*i};
    vector<Complex> actual = s.getState();
    for(int i = 0; i < 4; i++)
        std::cout << actual[i] << std::endl;

    // compare expected with actual
    for(int j = 0; j < expected.size(); j++) {
        EXPECT_NEAR(expected[j].real(), actual[j].real(), 1.0e-7);
        EXPECT_NEAR(expected[j].imag(), actual[j].imag(), 1.0e-7);
    }
}