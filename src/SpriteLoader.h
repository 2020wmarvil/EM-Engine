#pragma once

#include "SpriteData.h"

class SpriteLoader {
private:
    void TokenizeStringFloat(const std::string& str, int start, int stop, std::vector<float>& data) {
        std::string delimiter = ",";
        
        std::string s = str.substr(start, stop);
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            data.push_back(std::stof(token));
            s.erase(0, pos + delimiter.length());
        } data.push_back(std::stof(s));
    }
    void TokenizeStringUint(const std::string& str, int start, int stop, std::vector<unsigned int>& data) {
        std::string delimiter = ",";
        
        std::string s = str.substr(start, stop);
        size_t pos = 0;
        std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            data.push_back(std::stoul(token));
            s.erase(0, pos + delimiter.length());
        } data.push_back(std::stoul(s));
    }
public:
    SpriteLoader() {}
    ~SpriteLoader() {}

    SpriteData LoadSprite(const std::string& filepath) {
        std::vector<float> vertices;
        std::vector<unsigned int> indices;

        std::string str = "", line;
	    std::ifstream stream(filepath);
	    while (getline(stream, line)) {
            str += line;
	    }

        TokenizeStringFloat(str, str.find("vertices {")+10, str.find("}indices {")-(str.find("vertices {")+10), vertices);
        TokenizeStringUint(str, str.find("indices {")+9, str.find("};")-(str.find("indices {")+9), indices);

        SpriteData data(vertices, indices);

        return data;
    }
};