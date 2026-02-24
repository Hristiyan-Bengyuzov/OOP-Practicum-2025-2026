#include <iostream>
#include <vector>
#include <algorithm>

enum class Major {
	SE,
	IS,
	CS,
	AM,
	M,
	INF
};

struct Student {
	double grade;
	std::string facultyNum, name;
	Major major;

	void print(std::ostream& os = std::cout) const {
		os << name << " ("
			<< facultyNum << ") - "
			<< grade << std::endl;
	}
};

struct Group {
	std::vector<Student> students;

	double getAverageGrade() const {
		double sum = 0;
		for (const Student& student : students) {
			sum += student.grade;
		}

		return sum / students.size();
	}

	std::vector<Student> getStudentsWithScholarship(double minGrade) const {
		std::vector<Student> res;
		for (const Student& student : students) {
			if (student.grade >= minGrade)
			{
				res.push_back(student);
			}
		}

		return res;
	}

	void addStudent(const Student& student) {
		students.push_back(student);
	}

	// the more optimal way is to sort by faculty number and do binary search
	bool existsStudent(const std::string& facultyNum) const {
		for (const Student& student : students) {
			if (student.facultyNum == facultyNum)
			{
				return true;
			}
		}

		return false;
	}
};

int main() {
	Group group;

	int n;
	std::cout << "Enter number of students: ";
	std::cin >> n;

	for (int i = 0; i < n; i++) {
		Student s;

		std::cout << "Student " << i + 1 << ":" << std::endl;

		std::cout << "Name: ";
		std::cin >> s.name;

		std::cout << "Faculty number: ";
		std::cin >> s.facultyNum;

		std::cout << "Grade: ";
		std::cin >> s.grade;

		int majorInput;
		std::cout << "Major (0=SE, 1=IS, 2=CS, 3=AM, 4=M, 5=INF): ";
		std::cin >> majorInput;
		s.major = (Major)majorInput;

		group.addStudent(s);
	}

	std::cout << "Average grade: " << group.getAverageGrade() << std::endl;

	double minScholarship;
	std::cout << "Enter minimum grade for scholarship: ";
	std::cin >> minScholarship;

	std::vector<Student> scholars = group.getStudentsWithScholarship(minScholarship);

	std::cout << "Students receiving scholarship:" << std::endl;

	for (const Student& s : scholars) {
		s.print();
	}

	std::string searchFN;
	std::cout << "Enter faculty number to search: ";
	std::cin >> searchFN;

	if (group.existsStudent(searchFN))
	{
		std::cout << "Student exists in the group." << std::endl;
	}
	else
	{
		std::cout << "Student not found." << std::endl;
	}
}
