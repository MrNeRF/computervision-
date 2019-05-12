#include "File.h"
#include "fstream"
#include "iostream"

File::File(const std::string &m_path_to_file) : m_path_to_file {m_path_to_file}
{
    if (m_path_to_file.empty())
    {
        std::cerr << "Errror! No filename provided!" << std::endl;
        return;
    }

    // Test, if there is no slash, i.e. file is found in the current directory.
    std::string::size_type pos = m_path_to_file.rfind("/");
    if (std::string::npos == pos)
    {
        m_filename = m_path_to_file;
    }
    else
    {
        m_filename = m_path_to_file.substr(pos + 1);
        m_directory = m_path_to_file.substr(0, pos);
    }

    // Strip file ending
    pos = m_filename.rfind(".");
    if (std::string::npos != pos)
    {
        m_fileending = m_filename.substr(pos);
        m_filename   = m_filename.substr(0, pos);
    }

    std::ifstream fileReader;
    fileReader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        fileReader.open(m_path_to_file.c_str());
        m_buffer << fileReader.rdbuf();
        fileReader.close();
    }
    catch(const std::ifstream::failure& e)
    {
        std::cerr << "ERROR: File " 
                  << m_filename + m_fileending 
                  <<  " not successfully read" << std::endl;
    }
}

