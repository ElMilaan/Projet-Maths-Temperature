#include <iostream>
#include "headers/init.hpp"
#include <fstream>
#include <string>
#include <sstream>

void Init_info::displayDispo()
{
    std::cout << "Disposition : \n\n ";
    size_t index{0};
    while (index < disposition.size() - 1 && largeur != 0)
    {
        for (int i{0}; i < largeur; i++)
        {
            std::cout << disposition[index];
            index++;
        }
        std::cout << "\n ";
    }
    std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &os, const std::unordered_map<int, std::pair<int, Source>> map)
{
    for (const std::pair p : map)
    {
        os << "\n ( id=" << p.first << ",nb=" << p.second.first << " )";
    }
    return os;
}

std::ostream &operator<<(std::ostream &os, Init_info infos)
{
    os << std::endl
       << "Dimension de la scene (" << infos.largeur << " / " << infos.hauteur << ")" << std::endl
       << "Pas spatial (" << infos.h << ")" << std::endl
       << "Pas temporel (" << infos.k << ")" << std::endl
       << "Conductivite (" << infos.conductivite << ")" << std::endl
       << "Densite (" << infos.densite << ")" << std::endl
       << "Capacite (" << infos.capacite << ")" << std::endl
       << "Sources (" << infos.nb_sources << ")\n"
       << infos.sources << "\n\n";
    if (infos.disposition.size() > 0)
    {
        infos.displayDispo();
    }

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

bool openFile(std::ifstream &file, const std::string &path1, const std::string &path2)
{
    file.open(path1);
    if (!file.is_open())
    {
        file.open(path2);
    }
    return file.is_open();
}

void FileSC::readFile(Init_info &infos)
{
    std::ifstream my_file;

    if (openFile(my_file, FileSC::PATH1, FileSC::PATH2))
    {
        std::string my_line;
        while (getline(my_file, my_line))
        {
            std::vector<std::string> split_line = splitString(my_line);

            if (my_line.starts_with("largeur"))
            {
                infos.largeur = std::stoi(split_line[1]);
            }
            else if (my_line.starts_with("hauteur"))
            {
                infos.hauteur = std::stoi(split_line[1]);
            }
            else if (my_line.starts_with("h"))
            {
                infos.h = std::stod(split_line[1]);
            }
            else if (my_line.starts_with("k"))
            {
                infos.k = std::stod(split_line[1]);
            }
            else if (my_line.starts_with("conductivite"))
            {
                infos.conductivite = std::stod(split_line[1]);
            }
            else if (my_line.starts_with("densite"))
            {
                infos.densite = std::stod(split_line[1]);
            }
            else if (my_line.starts_with("capacite"))
            {
                infos.capacite = std::stod(split_line[1]);
            }
            else if (my_line.starts_with("air"))
            {
                infos.sources.insert({std::stoi(split_line[1]), {1, std::stoi(split_line[2])}});
                infos.nb_sources++;
            }
            else if (my_line.starts_with("radiateur") || my_line.starts_with("fenetre"))
            {
                infos.sources.insert({std::stoi(split_line[1]), {std::stoi(split_line[2]), std::stoi(split_line[3])}});
                infos.nb_sources += std::stoi(split_line[2]);
            }
            else if (my_line.starts_with("scene"))
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