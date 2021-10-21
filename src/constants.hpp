#pragma once

enum SupportedGame {
  Sword = 0x0100ABF008968000,
  Shield = 0x01008DB008C2C000,
};

namespace swsh {
  enum Pk8Offset {
    Wild = 0x8fea3648,
    WildLegend = 0x886bc058,
    Trade = 0xaf286078,
    Raid = 0x886c1ec8,
    Party = 0x450c68b0,
  };

  enum DenOffset {
    Vanilla = 0x450c8a70,
    IslandOfArmor = 0x450c94d8,
    CrownTundra = 0x450c9f40,
  };
}