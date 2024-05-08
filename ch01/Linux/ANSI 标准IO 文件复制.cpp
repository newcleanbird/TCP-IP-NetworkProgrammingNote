#include <cstdio>
#include <iostream>

void copyFileWithStdIO(const char* srcPath, const char* dstPath) {
    FILE* srcFile = fopen(srcPath, "rb");
    if (srcFile == nullptr) {
        perror("Error opening source file");
        return;
    }

    FILE* dstFile = fopen(dstPath, "wb");
    if (dstFile == nullptr) {
        perror("Error opening destination file");
        fclose(srcFile);
        return;
    }

    char buffer[4096];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, sizeof(buffer), srcFile)) > 0) {
        if (fwrite(buffer, 1, bytesRead, dstFile) != bytesRead) {
            perror("Error writing to destination file");
            break;
        }
    }

    if (ferror(srcFile)) {
        perror("Error reading from source file");
    }

    fclose(srcFile);
    fclose(dstFile);
}

int main() {
    copyFileWithStdIO("source.txt", "destination.txt");// 请确保替换"source.txt"和"destination.txt"为你需要复制的源文件路径和目标文件路径
    std::cout << "File copied successfully!" << std::endl;
    return 0;
}