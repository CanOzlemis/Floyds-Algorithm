#include <iostream>
#include <vector>


void display(std::vector < std::vector<int> > v, std::vector < std::vector<int> > z) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v[i].size(); j++) { //Printing the row of the d table
			if (v[i][j] == 99999999) // This checks for 'infinity'
				std::cout << "-" << "\t";  // place a - for infinity on the output
			else
				std::cout << v[i][j] << "\t";
		}
		std::cout << "\t||\t";  // Seperating in between
		for (int j = 0; j < z[i].size(); j++) { //Printing the row of the b table
			std::cout << z[i][j] << "\t";
		}
		std::cout << "\n";
	}
}

int min(int x, int y) {  //finding the mininum number
	if (x < y)
		return x;
	return y;
}


void floyd(int node, std::vector < std::vector <int> > conn) {
	std::vector< std::vector<int> > d0(node, std::vector<int>(node)), 
									d1(node, std::vector<int>(node)), 
									b0(node, std::vector<int>(node)), 
									b1(node, std::vector<int>(node));
	
	for (int i = 0; i < node; i++) {  //Initializer for both D table and B table
		for (int j = 0; j < node; j++) {
			if (i != j)
				d0[i][j] = conn[i][j]; // Setting up the D table
			else
				d0[i][j] = 99999999;  // This will be counted as infinity
			b0[i][j] = j + 1;  // Setting up the B table
		}
	}


	for (int r = 0; r < node; r++) { //NODE STEPS


		std::cout << "\t D" << r << " TABLE:\t\t\t\t\t B" << r << " TABLE:\n";
		display(d0, b0);


		for (int i = 0; i < node; i++) { // I COUNTER
			for (int j = 0; j < node; j++) { // J COUNTER

				if (d0[i][j] <= d0[i][r] + d0[r][j])  // SETTING THE B1
					b1[i][j] = b0[i][j];
				else
					b1[i][j] = b0[i][r]; // SETTING THE B1


				if (r == i || r == j) { // IGNORING THE SAME ROW AND COLUMNS AS i and j
					d1[i][j] = d0[i][j];
					continue; // Skipping to the next iteration
				}
				d1[i][j] = min(d0[i][j], d0[i][r] + d0[r][j]);  //Applying the formula
				
			}
		}
		std::cout << "\n\n\n";
		d0 = d1; // Changing the order of the table
		b0 = b1; // Changing the order of the table
	}

	int target, start, i = 0;



	while (true) {  //Getting the start and target node
		
		std::cout << "\n\n\tFIND SHORTEST PATH\n\n";
		std::cout << "Starting node : ";
		std::cin >> start;
		std::cout << "Target node : ";
		std::cin >> target;
		if (start < 1 || start > node || target < 1 || target > node) {  // If the node is out of boundries
			std::cout << "\tWRONG INPUT. TRY AGAIN\n";
			continue;
		}
		break;
	}

	std::cout << start << " ------ ";
	while (true) {
		if (b0[i][target - 1] == target) {
			std::cout <<  b0[i][target - 1];
			std::cout << "\n\tCOMPLETED\n\n";
			break;
		}
		std::cout  << b0[i][target - 1] << " ------ ";
		i = b0[i][target - 1] - 1;
	}
	
	
}

int main()
{
	int nodes, cost;

	std::cout << "How many nodes = ";
	nodes = 4;
	std::cin >> nodes;
	std::vector< std::vector <int> >  conn(nodes, std::vector<int> (nodes));


	
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < nodes; j++) {
			if (i != j) {
				std::cout << "Node " << i + 1 << " to " << j + 1 << " cost (-1 for infinity)= ";
				std::cin >> cost;
				if(cost == -1)
					cost = 99999999;
				conn[i][j] = cost;
			}else{
				cost = 99999999;
				conn[i][j] = cost;
			}
		}
	}
	floyd(nodes, conn);
    
}

