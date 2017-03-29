#pragma once
#ifndef __YUKI_DIRECTORY_H__
#define __YUKI_DIRECTORY_H__

#include <io.h>
#include <stdlib.h>
#include <direct.h>
#include <string>
#include <vector>
#include "log.h"

namespace Yuki {
	const int YUKI_MAX_PATH = 2048;
	
	class Directory {
    private:
		Directory() {}
		~Directory() {}
		
		static std::string current_path() {
			char path[YUKI_MAX_PATH];
			_getcwd(path, YUKI_MAX_PATH);
			return unix_style(path);
		}

        //static void dfs_find_files(bool recursive);

    public:
        // true: directory exits; false: no such directory
        //static bool set_directory(string path = ".");
        // return the abs path of the file with certain parten
        //static std::vector<std::string> find_files(string pattern = "*.*", bool recursive = false);

		// unix_style
		static std::string unix_style(std::string path) {
			std::string ret;
			Range(i, path.length()) {
				if (path[i] == '\\') {
					// "\\" and "\" turn into "/"
					if (i == 0 ||
						(i > 0 && path[i - 1] != '\\')) {
						ret += '/';
					}
				}
				else {
					ret += path[i];
				}
			}
			if (*(ret.end() - 1) != '/') ret += '/';
			return ret;
		}
		// exists
		static bool exists(std::string path) { return _access(path.c_str(), 0) != -1; }
        // mkdir
		static bool mkdir(std::string path) { return _mkdir(path.c_str()) != -1; }
		// mkdirs
		static bool mkdirs(std::string path) {
			bool ret = true;
			path = unix_style(path);
			Range(i, path.length()) {
				if (path[i] == '/') {
					if (i > 0 && path[i - 1] == ':') continue; // skip such as D:/
					std::string sub_str = path.substr(0, i);
					if (exists(sub_str)) continue; // skip if exists
					ret &= mkdir(sub_str);
				}
			}
			return ret;
		}
        // get dir
		static std::string getcwd() { return current_path(); }
        // delete
        //static bool delete_file(string path);
    };
}

#endif  // !__YUKI_DIRECTORY_H__