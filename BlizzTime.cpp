#include "BlizzTime.h"
#include "Define.h"

#include <sstream>

namespace BlizzTime
{
    void BlizzTime::ReadBlizzDate()
    {
        system("cls");
        std::cout << "-----------------------------------------------\n";
        std::cout << "Please insert a packet date in BlizzTime format\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << ">>> ";
        uint32 blizzTime = 0;
        std::cin >> blizzTime;

        uint32 year, month, dayOfWeek, dayOfMonth, hours, minutes, timeZone = 0;
        minutes = blizzTime & 0x3F;
        hours = (blizzTime >> 6) & 0x1F;
        dayOfWeek = (blizzTime >> 11) & 0x07;
        dayOfMonth = (blizzTime >> 14) & 0x3F;
        month = (blizzTime >> 20) & 0xF;
        year = (blizzTime >> 24) & 0x1F;
        timeZone = (blizzTime >> 29) & 0x03;

        year += 2000;
        month++;
        dayOfMonth++;

        std::cout << "-----------------------------------------------\n" << "The provided BlizzTime has the following data:\n\n";
        std::cout << "TimeZone: " << timeZone << "\n";
        std::cout << "Year: " << year << "\n";
        std::cout << "Month: " << month << "\n";
        std::cout << "Day of Month: " << dayOfMonth << "\n";
        std::cout << "Day of Week: " << dayOfWeek << " (" << NameOfDay[std::min<uint8>(dayOfWeek, 6)] << ")" << "\n";
        std::cout << "Hour: " << hours << "\n";
        std::cout << "Minute: " << minutes << "\n";
        std::cout << "-----------------------------------------------\n" << "Press enter to return to menu\n\n";

        system("pause");
        ShowMenu();
    }

    void BlizzTime::CreateBlizzDate()
    {
        system("cls");

        std::cout << "-----------------------------------------------\n";
        std::cout << "Please insert a date in the following format:\n";
        std::cout << "yyyy-mm-dd-hh (example: 2019-01-11-00)\n";
        std::cout << "-----------------------------------------------\n";
        std::cout << ">>> ";
        std::string date;
        std::cin >> date;

        std::string word;
        std::stringstream stream(date);
        std::vector<uint32> dateValues = { 0, 0, 0, 0 };

        uint8 i = 0;
        while (std::getline(stream, word, '-') && i < 4)
        {
            dateValues[i] = std::stoi(word);
            i++;
        }

        std::cout << "-----------------------------------------------\n";

        uint32 blizzTime = GenerateBlizzPacketDate(dateValues[0], dateValues[1], dateValues[2], dateValues[3]);
        if (blizzTime)
        {
            std::cout << "The packet BlizzTime is: \n";
            std::cout << blizzTime << "\n";
        }

        std::cout << "-----------------------------------------------\n" << "Press enter to return to menu\n\n";

        system("pause");
        ShowMenu();
    }

    void BlizzTime::ShowMenu()
    {
        system("cls");
        std::cout << "Please chose a option: \n1 - Read BlizzTime\n2 - Create BlizzTime\n-----------------------------------------------\n";
        std::string chosenOption;
        std::cin >> chosenOption;
        if (chosenOption.find("1") != std::string::npos)
            ReadBlizzDate();
        else if (chosenOption.find("2") != std::string::npos)
            CreateBlizzDate();
    }

    uint32 GenerateBlizzPacketDate(uint32 year, uint32 month, uint32 day, uint32 hour)
    {
        if (year <= 2000)
        {
            std::cout << "The provided year (" << year << ") must be at least 2001 or higher! \n";
            return 0;
        }

        if (month > 12)
        {
            std::cout << "The provided month (" << month << ") is higher than 12. What planet do you live on?! \n";
            return 0;
        }

        if (day > 31)
        {
            std::cout << "The provided day of month (" << day << ") is higher than 31. What planet do you live on?! \n";
            return 0;
        }

        if (hour > 24)
        {
            std::cout << "The provided hour (" << hour << ") is higher than 24. I know, nerds have 48 hour days but this is not how it works... \n";
            return 0;
        }

        uint32 blizzTime = ((year - 2000) << 24) | ((month - 1) << 20) | ((day - 1) << 14) | (hour << 6);

        return blizzTime;
    }
}
