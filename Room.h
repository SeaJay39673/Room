#ifndef ROOM_H
#define ROOM_H

#include <vector>
#include <map>
#include <iostream>
#include <time.h>
#include <algorithm>

using std::vector, std::map, std::cout, std::endl;

enum DoorLoc
{
    Left,
    Top,
    Right,
    Bottom,
    None
};

class Room
{
private:
    static int roomCount;     // Number of rooms created
    static Room *finalRoom;   // The final room
    static int possibleDoors; // Possible rooms to visit
    static int doorsVisited;  // Number of rooms visited
    map<DoorLoc, Room *> roomMap;
    vector<DoorLoc> doors;

    // randomly generate the doors in the room
    void generateDoors(DoorLoc previous = None, Room *rm = nullptr)
    {
        srand(time(0));
        vector<DoorLoc> roomsAvailable = {Left, Top, Right, Bottom};

        // If previous room exists, set door to previous
        if (previous != None)
        {
            roomsAvailable.erase(roomsAvailable.begin() + roomsAvailable.at(previous));
            roomMap[previous] = rm;
            doors.push_back(previous);
        }

        // Generate random number of doors from 0 - size of rooms available
        int numDoors = rand() % roomsAvailable.size() + (previous != None ? 0 : 1);
        possibleDoors += numDoors; // possible doors is the int of total possible doors in the current game
        int door;

        // Generate the doors
        for (int i = 0; i < numDoors; i++)
        {
            door = rand() % roomsAvailable.size();
            roomMap[roomsAvailable[door]] = nullptr;
            doors.push_back(roomsAvailable[door]);
            roomsAvailable.erase(roomsAvailable.begin() + door);
        }
    }

public:
    Room()
    {
        generateDoors();
    }

    // Generate room with a door to the previous room
    Room(DoorLoc previous, Room *rm)
    {
        roomCount++;
        if (finalRoom == nullptr) // If finalRoom not already found, search for it
        {
            if (doorsVisited >= possibleDoors) // If all doors are visited, make this room the final room
            {
                finalRoom = this;
                cout << "CONGRATULATIONS! You have found the final room!\n";
            }
            else // If not all doors are visited, chance for this room to be the final room
            {
                int random = rand() % 501;
                if (random < roomCount)
                {
                    finalRoom = this;
                    cout << "CONGRATULATIONS! You have found the final room!\n";
                }
            }
        }
        if (finalRoom != this) // If not final room, generate doors
        {
            generateDoors(previous, rm);
        }
        else // If final room, assign previous door
        {
            roomMap[previous] = rm;
            doors.push_back(previous);
        }
    }

    vector<DoorLoc> GetDoors() const
    {
        return doors;
    }

    Room *GetRoomFromDoor(DoorLoc door)
    {
        DoorLoc previous = None;
        if (roomMap.count(door)) // Calculate previous door from the door we're entering (the opposite door)
        {
            if (roomMap[door] == nullptr)
            {
                switch (door)
                {
                case Top:
                    previous = Bottom;
                    break;
                case Bottom:
                    previous = Top;
                    break;
                case Left:
                    previous = Right;
                    break;
                case Right:
                    previous = Left;
                    break;
                }
                doorsVisited++; // If we're creating this for the first time, increment doors visited
                roomMap[door] = new Room(previous, this);
            }
            return roomMap[door];
        }
        return nullptr;
    }

    void displayRoom()
    {
        cout << "\n\n";
        if (roomMap.count(Top))
        {
            cout << "\tTOP" << ((roomMap[Top] != nullptr) ? "(Visited)\n\n" : "\n\n");
        }
        if (roomMap.count(Left))
        {
            cout << "LEFT" << ((roomMap[Left] != nullptr) ? "(Visited)" : "");
        }
        if (roomMap.count(Right))
        {
            cout << "\t\tRight" << ((roomMap[Right] != nullptr) ? "(Visited)\n\n" : "\n\n");
        }
        else
        {
            cout << "\n\n";
        }
        if (roomMap.count(Bottom))
        {
            cout << "\tBottom" << ((roomMap[Bottom] != nullptr) ? "(Visited)\n" : "\n");
        }
        cout << "\n\n";
    }
};

int Room::roomCount = 0;
Room *Room::finalRoom = nullptr;
int Room::possibleDoors = 0;
int Room::doorsVisited = 0;

#endif