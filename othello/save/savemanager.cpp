#include "../inc/save/savemanager.hpp"

using namespace std;
using namespace Othello;
using namespace Othello::Board;
using namespace Othello::Save;
using namespace Othello::Players;

const std::string SaveManager::savePath = "save";

Othello::Save::Save SaveManager::load() {
	Othello::Save::Save save;
	std::ifstream saveFile( savePath, ios::in );
	unsigned char values = 0;

	try {
		if( saveFile.is_open() ) {
			string line, key, value;

			// On parcours chaque ligne. Une ligne = une variable de configuration.
			while( getline( saveFile, line ) ) {
				stringstream liness( line );

				// Récupération première partie de la ligne, la clé
				if( getline( liness, key, ':' ) ) {
					// Si on est sur la bonne clé (tableau)
					if( key == "board" ) {
						// On récupère la valeur et on la passe à la fonction qui la gère
						if( getline( liness, value ) ) {
							values++;
							if( !loadBoard( save, value ) )
								throw exceptions::invalid_save(); // Si le chargement a échoué, on quitte.
						} else {
							// On a pas de valeur, on quitte: la ligne est invalide, la sauvegarde st corrompue.
							throw exceptions::invalid_save();
						}
					} else if( key == "emptyNeighbors" ) {
						// On récupère la valeur et on la passe à la fonction qui la gère
						if( getline( liness, value ) ) {
							values++;
							if( !loadEmptyNeighbors( save, value ) )
								throw exceptions::invalid_save(); // Si le chargement a échoué, on quitte.
						} else {
							// On a pas de valeur, on quitte: la ligne est invalide, la sauvegarde st corrompue.
							throw exceptions::invalid_save();
						}
					} else if( key == "punCounts" ) {
						// On récupère la valeur et on la passe à la fonction qui la gère
						if( getline( liness, value ) ) {
							values++;
							if( !loadPunCounts( save, value ) )
								throw exceptions::invalid_save(); // Si le chargement a échoué, on quitte.
						} else {
							// On a pas de valeur, on quitte: la ligne est invalide, la sauvegarde st corrompue.
							throw exceptions::invalid_save();
						}
					} else if( key == "players" ) {
						// On récupère la valeur et on la passe à la fonction qui la gère
						if( getline( liness, value ) ) {
							values++;
							if( !loadPlayers( save, value ) )
								throw exceptions::invalid_save(); // Si le chargement a échoué, on quitte.
						} else {
							// On a pas de valeur, on quitte: la ligne est invalide, la sauvegarde st corrompue.
							throw exceptions::invalid_save();
						}
					}
				}
			}

			saveFile.close();

			// Si on a correctement chargé nos quatres éléments, la sauvegarde est valide: on continue.
			if( values == 4 )
				return save;
		}

		// Rien ne s'est passé comme il faut, on quitte
		throw exceptions::invalid_save();
	} catch( exceptions::invalid_save e ) {
		// Si la sauvegharde est invalide, on supprime le ficheir de sauvegarde et on informe le reste.
		remove();
		throw;
	}
}

bool SaveManager::loadBoard( Save& save, std::string value ) {
	int pieceInt;
	stringstream valuess( value );

	for( unsigned int i = 0; i < Board::sizeEdge; i++ ) {
		for( unsigned int j = 0; j < Board::sizeEdge; j++ ) {
			if( valuess >> pieceInt ) {
				if( Pun::check( pieceInt ) ) { // On teste si la valuer récupérée est correct
					save.board[ i ][ j ] = static_cast<Pun::Colors>( pieceInt ); //On l'ajoute
				}
			} else {
				return false; // Sinon on quitte (sauvegarde invalide)
			}
		}
	}

	return true;
}

bool SaveManager::loadEmptyNeighbors( Save& save, std::string value ) {
	std::istringstream valuess( value );

	// On tente d'extraire la valeur des voisins vides
	if( valuess >> save.emptyNeighbors )
		return true;
	return false;
}

bool SaveManager::loadPunCounts( Save& save, std::string value ) {
	std::istringstream valuess( value );

	// On tente d'extraire les valeurs des nombres de pions, noir puis blanc.
	if( !( valuess >> save.count.black ) )
		return false;
	if( !( valuess >> save.count.white ) )
		return false;
	return true;
}

Player* SaveManager::init( Player::Type type, string name, Pun::Colors color ) {
	switch( type ) {
		case Player::Type::Human:
			return new Human( name, color );
		case Player::Type::RandomAI:
			return new RandomAI( name, color );
		case Player::Type::SimpleAI:
			return new SimpleAI( name, color );
		case Player::Type::EnhancedAI:
			return new EnhancedAI( name, color );
	}

	return nullptr;
}

bool SaveManager::loadPlayers( Save& save, std::string value ) {
	std::istringstream valuess( value );
	string playerStr, currentStr, colorStr, typeStr, name;
	int colorInt, typeInt;
	bool current;
	unsigned char i = 0;

	while( getline( valuess, playerStr, ';' ) ) {
		istringstream playerss, currentss, colorss, typess;

		playerss.str( playerStr );

		if( !getline( playerss, currentStr, ',' ) )
			return false;

		if( !getline( playerss, typeStr, ',' ) )
			return false;

		if( !getline( playerss, colorStr, ',' ) )
			return false;

		if( !getline( playerss, name, ',' ) )
			return false;

		currentss.str( currentStr );
		if( !( currentss >> current ) )
			return false;

		colorss.str( colorStr );
		if( !( colorss >> colorInt ) )
			return false;

		if( !Pun::check( colorInt ) )
			return false;

		typess.str( typeStr );
		if( !( typess >> typeInt ) )
			return false;

		if( !Player::typeCheck( typeInt ) )
			return false;

		save.players.push_back( init( static_cast<Player::Type>( typeInt ), name, static_cast<Pun::Colors>( colorInt ) ) );

		if( current )
			save.currentPlayer = i;
		i++;
	}

	return true;
}

void SaveManager::save( Othello::Board::GameBoard* board, std::vector<Othello::Players::Player*>& players, vector<Player*>::iterator& current ) {
	ofstream saveFile;
	saveFile.open( savePath, ios::in | ios::trunc );

	if( saveFile.is_open() ) {
		if( !dumpBoard( board, saveFile ) )
			throw exceptions::invalid_save();
		if( !dumpEmptyNeighbors( board, saveFile ) )
			throw exceptions::invalid_save();
		if( !dumpPunCounts( board, saveFile ) )
			throw exceptions::invalid_save();
		if( !dumpPlayers( players, current, saveFile ) )
			throw exceptions::invalid_save();
		return;
	}

	throw exceptions::invalid_save();
}

bool SaveManager::dumpBoard( Othello::Board::GameBoard* ref, std::ostream& saveFile ) {
	const Board::punArray board = ref->getBoard();

	saveFile << "board:";

	for( unsigned int i = 0; i < Board::sizeEdge; i++ ) {
		for( unsigned int j = 0; j < Board::sizeEdge; j++ ) {
			if( !( saveFile << static_cast<int>( board[ i ][ j ] ) ) )
				return false; // Si on n'a pas réussi à mettre la valeur dans le fichier, on quitte.
			if( !( saveFile << " " ) )
				return false; // Si on n'a pas réussi à mettre la valeur dans le fichier, on quitte.
		}
	}

	saveFile << endl;

	return true;
}

bool SaveManager::dumpEmptyNeighbors( Othello::Board::GameBoard* ref, std::ostream& saveFile ) {
	saveFile << "emptyNeighbors:";

	if( !( saveFile << ref->getEmptyNeighbors() ) )
		return false;

	saveFile << endl;

	return true;
}

bool SaveManager::dumpPunCounts( Othello::Board::GameBoard* ref, std::ostream& saveFile ) {
	saveFile << "punCounts:";

	if( !( saveFile << ref->punCount( Pun::black ) ) )
		return false;

	saveFile << " ";

	if( !( saveFile << ref->punCount( Pun::white ) ) )
		return false;

	saveFile << endl;

	return true;
}

bool SaveManager::dumpPlayers( vector<Player*>& ref, vector<Player*>::iterator& current, std::ostream& saveFile ) {
	saveFile << "players:";

	for( vector<Player*>::iterator iplayer = ref.begin(); iplayer != ref.end(); ) {
		saveFile << ( iplayer == current )
		         << ","
		         << static_cast<int>( (*iplayer)->getType() )
		         << ","
		         << static_cast<int>( (*iplayer)->getColor() )
		         << ","
		         << (*iplayer)->getName();

		if( ++iplayer != ref.end() )
			saveFile << ";";
	}

	saveFile << endl;

	return true;
}

bool SaveManager::check() {
	std::ifstream saveFile( savePath, ios::in );

	if( saveFile.is_open() ) {
		saveFile.close();

		return true;
	}

	return false;
}

bool SaveManager::remove() {
	return ( std::remove( savePath.c_str() ) != 0 );
}
