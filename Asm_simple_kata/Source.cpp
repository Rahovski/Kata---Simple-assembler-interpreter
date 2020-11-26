/* https://www.codewars.com/kata/58e24788e24ddee28e000053/train/cpp  */

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string parse_command(string command, unsigned int& index_in_str) {
	string result = "";
	while (index_in_str < command.length()) {
		if ((command[index_in_str] != ' ')) {
			result += command[index_in_str];
			index_in_str++;
		}
		else {
			index_in_str++;
			return result;
		}
	}
	index_in_str++;
	return result;
}

static int& getReg(unordered_map<string, int>& regs, string name) {
	return regs[name];
}

void execute_command(unordered_map<string, int>& regs, string command, string reg, string val = "") {
	if (command == "mov") {
		if (isdigit(val[0]) || val[0] == '-') {
			int value = stoi(val);
			//regs[reg] = value;
			getReg(regs, reg) = value;
		}
		else {
			getReg(regs, reg) = getReg(regs, val);
		}
	}
	else if (command == "inc") {
		//regs[reg]++;
		getReg(regs, reg)++;
	}
	else if (command == "dec") {
		//regs[reg]++;
		getReg(regs, reg)--;
	}
}

unordered_map<string, int> assembler(const vector<string>& program) {
	unordered_map<string, int> reg_info;
	for (unsigned int i = 0; i < program.size(); i++) {
		unsigned int index = 0;
		string command = parse_command(program[i], index);
		if (command != "jnz") {
			string reg = parse_command(program[i], index);
			string str_value = parse_command(program[i], index);
			execute_command(reg_info, command, reg, str_value);
		}
		else {
			string reg = parse_command(program[i], index);
			//need to work with
			//jnz b - 2 (+++)
			//jnz 5 10 (---)
			string str_value = parse_command(program[i], index);
			int value = stoi(str_value);
			//
			index = 0;
			if ((i + value < 0) || (i + value >= program.size())) {
				continue;
			}
			if (getReg(reg_info, reg)) {
				i = i + value - 1;
			}
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