#ifndef PDF_PROCESSOR_H
#define PDF_PROCESSOR_H

#include <string>

void merge_pdfs(const std::string &output_file);
void compress_pdf(const std::string &input_file, const std::string &output_file);
void reorder_pdfs(const std::string &order_file);

#endif
