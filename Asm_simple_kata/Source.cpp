/* https://www.codewars.com/kata/58e24788e24ddee28e000053/train/cpp  */

//OOP solution
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
using namespace std;
static int& getReg(unordered_map<string, int>& regs, string name);
vector<string> split(string s);

class Command {
protected:
	string action_register;
	string com_argument;
public:
	virtual void command_execute(unordered_map<string, int>& regs_memory) = 0;
};

class mov_command : public Command {
public:
	mov_command(string reg, string arg) {
		action_register = reg;
		com_argument = arg;
	}
	void command_execute(unordered_map<string, int>& regs_memory) {
		if (isdigit(com_argument[0]) || com_argument[0] == '-') {
			int value = stoi(com_argument);
			//regs[reg] = value;
			getReg(regs_memory, action_register) = value;
		}
		else {
			getReg(regs_memory, action_register) = getReg(regs_memory, com_argument);
		}
	}
};

class inc_command : public Command {
public:
	inc_command(string reg) {
		action_register = reg;
	}
	void command_execute(unordered_map<string, int>& regs_memory) {
		getReg(regs_memory, action_register)++;
	}
};

class dec_command : public Command {
public:
	dec_command(string reg) {
		action_register = reg;
	}
	void command_execute(unordered_map<string, int>& regs_memory) {
		getReg(regs_memory, action_register)--;
	}
};

class jnz_command : public Command {
private:
	int jump_register = 0;
	unsigned int* num_of_command;
public:
	jnz_command(string reg, string arg, unsigned int *it) {
		action_register = reg;
		com_argument = arg;
		num_of_command = it;
		if (isdigit(action_register[0])) {
			jump_register = stoi(action_register);
		}
	}
	void command_execute(unordered_map<string, int>& regs_memory) {
		if (jump_register) {
			*num_of_command = *num_of_command + stoi(com_argument) - 1;
			jump_register--;
		}
		else if (!isdigit(action_register[0])) {
			if (getReg(regs_memory, action_register)) {
				*num_of_command = *num_of_command + stoi(com_argument) - 1;
			}
		}
	}
};

unordered_map<string, int> assembler(const vector<string>& program) {
	unordered_map<string, int> reg_info;
	vector<Command*> command_stack(program.size());
	unsigned int i = 0;
	for (i = 0; i < program.size(); i++) {
		vector<string> com_parts = split(program[i]);
		if (com_parts[0] == "mov") {
			command_stack[i] = new mov_command(com_parts[1], com_parts[2]);
		}
		else if (com_parts[0] == "inc") {
			command_stack[i] = new inc_command(com_parts[1]);
		}
		else if (com_parts[0] == "dec") {
			command_stack[i] = new dec_command(com_parts[1]);
		}
		else if (com_parts[0] == "jnz") {
			command_stack[i] = new jnz_command(com_parts[1], com_parts[2], &i);
		}
	}
	for (i = 0; i < command_stack.size(); i++) {
		command_stack[i]->command_execute(reg_info);
	}
	//free memory from object
	for (unsigned int i = 0; i < command_stack.size(); i++) {
		delete command_stack[i];
	}
	return reg_info;
}

static int& getReg(unordered_map<string, int>& regs, string name) {
	return regs[name];
}

vector<string> split(string s) {
	istringstream str(s);
	string item;
	vector<string> part_command;
	while (getline(str, item, ' ')) {
		part_command.push_back(item);
	}
	return part_command;
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