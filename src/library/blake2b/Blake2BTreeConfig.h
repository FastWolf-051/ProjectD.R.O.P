#pragma once

class Blake2BTreeConfig {
public:
    int FanOut;
    int IntermediateHashSize;
    int MaxHeight;

    long long LeafSize;

    Blake2BTreeConfig() {
        FanOut = 0;
        IntermediateHashSize = 0;
        LeafSize = 0;
        MaxHeight = 0;
    }

    static Blake2BTreeConfig CreateInterleaved(int parallel) {
        Blake2BTreeConfig result;

        result.FanOut = parallel;
        result.MaxHeight = 2;
        result.IntermediateHashSize = 64;

        return result;
    }
};
