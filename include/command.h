#pragma once
#include<string>
#include<vector>

class command
{
public:
	command(int n) : dynamicLevel(0) {
		if (n > 0) {
			N = n;
		}
		else
			N = -1;
	}

	void in();
private:
	void finalizePacket();
	void commitPacket();
	void ComOut();
	void ParserLeftBrake();
	void ParserRightBrake();
	bool IsCommand(std::string str)
	{
		// заглушка на будушее
		// например функция проверяет синтаксис комманды
		return true;
	}
	bool IS()
	{
		return  N>0;
	}
	int dynamicLevel; // Уровень вложенности динамических блоков
	int N;
	std::vector<std::string> batch;
};

void command::finalizePacket()
{
	// Если после завершения ввода остались команды вне динамического блока — обрабатываем их
	if (!batch.empty() && dynamicLevel == 0) {
		ComOut();

	}
}
void command::in()
{
	//N = 3;
	std::string str;
	if (!IS())return;
	while (std::getline(std::cin, str)) {
		if (str == "EOF" || str == "eof" )break;
		if (!str.empty()&& IsCommand(str)) {
			if (str == "{") {
				ParserLeftBrake();
				
				continue;
			}
		}
		if (str == "}") {
			ParserRightBrake();

			continue;
		}
		// Добавляем команду в пакет
		batch.push_back(str);
		commitPacket();
		
	}
	finalizePacket();
}
void command::commitPacket() {
	if ((int)batch.size() >= N && dynamicLevel == 0) {
		int i = 0;
		
		ComOut();

		batch.clear();
	}
}
void command::ParserRightBrake() {
	if (dynamicLevel > 0) {
		dynamicLevel--;
		if (dynamicLevel == 0) {
			// Завершаем текущий пакет, если он есть
			if (!batch.empty()) {
						
				
					ComOut();
				
				batch.clear();
			}
			N--;
		}
	}
	
}
void command::ParserLeftBrake()
{
	
		if (dynamicLevel == 0) {
			if (!batch.empty()) {
				
				ComOut();
				batch.clear();
			}
			N++;
		}
		dynamicLevel++;

	
}

void command::ComOut()
{
	int i = 0;
	std::cout << "bulk: ";
	for (const auto& cmd : batch) {

		std::ofstream out("bulk" + std::to_string(std::time(0)) + ".log");
		std::cout << cmd;
		out << cmd << std::endl;		
		std::this_thread::sleep_for(std::chrono::seconds(1));
		out.close();
		i++;
		if (i < batch.size()) {
			std::cout << ", ";
		}
		else
			std::cout << std::endl;
	
	}
}
