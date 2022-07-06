#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class IO
{

public:

	string read(string vertexPath, string fragmentPath) {
        // 1. retrieve the vertex/fragment source code from filePath
        string E_TEXT;
        ifstream E_FILE;
        // ensure ifstream objects can throw exceptions:
        E_FILE.exceptions(ifstream::failbit | ifstream::badbit);
        try{
            // open files
            E_FILE.open(vertexPath);
            std::stringstream E_Stream;
            // read file's buffer contents into streams
            E_Stream << E_FILE.rdbuf();

            // close file handlers
            E_FILE.close();
            // convert stream into string
            E_TEXT = E_Stream.str();
        }
        catch (std::ifstream::failure& e){
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: " << e.what() << std::endl;
        }
        return E_TEXT;
	}
};

