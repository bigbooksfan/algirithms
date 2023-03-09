#include <fstream>
#include <cmath>
#include <string>

struct Coords {
	int x;
	int y;
};

int GetLayer(const int n) {
	int i = 0;
	do {
		++i;
	} while (std::pow((i * 2 + 1), 2) <= n);
	return i;
}

Coords compute(const int n) {
	if (n == 0) {
		//Coords a{ 0, 0 };
		return { 0, 0 };
	}

	const int layer = GetLayer(n);

	// how much steps to remove
	int rem = std::pow(((layer - 1) * 2 + 1), 2);
	
	// current step in local coords
	int curr = n - rem;

	// layer over solid square
	int l2 = 0;
	for ( ; ; ) {
		if (curr < (layer * 2)) {
			break;
		}
		else {
			curr -= (layer * 2);
			++l2;
		}
	}

	// local coords
	int xe = 0, ye = 0;
	if (l2 == 0) {
		xe = 0;
		ye = (-1) * curr - 1;
	}
	if (l2 == 1) {
		xe = curr + 1;
		ye = (-1) * layer * 2;
	}
	if (l2 == 2) {
		xe = layer * 2;
		ye = curr - layer * 2 + 1;
	}
	if (l2 == 3) {
		xe = 2 * layer - curr - 1;
		ye = 0;
	}

	// absolute coords
	int x = 0, y = 0;
	x = xe - layer;
	y = ye + layer;

	Coords a{ x, y };
	return a;
}

int main() {
	// read
	std::ifstream f_in;
	f_in.open("input.txt");
	std::string line;
	std::getline(f_in, line);
	f_in.close();
	int n_read = std::stoi(line);

	// compute
	Coords a = compute(n_read);

	// write answer
	line = std::to_string(a.x) + " " + std::to_string(a.y);
	std::ofstream f_out;
	f_out.open("output.txt");
	f_out << line;
	f_out.close();
	return 0;
}
