#pragma once

#include <unistd.h> // readlink
#include <libgen.h> // dirname
#include <cstdlib> // basename
#include <cstring> // strdup

inline bool file_exists(string filename) {
	ifstream fin;

	fin.open(filename.c_str());
	if (fin.fail())
		return false;
	fin.close();

	return true;
}

inline bool str_from_file(string file_name, string &rtn_string)
{
	ifstream file;
	bool rtn_val = false;

	file.open(file_name.c_str());
	if (file.is_open()) {
		getline(file, rtn_string);
		file.close();
		rtn_val = true;
	}

	return rtn_val;
}

// https://www.securecoding.cert.org/confluence/display/seccode/POS30-C.+Use+the+readlink%28%29+function+properly
// http://linux.die.net/man/3/basename
inline string exe_path()
{
	enum {BUFFERSIZE = 2048};
	char buf[BUFFERSIZE];
	ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf)-1);
	if (len != -1) {
		buf[len] = '\0';

		char *path = buf;
		char *tmp = strdup(path);
		char *dname = dirname(tmp);
		//char *bname = basename(basec);
		//dirc = strdup(path);
		//basec = strdup(path);
		//dname = dirname(dirc);

		string rtn(dname);

		free(tmp);

		return rtn;
	} else {
		/* handle error condition */
		cout << "Could not readlink() of executable, exiting." << endl;
		exit(EXIT_FAILURE);
	}

	return "";
}
