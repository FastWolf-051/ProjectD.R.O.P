#pragma once

class Blake2BTreeConfig {
public:
    Blake2BTreeConfig()
        : FanOut(0),
          IntermediateHashSize(64),
          LeafSize(0),
          MaxHeight(0) {
    }

    int FanOut;
    int IntermediateHashSize;
    long long LeafSize;
    int MaxHeight;

    static Blake2BTreeConfig CreateInterleaved(int parallel) {
        Blake2BTreeConfig result;

        result.FanOut = parallel;
        result.MaxHeight = 2;
        result.IntermediateHashSize = 64;

        return result;
    }
};
