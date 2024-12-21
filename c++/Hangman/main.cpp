#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>

std::string getRandomElement(const std::map<std::string, std::vector<std::string>>& table, const std::string& category) {
    auto it = table.find(category);
    if (it != table.end() && !it->second.empty()) {
        const auto& values = it->second;
        size_t randomIndex = rand() % values.size();
        return values[randomIndex];
    } else {
        return "";
    }
}

void renderHangman(int level) {
    const std::vector<std::string> hangmanStages = {
        "  +---+\n      |\n      |\n      |\n     ===\n",
        "  +---+\n  O   |\n      |\n      |\n     ===\n",
        "  +---+\n  O   |\n  |   |\n      |\n     ===\n",
        "  +---+\n  O   |\n /|   |\n      |\n     ===\n",
        "  +---+\n  O   |\n /|\\  |\n      |\n     ===\n",
        "  +---+\n  O   |\n /|\\  |\n /    |\n     ===\n",
        "  +---+\n  O   |\n /|\\  |\n / \\  |\n     ===\n"
    };
    std::cout << hangmanStages[level];
}

void renderWord(const std::string& word, const std::string& guessedWord, const std::vector<char>& wrongGuesses) {
    for (char c : guessedWord) {
        std::cout << c << " ";
    }
    std::cout << "\n\nWrong letters: ";
    for (char c : wrongGuesses) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";
}

void startNewGame(const std::map<std::string, std::vector<std::string>>& categories) {
    std::string category;
    std::cout << "Hangman - [New Game]\nAvailable categories:\n";
    for (const auto& pair : categories) {
        std::cout << pair.first << " | ";
    }

    std::cout << "\nChoose a category: ";
    std::cin >> category;

    std::string randomWord = getRandomElement(categories, category);
    if (randomWord.empty()) {
        std::cout << "Invalid category or no words in category.\n";
        return;
    }

    std::string guessedWord(randomWord.size(), '_');
    std::vector<char> wrongGuesses;
    int hangmanLevel = 0;
    int maxPoints = randomWord.size();
    int points = 0;

    std::cout << "\nStarting game...\nCategory: [" << category << "]\n";

    while (hangmanLevel < 6 && guessedWord != randomWord) {
        renderHangman(hangmanLevel);
        renderWord(randomWord, guessedWord, wrongGuesses);

        char guess;
        std::cout << "Enter a letter: ";
        std::cin >> guess;

        guess = tolower(guess);
        std::string lowerWord = randomWord;
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);

        if (lowerWord.find(guess) != std::string::npos) {
            bool correct = false;
            for (size_t i = 0; i < lowerWord.size(); ++i) {
                if (lowerWord[i] == guess && guessedWord[i] == '_') {
                    guessedWord[i] = randomWord[i]; // Preserve original case
                    correct = true;
                    points++;
                }
            }
            if (!correct) {
                std::cout << "Letter already guessed!\n";
            }
        } else {
            wrongGuesses.push_back(guess);
            hangmanLevel++;
            points--;
        }
    }

    if (guessedWord == randomWord) {
        std::cout << "\nYou win! The word was: " << randomWord << "\n";
        std::cout << "Your score: " << points << "/" << maxPoints << "\n";
    } else {
        renderHangman(hangmanLevel);
        std::cout << "\nGame Over! The word was: " << randomWord << "\n";
    }
}

int main() {
    std::locale::global(std::locale(""));
    std::wcout.imbue(std::locale());

    std::map<std::string, std::vector<std::string>> categories = {
        {"Cities", {"Warsaw", "Paris", "London", "Berlin"}},
        {"Animals", {"Raccoon", "Ferret", "Coyote", "Moray"}},
        {"Office Items", {"Mouse", "Monitor", "Stapler", "Folder"}},
        {"Kitchen Items", {"Pan", "Sink", "Cutlery", "Fridge"}}
    };

    srand(static_cast<unsigned int>(time(0)));

    char playAgain;
    do {
        startNewGame(categories);
        std::cout << "\nPlay again? (y/n): ";
        std::cin >> playAgain;
    } while (tolower(playAgain) == 'y');

    return 0;
}
