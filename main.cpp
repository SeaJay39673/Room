#include <iostream>
#include <string>
#include <conio.h>

#include "Room.h"

using std::cout;

enum Keys
{
    LeftArrow = 75,
    UpArrow = 72,
    RightArrow = 77,
    DownArrow = 80,
    Escape = 27
};

char menu();
void printDoor(DoorLoc door);
int processInput(char ch);
bool isValidDoor(vector<DoorLoc> doors, DoorLoc door);

int main()
{
    Room *currentRoom = new Room;
    vector<DoorLoc> doors;
    char ch;
    int res;
    while (true)
    {
        cout << "ROOM:\n";
        doors = currentRoom->GetDoors();
        currentRoom->displayRoom();
        ch = menu();
        res = processInput(ch);
        if (res == -1)
        {
            cout << "GoodBye\n";
            return 0;
        }
        if (res == -2 || !isValidDoor(doors, (DoorLoc)res))
        {
            cout << "INVALID INPUT: TRY AGAIN\n";
            continue;
        }

        currentRoom = currentRoom->GetRoomFromDoor((DoorLoc)res);
    }
}

char menu()
{
    char ch;
    cout << "Which door would you like to enter? (Esc to exit): ";
    ch = _getch();
    cout << endl;
    return ch;
}

void printDoor(DoorLoc door)
{
    switch (door)
    {
    case Left:
        cout << "Left\n";
        break;
    case Top:
        cout << "Top\n";
        break;
    case Right:
        cout << "Right\n";
        break;
    case Bottom:
        cout << "Bottom\n";
        break;
    }
}

int processInput(char ch)
{
    switch (ch)
    {
    case LeftArrow:
        return Left;
    case UpArrow:
        return Top;
    case RightArrow:
        return Right;
    case DownArrow:
        return Bottom;
    case Escape:
        return -1;
    default:
        return -2;
    }
}

bool isValidDoor(vector<DoorLoc> doors, DoorLoc door)
{
    return std::find(doors.begin(), doors.end(), door) != doors.end();
}