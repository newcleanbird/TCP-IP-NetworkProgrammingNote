#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <cerrno>

void copyFileWithLowLevelIO(const char* srcPath, const char* dstPath) {
    int srcFd = open(srcPath, O_RDONLY);
    if (srcFd == -1) {
        perror("Error opening source file");
        return;
    }

    struct stat srcStat;
    if (fstat(srcFd, &srcStat) == -1) {
        perror("Error getting source file stats");
        close(srcFd);
        return;
    }

    int dstFd = open(dstPath, O_WRONLY | O_CREAT | O_TRUNC, srcStat.st_mode);
    if (dstFd == -1) {
        perror("Error opening destination file");
        close(srcFd);
        return;
    }

    char buffer[4096];
    ssize_t bytesRead;

    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
        if (write(dstFd, buffer, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            break;
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from source file");
    }

    close(srcFd);
    close(dstFd);
}

int main() {
    copyFileWithLowLevelIO("source.txt", "destination.txt");    // 请确保替换"source.txt"和"destination.txt"为你需要复制的源文件路径和目标文件路径。
    std::cout << "File copied successfully!" << std::endl;
    return 0;
}