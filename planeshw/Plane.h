#pragma once

class Plane
{
private:
	long long int Flights;
	long long int ID;
	char FirstName[256];
	char LastName[256];
public:
	Plane();
	Plane(const long long int ID, const char* Name, const char* Type, const long long int Flights);
	long long int GetID() const;
	void Print() const;
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