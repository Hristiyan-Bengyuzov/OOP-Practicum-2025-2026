class StreamWrap {
private:
	std::string folder;

	std::string buildPath(const std::string& file) {
		return folder + "/" + file;
	}

public:
	StreamWrap(const std::string& folder) : folder(folder) {}

	void write(const std::string& file, const std::string& str) {
		std::ofstream ofs(buildPath(file));

		if (!ofs.is_open())
		{
			return;
		}

		std::println(ofs, "{}", str);
	}

	std::string read(const std::string& file) {
		std::ifstream ifs(buildPath(file));

		if (!ifs.is_open())
		{
			return "";
		}

		std::string line;
		std::getline(ifs, line);
		return line;
	}
};
