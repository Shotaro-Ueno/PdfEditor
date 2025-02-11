#ifndef PDF_PROCESSOR_H
#define PDF_PROCESSOR_H
#include <vector>
#include <string>

void merge_pdfs(const std::string &output_file, const std::vector<std::string> &input_files);
void compress_pdf(const std::string &input_file, const std::string &output_file);
void reorder_pdfs(const std::string &input_file, const std::string &output_file, const std::vector<int> &page_order);

#endif
