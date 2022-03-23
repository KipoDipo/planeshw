#pragma once
#include <iostream>

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

Plane CreatePlane()
{
	long long int id;
	char name[256];
	char type[256];
	long long int flights;
	std::cin >> id >> name >> type >> flights;
	return Plane(id, name, type, flights);
}