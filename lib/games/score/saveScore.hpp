/*
** ARCADE PROJECT, 2024
** arcade
** File description:
** saveScore
*/

#include <string>

#ifndef SAVESCORE_HPP_
#define SAVESCORE_HPP_

namespace arcade {
    class Error : public std::exception
    {
        public:
            Error(const std::string& errorMessage);

        private:
            std::string _errorMessage;
            const char *what() const noexcept;
    };

    class SaveScore
    {
        public :
            SaveScore();
            ~SaveScore() {};
            void getPlayerName(std::string playerName);
            void getGameName(std::string gameName);
            void getScore(size_t score);
            void setFileName();
            int saveIntoFile();

        private:
            std::string _playerName;
            std::string _gameName;
            std::string _fileName;
            std::string _filePath;
            size_t _score;
            std::string setFilePath(std::string _fileName);
    };
}

#endif /* !SAVESCORE_HPP_ */
