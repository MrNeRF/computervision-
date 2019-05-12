#ifndef FILE_H
#define FILE_H

#include <string>
#include <sstream>

class File
{
    public:
        explicit File(const std::string &path_to_file);
        std::string GetFileName(void) {return m_filename;};
        std::string GetDirectory(void) {return m_directory;};
        std::string GetFileEnding(void) {return m_fileending;};
        std::string GetFileContents(void) {return m_buffer.str();}
        std::string GetFullPath(void) {return m_path_to_file;};

    private:

    std::string m_filename;
    std::string m_directory;
    std::string m_fileending;
    std::string m_path_to_file;
    std::stringstream m_buffer;
};


#endif