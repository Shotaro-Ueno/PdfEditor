#include "pdf_processor.h"
#include <iostream>
#include <vector>
#include <sstream>
void merge_pdfs(const std::string &output_file,const std::vector<std::string> &input_files) {
    
    std::ostringstream command;
    command << "qpdf --empty --pages";

    for (const auto &file : input_files) {
        command << " " << file;
    }

    command << " -- " << output_file;

    std::cout << "Executing: " << command.str() << std::endl;
    system(command.str().c_str());
}

void compress_pdf(const std::string &input_file, const std::string &output_file) {
   
    std::ostringstream command;
    command << "qpdf --stream-data=compress \"" << input_file << "\" \"" << output_file << "\"";

    std::cout << "Executing: " << command.str() << std::endl;
    int result = system(command.str().c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to compress PDF" << std::endl;
    }
}

void reorder_pdfs(const std::string &input_file, const std::string &output_file, const std::vector<int> &page_order) {
    
    if (page_order.empty()) {
        std::cerr << "Error: Page order is empty!" << std::endl;
        return;
    }

    std::ostringstream command;
    command << "qpdf --empty --pages \"" << input_file << "\"";
    
    for (int page : page_order) {
        command << " " << page;
    }

    command << " -- \"" << output_file << "\"";

    std::cout << "Executing: " << command.str() << std::endl;
    int result = system(command.str().c_str());
    if (result != 0) {
        std::cerr << "Error: Failed to reorder PDF pages" << std::endl;
    }
}
