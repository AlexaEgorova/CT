#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <sys\stat.h>

#include <portability\file_system.hpp>
#include <portability\file_system.cpp>

#include <opencv2/core/utility.hpp>

using namespace cv;
using namespace std;

void findFileTypes(string filename, map<string, int>& typesCount) {
	FileStorage fs(filename, FileStorage::READ);
	FileNode node = fs["FrameDataArray"];
	string txt;
	//map<string, int> typesCount;
	for (auto it : node) {
		FileNode subNode = it["FrameObjects"];
		for (auto subIt : subNode) {
			txt = (string)subIt["type"];
			if (typesCount.count(txt) != 0) {
				typesCount[txt] += 1;
			}
		}
	}
}

void readConfig(string path, string& keys, int&linesNumber) {
	string str;
	ifstream config;
	linesNumber = 0;
	config.open(path);
	while (getline(config, str)) {
		keys += str;
		linesNumber += 1;
	}
	config.close();
}

void findFolderTypes(string path, map<string, int> typesCount) {
	vector<String> paths;
	glob(path + "/*markup.xml", paths, true);
	for (auto &filename : paths) {
		cout << filename << endl;
		findFileTypes(filename, typesCount);
	}
}

int exists(const string& name) {
	struct stat s;
	return (stat(name.c_str(), &s));
}

int main(int argс, char* argv[]) {
	if (argс == 1) {
		cerr << "No path specified" << endl;
		return -1;
	}
	string path;
	path = argv[1];
	if (exists(path) == -1) {
		cerr << "No such file or directory: " << path << endl;
		return -1;
	}
	if ((stlplus::extension_part(path) != "txt")) {
		cerr << "Not a txt file: " << path << endl;
		return -1;
	}
	string keys = "";
	int linesNumber = 0;
	char* parsArgv;
	readConfig(path, keys, linesNumber);

	CommandLineParser parser(linesNumber, argv, keys);
	string xpath = parser.get<string>("path");
	string types = parser.get<string>("types");

	cout << xpath << endl;

	if (xpath.length() == 0) {
		cerr << "No path specfied" << endl;
		return -1;
	}
	if (exists(xpath) == -1) {
		cerr << "No such file or directory: " << xpath << endl;
		return -1;
	}
	map<string, int> typesCount;
	stringstream ss(types);
	while (ss.good()) {
		string str;
		getline(ss, str, ',');
		typesCount[str] = 0;
	}
	if (exists(xpath) == 1) {
		findFolderTypes(xpath, typesCount);
	} else {
		if (stlplus::extension_part(xpath) == "xml") {
			findFileTypes(xpath, typesCount);
		} else cerr << "Not a xml file: " << xpath << endl;
	}
	for (auto &i : typesCount) {
		cout << i.first << " : " << i.second << endl;
	}

	return 0;
}
