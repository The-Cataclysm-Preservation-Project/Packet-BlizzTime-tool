#include "Define.h"
#include <string>

#ifndef BLIZZTIME_H
#define BLIZZTIME_H

namespace BlizzTime
{
    void ReadBlizzDate();
    void CreateBlizzDate();

    uint32 GenerateBlizzPacketDate(uint32 year, uint32 month, uint32 day, uint32 hour);

    void ShowMenu();
}

#endif //BLIZZTIME_H