#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <set>
#include <iterator>

/* ========================================================================== */

	// Есть необходимость хранить список удаленных ip-адресов серверов в отдельном txt файле.
	// Каждый сервер должен храниться в отдельной строке файла.
	// Реализовать три функции:
	// 	GetServersList() – возвращает список серверов из файла;
	// 	AddServer() – добавляет сервер в файл;
	// 	DeleteServer() – удаляет сервер из файла. 
	// Сигнатура функций заранее не определена. 

/* ========================================================================== */

class Servers
{
    std::string pathToServersFile;
    std::set<std::string> servers;

public:
    
    // – возвращает список серверов из файла;
    void GetServersList(bool isSyncMode = false) 
    {
        std::string line;
        this->servers.clear();
        std::fstream in(this->pathToServersFile);
        if (in.is_open())
        {
            while (getline(in, line))
            {
                this->servers.emplace(line);
                // если syncMode выключен то выводим список серверов
                if (!isSyncMode) {
                    std::cout << line << std::endl;
                }
            }
        } else {
            std::cout<<"Can't open file"<<std::endl;
        }
        in.close();
    }

    // – добавляет сервер в файл;
	void AddServer(std::string server) 
    {
        std::ofstream out(this->pathToServersFile, std::ios::app); 

        if (out.is_open())
        {
            out << server << std::endl;
        }                        
        out.close();  
    }

    // 	DeleteServer() – удаляет сервер из файла. 
    void DeleteServer(std::string delServer)
    {
        // Синхронизация содержимого файла и свойства this->servers // где set<string>
        this->GetServersList(true);
        
        if (this->servers.find(delServer) == this->servers.end()) {
            
            std::cout << "Server " << delServer << " is not exists" << std::endl;

        } else {

            // удаляем сперва из Множества
            this->servers.erase(delServer);

            std::ofstream file(this->pathToServersFile, std::ios::trunc); // если ios::app то он добавляет в файл
            
            if (file.is_open())
            {
                copy(this->servers.begin(), this->servers.end(), std::ostream_iterator<std::string>(file, "\n"));
            } else {
                std::cout<<"Can't open file"<<std::endl;
            }
            std::cout << "Server " << delServer << " was deleted" << std::endl;
            file.close();
        }   
    }

    Servers(std::string FilePathServers)
    {
        this->pathToServersFile = FilePathServers;
    }

    ~Servers() = default;
};

/* ========================================================================== */

int main()
{
    
    Servers test("ips.txt");

    test.AddServer("192.23.54.91");
    test.AddServer("192.23.54.92");
    test.AddServer("192.23.54.93");
    test.AddServer("192.23.54.94");

    std::cout << "Before Deleting" << std::endl;
    test.GetServersList();
    

    test.DeleteServer("192.23.54.93");
    test.DeleteServer("192.23.54.96");

    std::cout << "After Deleting" << std::endl;
    test.GetServersList();
    std::cout << std::endl;
    return EXIT_SUCCESS;
}

/*
rb02@RB02MB:~/Develop/CPP/CPPvac$ ./CPPvac_task2
Before Deleting
192.23.54.91
192.23.54.92
192.23.54.93
192.23.54.94
Server 192.23.54.93 was deleted
Server 192.23.54.96 is not exists
After Deleting
192.23.54.91
192.23.54.92
192.23.54.94
*/