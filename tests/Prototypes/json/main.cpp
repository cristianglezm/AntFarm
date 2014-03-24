#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h>
#include <rapidjson/filestream.h>
#include <string>
#include <iostream>
#include <ios>
int main(){
// Prepare reader and input stream.
	rapidjson::Reader reader;
	FILE* file = fopen("menu.json","ra");
	std::iostream input("menu.json",std::ios::in | std::ios::app);
	rapidjson::FileStream is(input);

	// Prepare writer and output stream.
	rapidjson::FileStream os(stdout);
	rapidjson::PrettyWriter<rapidjson::FileStream> writer(os);

	// JSON reader parse from the input stream and let writer generate the output.
	if (!reader.Parse<1>(is,writer)) {
		fprintf(stderr, "\nError(%u): %s\n", (unsigned)reader.GetErrorOffset(), reader.GetParseError());
	}

    return 0;
}
