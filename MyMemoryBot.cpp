#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class MyMemoryBot {
public:
	MyMemoryBot(const string& filename) : memory("memory.txt") {}

	// Funciton to remember a new item
	void remember(const string& item) {
		ofstream outFile(memory, ios::app); // Okpen file in append mode
		if (outFile.is_open()) {
			outFile << item << endl; // Write item to file
			outFile.close(); // Close the file
			cout << "MyMemoryBot: I've stored that for you!" << endl;
		}
		else {
			cout << "MyMemoryBot: Oops! I couldn't open the memory file." << endl;
		}
	}

	// Function to recall all memories
	void recallAll() {
		ifstream inFile(memory);
		if (inFile.is_open()) {
			string line;
			cout << "MyMemoryBot: Here's everything I remember: " << endl;
			while (getline(inFile, line)) {
				cout << " - " << line << endl; //Print each memory
			}
			inFile.close(); // Close the file
		}
		else {
			cout << "MyMemoryBot: I can't access my memories. Did I lose my file?" << endl;
		}
	}

	// Function to recall a specific memory
	void recallSpecific(const string& item) {
		ifstream inFile(memory);
		if (inFile.is_open()) {
			string line;
			bool found = false;
			while (getline(inFile, line)) {
				if (line == item) {
					cout << "MyMemoryBot: I remember that! It's: " << line << endl;
					found = true;
					break; // Exit loop if found
				}
			}
			inFile.close(); // Close the file
			if (!found) {
				cout << "MyMemoryBot: Sorry, I don't recall that specific memory." << endl;
			}
		}
		else {
				cout << "MyMemoryBot: I can't access my memories. Did I lose my file?" << endl;
			}
		}

private:
	string memory; // Name of the memory file
	
};

int main() {
	cout << "Welcome to MyMemoryBot!" << endl;
	cout << "Your friendly memory assistant. Type 'help' for commands." << endl;

	MyMemoryBot bot("memories.txt"); // Initialize MyMemoryBot with a file name
	string command, input;

	while (true) {
		cout << "> ";
		getline(cin, command); // Get user input

		// Process commands
		if (command == "help") {
			cout << "Commands:" << endl;
			cout << " remember <something> - I will remember it for you." << endl;
			cout << " recall all - I will recall everything I've remembered." << endl;
			cout << " recall <something> - I will try to recall that specific memory." << endl;
			cout << " exit - Goodbye!" << endl;
		}
		else if(command.substr(0,8) == "remember") {
			input = command.substr(9); // Extract the memory to remember
			if (input.empty()) {
				cout << "MyMemoryBot: You need to tell me something to remember!" << endl;
			}
			else {
				bot.remember(input);
			}
		}
		else if (command == "recall all") {
			bot.recallAll();
		}
		else if (command.substr(0, 6) == "recall") {
			input = command.substr(7); // Extract the specific memory to recall
			if (input.empty()) {
				cout << "MyMemoryBot: You need to specify what to recall!" << endl;
			}
			else {
				bot.recallSpecific(input);
			}
		}
		else if (command == "exit") {
			cout << "MyMemoryBot: Goodbye! I'll be here when you need me!" << endl;
			break; // Exit the loop
		}
		else {
			cout << "MyMemoryBot: I didn't understand that. Type 'help' for commands." << endl;
		}
	}

	return 0; // Indicate successful completion
}