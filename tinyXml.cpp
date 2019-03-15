#include <iostream>
#include <fstream>
#include <string>
//#include "tinyxml2.cpp"
#include "tinyxml2.h"
#include <map>
#include <fstream>
#include <vector>

using namespace std;
using namespace tinyxml2;

bool attend(const string &s, map<string, int> &m)
{
    return m.count(s) != 0;
}

int main() {

    //vector<string>& stops = buses_to_stops[bus];
    XMLDocument doc;
    string path;
    cin >> path;
    doc.LoadFile(path.c_str());


    map<string, int> infoArrayTypes;
    map<string, int> frameArrayTypes;

    //count types in ClassInfoArray
    XMLElement *xml_storage = nullptr;
    xml_storage = doc.FirstChildElement("opencv_storage");
    XMLElement *xml_info_array = nullptr;
    xml_info_array = xml_storage->FirstChildElement("ClassInfoArray");
    XMLElement *xml_ = nullptr;
    xml_ = xml_info_array->FirstChildElement("_");

    while (xml_ != NULL) {
        XMLElement *xml_type = nullptr;
        xml_type = xml_->FirstChildElement("type");
        string txt;
        txt = xml_type->GetText();
        if (attend(txt, infoArrayTypes)) {
            infoArrayTypes[txt] += 1;
        } else {
            infoArrayTypes.insert(pair<string, int>(txt, 1));
        }
        xml_ = xml_->NextSiblingElement("_");
    }

    //сount types in FrameDataArray
    xml_storage = nullptr;
    xml_storage = doc.FirstChildElement("opencv_storage");
    XMLElement *xml_frame_array = nullptr;
    xml_frame_array = xml_storage->FirstChildElement("FrameDataArray");
    xml_ = nullptr;
    xml_ = xml_frame_array->FirstChildElement("_");

    while (xml_) {
        XMLElement *xml_frame_objects = nullptr;
        xml_frame_objects = xml_->FirstChildElement("FrameObjects");
        XMLElement *xml__ = nullptr;
        xml__ = xml_frame_objects->FirstChildElement("_");

        while (xml__) {
            XMLElement *xml_type = nullptr;
            xml_type = xml__->FirstChildElement("type");
            string txt;
            txt = xml_type->GetText();
            if (attend(txt, frameArrayTypes)) {
                frameArrayTypes[txt] += 1;
            } else {
                frameArrayTypes.insert(pair<string, int>(txt, 1));
            }
            xml__ = xml__->NextSiblingElement("_");
        }

        xml_=xml_->NextSiblingElement("_");
    }

    cout << "ClassInfoArray: " << endl << endl;
    for(auto &i : infoArrayTypes) {
        cout << i.first << " : " << i.second << endl;
    }
    cout << endl << endl << "FrameDataArray: " << endl << endl;
    for(auto &i : frameArrayTypes) {
        cout << i.first << " : " << i.second << endl;
    }
    return 0;
}
