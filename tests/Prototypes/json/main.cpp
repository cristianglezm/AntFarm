/*
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/reader.h>
#include <rapidjson/filestream.h>
*/
/// includes from json-cpp
#include <json/json.h>
#include <string>
#include <fstream>
int main(){
    std::ifstream input;
    input.open("menu.json",std::ios::in);

    /*
    /// test with json-cpp
    Json::Reader reader;
    Json::Value root(Json::ValueType::objectValue);
    reader.parse(input,root);
    */

    /*
    // Prepare reader and input stream.
	rapidjson::Reader reader;
	FILE* file = fopen("menu.json","ra");
	rapidjson::FileStream is(file);

	// Prepare writer and output stream.
	rapidjson::FileStream os(stdout);
	rapidjson::PrettyWriter<rapidjson::FileStream> writer(os);

	// JSON reader parse from the input stream and let writer generate the output.
	if (!reader.Parse<1>(is,writer)) {
		fprintf(stderr, "\nError(%u): %s\n", (unsigned)reader.GetErrorOffset(), reader.GetParseError());
	}
    */
    return 0;
}
