#ifndef ECE_OTHELLO_PUN_HPP
#define ECE_OTHELLO_PUN_HPP

//enumeration qui permet de savoir si une case est blanche noire ou vide !
struct Pun {
	enum Colors {
		blank = 0,
		black = 1,
		white = 2
	};

	static inline Colors opposite( Colors color ) {
		return (Colors) ( (int) Colors::white - (int) color + (int) Colors::black );
	}
};


#endif //ECE_OTHELLO_PUN_HPP
