#ifndef LZMADECOMPRESS_H_
#define LZMADECOMPRESS_H_

#include <qdebug.h>

#include <../../../Moc/Logger/MocIOStream.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <errno.h>
#include <lzma.h>

static bool init_decoder(lzma_stream* strm);

static bool decompress(lzma_stream* strm, const char* inname, FILE* infile, FILE* outfile);

int lzmaDecomress(const std::string& file, const std::string& out_file);

#endif // !LZMADECOMPRESS_H_