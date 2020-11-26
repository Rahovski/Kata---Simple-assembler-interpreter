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

//how to avoid names with digits
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

	//flag and system register for jnz
	unsigned int jump_register = 0;//if command jnz 5 -2
	bool isJnzDone = false;

	for (unsigned int i = 0; i < program.size(); i++) {
		if (i == 6) {
			cout << "KEK" << endl;
		}
		unsigned int index = 0;
		string command = parse_command(program[i], index);
		if (command != "jnz") {
			string reg = parse_command(program[i], index);
			string str_value = parse_command(program[i], index);
			execute_command(reg_info, command, reg, str_value);
		}
		else {
			string reg = parse_command(program[i], index);
			//check, if we have jnz command - jnz (digit) -2
			if (isdigit(reg[0])) {
				if (!jump_register) {
					//if we completed jnz command, when we will go to next command
					if (isJnzDone) {
						isJnzDone = false;
						continue;
					}
					else {
						jump_register = stoi(reg);
					}
				}
			}
			string str_value = parse_command(program[i], index);
			int value = stoi(str_value);
			if ((i + value < 0) || (i + value >= program.size())) {
				continue;
			}
			if (jump_register) {
				i = i + value - 1;
				jump_register--;
				if (!jump_register) {
					isJnzDone = true;
				}
			} else  if (getReg(reg_info, reg)) {
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

/*
8
mov d 100
dec d
mov b d
jnz b -2
inc d
mov a d
jnz 5 10
mov c a


equal to [ [unsupported type], [unsupported type], [unsupported type] ]
Actual: [ [unsupported type], [unsupported type], [unsupported type], [unsupported type] ]
*/

/*
11
mov c 12
mov b 0
mov a 200
dec a
inc b
jnz a -2
dec c
mov a b
jnz c -5
jnz 0 1
mov c a

Expected: equal to [ [unsupported type], [unsupported type], [unsupported type] ]
Actual: [ [unsupported type], [unsupported type], [unsupported type], [unsupported type] ]
*/