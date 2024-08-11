#include <iostream>
#include <random>
#include <vector>

int eval(std::vector<int>& vec, int score);
std::vector<std::vector<int>> get_data(int gens, int size);
void print_matrix(std::vector<std::vector<int>>& matrix, int size);
int abs(int num);
int fac(int num);
int select(const std::vector<double>& weights);
std::vector<double> get_weights(std::vector<std::vector<int>>& vec, int sc);
std::vector<std::vector<int>> fitness(std::vector<std::vector<int>>& vec, std::vector<double>& weights);
void mutate(std::vector<std::vector<int>>& vec);
void cross(std::vector<std::vector<int>>& vec);

int main() {
	int size = 8;
	int score = fac(size) / (2 * fac(size - 2));
	while (true) {
		std::vector<std::vector<int>> vec = get_data(100, size);
		for (int i = 0; i < 1000; i++) {
            std::vector<double> weights = get_weights(vec, score);
            vec = fitness(vec, weights);
            cross(vec);
            mutate(vec);
		}
	}
}

void mutate(std::vector<std::vector<int>>& vec) {
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = vec[0].size()-1;
	std::uniform_int_distribution<> distribution(min, max);
	for (int i = 0; i < vec.size(); i++) {
		vec[i][distribution(gen)] = distribution(gen);
	}
}

void cross(std::vector<std::vector<int>>& vec) {
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = vec[0].size();
	std::uniform_int_distribution<> distribution(min, max);
	int idx = 0;
	std::vector<int> tmp;
	
	for (int i = 0; i < vec.size(); i += 2) {
		idx = distribution(gen);
		for (int j = 0; j < idx; j++) {
			tmp.push_back(vec[i][j]);
		}
		for (int j = 0; j < idx; j++) {
			vec[i][j] = vec[i+1][j];
			vec[i+1][j] = tmp[j];
		}
	}
}

std::vector<double> get_weights(std::vector<std::vector<int>>& vec, int sc) {
	std::vector<double> weights;
	double score = 0;
	double sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		score = eval(vec[i], sc); 
		if (score == -1) {
			for (int j = 0; j < vec[i].size(); j++) {
				std::cout << vec[i][j] << ' ';
			}
			std::cout << std::endl;
			exit(0);
		}
		weights.push_back(score);
		sum += score;
	}

	double mul = 100 / sum;
	for (int i = 0; i < weights.size(); i++) {
		weights[i] = (weights[i] * mul) / 100.0;
	}
	return weights;
}

std::vector<std::vector<int>> fitness(std::vector<std::vector<int>>& vec, std::vector<double>& weights) {
	std::vector<std::vector<int>> ans;
	for (int i = 0; i < vec.size(); i++) {
		ans.push_back(vec[select(weights)]);
	}
	return ans;
}

int select(const std::vector<double>& weights) {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    std::uniform_real_distribution<> dis(0.0, std::accumulate(weights.begin(), weights.end(), 0.0));

    double randomValue = dis(gen);
    double sum = 0.0;

    for (std::size_t i = 0; i < weights.size(); i++) {
        sum += weights[i];
        if (randomValue < sum) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

void print_matrix(std::vector<std::vector<int> >& matrix, int size) {
	int sc = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < size; j++) {
			std::cout << matrix[i][j] << ' ';
		}
		std::cout  << "score: " << eval(matrix[i], sc) << std::endl;
	}
}

std::vector<std::vector<int>> get_data(int gens, int size) {
	std::vector<std::vector<int>> ans;
	std::random_device rd;
	std::mt19937 gen(rd());
	int min = 0;
	int max = size-1;
	std::uniform_int_distribution<> distribution(min, max);
	for (int i = 0; i < gens; i++) {
		std::vector<int> tmp;
		for (int j = 0; j < size; j++) {  
			tmp.push_back(distribution(gen));
		}
		ans.push_back(tmp);
	}
	return ans; 
}

int eval(std::vector<int>& vec, int score) {
	int tmp = score;
	bool flag = 1;
	bool flag_diag = 1;
	bool flag_diag2 = 1;
	for (int i = 0; i < vec.size()-1; i++) {
		flag = 1;
		flag_diag = 1;
		flag_diag2 = 1;
		for (int j = i+1; j < vec.size(); j++) {
			if (vec[i] == vec[j] && flag) {
				score--;
				flag = 0;
			}
			if ((vec[i] - i == vec[j] - j) && flag_diag) {
				score--;
				flag_diag = 0;
			}
			if ((vec[i] + i == vec[j] + j) && flag_diag2) {
				score--;
				flag_diag2 = 0;
			}
		}
	}
	if (tmp == score) {
		return -1;
	}
	return score;
}

int abs(int num) {
	if (num < 0) {
		return -num;
	}
	return num;
}

int fac(int num) {
	int ans = 1;
	for (int i = 2; i <= num; i++) {
		ans *= i;
	}
	return ans;
}
		
