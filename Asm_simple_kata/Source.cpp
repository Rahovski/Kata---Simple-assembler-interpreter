#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string parse_command(string command, unsigned int& index_in_str) {
	string result;
	while ((index_in_str != command.length()) && (command[index_in_str] != ' ')) {
		result += command[index_in_str];
		index_in_str++;
	}
	index_in_str++;
	return result;
}

static int& getReg(unordered_map<string, int>& regs, string name) {
	return regs[name];
}

unordered_map<string, int> assembler(const vector<string>& program) {
	unordered_map<string, int> reg_info;
	for (unsigned int i = 0; i < program.size(); i++) {
		unsigned int index = 0;
		string command = parse_command(program[i], index);
		string reg = parse_command(program[i], index);
		if (command == "mov") {
			string value = parse_command(program[i], index);
		}
		else if (command == "inc") {

		}
		else if (command == "dec") {

		}
		else if (command == "jnz") {
			string value = parse_command(program[i], index);
		}
	}
	return reg_info;
}

int main() {
	unsigned int comm = 0;
	cin >> comm;
	cin.ignore();
	vector<string> asm_command;
	for (unsigned int i = 0; i < comm; i++) {
		string command;
		getline(cin, command);
		asm_command.push_back(command);
	}
	unordered_map<string, int> answer = assembler(asm_command);
	return 0;
}