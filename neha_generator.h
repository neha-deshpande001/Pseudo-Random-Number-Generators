// File: neha_generator.h


class neha_generator {
public:
	// CONSTRUCTOR
				// default parameter - seed = 1
	neha_generator(int seed = 1);

	// ACCESSORS
	int random_number();
	int get_seed() const;

	// MODIFIERS
	void set_seed(int seed);

	// OTHER
	int numDigits(int num) const;

private: // REPRESENTATION (member variables)
	int seed;
	int current;
};
