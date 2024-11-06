#include <iostream>
#include "headers/init.hpp"
#include <fstream>
#include <string>
#include <sstream>

void displayDispo(const std::vector<unsigned int> vec)
{
    for (unsigned int i : vec)
    {
        std::cout << i;
    }
}

std::ostream &operator<<(std::ostream &os, const std::unordered_map<int, std::pair<int, Source>> map)
{
    for (const std::pair p : map)
    {
        os << "( id=" << p.first << " , nb=" << p.second.first << " )" << std::endl;
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, Init_info infos)
{
    os << std::endl
       << "Dimension de la scene : (" << infos.largeur << " | " << infos.hauteur << ")" << std::endl
       << "Pas spatial : " << infos.h << std::endl
       << "Pas temporel : " << infos.k << std::endl
       << "Conductivite : " << infos.conductivite << std::endl
       << "Densite : " << infos.densite << std::endl
       << "Capacite : " << infos.capacite << std::endl
       << "Sources (" << infos.nb_sources << ") : " << infos.sources << std::endl
       << "Disposition : " << infos.disposition.size();

    return os;
}

std::vector<std::string> splitString(std::string str)
{
    std::stringstream ss(str);
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> split_line(begin, end);
    return split_line;
}

void FileSC::readFile(Init_info &infos)
{
    std::ifstream my_file;

    my_file.open(PATH);
    if (my_file.is_open())
    {
        std::string my_line;
        while (getline(my_file, my_line))
        {
            std::vector<std::string> split_line = splitString(my_line);

            if (my_line._Starts_with("largeur"))
            {
                infos.largeur = std::stoi(split_line[1]);
            }
            else if (my_line._Starts_with("hauteur"))
            {
                infos.hauteur = std::stoi(split_line[1]);
            }
            else if (my_line._Starts_with("h"))
            {
                infos.h = std::stod(split_line[1]);
            }
            else if (my_line._Starts_with("k"))
            {
                infos.k = std::stod(split_line[1]);
            }
            else if (my_line._Starts_with("conductivite"))
            {
                infos.conductivite = std::stod(split_line[1]);
            }
            else if (my_line._Starts_with("densite"))
            {
                infos.densite = std::stod(split_line[1]);
            }
            else if (my_line._Starts_with("capacite"))
            {
                infos.capacite = std::stod(split_line[1]);
            }
            else if (my_line._Starts_with("air"))
            {
                infos.sources.insert({std::stoi(split_line[1]), {1, std::stoi(split_line[2])}});
                infos.nb_sources++;
            }
            else if (my_line._Starts_with("radiateur") || my_line._Starts_with("fenetre") || my_line._Starts_with("scene"))
            {
                infos.sources.insert({std::stoi(split_line[1]), {std::stoi(split_line[2]), std::stoi(split_line[3])}});
                infos.nb_sources += std::stoi(split_line[2]);
            }
            else if (my_line._Starts_with("scene"))
            {
                for (const char c : split_line[1])
                {
                    infos.disposition.push_back(std::stoi(std::string(1, c)));
                }
            }
        }
    }
    else
    {
        std::cout << "Couldn't open file\n";
    }
}