#include<iostream>
#include<vector>
#include<fstream>
#include <sstream>
using namespace std;
struct Company {
	string name;
	string profit_tax;
	string address;
};
vector<Company>ReadListCompany(string file_name) {
	vector <Company> temp;
	std::ifstream readfile(file_name);
	if (!readfile.is_open()) {
		cout << "Can not open file\n";
		
	}
	string line;
	while (getline(readfile, line)) {
		Company company;
		std::istringstream iss (line);
		getline(iss, company.name, '|');
		getline(iss, company.profit_tax, '|');
		getline(iss, company.address);
		temp.push_back(company);
	}
	return temp;

}

unsigned long long HashString(string company_name) {
	const int p = 31;
	int m = 1000000009;
	string s = company_name;
	if (s.size() > 20) {
		s = s.substr(s.size() - 20);
	}
	unsigned long long hash_value = 0;

	for (int i = 0; i < s.size(); ++i) {
		char c = s[i];
		hash_value = (hash_value + (static_cast<unsigned long long>(c) * static_cast<unsigned long long>(pow(p, i))) % m) % m;
	}

	return hash_value;
}
Company* CreateHashTable(vector<Company> list_company) {
	int size = 5000;
	Company* table = new Company[size];
	for (Company temp : list_company) {
		int i = 0;
		int index = HashString(temp.name) % size;
		while (table[index].name != "") {
			index = (index + i) % size;
			i++;
		}
		table[index] = temp;
	}
	return table;
}
void Insert(Company* hash_table, Company company) {
	int size = 5000;
	int index = HashString(company.name) % 5000;
	int i = 0;
	while (hash_table[index].name != "") {
		index = (index + i) % size;
		i++;
	}
	hash_table[index] = company;
}
Company Search(Company* hash_table, string company_name) {
	int size = 5000;
	int index = HashString(company_name) % size;
	int i = 0;
	while (i > size && hash_table[index].name != company_name && hash_table[index].name != "") {
		index = (index + i) % size;
		i++;
	}
	if (hash_table[index].name == company_name) {
		return hash_table[index];
	}
	else {
		return { "", "", "" };
	}

}
int main() {
	string file_name = "MST.txt";
	vector<Company> companies = ReadListCompany(file_name);

	Company* hash_table = CreateHashTable(companies);

	// Example: Insert a new company
	Company new_company = { "NewCompany", "123456789", "New Address" };
	Insert(hash_table, new_company);

	// Example: Search for a company
	string company_to_search = "CONG TY TNHH NONG NGHIEP CONG NGHE CAO MIEN DONG VIET";
	Company result = Search(hash_table, company_to_search);

	if (result.name != "") {
		cout << "Company found: " << result.name << ", MST: " << result.profit_tax << ", Address: " << result.address << endl;
	}
	else {
		cout << "Company not found." << endl;
	}

	// Don't forget to delete the hash table array when done using it
	delete[] hash_table;

	return 0;
}
