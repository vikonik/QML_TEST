#include "rfmax.h"

RFMax::RFMax()
{
    packetToPcType_1  = new PacketToPcType_1_t;
    packetToPcType_2  = new PacketToPcType_2_t;
    packetToMcuType_1 = new PacketToMcuType_1_t;
    packetToMcuType_2 = new PacketToMcuType_2_t;
}
