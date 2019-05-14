#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
#include <sstream>

class File
{
    public:
        explicit File(const std::string &path_to_file);
        void GetContents(std::string &buffer);
        const std::string GetFileName(void) const {return m_filename;};
        const std::string GetDirectory(void) const {return m_directory;};
        const std::string GetFileEnding(void) const {return m_fileending;};
        const std::string GetFullPath(void) const {return m_path_to_file;};

    private:

    std::string m_filename;
    std::string m_directory;
    std::string m_fileending;
    std::string m_path_to_file;
};


#endif