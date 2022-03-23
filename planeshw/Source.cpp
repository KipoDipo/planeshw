#include <iostream>
#include <fstream>
#include "Plane.h"
#define FILE_PATH "Planes.db"

using namespace std;

int GetElementCountFromFile(ifstream& stream, int sizeOfClass)
{
	stream.seekg(0, stream.end);
	int length = stream.tellg() / sizeOfClass;
	stream.seekg(0, stream.beg);
	return length;
}

int main()
{
	ofstream outFile(FILE_PATH, ios::binary | ios::app);

	if (!outFile.is_open())
	{
		cout << "err...";
		return -1;
	}

	char command[32];
	while (strcmp(command, "exit") != 0)
	{
		cin >> command;
		if (strcmp(command, "create") == 0)
		{
			Plane newPlane = CreatePlaneFromInput();
			outFile.write(reinterpret_cast<const char*>(&newPlane), sizeof(newPlane));
			cout << "Record saved!\n";
		}
		else if (strcmp(command, "search") == 0)
		{
			long long int id;
			cin >> id;
			bool hasFoundId = false;

			ifstream inFile(FILE_PATH, ios::binary);

			int planesInFile = GetElementCountFromFile(inFile, sizeof(Plane));
			Plane* planes = new Plane[planesInFile];

			for (int i = 0; i < planesInFile; i++)
			{
				inFile.read(reinterpret_cast<char*>(&planes[i]), sizeof(Plane));
				if (planes[i].GetID() == id)
				{
					planes[i].Print();
					hasFoundId = true;
					break;
				}
			}

			if (!hasFoundId)
				cout << "Record not found!\n";

			delete[] planes;
			inFile.close();
		}
		outFile.flush();
	}
	outFile.close();
}