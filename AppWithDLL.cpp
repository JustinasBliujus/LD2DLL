#include "../DLL/Dll.h"
int main()
{
    // Measure start time
    ManageTimer(TimerAction::TIMER_START);
 
    // Prompt the user to input username, day, and timeInterval
    string username;
    string days;
    string timeInterval;
    string pause;
    std::cout << "Enter username to limit his time: ";
    std::getline(std::cin, username);

    std::cout << "Enter day (e.g., M-Su): ";
    std::getline(std::cin, days);

    std::cout << "Enter time interval (e.g., 18:00-20:00): ";
    std::getline(std::cin, timeInterval);

    // Call modifyUserTime with user input
    modifyUserTime(username, days, timeInterval);

    std::cout << "Testi darba?";
    std::getline(std::cin, pause);

    // Create directory structure
    createDirectoriesAndFiles(name, surname);

    std::cout << "Testi darba?";
    std::getline(std::cin, pause);

    // Calculate and write data for different F values
    double x0 = -(2210328 % 19); 
    double xn = 2210328 % 25;   
    double dx = 2210328 / 100000000.0;
    double FValues[] = { -2, -1, 0, 1, 2 };
    int numFValues = sizeof(FValues) / sizeof(FValues[0]);
 
    for (int i = 0; i < numFValues; ++i) {
    
        calculateAndWriteData(FValues[i], x0, xn, dx);
        // Merge and sort files
        int Fvalue = FValues[i];
        string fileName = "output_F=" + to_string(Fvalue) + ".txt";
        mergeAndSortFiles("Surname", fileName);
    }

    std::cout << "Testi darba?";
    std::getline(std::cin, pause);
    // Delete files
    deleteDirectories(name, surname);
    // Measure end time
    ManageTimer(TimerAction::TIMER_END);
    double elapsedTime = GetElapsedTime();
    std::cout << "Elapsed Time: " << elapsedTime << " seconds\n";
    std::cout << "Baigti darba?";
    std::getline(std::cin, pause);

    return 0;
}
