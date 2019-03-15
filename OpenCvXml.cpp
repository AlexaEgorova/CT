#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

using namespace cv;
using namespace std;


int main() {
	string filename;
	while (getline(cin, filename) && !filename.empty()) {
		FileStorage fs(filename, FileStorage::READ);
		FileNode node = fs["FrameDataArray"];
		string txt;
		map<string, int> typesCount;

		for (auto it : node) {
			FileNode subNode = it["FrameObjects"];
			for (auto subIt : subNode) {
				txt = (string)subIt["type"];
				typesCount[txt] += 1;
			}
		}

		for (auto &i : typesCount) {
			cout << i.first << " : " << i.second << endl;
		}
	}
	return 0;
}

