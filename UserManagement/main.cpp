#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

int display_menu()
{
	int choice = 0;

	bool valid = false;

	while (valid == false)
	{
		std::cout << "1. Show registered users" << std::endl;
		std::cout << "2. Register a new user" << std::endl;
		std::cout << "3. Delete a registered user" << std::endl;
		std::cout << "4. Delete all users" << std::endl;
		std::cout << "5. Exit" << std::endl;
		std::cout << "choice: ";
		std::cin >> choice;
		if (1 <= choice && choice <= 5)
			valid = true; 
	}
	return choice;
}

std::string capitalize(std::string text)
{
	std::string capitalized_text;
	capitalized_text += toupper(text[0]);
	for (int i=1;i<text.size();i++)
	{
		capitalized_text += text[i];
	}
	return capitalized_text;
}

std::vector<std::string> format_display(std::string line)
{
	std::vector<std::string>data_return;

	std::string name;
	std::string age;
	std::string expire_date;

	std::string actual;
	bool append = false;
	int counter = 0;
	for(int i = 0; i < line.size(); i++)
	{
		
		if (line[i]==':')
		{
			append = true;
			counter++;
		}
		else if (line[i]==',')
		{
			append = false;
			if(counter==1)
			{
				name = actual;
			}
			else if (counter==2)
			{
				age = actual;
			}
			else
			{
				expire_date = actual;
			}
			actual = "";

		}
		else if (append == true)
		{
			actual += line[i];
		}
	}
	std::cout << name << " " << age << " " << expire_date << std::endl;
	data_return.push_back(capitalize(name));
	data_return.push_back(age);
	data_return.push_back(expire_date);

	return data_return;

}

std::string spaces(int n, std::string a) {
	std::string s = "";
	for (int i = 0; i < n; ++i) s += a;
	return s;
}

int display_registered_users()
{
	std::ifstream registered("registered_users.txt");
	std::string line;
	std::vector<std::vector<std::string>> data;

	int blank_line_spaces = 10;
	while (std::getline(registered,line))
	{	
		data.push_back(format_display(line));
	}
	std::cout << spaces(120, "_") << std::endl;
	std::cout << "Name" << spaces(11, " ") << "Age" << spaces(12, " ") << "Expiry" << spaces(9, " ") << std::endl;
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = 0; j<3;j++)
		{
			std::cout << data[i][j] << spaces(abs(static_cast<int>(data[i][j].size()) - 15), " ");
		}
		std::cout << std::endl;
	}
	std::cout << spaces(120, "_") << std::endl;
	return 0;
}

void create_user(std::string name, std::string age, std::string expire_date)
{
	std::ofstream registered("registered_users.txt", std::ios_base::app);
	registered << "name :" + name + ", age:" + age + ", expire_date:" + expire_date + ",\n";
	
}

void show_deleteable_users()
{
	std::ifstream file("registered_users.txt");
	std::string line;
	int counter = 0;
	std::cout << spaces(120, "_") << std::endl;
	bool append = false;
	std::string name;
	std::string age;
	std::string expire_date;
	std::string actual;
	int line_nr = 1;
	while (std::getline(file, line))
	{
		for (int i = 0; i < line.size(); i++)
		{

			if (line[i] == ':')
			{
				append = true;
				counter++;
			}
			else if (line[i] == ',')
			{
				append = false;
				if (counter == 1)
				{
					name = actual;
				}
				else if (counter == 2)
				{
					age = actual;
				}
				else
				{
					expire_date = actual;
				}
				actual = "";

			}
			else if (append == true)
			{
				actual += line[i];
			}
		}
		std::cout << line_nr << " | " << name << spaces(abs(static_cast<int>(name.size()) - 15), " ") << age << spaces(abs(static_cast<int>(age.size()) - 15), " ") << expire_date << std::endl;
		line_nr++;
	}
}

void delete_user(int index)
{
	//line.replace(line.find(deleteline),deleteline.length(),"");
	std::ifstream filein("registered_users.txt"); //File to read from
	std::ofstream fileout("temp.txt"); //Temporary file

	std::string strTemp;
	int actual_index = 1;
	while (filein >> strTemp)
	{
		if (actual_index == index) {
			strTemp = "";
		}
		strTemp += "\n";
		fileout << strTemp;
		actual_index++;
	}
	std::string line;
	//For writing text file
	//Creating ofstream & ifstream class object
	std::ifstream ini_file{ "temp.txt" };
	std::ofstream out_file{ "registered_users.txt" };

	while (getline(ini_file, line)) {
		out_file << line << "\n";
	}



	//Closing file
	ini_file.close();
	out_file.close();

	remove("temp.txt");
	
}

void remove_all()
{
	remove("registered_users.txt");
	std::cout << spaces(120, "_");
	for (int i = 0; i < 101; i++)
	{
		if (i % 10 == 0)
		{
			std::string loading = "[";
			for (int j = 0; j < static_cast<int>(i / 10); j++)
			{
				loading += "#";
			}
			for (int j = 0; j < abs(static_cast<int>(i / 10) - 10); j++)
			{
				loading += ".";
			}
			loading += "]";
			std::cout << "Deleting. . ." << loading << "\r";
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
	std::cout << "Success !" << std::endl;
	std::cout << spaces(120, "_");
}

int main(int argc, char* argv[])
{
MENU_DISPLAY:
	const int choice = display_menu();

	if (choice == 1)
	{
		display_registered_users();
	}
	else if (choice == 2)
	{
		std::cout << spaces(120, "_") << std::endl;
		std::string name;
		std::string age;
		std::string expiry;

		std::cout << "Enter User's name: ";
		std::cin >> name;
		std::cout << std::endl << "Enter User's age: ";
		std::cin >> age;
		std::cout << std::endl << "Enter User's expiry: ";
		std::cin >> expiry;

		create_user(name, age, expiry);
	}
	else if (choice == 3)
	{
		int index;
		show_deleteable_users();
		std::cout << spaces(120, "_") << std::endl;
		std::cout << "Choose by index(-1 to cancel): ";
		std::cin >> index;
		if (index != -1)
		{
			delete_user(index-1);
		}
		std::cout << spaces(120, "_") << std::endl;
	}
	else if (choice == 4)
	{
		remove_all();
	}
	else
	{
		return 0;
	}
	goto MENU_DISPLAY;
}
