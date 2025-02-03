#include "pdf_processor.h"
#include <iostream>

void merge_pdfs(const std::string &output_file) {
    std::cout << "Merging PDFs into " << output_file << std::endl;
}

void compress_pdf(const std::string &input_file, const std::string &output_file) {
    std::cout << "Compressing " << input_file << " to " << output_file << std::endl;
}

void reorder_pdfs(const std::string &order_file) {
    std::cout << "Reordering PDFs based on " << order_file << std::endl;
}
