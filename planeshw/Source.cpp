#include <iostream>
#include <fstream>
#define FILE_PATH "Planes.db"

using namespace std;

class Plane
{
private:
	long long int Flights;
	long long int ID;
	char FirstName[256];
	char LastName[256];
public:
	Plane()
	{
	}
	Plane(const long long int ID, const char* Name, const char* Type, const long long int Flights)
	{
		this->ID = ID;
		strcpy_s(FirstName, Name);
		strcpy_s(LastName, Type);
		this->Flights = Flights;
	}
	long long int GetID() const
	{
		return ID;
	}
	void Print() const
	{
		std::cout << ID << " " << FirstName << " " << LastName << " " << Flights << std::endl;
	}
};

Plane CreatePlaneFromInput()
{
	long long int id;
	char name[256];
	char type[256];
	long long int flights;
	std::cin >> id >> name >> type >> flights;
	return Plane(id, name, type, flights);
}

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