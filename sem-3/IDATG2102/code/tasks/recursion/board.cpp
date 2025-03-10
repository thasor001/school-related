#include <iostream>
#include <vector>
#include <algorithm>

const int gSize = 10;

bool gArray[gSize][gSize];

std::vector <std::pair<std::pair<int, int>, int>> nodes;
int gGroups, counter;


void build_array() {
	for (int i = 0; i < gSize; i++)
		for (int j = 0; j < gSize; j++)
			gArray[i][j] = false;

	// Hard code where the nodes are on the board.
	gArray[0][9] = true;
	gArray[1][3] = true;
	gArray[1][4] = true;
	gArray[1][9] = true;
	gArray[3][4] = true;
	gArray[3][7] = true;
	gArray[4][3] = true;
	gArray[4][7] = true;
	gArray[5][7] = true;
	gArray[5][8] = true;
	gArray[6][4] = true;
	gArray[6][5] = true;
	gArray[7][1] = true;
	gArray[7][2] = true;
	gArray[8][1] = true;
	gArray[8][2] = true;
	gArray[8][8] = true;
	gArray[9][7] = true;
	gArray[9][8] = true;

}

void display() {
	for (int i = 0; i < gSize; i++) {
		std::cout << '\n';
		for (int j = 0; j < gSize; j++) {
			if (gArray[i][j]) {
				std::cout << "\u25CF" << ' ';
			} else
				std::cout << "\u25A1" << ' ';
		}
	}
	std::cout << '\n';
	for (const auto & pair : nodes) {
		std::cout << "X, Y : " << pair.first.second << " " <<
		pair.first.first <<"  Group : " << pair.second << std::endl;
	}

	std::cout << "\n\n" << "Nodes size : " << nodes.size() <<
	'\n' << "Number of Groups : " << gGroups << std::endl;
}

// gArray[y][x]

// Nodes are in the same group if they are touching eachother or touching
// a different node that is touching another one, NB! "does not include diagonal nodes".
void traverse_x(const int y, const int x) {
	if (x < gSize) {
		if (gArray[y][x]) {
			int nr = (gArray[y][x-1]) ? nodes.back().second : ++gGroups;

			nodes.push_back({{y, x}, nr});
			counter++;
		}
		traverse_x(y, x + 1);
	}
}


void main_rec(const int y) {
        if (y < gSize) {
			counter = 0;
        	traverse_x(y, 0);

			for (int i = nodes.size() - counter; i < nodes.size(); i++) {
				if (gArray[y-1][nodes[i].first.second]) {
					auto it = std::find_if(nodes.begin(), nodes.end(), [y, i](const auto& pair)
					{ return (pair.first.first == y-1 && pair.first.second == nodes[i].first.second); });

					for (auto& pair : nodes)
						if (pair.second == nodes[i].second) { pair.second = it->second; }
					gGroups--;
				}
			}
        main_rec(y + 1);
	}
}

int main(int argc, char *argv[]) {
	build_array();
	main_rec(0);
	display();

	return 0;
}
